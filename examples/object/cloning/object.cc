
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
clone (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = args[0]->ToObject();
	return scope.Close(obj->Clone());
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "clone", clone);
}

NODE_MODULE(object, init);