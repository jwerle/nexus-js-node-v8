
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
getOwnPropertyNames (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = args[0]->ToObject();
	return scope.Close(obj->GetOwnPropertyNames());
}

v8::Handle<v8::Value>
getPropertyNames (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Object> obj = args[0]->ToObject();
	return scope.Close(obj->GetPropertyNames());
}

void
init (v8::Handle<v8::Object> obj) {
	v8::Local<v8::Object> prototype = v8::Object::New();
	prototype->Set(
		v8::String::New("property"),
		v8::String::New("value")
	);

	obj->SetPrototype(prototype);

	obj->Set(
		v8::String::New("foo"), 
		v8::String::New("bar")
	);

	obj->Set(
		v8::String::New("biz"), 
		v8::String::New("baz")
	);
	
	obj->Set(
		v8::String::New("getOwnPropertyNames"),
		v8::FunctionTemplate::New(getOwnPropertyNames)->GetFunction()
	);

	obj->Set(
		v8::String::New("getPropertyNames"),
		v8::FunctionTemplate::New(getPropertyNames)->GetFunction()
	);
}

NODE_MODULE(object, init);