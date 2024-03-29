#include <nan.h>
#include "nan_worker.h"
#include "uv_worker.h"

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("setIoImmediate").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(NANAsyncWorker)).ToLocalChecked());
  Nan::Set(target, Nan::New("setUvImmediate").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(UVASyncWorker)).ToLocalChecked());
}

NODE_MODULE(addon, Init)
