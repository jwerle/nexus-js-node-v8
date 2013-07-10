
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
create (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = v8::Object::New();
	return scope.Close(obj);
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "create", create);
}

NODE_MODULE(object, init);