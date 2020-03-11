var gameArea = {
    canvas: document.querySelector("canvas"),
    
    frameNo: 0,
    menu: 0,
    
    play: function() {
        this.context = this.canvas.getContext("2d");
        // zistovanie mysky
        window.addEventListener("mousemove", function(e) {
        gameArea.x = e.pageX;
        gameArea.y = e.pageY;
    }),

    // interval obnovovania  
    this.interval = setInterval(updateGameAreaPlay, 1000 / 60);
    },

    // cistenie cavnas
    clear: function() {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }
  };