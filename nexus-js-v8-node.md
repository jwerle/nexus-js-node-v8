# The Nexus of JavaScript, v8, and Node.js

#### by Joseph Werle

# 1. Introduction 

## 1.2 What is JavaScript?

JavaScript, sometimes abbreviated ***JS*** is an interpreted computer programming language originally designed and implemented for web browsers. It was created so client side executable scripts written in the language can interact with the user viewing the web page. It is a dynamic, type safe, prototyped based language that was influenced by ***C*** and ***Java*** programming languages.

The language's birth can be traced back to the Netscape Foundation which first made its appearance in the Netscape browser in September of 1995. It was developed under the name ***Mocha*** by Brendan Eich, released under the name ***LiveScript***, and eventually renamed to ***JavaScript*** [1].

Since its creation the language has been used in multiple environments such as the browser, server, and embedded systems. It is currently standardized by the ECMA International standards organization under the name ECMAScript. Other well known implementations of the standard include langauges like JScript, the proprietary JavaScript implementation from Microsoft for Internet Explorer; and ActionScipt, an object-oriented language designed for scripting Flash applications originally developed by Macromedia, which is now owned by Adobe Systems.


### 1.2.1 CommonJS

In an effort to continue standardizing the way we write JavaScript a project known as CommonJS was born. The goal of the project is "specifying an ecosystem for JavaScript outside the browser" [2]. It currently aims for modularity, packaging, common interfaces, and the uniformity of a baseline.

>"What I'm describing here is not a technical problem. It's a matter of people getting together and making a decision to step forward and start building up something bigger and cooler together." [3]

— Kevin Dangoo

---

[1] - http://web.archive.org/web/20070916144913/http://wp.netscape.com/newsref/pr/newsrelease67.html
[2] - http://wiki.commonjs.org/wiki/CommonJS
[3] - http://www.blueskyonmars.com/2009/01/29/what-server-side-javascript-needs/

## 1.3 What is v8?

The V8 JavaScript engine, or sometimes referred to as just ***v8*** is an open source JavaScript engine developed and maintained by Google. It was created as the core JavaScript engine for the Chrome browser and now used in a variety of projects including Node.js, Chromium Browser, and the Chromium Embedded Framework (CEF). It is written in C++ and intended for a variety of operating systems. It was first released with the first version of the Chrome Browser on September 2, 2008 [1].

***Figure 1.1 - A function written in v8 that returns a string "world"***

```c++
v8::Handle<v8::Value> helloWorld (const v8::Arguments &args) {
  v8::HandleScope scope;
  v8::Local<v8::String> hello = v8::String::New("world");
  return scope.Close(hello);
}
```

***Figure 1.2 - A function written in JavaScript that returns a string "world"***

```js
function helloWorld () {
  var hello = "world";
  return hello;
}
```

---

[1] - http://en.wikipedia.org/wiki/V8_(JavaScript_engine)

## 1.4 What is Node.js?

Node.js, sometimes referred to as ***node*** is a server side system for writing highly scalable network applications. It is commonly used to construct web servers. It is an event-driven system running on a single thread which differs from most web servers which are thread based. 

Node.js runtime is built on top of the v8 JavaScript engine, the libuv platform abstraction layer, and the node.js core library. It was created by Ryan Dahl in 2009 at Joyent, a software and services company based in San Fransisco, CA. It is currently maintained by Joyent and an active and passionate community of developers. It implements a handful of specifications defined by CommonJS such as Modules 1.0 [1].


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

Though JavaScript is the core front-end language for browsers, it can be used anywhere a valid JavaScript engine is available such as Node.js with the v8 engine. Other engines include Rhino, a Java based JavaScript engine developed by Mozilla; SpiderMonkey, a C implementation of the Rhino engine; and JavaScriptCore, the JavaScript engine for WebKit implementations and OS X environments that provide scripting JavaScript. 

Google's v8 compiles JavaScript to native machine code before executing it as opposed to interpreting or executing bytecode. In environments like the browser JavaScript can be executed on the fly with a method known as just-in-time (JIT) compilation. The Node.js software with libuv sits on top of v8 as a compilation of interfaces to the machine. With a JavaScript front-end to the Node.js, libuv, and v8 package one has access to a plethora of interfaces to the machine including file i/o, tcp, and http.

