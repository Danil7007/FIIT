function assert(condition, opt_message) {
  if (!condition) {
    var msg = 'Assertion failed';
    if (opt_message) msg = msg + ': ' + opt_message;
    throw new Error(msg);
  }
}
