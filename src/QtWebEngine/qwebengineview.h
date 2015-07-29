#ifndef QWEBENGINEVIEWWRAP_H
#define QWEBENGINEVIEWWRAP_H

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <QWebEngineView>

//
// QWebEngineViewWrap()
//
class QWebEngineViewWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QWebEngineView* GetWrapped() const { return q_; };

 private:
  QWebEngineViewWrap(const v8::Arguments& args);
  ~QWebEngineViewWrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
  static v8::Handle<v8::Value> Show(const v8::Arguments& args);
  static v8::Handle<v8::Value> Load(const v8::Arguments& args);

  // Wrapped object
  QWebEngineView* q_;
};

#endif