The libuv platform abstraction layer provides a library for building scalable cross platform applications. It sits at the core of the Node.js application stack and is the best way to write C code that can run on BSD, Linux, and Windows based systems [1]. Before the integration of libuv, libev, an asynchronous event notification library, and libeio, an asynchronous i/o library for C were used [2]. As the project grew and a higher demand for Windows support amplified a solution was needed because of lack of support for the Windows system by libev. [3] When node-v0.9.0 was released libev was removed from libuv entirely [4] and a similar API was provided. Since the projects growth many other languages have implemented bindings such as Ruby, Go, and Python for libuv [5].

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

With a core library much of the heavy lifting of writing a simple http server with Node.js becomes trivial with a core module called `http`. 

***Figure 1.5 - An example of a simple http server written in JavaScript for a Node.js application***

```js
require('http').createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('Hello world!');
}).listen(8000, '127.0.0.1');

console.log("server running at http://127.0.0.1:8000")
```

Your Node.js application requires the `http` module and creates a server. the `createServer` function accepts a function as an argument which is executed on each request. If you are accustomed to asynchronous programming then this will seem familiar.

---

[1] - http://opensourcebridge.org/sessions/920
[2] - http://nikhilm.github.io/uvbook/introduction.html
[3] - http://nikhilm.github.io/uvbook/introduction.html#background
[4] - https://github.com/joyent/libuv/issues/485
[5] - https://github.com/joyent/libuv/wiki/Projects-that-use-libuv


# 2 Understanding the link between v8 and JavaScript

In this section we will learn some of the basic links between data types, functions and th rest of the basic parts of JavaScript. We will understand how to create primitive data types in C++ and how to do the same in JavaScript. I make the assumption that you have a basic understanding of JavaScript and Node.js.

## 2.x Isolates

In v8, isolates in represent an isolated instance of a v8 engine. Every v8 isolate has a completely unique state and objects from any isolate should not be mixed with other isolates. During initialization v8 creates a default isolate and enters its scope. Other isolates may be created and used with each other in parallel running in separate threads. An isolate may only be entered by one thread at any given time during execution. [1]

***Figure 2.x - Creating a new Isolate in C++ with V8***

```c++
Isolate *isolate = Isolate::New();
```

***Figure 2.x - Getting the current isolate in C++ with V8***

```c++
Isolate *isolate = Isolate::GetCurrent();
```

---

[1] - http://izs.me/v8-docs/classv8_1_1Isolate.html

## 2.x Contexts

In v8, a context is an execution environment that allows separate, unrelated, JavaScript to run in a single instance of v8 [1]. You must always declare the context in which you want any JavaScript to be executed in. The need for contexts in v8 comes from the need for multiple global objects existing like iframes or new windows or tabs in a browser. After a context is created you may create another and choose to leave and enter it when you please [1].

***Figure 2.x - Declaring a new Context in C++ with V8***

```c++
Persistent<Context> context = Context::New();
```

***Figure 2.x - 

---

[1] - https://developers.google.com/v8/embed#contexts

## 2.x Primitive Data types

If you have ever opened up a console and played around JavaScript then you will quickly become familiar with the built-in primitive data types. Things like `Number` and `Boolean` quickly show up as soon as you start adding logic to a function. Declaring them is as easy as defining a variable with a left hand assignment much like `var num = 4;` or `var bool = false;`. But, how exactly could these be declared in C++? Declaring a primitive in C++ is less trivial.


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

## 2.x Objects

According to ECMA-262 section 4.2.1 *Objects* are not created in ways similar to C++, Java, or SmallTalk, but rather though literal notation or via *constructors* that execute an initialization function in the scope of a new object.

***Figure 2.x - Creating a literal object in JavaScript***

```js
var obj = {};
console.log(obj); // {}
```

***Figure 2.x - Creating an object via a constructor***

```js
function MyObject() {}
var obj = new MyObject();
console.log(obj); // {}
```

### 2.x Using Objects

In v8 we can do a lot of the same things we can do in JavaScript with objects like creating, setting properties, cloning, reading prototype, and more.

#### 2.x Creating Objects

Creating an object in v8 is a little more of a task but the same results above can be accomplished. For this section we will focus on create literal objects from the `v8::Object` class. To create an object in v8 we need to execute the static method `New()` on the `v8::Object` class.

***Figure 2.x - Creating a new object in in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
```

#### 2.x Setting properties

In JavaScript we can set properties on objects using dot or bracket notation. We can do the same in v8 with a method call `Set()` on an object instance.

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

Notice that we must create a new `v8::String` instance with the `New()` static method that accepts a `char *` or a C-style string as an argument.

#### 2.x Cloning

In v8 we can make shallow copies of objects using the `Clone()` method found on an instance of `v8::Object`. All objects in copy will point to original references.

***Figure 2.x - Cloning an object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->Clone();
```

