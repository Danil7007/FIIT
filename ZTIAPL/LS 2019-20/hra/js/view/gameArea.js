// premenná pre CANVAS ------------------------------------------------------------------------------------------

var gameArea = {
    soundMode: "menu",
    mute: 0,
    lives: 3,
    fps: 60,
    diff: 5,
    mouseX: 0,
    mouseY: 0,
    mode: 3,
    previousMode: 1,
    paused: 0,
    canvas: document.querySelector("canvas"), // ziskanie elementu canvas
    nadpis: document.querySelector("h1"), // ziskanie elementu nadpis
    frameNo: 0,
    menu: 0,
    createCanvas: function () {
      this.context = this.canvas.getContext("2d"); // ziskanie contextu - obsahu canvas
      this.canvas.width = 613.9;
      this.canvas.height = 434;
  
      // offset od vrchu stranky po canvas
      this.oX = parseInt(window.getComputedStyle(this.canvas).marginLeft);
      this.oY =
        parseInt(window.getComputedStyle(this.canvas).marginTop) +
        parseInt(window.getComputedStyle(this.nadpis).height);
    },
  
    // cistenie canvas
    clear: function () {
      this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
    },
};