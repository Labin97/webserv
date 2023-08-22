#include "Node.hpp"

/* Level Bit Flags */
#define NONE_LEVEL (1 << 0)
#define HTTP_LEVEL (1 << 1)
#define SERVER_LEVEL (1 << 2)
#define LOCATION_LEVEL (1 << 3)
#define CREATE_NODE (1 << 4)
#define DIRECTIVE (1 << 5)
#define OPEN_BRACKET (1 << 6)
#define CLOSE_BRACKET (1 << 7)
#define SEMICOLON (1 << 8)
#define ERROR (1 << 9)

/* context */
#define HTTP (NONE_LEVEL | CREATE_NODE)
#define SERVER (HTTP_LEVEL | CREATE_NODE)
#define LOCATION (SERVER_LEVEL | CREATE_NODE)
/* http server location */
#define ERROR_PAGE (HTTP_LEVEL | SERVER_LEVEL | LOCATION_LEVEL | DIRECTIVE)
#define CLIENT_MAX_BODY_SIZE                                                   \
  (HTTP_LEVEL | SERVER_LEVEL | LOCATION_LEVEL | DIRECTIVE)
#define AUTO_INDEX (HTTP_LEVEL | SERVER_LEVEL | LOCATION_LEVEL | DIRECTIVE)
#define INDEX (HTTP_LEVEL | SERVER_LEVEL | LOCATION_LEVEL | DIRECTIVE)
/* server */
#define LISTEN (SERVER_LEVEL | DIRECTIVE)
#define SERVER_NAME (SERVER_LEVEL | DIRECTIVE)
/* server location */
#define RETURN (SERVER_LEVEL | LOCATION_LEVEL | DIRECTIVE)
/* location */
#define ALIAS (LOCATION_LEVEL | DIRECTIVE)
#define LIMIT_EXCEPT (LOCATION_LEVEL | DIRECTIVE)
/* { } ; */

Node::Node(std::vector<std::string> &configTokens,
           std::vector<std::string>::iterator &token, Node *parent, int level)
    : mParent(parent) {
  int tokenInfo;

  for (; token != configTokens.end(); token++) {
    tokenInfo = getTokenInfo(*token);

    if ((tokenInfo & level) == 0 && tokenInfo != CLOSE_BRACKET) {
      printf("tokenInfo = %d\nlevel = %d\n", tokenInfo, level);
      sendError("Error: Invalid token level");
    }
    
    if (tokenInfo & CREATE_NODE) {
      if (tokenInfo == LOCATION) { /* location */
        tokenInfo = getTokenInfo(*(++token));
         
        /* Save location info */
      }

      tokenInfo = getTokenInfo(*(++token));
      if ((tokenInfo & OPEN_BRACKET) == 0) {
        sendError("Error: Bracket not opened\n");
      }

      Node *newNode = new Node(configTokens, ++token, this,
                               (level & LOCATION_LEVEL) ? level : level << 1);
      mChildren.push_back(newNode);
    } else if (tokenInfo & OPEN_BRACKET) {
      sendError("Error: Wrong bracket\n");
    } else if (tokenInfo & CLOSE_BRACKET) {
      if (level == NONE_LEVEL && (token != configTokens.end())) {
        sendError("Error: Wrong bracket\n");
      }
      return;
    } else {
      addDirective(configTokens, token);
    }
  }
}

Node::~Node(void) { deleteTree(); }

int Node::getTokenInfo(std::string token) {
  if (token == "{") {
    return (OPEN_BRACKET);
  } else if (token == "}") {
    return (CLOSE_BRACKET);
  } else if (token == ";") {
    return (SEMICOLON);
  } else if (token == "http") {
    return (HTTP);
  } else if (token == "server") {
    return (SERVER);
  } else if (token == "location") {
    return (LOCATION);
  } else if (token == "error_page") {
    return (ERROR_PAGE);
  } else if (token == "client_max_body_size") {
    return (CLIENT_MAX_BODY_SIZE);
  } else if (token == "autoindex") {
    return (AUTO_INDEX);
  } else if (token == "index") {
    return (INDEX);
  } else if (token == "listen") {
    return (LISTEN);
  } else if (token == "server_name") {
    return (SERVER_NAME);
  } else if (token == "return") {
    return (RETURN);
  } else if (token == "alias") {
    return (ALIAS);
  } else if (token == "limit_except") {
    return (LIMIT_EXCEPT);
  }
  return (ERROR);
}

void Node::addDirective(std::vector<std::string> &configTokens,
                        std::vector<std::string>::iterator &token) {
  std::string key = *token;

  if (mDirectives.find(key) != mDirectives.end()) {
    sendError("Error: Directive already exists\n");
  }
  std::vector<std::string> values;
  token++;
  for (; token != configTokens.end(); token++) {
    int tokenInfo = getTokenInfo(*token);
    if (tokenInfo & SEMICOLON) {
      break;
    }
    values.push_back(*token);
  }
  if (token == configTokens.end()) {
    sendError("Error: Syntax Error\n");
  }
  mDirectives[key] = values;
}

void Node::deleteTree(void) {
   for (std::vector<Node *>::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
    (*it)->deleteTree();
    delete (*it);
  }
  mChildren.clear();
}
 