#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "qapplication.h"
#include "../webchannel.h"
#include "../qt_v8.h"

using namespace v8;

Persistent<Function> QApplicationWrap::constructor;

int QApplicationWrap::argc_ = 0;
char** QApplicationWrap::argv_ = NULL;

QApplicationWrap::QApplicationWrap() {
  q_ = new QApplication(argc_, argv_);

  Q_INIT_RESOURCE(qtnode);

  WebChannel::instance();
}

QApplicationWrap::~QApplicationWrap() {
  delete q_;
}

void QApplicationWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QApplication"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("processEvents"),
      FunctionTemplate::New(ProcessEvents)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("exec"),
      FunctionTemplate::New(Exec)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("webChannelUrl"),
      FunctionTemplate::New(WebChannelUrl)->GetFunction());

  constructor = Persistent<Function>::New(
      tpl->GetFunction());
  target->Set(String::NewSymbol("QApplication"), constructor);
}

Handle<Value> QApplicationWrap::New(const Arguments& args) {
  HandleScope scope;

  QApplicationWrap* w = new QApplicationWrap();
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QApplicationWrap::ProcessEvents(const Arguments& args) {
  HandleScope scope;

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->processEvents();

  return scope.Close(Undefined());
}

Handle<Value> QApplicationWrap::Exec(const Arguments& args) {
  HandleScope scope;

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->exec();

  return scope.Close(Undefined());
}

Handle<Value> QApplicationWrap::WebChannelUrl(const Arguments& args) {
  HandleScope scope;

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());

  return scope.Close(qt_v8::FromQString(WebChannel::instance()->url()));
}
