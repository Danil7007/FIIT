window.onload = function() {
  // Create a subject to observe
  var subject = new Subject()

  // Create 10 observers
  for (var i = 0; i < 10; i++) {
    var observer = new Observer()
    subject.registerObserver(observer)
  }
  // Notfy all observers
  subject.notifyObservers()

  // Create special observer to watch subject.value
  var specialObserver = new Observer()
  specialObserver.notify = function(subject) {
    console.log("specialObserver: " + subject.value)
  }
  subject.registerObserver(specialObserver)
    // Create new subject value
  subject.value = 30
    // Notify all observers
  subject.notifyObservers()

  // Change the value
  subject.value = 42
  // Notify all observers again
  subject.notifyObservers()
}
