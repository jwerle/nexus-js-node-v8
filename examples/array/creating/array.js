
var assert = require('assert')
	,	array = require('bindings')('array')

assert(array.create() instanceof Array);
assert(1 === array.create(1).length);