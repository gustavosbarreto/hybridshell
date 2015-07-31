#ifndef QAPPLICATIONWRAP_H
#define QAPPLICATIONWRAP_H

#include <node.h>
#include <QApplication>

class WebChannel;

class QApplicationWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QApplication* GetWrapped() const { return q_; };

 private:
  QApplicationWrap();
  ~QApplicationWrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
  static v8::Handle<v8::Value> ProcessEvents(const v8::Arguments& args);
  static v8::Handle<v8::Value> Exec(const v8::Arguments& args);

  static v8::Handle<v8::Value> WebChannelUrl(const v8::Arguments& args);

  WebChannel *webChannel_;

  // Wrapped object
  QApplication* q_;
  static int argc_;
  static char** argv_;
};

#endif
