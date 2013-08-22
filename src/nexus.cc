
#include <v8.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "nexus.h"

bool ExecuteString(v8::Isolate* isolate,
                   v8::Handle<v8::String> source,
                   v8::Handle<v8::Value> name,
                   bool print_result,
                   bool report_exceptions);

void ReportException(v8::Isolate* isolate, v8::TryCatch* handler);
v8::Handle<v8::String> ReadFile(const char* name);
v8::Handle<v8::Value> test (const v8::Arguments &args);

// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

v8::Handle<v8::Context> createContext (v8::Isolate *isolate) {
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	
	global->Set(v8::String::New("test"), v8::FunctionTemplate::New((v8::FunctionCallback) test));

	return v8::Context::New(isolate, NULL, global);
}

v8::Handle<v8::String> ReadFile(const char* name) {
  FILE* file = fopen(name, "rb");
  if (file == NULL) return v8::Handle<v8::String>();

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
    i += read;
  }
  fclose(file);
  v8::Handle<v8::String> result = v8::String::New(chars, size);
  delete[] chars;
  return result;
}

v8::Handle<v8::Value>
test (const v8::Arguments &args) {
	v8::HandleScope scope(args.GetIsolate());
	if (0 == args.Length()) {
		puts("nothing to print");
		return scope.Close(v8::False());
	} else {
		v8::String::Utf8Value str(args[0]);
		const char *cstr = ToCString(str);
		printf("%s\n", cstr);
	}

	return scope.Close(args[0]);
}


bool ExecuteString(v8::Isolate* isolate,
                   v8::Handle<v8::String> source,
                   v8::Handle<v8::Value> name,
                   bool print_result,
                   bool report_exceptions) {
  v8::HandleScope handle_scope(isolate);
  v8::TryCatch try_catch;
  v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
  if (script.IsEmpty()) {
    // Print errors that happened during compilation.
    if (report_exceptions)
      ReportException(isolate, &try_catch);
    return false;
  } else {
    v8::Handle<v8::Value> result = script->Run();
    if (result.IsEmpty()) {
      assert(try_catch.HasCaught());
      // Print errors that happened during execution.
      if (report_exceptions)
        ReportException(isolate, &try_catch);
      return false;
    } else {
      assert(!try_catch.HasCaught());
      if (print_result && !result->IsUndefined()) {
        // If all went well and the result wasn't undefined then print
        // the returned value.
        v8::String::Utf8Value str(result);
        const char* cstr = ToCString(str);
        printf("%s\n", cstr);
      }
      return true;
    }
  }
}

void ReportException(v8::Isolate* isolate, v8::TryCatch* try_catch) {
  v8::HandleScope handle_scope(isolate);
  v8::String::Utf8Value exception(try_catch->Exception());
  const char* exception_string = ToCString(exception);
  v8::Handle<v8::Message> message = try_catch->Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    fprintf(stderr, "%s\n", exception_string);
  } else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = ToCString(filename);
    int linenum = message->GetLineNumber();
    fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
    // Print line of source code.
    v8::String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = ToCString(sourceline);
    fprintf(stderr, "%s\n", sourceline_string);
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
      fprintf(stderr, " ");
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      fprintf(stderr, "^");
    }
    fprintf(stderr, "\n");
    v8::String::Utf8Value stack_trace(try_catch->StackTrace());
    if (stack_trace.length() > 0) {
      const char* stack_trace_string = ToCString(stack_trace);
      fprintf(stderr, "%s\n", stack_trace_string);
    }
  }
}





/// MAIN

int
main (int argc, char* argv[]) {
	const char *file = "./src/nexus.js";

	v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	{
		v8::HandleScope scope(isolate);
		v8::Handle<v8::Context> context = createContext(isolate);

		if (context.IsEmpty()) {
			fprintf(stderr, "error creating context\n");
			return 1;
		}

		context->Enter();

		{
			v8::Handle<v8::String> source = ReadFile(file);

      if (source.IsEmpty()) {
        fprintf(stderr, "Error reading '%s'\n", file);
        return 1;
      }

			ExecuteString(isolate, source, v8::String::New("nexus"), true, true);
		}

		context->Exit();
	}

	v8::V8::Dispose();

	return 0;
}