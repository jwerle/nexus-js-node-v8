
var assert = require('assert')
	,	object = require('bindings')('object')

assert(object.proto);
assert(object.property === object.proto.property);
assert(object.__proto__.property === object.property);