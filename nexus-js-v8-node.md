# The Nexus of JavaScript, v8 and Node.js

#### by Joseph Werle

# 1. Introduction 

## 1.2 What is JavaScript?

JavaScript, sometimes abbreviated ***JS*** is an interpreted computer programming language originally designed and implemented for web browsers. It was created so client side executable scripts written in the language could interact with the user viewing the web page. It is a dynamic, type safe, prototype based language that was influenced by the ***C*** and ***Java*** programming languages.

The language's birth can be traced back to the Netscape Foundation which first made its appearance in the Netscape browser in September of 1995. It was developed under the name ***Mocha*** by Brendan Eich, released under the name ***LiveScript***, and eventually renamed to ***JavaScript*** [1].

Since its creation the language has been used in multiple environments such as browsers, servers, and embedded systems. It is currently standardized by the ECMA International standards organization under the name ECMAScript. Other well known implementations of the standard include languages like JScript, the proprietary JavaScript implementation from Microsoft for Internet Explorer; and ActionScipt, an object-oriented language designed for scripting Flash applications originally developed by Macromedia, which is now owned by Adobe Systems.


### 1.2.1 CommonJS

In an effort to continue standardizing the way we write JavaScript a project known as CommonJS was born. The goal of the project is "specifying an ecosystem for JavaScript outside the browser" [2]. It currently aims for modularity, packaging, common interfaces and the uniformity of a baseline.

>"What I'm describing here is not a technical problem. It's a matter of people getting together and making a decision to step forward and start building up something bigger and cooler together." [3]

— Kevin Dangoo

---

[1] - http://web.archive.org/web/20070916144913/http://wp.netscape.com/newsref/pr/newsrelease67.html
[2] - http://wiki.commonjs.org/wiki/CommonJS
[3] - http://www.blueskyonmars.com/2009/01/29/what-server-side-javascript-needs/

## 1.3 What is v8?

The V8 JavaScript engine, sometimes referred to as just ***v8***, is an open source JavaScript engine developed and maintained by Google. It was created as the core JavaScript engine for their Chrome browser and is now used in a variety of projects including Node.js, the Chromium open source browser and the Chromium Embedded Framework (CEF). It is written in C++ and intended for a variety of operating systems. It was originally released with the first version of the Chrome Browser on September 2, 2008 [1].

***Figure 1.1 - A function written in v8 that returns the string "world"***

```c++
v8::Handle<v8::Value> helloWorld (const v8::Arguments &args) {
  v8::HandleScope scope;
  v8::Local<v8::String> hello = v8::String::New("world");
  return scope.Close(hello);
}
```

***Figure 1.2 - A function written in JavaScript that returns the string "world"***

```js
function helloWorld () {
  var hello = "world";
  return hello;
}
```

---

[1] - http://en.wikipedia.org/wiki/V8_(JavaScript_engine)

## 1.4 What is Node.js?

Node.js, sometimes referred to as just ***node***, is a server side system for writing highly scalable network applications. It is commonly used to construct web servers. It is an event-driven system running on a single thread which differs from most web servers which are primarily thread based. 

The Node.js runtime is built on top of the v8 JavaScript engine, the libuv platform abstraction layer and the node.js core library. It was created by Ryan Dahl in 2009 at Joyent, a software and services company based in San Fransisco, CA. It is currently maintained by Joyent and an active and passionate community of developers. It implements a handful of specifications defined by CommonJS such as Modules 1.0 [1].


***Figure 1.3 - An example of JavaScript written in a Node.js application***

```js
var fs = require('fs')
fs.readFile('/tmp/hello', function (err, data) {
  if (err) throw err;
  // do something with `data`
  console.log(data);
});
```

---

[1] - http://wiki.commonjs.org/wiki/Modules/1.0

## 1.5 How does it all fit together?

Though JavaScript is the core front-end language for browsers, it can be used anywhere a valid JavaScript engine is available such as Node.js with the v8 engine. Other engines include Rhino, a Java based JavaScript engine developed by Mozilla; SpiderMonkey, a C implementation of the Rhino engine; and JavaScriptCore, the JavaScript engine for WebKit implementations and OS X environments. 

Google's v8 compiles JavaScript to native machine code before executing it as opposed to interpreting or executing byte code. In environments like the browser JavaScript can be executed on the fly with a method known as just-in-time (JIT) compilation. The Node.js software with libuv sits on top of v8 as a compilation of interfaces to the machine. With a JavaScript front-end to the Node.js, libuv and v8 package one has access to a plethora of interfaces to the machine including file i/o, tcp and http.

