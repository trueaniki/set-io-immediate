#include <nan.h>

class NaNAsyncWorker : public Nan::AsyncWorker {
public:
  NaNAsyncWorker(Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {}
  ~NaNAsyncWorker() {}

  __attribute__((noinline)) void Execute () {
    return;
  }

  __attribute__((noinline)) void HandleOKCallback () {
    Nan::HandleScope scope;

    callback->Call(0, NULL);
  }
};

NAN_METHOD(NANAsyncWorker) {
  Nan::Callback *workerDone = new Nan::Callback(info[0].As<v8::Function>());
  Nan::Callback *workerStart = new Nan::Callback(info[1].As<v8::Function>());
  Nan::AsyncQueueWorker(new NaNAsyncWorker(workerDone));
  workerStart->Call(0, NULL);
}
