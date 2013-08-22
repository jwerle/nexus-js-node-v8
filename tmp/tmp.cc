
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
myNativeFunction (const v8::Arguments &args) {
	v8::HandleScope scope;
	return scope.Close(v8::Undefined());
}

v8::Handle<v8::Value>
Date (const v8::Arguments &args) {
  v8::HandleScope scope;
  v8::Local<v8::Value> d = v8::Date::New(1224744689038.0);
  return scope.Close(d);
}

v8::Handle<v8::Value>
Function (const v8::Arguments &args) {
	v8::HandleScope scope;
  v8::Local<v8::FunctionTemplate> f_tpl = v8::FunctionTemplate::New(myNativeFunction);
  f_tpl->Set(v8::String::New("funcProperty"), v8::Number::New(123));
  v8::Local<v8::Function> fn = f_tpl->GetFunction();
  v8::Handle<v8::Value> a[] = {
		v8::String::New("a"),
		v8::String::New("b"),
		v8::String::New("c")
  };	
  
  return scope.Close(fn->Call(fn, 3, a));	
}


void
init (v8::Handle<v8::Object> exports) {
  NODE_SET_METHOD(exports, "date", Date);
  NODE_SET_METHOD(exports, "func", Function);
}

NODE_MODULE(tmp, init);