The libuv platform abstraction layer provides a library for building scalable cross platform applications. It sits at the core of the Node.js application stack and is the best way to write C code that can run on BSD, Linux and Windows based systems [1]. Before the integration of libuv, libev, an asynchronous event notification library, and libeio, an asynchronous i/o library for C were used [2]. As the project grew - and a higher demand for Windows support amplified - a solution was needed to address the lack of libev's support for the Windows platform. [3] When node-v0.9.0 was released libev was removed from libuv entirely [4] and a similar API was provided. Following the project's continued growth many other languages implemented bindings such as Ruby, Go and Python [5].

So we have an elegant language like JavaScript, v8, a powerful JavaScript engine, and libuv, a cross platform abstraction layer all working together in a software stack we call Node.js. On top of the all this power is a set of modules known as the Node.js core library which is what we consume as application developers. 

### 1.5.1 Node.js Application stack

***Figure 1.4 - The Node.js application stack***

```
-------------------------------------
|                                   |
|      Your Node.js application     |
|                                   |
-------------------------------------
|                                   |
| Node.js Core Library (JavaScript) |
|                                   |
-------------------------------------
|                                   |
|       Node.js Bindings (C++)      |
|                                   |
-------------------------------------
|                                   |
|          Google V8 (C++)          |
|                                   |
-------------------------------------
|                                   |
|             libuv (C)             |
|                                   |
-------------------------------------
```

### 1.5.2 Example HTTP server

Using the core module `http`, much of the heavy lifting involved in writing a simple http server with Node.js becomes trivial.

***Figure 1.5 - An example of a simple http server written in JavaScript for a Node.js application***

```js
require('http').createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('Hello world!');
}).listen(8000, '127.0.0.1');

console.log("server running at http://127.0.0.1:8000")
```

Your Node.js application requires the `http` module and creates a server. The `createServer` function accepts a function as an argument which is executed on each request. If you are accustomed to asynchronous programming then this will seem familiar.

---

[1] - http://opensourcebridge.org/sessions/920
[2] - http://nikhilm.github.io/uvbook/introduction.html
[3] - http://nikhilm.github.io/uvbook/introduction.html#background
[4] - https://github.com/joyent/libuv/issues/485
[5] - https://github.com/joyent/libuv/wiki/Projects-that-use-libuv


# 2 Understanding the link between v8 and JavaScript

In this section we will review some of the basic links between data types, functions and the rest of the basic parts of JavaScript. We will understand how to create primitive data types in C++ and how to do the same in JavaScript. I make the assumption that you already have a basic understanding of JavaScript and Node.js.

## 2.x Isolates

In v8, isolates represent an isolated instance of a v8 engine bound to a process. Every v8 isolate has a completely unique state and objects from other isolates should not be mixed. During initialization v8 creates a default isolate and enters its scope. Other isolates may be created and used with each other in parallel running in separate threads. An isolate may only be entered by one thread at any given time during execution. [1]

***Figure 2.x - Creating a new Isolate in C++ with V8***

```c++
v8::Isolate *isolate = v8::Isolate::New();
```

***Figure 2.x - Getting the current isolate in C++ with V8***

```c++
v8::Isolate *isolate = v8::Isolate::GetCurrent();
```

---

[1] - http://izs.me/v8-docs/classv8_1_1Isolate.html

## 2.x Contexts

In v8, a context is an execution environment that allows separate, unrelated JavaScript to run in a single instance of v8 [1]. You must always declare the context in which you want any JavaScript to be executed. The need for contexts in v8 stems from the need for multiple global objects existing like iframes or new windows or tabs in a browser. After a context is created you may create another and choose to leave and enter it when you please [1].

***Figure 2.x - Declaring a new Context in C++ with V8***

```c++
v8::Persistent<v8::Context> context = v8::Context::New();
```

***Figure 2.x - Getting the current context in C++ with V8***

```c++
v8::Context context = v8::Context::GetCurrent();
```

During execution, when a context is declared it must also be entered. This can be achieved with the `v8::Context::Enter` method. Only one context may be entered at a time. Once a context is entered all JavaScript execution is bound to that context until otherwise explicitly exited with the `v8::Context::Exit` method.

***Figure 2.x - Entering a context in C++ with V8***

```c++
context->Enter(); {

}
```

***Figure 2.x - Exiting a context in C++ with V8***

```c++
context->Exit(); {

}
```

---

[1] - https://developers.google.com/v8/embed#contexts

## 2.x Scopes

Scopes in v8 are a way of organizing variables declared within a function. Typically, your scope is declared at the beginning of a function so all subsequent local variables are pushed to that scope stack. These variables will be removed by the garbage collector after the scope has been closed.

***Figure 2.x - Declaring a new scope in C++ with V8***

