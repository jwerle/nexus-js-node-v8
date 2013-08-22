
var hello = require('bindings')('hello')

console.log(hello.hello())
console.log(hello.world())
console.log(hello.greet('joe'))
