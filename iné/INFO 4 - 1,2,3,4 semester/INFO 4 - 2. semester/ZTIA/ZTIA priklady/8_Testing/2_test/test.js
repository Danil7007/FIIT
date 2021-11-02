// Test without breaking
function test(id, func) {
	try {
		func()
	}
	catch(err) {
		console.log("Test "+id+" FAILED! "+err)
		return false
	}
	console.log("Test "+id+" OK!")
	return true
}

// Simple helper functions
function pass(condition, message) {
	if (!condition) throw(message)
}

function fail(condition, message) {
	if (condition) throw(message)
}