```c++
v8::HandleScope scope;
```

***Figure 2.x - Declaring a new scope bound to an isolate in C++ with V8***

```c++
v8::HandleScope scope(some_isolate);
```

At the end of a function a scope must be closed. You can close a scope by making a call to the `v8::HandleScope::Close` method which accepts a `v8::Handle<v8::Value>` argument which can be anything that inherits from `v8::Value` (functions, objects, primitives, etc). If you return the value from `v8::HandleScope::Close` and provide an argument of `v8::Handle<v8::Value>` then it will become the return value of the function.

***Figure 2.x - Closing a scope in C++ with V8***

```c++
scope.Close();
```

***Figure 2.x - Closing a scope with a return value in C++ with V8***

```c++
return scope.Close(v8::Undefined());
```

## 2.x Local and Persistent variables

In v8 you can declare a variable to be "local" or "persistent." If you suspect a local variable is local to the scope of a function then you are correct. Whenever a scope is declared with `v8::HandleScope` all subsequent `v8::Local<>` variables belong to that scope and will be garbage collected (deleted) when the scope is closed. If a variable is declared as persistent then it will exist until otherwise explicitly deleted.

***Figure 2.x - Declaring a local variable in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
```

***Figure 2.x - Declaring a persistent variable in C++ with V8***

```c++
v8::Persistent<v8::Object> global = v8::Object::New();
```

## 2.x Class hierarchy

In JavaScript we've come to know the prototypal chain of inheritance and the way it can work to our advantage. Similarly to JavaScript, almost all v8 primitives inherit from `Object` except values inherited from something known as `v8::Data`. The `v8::Data` class acts as the superclass for all values and API object templates in v8. It is superseded by a few classes such as `v8::Signature`, `v8::Template`, `v8::TypeSwitch`, and `v8::Value`.

The `v8::Signature` class is responsible for specifying receivers and arguments with which a function may be called. You will generally *not* have to work with this class.

The `v8::Template` class is a superclass for function and object templates such as `v8::FunctionTemplate` or `v8::ObjectTemplate`. You will often end up working with child classes of `v8::Template`.

The `v8::Value` class is a superclass for all JavaScript values and objects. It is the parent class of `v8::Object` and `v8::Primitive`.

***Figure 2.x - V8 class hierarchy***

```
v8::Data
  -> v8::Signature
  -> v8::Template
    -> v8::FunctionTemplate
    -> v8::ObjectTemplate
  -> v8::TypeSwitch
  -> v8::Value
    -> v8::Object
      -> v8::Array
      -> v8::BooleanObject
      -> v8::Date
      -> v8::Function
      -> v8::NumberObject
      -> v8::RegExp
      -> v8::StringObject
    -> v8::Primitive
      -> v8::Boolean
      -> v8::String
      -> v8::Number
        -> v8::Int32
        -> v8::Uint32
```

This class hierarchy should seem very familiar to those already accustomed to the JavaScript prototype chain.

## 2.x Primitive Data types

If you've ever opened up a browser console and interactively played around with JavaScript then you're already familiar with the built-in primitive data types. Things like `Number` and `Boolean` quickly accumulate as you start adding logic to a function. Declaring them is as easy as defining a variable with a left hand assignment much like `var num = 4;` or `var bool = false;`. But, how exactly can these primitives be declared in C++? Declaring a primitive in C++ is less trivial.


***Figure 2.x - Declaring a number in C++ with V8***

```c++
v8::Local<v8::Number> num = v8::Number::New(4);
```

***Figure 2.x - Declaring a boolean in C++ with V8***

```c++
v8::Local<v8::Boolean> bool = v8::Boolean::New(true);
```

***Figure 2.x - Declaring a string in C++ with V8***

```c++
v8::Local<v8::String> str = v8::String::New("hello world");
```

***Figure 2.x - Declaring a null value in C++ with V8***

```c++
v8::Local<v8::Null> null = v8::Null();
```

***Figure 2.x - Declaring an undefined value in C++ with V8***

```c++
v8::Local<v8::Undefined> undefined = v8::Undefined();
```

All primitives, or anything that extends `v8::Primitive`, are also child classes of `v8::Value`

## 2.x Objects

According to ECMA-262 section 4.2.1 *Objects* are not created in ways similar to C++, Java or SmallTalk, but rather though literal notation or via *constructors* that execute an initialization function in the scope of a new object.

***Figure 2.x - Creating a literal object in JavaScript***

```js
var obj = {};
console.log(obj); // {}
```

***Figure 2.x - Creating an object with the Object constructor in JavaScript***

```js
var obj = new Object();
console.log(obj); // {}
```

***Figure 2.x - Creating an object via a constructor***

```js
function MyObject() {}
var obj = new MyObject();
console.log(obj); // {}
```

### 2.x Using Objects

In v8 we can do a lot of the same things we can do in JavaScript with objects like creating, setting properties, cloning, reading prototypes and more.

#### 2.x Creating Objects

Creating an object in v8 is a little more complicated but the same results as above can be accomplished. For this section we will focus on create literal objects from the `v8::Object` class. To create an object in v8 we need to execute the static method `New()` on the `v8::Object` class.

***Figure 2.x - Creating a new object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
```

