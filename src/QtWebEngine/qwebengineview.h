#ifndef QWEBENGINEVIEWWRAP_H
#define QWEBENGINEVIEWWRAP_H

#include <node.h>
#include <node_object_wrap.h>

#include <QWebEngineView>
#include <QUuid>

//
// QWebEngineViewWrap()
//
class QWebEngineViewWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QWebEngineView* GetWrapped() const { return q_; };

 private:
  QWebEngineViewWrap(const v8::FunctionCallbackInfo<v8::Value>& args);
  ~QWebEngineViewWrap();
  static v8::Persistent<v8::Function> constructor;
  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped methods
  static void Show(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Load(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Exec(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Uuid(const v8::FunctionCallbackInfo<v8::Value>& args);

  // Wrapped object
  QWebEngineView* q_;

  QUuid uuid_;
};

#endif
