
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
create (const v8::Arguments &args) {
	v8::HandleScope scope;
	bool value = args[0]->BooleanValue();
	char *str = *v8::String::Utf8Value(args[0]->ToString());
	printf("%s\n", str);
	v8::Local<v8::Value> b = v8::BooleanObject::New(value);
	//printf("%s\n", b->BooleanValue());
	return scope.Close(v8::Boolean::New(b->BooleanValue()));
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "create", create);
}

NODE_MODULE(boolean, init);