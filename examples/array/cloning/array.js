
var assert = require('assert')
	,	array = require('bindings')('array')
	, obj1 = {foo: 'bar'}
	, arr = [ obj1 ]
	, obj2 = array.cloneAt(arr, 0)

obj2.foo = 'biz';

assert(obj1.foo !== obj.foo);