#### 2.x Setting properties

In JavaScript we can set properties on objects using dot or bracket notation. We can do the same in v8 with the `v8::Object::Set` method on an object instance.

***Figure 2.x - Setting a property on an object in JavaScript***

```js
obj.foo = 'bar';
// or
obj['foo'] = 'bar';
```

***Figure 2.x - Setting a property on an object in C++ with V8***

```c++
obj->Set(v8::String::New("foo"), v8::String::New("bar"));
```

Note that we must create a new `v8::String` instance with the `v8::String::New` static method which accepts a `char *` or a C-style string as an argument.

#### 2.x Cloning

In v8 we can make shallow copies of objects using the `v8::Object::Clone` method found on an instance of `v8::Object`. All objects in the copy will point to original references.

***Figure 2.x - Cloning an object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
v8::Local<v8::Object> clone = obj->Clone();
```

#### 2.x Getting the prototype of an object

In JavaScript we have become accustomed to using `__proto__` for getting the prototype of an object. You can do the same in v8 with the `GetPrototype()` method on a `v8::Object` instance.

***Figure 2.x - Getting the prototype of an object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
v8::Local<v8::Object> proto = obj->GetPrototype();
```

#### 2.x Setting the prototype of an object

In JavaScript we set the prototype of an object via its constructor, but in v8 we use the `SetPrototype` method on a `v8::Object` instance.

***Figure 2.x - Setting the prototype of an object in C++ with V8***

```c++
v8::Local<v8::Object> prototype = v8::Object::New();
prototype->Set(v8::String::New("property"), v8::String::New("value"));
v8::Local<v8::Object> obj = v8::Object::New();
obj->SetPrototype(prototype);
```

#### 2.x Getting own property name

In JavaScript we can retrieve an array of own property names for an object using `Object.getOwnPropertyNames()`, excluding properties up the prototype chain. In v8 we can do the same on a `v8::Object` instance with the `v8::Object::GetOwnPropertyNames` method.

***Figure 2.x - Getting own property names of an object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->Set(v8::String::New("foo"), v8::String::New("bar"));
obj->Set(v8::String::New("biz"), v8::String::New("baz"));
v8::Local<v8::Array> names = obj->GetOwnPropertyNames(); // foo, biz
```

#### 2.x Getting property names included in the prototype

In JavaScript we normally cannot look at all the property names of an object and its prototype chain, however, in v8 we can with the `v8::Object::GetPropertyNames` method on a `v8::Object`

***Figure 2.x - Getting property names of an object in C++ with V8***

```c++
v8::Local<v8::Array> names = obj->GetPropertyNames();
```

#### 2.x Getting the constructor of an object instance

In JavaScript we can obtain the constructor of an object instance by simply referring to the `constructor` property of that object. In v8 we need to make a call to the `v8::Object::GetConstructor` method on a `v8::Object` instance.

***Figure 2.x - Getting the constructor of an object instance in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
v8::Local<v8::Function> cons = obj->GetConstructor();
```

You can also retrieve the name of a constructor with the `v8::Object::GetConstructorName` method on a `v8::Object` instance.

***Figure 2.x - Getting the name of a constructor of an object instance in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
v8::Local<v8::String> name = obj->GetConstructorName();
```

### 2.x Arrays

In JavaScript we work with arrays for all sorts of reasons. We can manage sets of data, queues, stacks, etc. We can push, pop, shift, unshift and do all manner of sorting and filtering on the indexed set of data. In v8 we are not privileged to perform these tasks in a simple manner like in JavaScript, but we can make it work.

#### 2.x Creating an array

Creating an array in v8 is as simple as creating any other object. We utilize the `v8::Array::New(int length = 0)` static method on the `v8::Array` class which accepts an optional `int` value which determines the length of the initialized array.

***Figure 2.x - Creating an array with no length in C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New();
```

***Figure 2.x - Creating an array with a length of 5 in C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New(5);
```

#### 2.x Adding elements to an array

Adding elements to an array in JavaScript is simplified by methods such as `.push()` and `.unshift()`. We can also directly access an index of an array in JavaScript and set its value. In v8 a `v8::Array` instance doesn't have methods that provide these conveniences, but since it does inherit from `v8::Object` we can set properties on it much like an object.

***Figure 2.x - Adding an element to an array C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New();
array->Set(v8::Number::New(0), v8::String::New("foo"));
```

