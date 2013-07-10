
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
cloneAt (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Array> arr = args[0]->ToObject().As<v8::Array>();
	uint32_t index = args[1]->NumberValue();

	v8::Handle<v8::Value> val = arr->CloneElementAt(index);

	return scope.Close(val);
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "cloneAt", cloneAt);
}

NODE_MODULE(array, init);