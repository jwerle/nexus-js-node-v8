
var assert = require('assert')
	,	object = require('bindings')('object')

assert('bar' === object.foo);
assert('baz' === object.biz);

assert(!!~object.getOwnPropertyNames(object).indexOf('foo'));
assert(!!~object.getOwnPropertyNames(object).indexOf('biz'));
assert(!~object.getOwnPropertyNames(object).indexOf('property'));

assert(!!~object.getPropertyNames(object).indexOf('property'));