#ifndef NODE_HPP
#define NODE_HPP

#include "Core.hpp"

class Node {
public:
  Node(std::vector<std::string> &configTokens,
       std::vector<std::string>::iterator &tokenLocation, Node *parent, int level);
  ~Node(void);
  void PrintTree(int level);
  
private:
  Node();
  int getTokenInfo(std::string token);
  void addDirective(std::vector<std::string> &configTokens,
       std::vector<std::string>::iterator &tokenLocation);
  void nodeError(const std::string &msg);
  void deleteTree(void);

public:
  std::map<std::string, std::vector<std::string> > mDirectives;
  std::vector<Node *> mChildren;
  int mLevel;

private:
  Node *mParent;
};



#endif