#### 2.x Getting the prototype of an object

In JavaScript we have become accustomed to using `__proto__` for getting the prototype of an object. You can do the same in v8 with the `GetPrototype()` method on a `v8::Object` instance.

***Figure 2.x - Getting the prototype of an object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->GetPrototype();
```

#### 2.x Setting the prototype of an object

In JavaScript we can set the prototype of an object via its constructor but in v8 we can use the `SetPrototype` method on an `v8::Object` instance.

***Figure 2.x - Setting the prototype of an object in C++ with V8***

```c++
v8::Local<v8::Object> prototype = v8::Object::New();
prototype->Set(v8::String::New("property"), v8::String::New("value"));
v8::Local<v8::Object> obj = v8::Object::New();
obj->SetPrototype(prototype);
```

#### 2.x Getting own property name

In JavaScript we can retrieve an array of own property names for an object using `Object.getOwnPropertyNames()` excluding properties on the prototype chain. In v8 we can do the same on an `v8::Object` instance with the `GetOwnPropertyNames()` method.


***Figure 2.x - Getting own property names of an object in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->Set(v8::String::New("foo"), v8::String::New("bar"));
obj->Set(v8::String::New("biz"), v8::String::New("baz"));
obj->GetOwnPropertyNames(); // should return an array containing the values ['foo', 'biz']
```

#### 2.x Getting property names including the prototype

In JavaScript we normally cannot look at all the property names of an object and its prototype chain, but i v8 we can with the `GetPropertyNames()` method on an `v8::Object`

***Figure 2.x - Getting property names of an object in C++ with V8***

```c++
obj->GetPropertyNames();
```

#### 2.x Getting the constructor of an object instance

In JavaScript we can obtain the constructor of an object instance by simply referring to the `constructor` property on an object. In v8 we need to make a call to the `GetConstructor` method on a `v8::Object` instance.

***Figure 2.x - Getting the constructor of an object instance in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->GetConstructor();
```

You can also retrieve the name of a constructor with the `GetConstructorName` method on a `v8::Object` instance.

***Figure 2.x - Getting the name of a constructor of an object instance in C++ with V8***

```c++
v8::Local<v8::Object> obj = v8::Object::New();
obj->GetConstructorName();
```

### 2.x Arrays

In JavaScript we are used to working arrays for all sorts of reasons. We can manage sets of data, queues, stacks, etc. We can push, pop, shift, unshift and do all sorts of sorting and filtering on an indexed set of data. In v8 we are not privileged to perform these tasks in a simple manner like we can in JavaScript, but we can make it work.

#### 2.x Creating an array

Creating an array in v8 is as simple as creating any other object. We must utilize the `New(int length = 0)` static method on the `v8::Array` class which accepts an optional `int` which determines the length of the initialized array.

***Figure 2.x - Creating an array with no length in C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New();
```

***Figure 2.x - Creating an array with a length of 5 in C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New(5);
```

#### 2.x Element cloning

In v8 we are provided with a method called `CloneElementAt(uint32_t index)` on a `v8::Array` instance that allows us to clone an element at a specified index in an array.

***Figure 2.x - Cloning an element at a specified index in C++ with V8***

```c++
v8::Local<v8::Array> array = v8::Array::New();
v8::Local<v8::Object> array[0] = v8::Object::New();
array[0]->Set(
  v8::String::New("name"), v8::String:New("werle")
);

v8::Local<v8::Objects> object = array->CloneElementAt(0);
```

### 2.x Regular Expression Objects

### 2.x Date

### 2.x Boolean Objects

### 2.x Number Objects

### 2.x String Objects

### 2.x Function Objects

## 2.x Functions

## 2.x Methods

## 2.x Constructors

## 2.x Prototypes

## 2.x Regular Expression

## 2.x Global

## 2.x Scopes

## 2.x Casting

## 2.x Exceptions

# 3 Understanding the link between Node.js and v8

## 3.x Node Marcos

## 3.x The `node_isolate`

## 3.x The `context`

## 3.x The `context_scope`

# 4 Building a native Node.js module

## 4.x Requirements

## 4.x Boilerplate

# 5 Things to be aware of

# 6 Extra goodies to make development easier

# 7 Conclusion 