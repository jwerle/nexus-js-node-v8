
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>


v8::Handle<v8::Value>
cast (const v8::Arguments &args) {
	v8::HandleScope scope;

	if (args.Length() == 0 || args.Length() > 1) {
		v8::ThrowException(
			v8::Exception::Error(v8::String::New("wrong number of arguments"))
		);

		return scope.Close(v8::Undefined());
	}

	return scope.Close(args[0]->ToArray());
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "cast", cast);
}

NODE_MODULE(array, init);