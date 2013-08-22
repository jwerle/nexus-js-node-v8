(function () {
	test('foo');
	test(this.toString())
})(this);