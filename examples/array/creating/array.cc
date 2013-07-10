
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
create (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Array> arr;

	if (args.Length() == 1 && args[0]->IsNumber()) {
		 arr = v8::Array::New(args[0]->NumberValue());
	} else {
		arr = v8::Array::New();
	}

	return scope.Close(arr);
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "create", create);
}

NODE_MODULE(array, init);