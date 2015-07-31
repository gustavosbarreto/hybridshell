#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "qwebengineview.h"
#include "../webchannel.h"
#include "../nodejsevaluator.h"
#include "../qt_v8.h"

#include <QDebug>

using namespace v8;

Persistent<Function> QWebEngineViewWrap::constructor;

//
// QWebEngineViewWrap()
//

QWebEngineViewWrap::QWebEngineViewWrap(const Arguments& args) {
  q_ = new QWebEngineView();
  uuid_ = QUuid::createUuid();
}

QWebEngineViewWrap::~QWebEngineViewWrap() {
  delete q_;
}

void QWebEngineViewWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QWebEngineView"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Wrapped methods
  tpl->PrototypeTemplate()->Set(String::NewSymbol("show"),
      FunctionTemplate::New(Show)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("load"),
      FunctionTemplate::New(Load)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("exec"),
      FunctionTemplate::New(Exec)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("uuid"),
      FunctionTemplate::New(Uuid)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QWebEngineView"), constructor);
}

Handle<Value> QWebEngineViewWrap::New(const Arguments& args) {
  HandleScope scope;

  QWebEngineViewWrap* w = new QWebEngineViewWrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QWebEngineViewWrap::Show(const Arguments& args) {
  HandleScope scope;

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  q->show();

  return scope.Close(Undefined());
}

Handle<Value> QWebEngineViewWrap::Load(const Arguments& args) {
  HandleScope scope;

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  if (args[0]->IsString()) {
    q->load(QUrl(QString(*v8::String::Utf8Value(args[0]->ToString()))));
  }

  return scope.Close(Undefined());
}

Handle<Value> QWebEngineViewWrap::Exec(const Arguments& args) {
  HandleScope scope;

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  if (args[0]->IsString()) {
      WebChannel::instance()->nodeJSEvaluator()->sendJavaScriptToBrowser(w->uuid_, QString(*v8::String::Utf8Value(args[0]->ToString())));
  }

  return scope.Close(Undefined());
}

Handle<Value> QWebEngineViewWrap::Uuid(const Arguments& args) {
  HandleScope scope;

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  Local<Value> uuid = qt_v8::FromQString(w->uuid_.toString());

  return scope.Close(uuid);
}
