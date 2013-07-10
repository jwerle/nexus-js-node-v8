
var assert = require('assert')
	,	object = require('bindings')('object')

assert(Object === object.getConstructor({}));
assert(Array === object.getConstructor([]));

assert('Object' === object.getConstructorName({}));
assert('Array' === object.getConstructorName([]));