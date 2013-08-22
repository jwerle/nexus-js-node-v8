
#include <node.h>

v8::Handle<v8::Value>
hello (const v8::Arguments &args) {
  v8::HandleScope scope;
  return scope.Close(v8::String::New("hello"));
      }

v8::Handle<v8::Value>
world (const v8::Arguments &args) {
  v8::HandleScope scope;
  return scope.Close(v8::String::New("world"));
}

v8::Handle<v8::Value>
greet (const v8::Arguments &args) {
  v8::HandleScope scope;
  return scope.Close(
      v8::String::Concat(
        v8::String::New("Hello "),
        args[0]->ToString()
      )
  );
}

void Init (v8::Handle<v8::Object> exports) {
  NODE_SET_METHOD(exports, "hello", hello);
  NODE_SET_METHOD(exports, "world", world);
  NODE_SET_METHOD(exports, "greet", greet);
}

NODE_MODULE(hello, Init);

