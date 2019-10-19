// Object Subject
function Subject() {
  // Storage for observers
  this.observerCollection = []
}

// Add an observer
Subject.prototype.registerObserver = function(observer) {
  this.observerCollection.push(observer)
}

// Remove an observer
Subject.prototype.unregisterObserver = function(observer) {
  var index = this.observerCollection.indexOf(observer)
  delete this.observerCollection[index]
}

// Notify all observers
Subject.prototype.notifyObservers = function() {
  for (index in this.observerCollection) {
    var observer = this.observerCollection[index]
    observer.notify(this)
  }
}
