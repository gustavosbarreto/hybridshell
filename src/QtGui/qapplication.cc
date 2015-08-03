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
  Isolate *isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "QApplication"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "processEvents", ProcessEvents);
  NODE_SET_PROTOTYPE_METHOD(tpl, "exec", Exec);
  NODE_SET_PROTOTYPE_METHOD(tpl, "webChannelUrl", WebChannelUrl);

  constructor.Reset(isolate, tpl->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "QApplication"), tpl->GetFunction());
}

void QApplicationWrap::New(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QApplicationWrap* w = new QApplicationWrap();
  w->Wrap(args.This());
}

void QApplicationWrap::ProcessEvents(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->processEvents();
}

void QApplicationWrap::Exec(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());
  QApplication* q = w->GetWrapped();

  q->exec();
}

void QApplicationWrap::WebChannelUrl(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QApplicationWrap* w = ObjectWrap::Unwrap<QApplicationWrap>(args.This());


  args.GetReturnValue().Set(qt_v8::FromQString(Isolate::GetCurrent(), WebChannel::instance()->url()));
}
