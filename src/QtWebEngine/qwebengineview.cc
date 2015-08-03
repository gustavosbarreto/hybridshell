#include <node.h>
#include "qwebengineview.h"
#include "../webchannel.h"
#include "../nodejsevaluator.h"
#include "../qt_v8.h"

#include <QVariantList>

using namespace v8;

Persistent<Function> QWebEngineViewWrap::constructor;

//
// QWebEngineViewWrap()
//

QWebEngineViewWrap::QWebEngineViewWrap(const FunctionCallbackInfo<v8::Value>& args) {
  q_ = new QWebEngineView();
  uuid_ = QUuid::createUuid();
}

QWebEngineViewWrap::~QWebEngineViewWrap() {
  delete q_;
}

void QWebEngineViewWrap::Initialize(Handle<Object> target) {
  Isolate *isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "QWebEngineView"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Wrapped methods
  NODE_SET_PROTOTYPE_METHOD(tpl, "show", Show);
  NODE_SET_PROTOTYPE_METHOD(tpl, "load", Load);
  NODE_SET_PROTOTYPE_METHOD(tpl, "exec", Exec);
  NODE_SET_PROTOTYPE_METHOD(tpl, "uuid", Uuid);

  constructor.Reset(isolate, tpl->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "QWebEngineView"), tpl->GetFunction());
}

void QWebEngineViewWrap::New(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QWebEngineViewWrap* w = new QWebEngineViewWrap(args);
  w->Wrap(args.This());

  args.GetReturnValue().Set(args.This());
}

void QWebEngineViewWrap::Show(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  q->show();
}

void QWebEngineViewWrap::Load(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  if (args[0]->IsString()) {
    q->load(QUrl(QString(*v8::String::Utf8Value(args[0]->ToString()))));
  }
}

void QWebEngineViewWrap::Exec(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  if (args[0]->IsString()) {
      QVariant thisArgs;

      if (args.Length() > 1) {
          Local<Value> value = args[1];
          thisArgs = qt_v8::ValueToVariant(Isolate::GetCurrent(), value);
      }

      WebChannel::instance()->nodeJSEvaluator()->sendJavaScriptToBrowser(w->uuid_,
                                                                         QString(*v8::String::Utf8Value(args[0]->ToString())),
                                                                         thisArgs);
  }
}

void QWebEngineViewWrap::Uuid(const FunctionCallbackInfo<v8::Value>& args) {
  HandleScope scope(Isolate::GetCurrent());

  QWebEngineViewWrap* w = node::ObjectWrap::Unwrap<QWebEngineViewWrap>(args.This());
  QWebEngineView* q = w->GetWrapped();

  Local<Value> uuid = qt_v8::FromQString(Isolate::GetCurrent(), w->uuid_.toString());

  args.GetReturnValue().Set(uuid);
}
