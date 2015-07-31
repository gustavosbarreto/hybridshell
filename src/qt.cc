#define BUILDING_NODE_EXTENSION
#include <node.h>

#include "QtGui/qapplication.h"
#include "QtWebEngine/qwebengineview.h"

using namespace v8;

void Initialize(Handle<Object> target) {
  QApplicationWrap::Initialize(target);
  QWebEngineViewWrap::Initialize(target);
}

NODE_MODULE(qt, Initialize)
