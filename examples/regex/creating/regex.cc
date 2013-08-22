
#include <node.h>
#include <v8.h>
#include <stdlib.h>
#include <string.h>

v8::Handle<v8::Value>
create (const v8::Arguments &args) {
	v8::HandleScope scope;
	v8::Local<v8::Array> arr;

	if (1 ==args.Length()) {
		if (args[0]->IsString()) {
		 v8::Local<v8::RegExp> regex = v8::RegExp::New(args[0]->ToString(), static_cast<v8::RegExp::Flags>(v8::RegExp::kNone));
		} else {
			v8::ThrowException(v8::Exception::TypeError(v8::String::New("expecting string")));
			return scope.Close(v8::Undefined());
		}
	} else if (2 == args.Length()) {
		if (!args[0]->IsString()) {
		 v8::ThrowException(v8::Exception::TypeError(v8::String::New("expecting string")));
		 return scope.Close(v8::Undefined());
		} else if (!args[1]->IsString()) {
		 v8::ThrowException(v8::Exception::TypeError(v8::String::New("expecting string")));
		 return scope.Close(v8::Undefined());
		}

		v8::String::Utf8Value str(args[1]->ToString());
		for (int i = 0; i < sizeof(*str); ++i) {
			
		}
		v8::Local<v8::RegExp> regex = v8::RegExp::New(args[0]->ToString(), static_cast<v8::RegExp::Flags>(v8::RegExp::kNone));
	}

	return scope.Close(regex);
}

void
init (v8::Handle<v8::Object> exports) {
	NODE_SET_METHOD(exports, "create", create);
}

NODE_MODULE(regex, init);