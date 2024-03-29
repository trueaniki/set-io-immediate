#include <nan.h>
#include <uv.h>

// This noinline attribute will not work with MSVC and clang
__attribute__((noinline)) void execute(uv_work_t* req) {
  auto a = 1;
  a++;
  return;
}

__attribute__((noinline)) void handleOKCallback(uv_work_t* req, int status) {
  Nan::HandleScope scope;

  Nan::Callback *callback = static_cast<Nan::Callback*>(req->data);
  callback->Call(0, NULL);
  return;
}

NAN_METHOD(UVASyncWorker) {
  Nan::Callback *workerDone = new Nan::Callback(info[0].As<v8::Function>());
  Nan::Callback *workerStart = new Nan::Callback(info[1].As<v8::Function>());

  uv_work_t* req = new uv_work_t;
  req->data = workerDone;
  uv_queue_work(uv_default_loop(), req, execute, handleOKCallback);
  workerStart->Call(0, NULL);
}
