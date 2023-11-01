#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "Common.hpp"
#include "Core.hpp"
#include "IRequestHandler.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <sys/stat.h>

class Http;
class Request;
class Router {
public:
  static IRequestHandler *Routing(Http &http);

private:
  Router();
  ~Router();
  Router(const Router &other);
  Router &operator=(const Router &other);
};

class GetHandler : public IRequestHandler {
public:
  virtual void Handle(int port, Http &http, int socket);

private:
  std::string autoIndex(const std::string &path);
};

class PostHandler : public IRequestHandler {
public:
  virtual void Handle(int port, Http &http, int socket);
};

class DeleteHandler : public IRequestHandler {
public:
  virtual void Handle(int port, Http &http, int socket);
};

class PutHandler : public IRequestHandler {
public:
  virtual void Handle(int port, Http &http, int socket);
};
#endif