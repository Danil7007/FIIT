test( "add, test addition", function() {
	pass(add(2,2)==4, "This should pass")
	fail(add(0,2)==3, "This should fail")
})

test( "add, test number of arguments", function() {
	pass(add(2)==undefined, "One argument must return undefined")
	pass(add(2,2,2)==4, "Only add two arguments")
})

test( "add, test type of arguments", function() {
	pass(add(3,"4")==undefined, "Only numbers should be added")
	fail(add("2",[3])==4, "Only numbers should be added")
})