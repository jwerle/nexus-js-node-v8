
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
getConstructor (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = args[0]->ToObject();
	return scope.Close(obj->GetConstructor());
}

v8::Handle<v8::Value>
getConstructorName (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = args[0]->ToObject();
	return scope.Close(obj->GetConstructorName());
}

void
init (v8::Handle<v8::Object> obj) {
	obj->Set(
		v8::String::New("getConstructor"), 
		v8::FunctionTemplate::New(getConstructor)->GetFunction()
	);

	obj->Set(
		v8::String::New("getConstructorName"), 
		v8::FunctionTemplate::New(getConstructorName)->GetFunction()
	);
}

NODE_MODULE(object, init);