#include "nodejsevaluator.h"

#include <node.h>

#include "qt_v8.h"

using namespace v8;

NodeJSEvaluator::NodeJSEvaluator(): QObject()
{

}

QVariant NodeJSEvaluator::eval(QString str)
{
    HandleScope scope;

    Local<Function> eval = Local<Function>::Cast( Context::GetCurrent()->Global()->Get(String::New("eval")) );
    Local<Value> arguments[1] = { qt_v8::FromQString(str) };
    Local<Value> result = eval->Call(Context::GetCurrent()->Global(), 1, arguments);

    return qt_v8::ValueToVariant(result);
}
