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

Though JavaScript is the core front-end language for the Node.js software it can be used anywhere a valid JavaScript engine is available such as the V8 JavaScript engine in the Chrome Browser. Other engines include Rhino, a Java based JavaScript engine developed by Mozilla; SpiderMonkey, a C implementation of the Rhino engine; and JavaScriptCore, the JavaScript engine for WebKit implementations and OS X environments that provide scripting JavaScript. 

Google's v8 compiles JavaScript to native machine code before executing it as opposed to interpreting or executing bytecode. In environments like the browser JavaScript can be executed on the fly with a method known as just-in-time (JIT) compilation. The Node.js software with libuv sits on top of v8 as a compilation of interfaces to the machine. With a JavaScript front-end to the Node.js, libuv, and v8 package one has access to a plethora of interfaces to the machine including file i/o, tcp, and http.

The libuv platform abstraction layer provides a library for building scalable cross platform applications. It sits at the core of the Node.js application stack and is the best way to write C code that can run on BSD, Linux, and Windows based systems [1]. Before the integration of libuv, libev, an asynchronous event notification library, and libeio, an asynchronous i/o library for C were used [2]. As the project grew and a higher demand for Windows support amplified a solution was needed because of lack of support for the Windows system by libev. [3] When node-v0.9.0 was released libev was removed from libuv entirely [4] and a similar API was provided. Since the projects growth many other languages have implemented bindings such as Ruby, Go, and Python for libuv [5].

So we have an elegant language like JavaScript, a powerful engine like v8, and a cross platform abstraction layer like libuv all working together in a software stack we call Node.js. On top of the all this power is a set of modules known as the Node.js core library which is what we consume as application developers. 

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


# 2 Understanding the basic links between v8, Node.js, and JavaScript

In this section we will learn some of the basic links between data types, functions and th rest of the basic parts of JavaScript. We will understand how to create primitive data types in C++ and how to do the same in JavaScript. I make the assumption that you have a basic understanding of JavaScript and Node.js.

## Isolates

In v8, isolates in represent an isolated instance of a v8 engine. Every v8 isolate has a completely unique state and objects from any isolate should not be mixed with other isolates. During initialization v8 creates a default isolate and enters its scope. Other isolates may be created and used with each other in parallel running in separate threads. An isolate may only be entered by one thread at any given time during execution. [1]

***Figure 2.x - Creating a new Isolate in C++ with V8***

```c++
Isolate *isolate = Isolate::New();
```

***Figure 2.x - Getting the current isolate in C++ with V8***

```c++
```

---

[1] - http://izs.me/v8-docs/classv8_1_1Isolate.html

## Contexts

In v8, a context is an execution environment that allows separate, unrelated, JavaScript to run in a single instance of v8 [1]. You must always declare the context in which you want any JavaScript to be executed in. The need for contexts in v8 comes from the need for multiple global objects existing like iframes or new windows or tabs in a browser. After a context is created you may create another and choose to leave and enter it when you please [1].

***Figure 2.x - Declaring a new Context in C++ with V8***

```c++
Persistent<Context> context = Context::New();
```

***Figure 2.x - 

---

[1] - https://developers.google.com/v8/embed#contexts

## 2.1 Primitive Data types

If you have ever opened up a console and played around JavaScript then you will quickly become familiar with the built-in primitive data types. Things like `Number` and `Boolean` quickly show up as soon as you start adding logic to a function. Declaring them is as easy as dfining a variable with a left hand assignment much like `var num = 4;` or `var bool = false;`. But, how exactly could these be declared in C++? Declaring a primitive in C++ is less trivial.


***Figure 2.1 - Declaring a number in C++ with V8***

```c++
v8::Local<v8::Number> num = v8::Number::New(4);
```

***Figure 2.2 - Declaring a boolean in C++ with V8***

```c++
v8::Local<v8::Boolean> bool = v8::Boolean::New(true);
```

***Figure 2.3 - Declaring a string in C++ with V8***

```c++
v8::Local<v8::String> str = v8::String::New("hello world");
```

***Figure 2.4 - Declaring a null value in C++ with V8***

```c++
v8::Local<v8::Null> null = v8::Null();
```

***Figure 2.5 - Declaring an undefined value in C++ with V8***

```c++
v8::Local<v8::Undefined> undefined = v8::Undefined();
```


## 2.2 Objects

## 2.3 Arrays

## 2.4 Functions

## 2.4 Methods

## 2.5 Constructors

## 2.6 Prototypes

##  Scopes

## Casting

## Exceptions