
var assert = require('assert')
	,	object = require('bindings')('object')
	, refObj = { name: 'werle' }
	,	obj1 = { ref: refObj, value: 'foo' }
	,	obj2 = object.clone(obj1)

// change the `name` property on the `refObj`
obj2.ref.name = 'joe';

// change the `value` property on `obj2`
obj2.value = 'bar';

// assert the `name` property was changed
assert('joe' === obj1.ref.name);

// assert the name property was changed on the `refObj`
assert(refObj.name === obj1.ref.name);

// assert the `value` property on `obj1` reamins the same
assert('foo' === obj1.value);