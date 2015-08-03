#include "nodejsevaluator.h"

#include <node.h>

#include "qt_v8.h"

#include <QDebug>

using namespace v8;

NodeJSEvaluator::NodeJSEvaluator(): QObject()
{

}

QVariant NodeJSEvaluator::eval(QString str)
{
    HandleScope scope(Isolate::GetCurrent());

    TryCatch trycatch;

    Local<Script> script = Script::Compile(qt_v8::FromQString(Isolate::GetCurrent(), str));
	if (script.IsEmpty()) {
        Local<Message> message = trycatch.Message();
        qDebug() << qt_v8::ToQString(message->Get());
	} else {
        Local<Value> result = script->Run();

        if (trycatch.HasCaught()) {
            Local<Message> message = trycatch.Message();
            qDebug() << qt_v8::ToQString(message->Get());
        } else {
            return qt_v8::ValueToVariant(Isolate::GetCurrent(), result);
        }
    }

    return QVariant();
}

void NodeJSEvaluator::sendJavaScriptToBrowser(const QUuid &uuid, QString str, const QVariant &thisArgs)
{
    emit evaluateJavaScript(uuid.toString(), str, thisArgs);
}
