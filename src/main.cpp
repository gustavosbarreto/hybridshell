#include <iojs/src/node.h>
#include <iojs/src/node_internals.h>
#include <iojs/src/env.h>
#include <iojs/src/env-inl.h>

#include <uv/include/uv.h>
#include <v8/include/v8.h>

#include <libplatform/libplatform.h>

#include <qt-event-dispatcher-libuv/src/eventdispatcherlibuv.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    auto dispatcher = new qtjs::EventDispatcherLibUv();

    QCoreApplication::setEventDispatcher(dispatcher);

    QApplication app(argc, argv);

    dispatcher->setFinalise();

    argv = uv_setup_args(argc, argv);

    int exec_argc = 0;
    const char **exec_argv = NULL;

    node::Init(&argc, const_cast<const char **>(argv), &exec_argc, &exec_argv);

    v8::Platform* platform = v8::platform::CreateDefaultPlatform(THREAD_POOL_SIZE);
    v8::V8::InitializePlatform(platform);
	v8::V8::Initialize();

    v8::Isolate* isolate = v8::Isolate::New();

    new v8::Locker(isolate);
    new v8::Isolate::Scope(isolate);

    {
        v8::HandleScope handle_scope(isolate);
        v8::Handle<v8::Context> context = v8::Context::New(isolate);

        node::Environment *env = node::CreateEnvironment(isolate, uv_default_loop(), context, argc, argv, exec_argc, exec_argv);

        new v8::Context::Scope(context);

        node::LoadEnvironment(env);

        QCoreApplication::exec();

        node::RunAtExit(env);
        env->context()->Global().Clear();
    }

    v8::V8::Dispose();

    return 0;
}