#### 2.x Element cloning

In v8 we are provided with a method called `CloneElementAt(uint32_t index)` on a `v8::Array` instance that allows us to clone an element at a specified index.

***Figure 2.x - Cloning an element at a specified index in C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New();
v8::Local<v8::Object> array[0] = v8::Object::New();
array[0]->Set(
  v8::String::New("name"), v8::String:New("werle")
);

v8::Local<v8::Objects> object = array->CloneElementAt(0);
```

### 2.x Date

Date objects in v8 are constructed similarly to Date objects in JavaScript. The `v8::Date::New` static method accepts a `double`, which is a valid timestamp, as an argument.

```c++ 
v8::Local<v8::Value> date = v8::Date::New(1224744689038.0);
```

With the `v8::Date` instance we can retrieve the actual number value much like `v8::Value::NumberValue`.

```c++
printf("%d\n", date.As<v8::Date>()->NumberValue());
```

## 2.x Functions

With v8 we have the power to bind JavaScript functions to functions defined in v8 through a class known as `v8::FunctionTemplate`. The `v8::FunctionTemplate` class acts as a wrapper around the actual routine. It also contains a reference to its prototype.

In order to correctly bind a function we need to create a function template.

```c++
v8::Local<v8::FunctionTemplate> f_tpl = v8::FunctionTemplate::New();
```

`v8::FunctionTemplate` instances represent the actual function in JavaScript and just like in JavaScript a function is also an object. We can set properties or "static" members on a function just like we would set a property on a `v8::Object` instance.

```c++
f_tpl->Set(v8::String::New("funcProperty"), v8::Number::New(123));
```

Our `v8::FunctionTemplate` instance is created but it lacks a call handler or a `v8::FunctionCallback`. A call handler or `v8::FunctionCallback` is a function defined in v8 or in C++ that is called when the function is invoked in JavaScript. We can set the `v8::FunctionCallback` as an argument to `v8::FunctionTemplate::New(callback)` or with the `v8::FunctionTemplate::SetCallHandler` method.

```c++
// as argument to constructor
v8::Local<v8::FunctionTemplate> fn_tpl = v8::FunctionTemplate::New(myNativeFunction);

