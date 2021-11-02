function add() {
	var ret = 0
	for (var i = 0; i < 2; i++) {
		var arg = arguments[i]
		if (typeof(arg)!="number") return undefined;
		ret += arg
  }
  return ret
}
