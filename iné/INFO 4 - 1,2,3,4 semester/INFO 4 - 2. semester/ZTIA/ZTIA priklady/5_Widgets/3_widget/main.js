var app // for easier debug

// Just start our application and add some widgets to it
window.onload = function() {
  app = new App("canvas")

  // Add buttons
  var button1 = new Button("Button1", 10, 10, 100, 50)
  button1.action = function() {
    alert("Button 1")
  }
  app.add(button1)

  var button2 = new Button("Button2", 150, 10, 100, 50)
  button2.action = function() {
    console.log("Button 2")
  }
  app.add(button2)


  // Add a container
  var container = new Widget(10, 80, 370, 200)
  app.add(container)
    //container.visible = false

  // Add textfields
  var field1 = new Textfield("Textfield1", 10, 10, 300, 50)
  field1.action = function() {
    alert(field1.text)
  }
  container.add(field1)

  var field2 = new Textfield("Textfield2", 10, 80, 300, 50)
  field2.action = function() {
    console.log(field2.text)
  }
  container.add(field2)


  var generatedContainer = new Widget(0, 0, 370, 200)
  for( i=0; i<370; i+=70) {
    for( j=0; j<200; j+=70) {
      var button = new Button(i+","+j, i, j, 50, 50)
      button.action = function() {
        alert("Button: "+i+","+j)
      }
      generatedContainer.add(button)
    }
  }

  var buttonx = new Button("ClearButton", 320, 10, 50, 50)
  buttonx.action = function() {
    field1.text = ""
    app.nodes = generatedContainer.nodes
  }
  container.add(buttonx)

  // Start the application main loop
  app.start()
}