// on instance with SetCallHandler
f_tpl->SetCallHandler(myNativeFunction);
```

After we have set up our `v8::FunctionTemplate` correctly we can get the actual representation of the function created which is wrapped by a class known as `v8::Function`. The `v8::Function` class extends the `v8::Object` class and therefore just like in JavaScript it is also an object. With this class we can call the actual function, set and get the function name and use it as a constructor which will be covered in the next section.

We can get an instance of the `v8::Function` contained within the `v8::FunctionTemplate` instance by calling the `v8::FunctionTemplate::GetFunction()` method.

```c++
v8::Local<v8::Function> fn = f_tpl->GetFunction();
```

After retrieving the function we can call it with the `v8::Function::Call` method much like with the `Function.prototype.call` method in JavaScript. It accepts a receiver, an argument count, and an array of arguments.

***Figure 2.x - Calling a function with v8::Function::Call C++ with V8***

```c++
v8::Handle<v8::Value> args[] = { v8::Number::New(0), v8::Number::New(1) };
v8::Handle<v8::Value> ret = fn->Call(fn, 2, args);
```

This is equivalent to calling a function in JavaScript like this:

```js
var ret = fn.call(fn, 0, 1);
// or 
var ret = fn(0, 1);
```

## 2.x Constructors

Much like in JavaScript, functions in v8 are also constructors by nature. A function can be invoked to create a new instance. This is achieved with the `v8::Function::NewInstance` method which accepts an `int` as its first argument which is the length of the arguments array and an array of arguments as the second argument. This is very similar to the `v8::Function::Call` method.

***Figure 2.x - Creating an object instance with v8::Function::NewInstance C++ with V8***

```c++
v8::Handle<v8::Value> args[] = { v8::String::New("beep"), v8::String::New("boop") };
v8::Local<v8::Value> instance = fn->NewInstance(2, args);
```

## 2.x Prototypes

Prototypes in JavaScript are a way for objects to inherit from one another. Unlike C++ or Java, which are both classical languages, JavaScript is prototypal which is a form of inheritance where objects serve as prototypes of an instance. These prototypes inherit from each other through what is known as the prototype chain. With v8 we can achieve the same inheritance model with the `v8::FunctionTemplate` class.

In order to define a function's prototype - a function template must be created.

```c++
v8::Local<v8::FunctionTemplate> f_tpl = v8::FunctionTemplate::New();
```

After a function template is constructed you can then set its call handler with a `v8::FunctionCallback`. This is done by calling the `v8::FunctionTemplate::SetCallHandler` method.

```c++
f_tpl->SetCallHandler(myFunction);
```

The state of the function template is much like a class without any methods or properties. In JavaScript we add class methods by adding to the prototype of the function. In order to achieve the same results in v8 we must get a reference to the function's prototype. This is achieved by retrieving the `v8::FunctionTemplate` instance's prototype `v8::ObjectTemplate` instance with the `v8::FunctionTemplate::PrototypeTemplate` method.

***Figure 2.x - Retrieving a prototype template from a function template C++ with V8***

```c++
v8::Local<v8::ObjectTemplate> prototype = f_tpl->PrototypeTemplate();
```

## 2.x Methods

Methods in JavaScript are usually functions bound to an object. They can be dynamically attached or part of a prototype. Class methods are usually defined on a prototype, but can be attached to object instances too. Either way you are just setting properties on an object whether that may be a function, a prototype or an object.

To define a method for a function or constructor, you must get its prototype template from its function template and set it.

***Figure 2.x - Setting a method on a prototype in C++ with V8***

```c++
v8::Local<v8::ObjectTemplate> prototype = f_tpl->PrototypeTemplate();
prototype->Set(v8::String::New("myMethod"), v8::FunctionTemplate::New(myNativeFunction);
```

You can also set a method on an object's instance dynamically through something known as an instance template. The instance template is retrievable through the `v8::FunctionTemplate::InstanceTemplate` method.

***Figure 2.x - Getting an instance template in C++ with V8***

```c++
v8::Local<v8::ObjectTemplate> instance_t = f_tpl->InstanceTemplate();
```

With an instance template you can set properties and methods that are attached to the newly created object during instantiation.

***Figure 2.x - Setting an instance method in C++ with V8***

```c++
instance_t->Set(v8::String::New("myInstanceMethod"), v8::FunctionTemplate::New(myOtherNativeFunction);
```

Since templates are just like objects we can set methods on plain objects as well.

***Figure 2.x - Setting an object method in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->Set(v8::String::New("myMethod"), v8::FunctionTemplate::New(myMethod);
```

## 2.x Global

In every `v8::Context` instance there exists a global object instance of `v8::Object`. The global object represents the top level scope of the currently entered context. You can retrieve the current global object with the `v8::Context::Global` method.

***Figure 2.x - Retrieving a context's global object in C++ with V8***

```c++
v8::Local<v8::Object> global = v8::Context::GetCurrent()->Global();
```

The global object is just an instance of `v8::Object`. You can retrieve the global object at any time and add or remove properties from it much like you would a normal `v8::Object` instance.

***Figure 2.x - Setting a property on a context's global object in C++ with V8***

```c++
v8::Local<v8::Object> global = v8::Context::GetCurrent()->Global();
global->Set(v8::String::New("version"), v8::Number::New(4));
```

## 2.x Exceptions

Exceptions in JavaScript are usually handled with a `try {} catch (e) {}` block, but in v8 we must use the `v8::TryCatch` class to achieve the same functionality.

In an example runtime lets assume we have a function that is called sometime during execution and its only role is to execute a string of JavaScript that is provided to it as an argument from a JavaScript runtime. It can be described as a v8 function like such:

```c++
v8::Handle<v8::Value>
Function (const v8::Arguments &args) {
```

Within the body of this function a `v8::HandleScope`, `v8::TryCatch` and `v8::String` are declared.

```c++
  v8::HandleScope scope;
  v8::TryCatch try_catch;
  v8::Local<v8::String> src = args[0]->ToString();
  v8::Local<v8::String> name = v8::String::New("eval");
```

Using the `v8::Script::Compile` static method to compile the given source that is an instance of `v8::String` with a given file name we set to "eval" (that is also an instance of `v8::String`) the result can be determined. `v8::Script::Compile` returns an instance of `v8::Script`

```c++
  v8::Handle<v8::String> script = v8::String::Compile(src, name);
```

The result can be checked with the `v8::Handle<v8::Script>::IsEmpty` method.

```c++
  if (script.IsEmpty()) { // there was an error
```

If the script result was empty then there was most likely an error. The error can be caught using the instance of `v8::TryCatch`.

```c++
    v8::String::Utf8Value exception(try_catch->Exception());
    v8::Handle<v8::Message> message = try_catch->Message();
```

If the message is empty then the exception can be printed to `stderr` using `fprintf`. But, if there was a message - like an error thrown with a message string, then using the `v8::Message` API, a verbose message with line, column and stack traces can be contrived and written to `stderr`. Due to the extent of the `v8::Message` API an example will be omitted. See `v8::Message` below.

```c++
    if (message.IsEmpty() {
      const char *exception_str = *(message);
      fprintf(stderr, "%s\n", exception_str);
    } else {
      // output verbose error
    }
```

Finally we return an undefined value and close the scope.

```c++
  return scope.Close(v8::Undefined());
}
```

**The `v8::Message` API consists of the following methods:**

Gets the string representation of the message.

```c++
v8::Local<v8::String> v8::Mesage::Get();
```

Gets the source line of the message.

```c++
v8::Local<v8::String> v8::Message::GetSourceLine();
```

Returns the resource name for the script from where the function causing the error originates.

```c++
v8::Handle<v8::Value> v8::Message::GetScriptResourceName();
```

Returns the resource data for the script from where the function causing the error originated.

```c++
v8::Handle<v8::Value> v8::Message::GetScriptData();
```

Gets the stack trace for the executed script from which the message was created.

```c++
v8::Handle<v8::StackTrace> v8::Message::GetStackTrace();
```

Returns the number, 1-based, of the line where the error occurred.

```c++
int v8::Message::GetLineNumber();
```

Returns the index within the script of the first character where the error occurred.

```c++
int v8::Message::GetStartPosition();
```

Returns the index within the script of the last character where the error occurred.

```c++
int v8::Message::GetEndPosition();
```

Returns the index within the line of the first character where the error occurred.

```c++
int v8::Message::GetStartColumn();
```

Returns the index within the line of the last character where the error occurred.

```c++
int v8::Message::GetEndColumn();
```

# 3 Understanding the link between Node.js and v8

The link between Node.js and v8 consists of a set of scripts and predefined modules that bootstrap when the `node` executable is invoked. The `node_isolate`, `context` and `context_scope` are all set up to create the runtime environment. Functions like `require` are defined to facilitate modular loading of files into the context. Objects like `process` are also defined to provide meta information about the process and environment in which the node executable is currently running. The `process` object also controls streams to `stdin`, `stdout` and `stderr` for stdio. The `process` object also provides a global way of catching errors and providing asynchronous routines within the event loop through a function called `process.nextTick`. Node.js also sets up objects like `module`, `exports`, `console` and `global`. It also introduces the `Buffer` constructor. Variables global to the module are set including `__filename`, `__dirname` and `exports` which is a property of the `module` object itself.

## 3.x The `node_isolate`

The `node_isolate` is the single isolate that is created during bootstrap. It represents the process that is currently executing the runtime. For each `v8::HandleScope` instance that is created the `node_isolate` is provided to it.

***Figure 3.x - Node.js handle_scope created (src: node.cc)***

```c++
HandleScope handle_scope(node_isolate);
```

## 3.x The `context`

During initialization a context is created after the `v8::HandleScope` is declared. It is the only context created during bootstrap. It is given the only `node_isolate` as its `v8::Isolate` instance.

***Figure 3.x - Node.js context created (src: node.cc)***

```c++
// Create the one and only Context.
Local<Context> context = Context::New(node_isolate);
```

## 3.x The `context_scope`

After a context is created a `v8::Context::Scope` instance is created and given the `context` as its `v8::Context` instance.

***Figure 3.x - Node.js context_scope created (src: node.cc)***

```c++
Context::Scope context_scope(context);
```

## 3.x Node Marcos

**NODE_DEFINE_CONSTANT(target, constant)**

The `NODE_DEFINE_CONSTANT` macro provides an easier way to define a constant on a given target:

```c++
#include <unistd.h>

// ..
// ..

v8::Local<v8::Object> obj = v8::Object::New();
NODE_DEFINE_CONSTANT(obj, EACCES); // sets `obj.EACCES = EACCES;` in JavaScript
```

**NODE_SET_METHOD(recv, name, callback)**

The `NODE_SET_METHOD` macro provides an easier way to define a function callback on a given object.

* The `recv` is of a type signature: `const TypeName &recv`.
* The `name` is of a type signature: `const char *name`.
* The `callback` is of a type signature: `v8::FunctionCallback callback`.

***Example:***

In an init function set it to the incoming `exports` object.

```c++
void
Init (v8::Handle<v8::Object> exports) {
  NODE_SET_METHOD(exports, "myFunc", MyFunction);
}
```

**NODE_SET_PROTOTYPE_METHOD(recv, name, callback)**

The `NODE_SET_PROTOTYPE_METHOD` macro provides an easier way to set a function as a prototype method on a `v8::FunctionTemplate` instance.

* The `recv` is of a type signature: `v8::Handle<v8::FunctionTemplate> recv`.
* The `name` is of a type signature: `const char *name`.
* The `callback` is of a type signature: `v8::FunctionCallback callback`.

***Example:***

Using a `v8::FunctionTemplate` instance you can define a method.

```c++
NODE_SET_PROTOTYPE_METHOD(f_tpl, "myMethod", MyMethod);
```

**NODE_MODULE(modname, regfunc)**

The `NODE_MODULE` macro provides a way of initializing a module with an initialization function.

***Example:***

```c++
void
InitModule (v8::Handle<v8::Object> exports) {
  // do something during initialization
}

NODE_MODULE(module, InitModule);
```

# 4 Building a native Node.js module

Building a native Node.js module may require a few questions to be answered before starting: 

* Can it be done in pure JavaScript? 
* Are there performance gains?
* Is it maintainable?
* Am I reinventing the wheel?

Some of these questions you may answer yes to and some no but ultimately it is these questions that can drive your decision to go native or not.

When you start to write your module you should be aware of build tools like `node-gyp` and `node-waf`. For this article we will focus on `node-gyp` as it is the popular and much more supported choice for building and compiling your native code with Node.js.

Node-GYP was built by Nathan Rajlich, known on the interweb as TooTallNate. This tool was built to ease the process of building native Node.js modules. It is a cross platform command line tool and is meant to be the replacement for `node-waf` (as of Node.js version `0.8`).

You can install the command line executable with `npm`:

```sh
$ [sudo] npm install node-gyp -g
```

The `-g` flag indicates that it should be global. `npm` will then expose its binary executable to your `$PATH` variable.

Compiling your project is as easy as running these commands:

```sh
$ node-gyp configure
$ node-gyp build
```

## 4.x Requirements

In order for you to properly build and compile your node module you will need to set up a file called `binding.gyp` in the root of your project.

A simple `binding.gyp` file could look like this:

```gyp
{
  "targets": [
    {
      "target_name": "my_module",
      "sources": [ "my_module.cc" ]
    }
  ]
}
```

`targets` is an array of targets to be compiled when invoked with `$ node-gyp build`. The `target_name` is the name of the file that is outputted and the `sources` array is a list of source files that are to be compiled in the order they are provided.

After invoking `$ node-gyp build` a `build/` directory is created in the root of the project with a child directory `Release/` where the target was compiled to. In the case of the example above the compiled node module would exist at `build/Release/my_module.node` and can be required as `require('./build/Release/my_module')` in your JavaScript code.

## 4.x Boilerplate

The basic needs of a native Node.js module are a header file, an initialization function and a call to `NODE_MODULE` to register the module with Node.js.

***Figure 4.x - Boilerplate code for native Node.js module in C++***

```c++
#include <node.h>

void Init (v8::Handle<v8::Object> exports) {
  // initialization code
}

NODE_MODULE(my_module, Init);
```

# 5 Things to be aware of



# 6 Extra goodies to make development easier

* bindings - A `npm` module to make it easier to require native modules in a project
```js
var myModule = require('bindings')('myModule'); // requires ./build/Release/myModule.node
```

# 7 Example hello world

Here is a sample hello world module that creates three functions `.hello()`, `.world()`, and `.greet(name)`.

* `.hello()` - will return a string "hello"
* `.world()` - will return a string "world"
* `.greet(name)` - will return a string "hello `name`!" where `name` is a provided argument

***Figure 4.x - Boilerplate code for native Node.js module in C++***

```c++
#include <node.h>

v8::Handle<v8::Value>
hello (const v8::Arguments &args) {
  v8::HandleScope scope;
  return scope.Close(v8::String::New("hello"));
}

v8::Handle<v8::Value>
world (const v8::Arguments &args) {
  v8::HandleScope scope;
  return scope.Close(v8::String::New("world"));
}

v8::Handle<v8::Value>
greet (const v8::Arguments &args) {
  v8::HandleScope scope;
  return scope.Close(
    v8::String::Concat(
      v8::String::New("hello "),
      args[0]->ToString()
    )
  );
}

void Init (v8::Handle<v8::Object> exports) {
  NODE_SET_METHOD(exports, "hello", hello);
  NODE_SET_METHOD(exports, "world", world);
  NODE_SET_METHOD(exports, "greet", greet);
}

NODE_MODULE(hello, Init);
```

In our JavaScript file we can require this module and invoke the methods we defined.

```js
var hello = require('./build/Release/hello');

console.log(hello.hello()) // hello
console.log(hello.world()) // world
console.log(hello.greet('joe')) // hello joe
```

# 8 Conclusion 
