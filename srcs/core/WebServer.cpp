#include "WebServer.hpp"
#include "Config.hpp"

WebServer::WebServer(const std::string &path) : mGood(true) {
  Config::makeConfigTree(path);
  if (Common::mConfigTree == NULL) {
    mGood = false;
    return;
  }

  mServerList = Config::makeServerList(Common::mConfigTree);
  if (mServerList.empty()) {
    mGood = false;
    return;
  }

  Common::mKqueue = kqueue();
  if (Common::mKqueue == -1) {
    mGood = false;
    return;
  }
}

bool WebServer::IsGood(void) const { return (mGood); }

WebServer::~WebServer(void) {
  int safeExit = 1;

  if (Common::mKqueue != -1) {
    close(Common::mKqueue);
  } else {
    safeExit = 0;
  }

  if (!mServerList.empty()) {
    for (std::map<int, Server *>::iterator it = mServerList.begin();
         it != mServerList.end(); ++it) {
      delete it->second;
    }
    mServerList.clear();
  } else {
    safeExit = 0;
  }

  if (Common::mConfigTree) {
    delete (Common::mConfigTree);
  } else {
    safeExit = 0;
  }

  if (safeExit == 0) {
    exit(1);
  }
}

void WebServer::Run(void) {
  if (!IsGood()) {
    return;
  }
  eventMonitoring();
}

void WebServer::eventMonitoring(void) {
  while (true) {
    int newEvent = kevent(Common::mKqueue, NULL, 0, &mEventList[0],
                          mEventList.size(), NULL);

    if (newEvent < 0 && errno == EINTR) {
      return;
    }

    for (int index = 0; index < newEvent; index++) {
      struct kevent currentEvent = mEventList[index];
      eventHandler(currentEvent);
    }
  }
}

void WebServer::eventHandler(struct kevent &currentEvent) {
  if (currentEvent.flags & EV_ERROR) {
    // error
  }
  IEventHandler *object = static_cast<IEventHandler *>(currentEvent.udata);
  object->EventHandler(currentEvent);
}