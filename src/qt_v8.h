#ifndef QTV8_H
#define QTV8_H

#include <node.h>

#include <QString>
#include <QVariant>

namespace qt_v8 {
using namespace v8;

inline QString ToQString(v8::Local<v8::String> str) {
  return QString::fromUtf16( *v8::String::Value(str) );
}

inline v8::Local<v8::String> FromQString(QString str) {
  return v8::String::New( str.utf16() );
}

inline QVariant ValueToVariant(Local<Value> &value) {
    QVariant ret;

    if (value->IsString()) {
        ret = ToQString(value.As<String>());
    } else if (value->IsNumber()) {
        ret = value.As<Number>()->Value();
    } else if (value->IsBoolean()) {
        ret = value->BooleanValue();
    } else if (value->IsNull()) {
        // by default ret is null
    } else if (value->IsObject()) {
        Local<Object> obj = value->ToObject();
        Local<Array> properties = obj->GetPropertyNames();

        QVariantMap map;

        for (uint32_t i = 0; i < properties->Length(); i++) {
            Local<Value> key = properties->Get(Number::New(i));
            Local<Value> val = obj->Get(key);

            map[ToQString(key.As<String>())] = ValueToVariant(val);
        }

        ret = map;
    } else if (value->IsArray()) {
        Local<Array> array = value.As<Array>();

        QVariantList list;

        for (uint32_t i = 0; i < array->Length(); i++) {
            Local<Value> val = array->Get(i);

            list.append(ValueToVariant(val));
        }

        ret = list;
    }

    return ret;
}

} // namespace

#endif
