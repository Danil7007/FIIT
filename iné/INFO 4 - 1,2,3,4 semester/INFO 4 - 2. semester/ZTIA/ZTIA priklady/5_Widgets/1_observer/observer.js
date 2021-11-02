// Observer object
function Observer() {}

// Notify method that Subject calls on notifyObservers
Observer.prototype.notify = function(subject) {
  console.log("Observer.notify from " + subject)
    // Do something
}
