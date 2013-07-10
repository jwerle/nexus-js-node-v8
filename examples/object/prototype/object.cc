
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

void
init (v8::Handle<v8::Object> obj) {
	v8::Local<v8::Object> prototype = v8::Object::New();
	prototype->Set(v8::String::New("property"), v8::String::New("value"));
	obj->SetPrototype(prototype);
	obj->Set(v8::String::New("proto"), obj->GetPrototype());
}

NODE_MODULE(object, init);