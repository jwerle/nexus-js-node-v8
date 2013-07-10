
var assert = require('assert')
	,	object = require('bindings')('object')

assert(object.create() instanceof Object);