//globalne premenne
var fps = 60;
var redrawInterval;
var frameNo = 0;
var sec = 0;


//inicializačná funkcia
function init() {
    preloadAssets();
    gameArea.createCanvas();
    setTimeout(play, 400);  
}

// prednacitanie obrazkov
function preloadAssets() {
    this.background01_01 = new Image(); 
    this.background01_01.src = "bg01_01.png"; 

    this.chapadlo01 = new Image();
    this.chapadlo01.src = "chapadlo01.PNG";
    this.chapadlo02 = new Image();
    this.chapadlo02.src = "chapadlo02.PNG";
    this.chapadlo03 = new Image();
    this.chapadlo03.src = "chapadlo03.PNG";

    this.octo03 = new Image();
    this.octo03.src = "octo03.png";
}

// play
function play() {
    fps = 60;

    chapadielko1 = new chapadlo(100, 200, 200);
    chapadielko2 = new chapadlo(200, 200, 200);
    chapadielko3 = new chapadlo(300, 200, 200);
    chapadielko4 = new chapadlo(400, 200, 200);
  
    redrawInterval = setInterval(updateGameAreaPlay, 1000 / fps);
    
}

// update
function updateGameAreaPlay() {
    frameNo += 1;

    if (frameNo > 60) {
        frameNo = 0;
    }
    gameArea.clear(); 

    switch (
        true //prehrávanie animácie
      ) {
        case frameNo <= 15:
            gameArea.context.drawImage(
                background01_01,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
            );

            chapadielko1.drawMe(1);
            chapadielko2.drawMe(2);
            chapadielko3.drawMe(3);
            chapadielko4.drawMe(2);
            break;
        case frameNo <= 30:
            gameArea.context.drawImage(
                background01_01,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
            );

            chapadielko1.drawMe(2);
            chapadielko2.drawMe(3);
            chapadielko3.drawMe(2);
            chapadielko4.drawMe(1);
            break;
        case frameNo <= 45:
            gameArea.context.drawImage(
                background01_01,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
            );

            chapadielko1.drawMe(3);
            chapadielko2.drawMe(2);
            chapadielko3.drawMe(1);
            chapadielko4.drawMe(2);
            break;
        case frameNo <= 60:
            gameArea.context.drawImage(
                background01_01,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
            );

            var random = Math.floor(Math.random() * 20);
            chapadielko1.drawMe(2);
            chapadielko2.drawMe(1);
            chapadielko3.drawMe(2);
            chapadielko4.drawMe(3);

            // chapadlo 01
            if (chapadielko1.Y >= 0 && random == 0) {
                chapadielko1.height += 50;
                chapadielko1.Y -= 50;

                if (chapadielko1.Y < 0) {
                    chapadielko1.Y = 200;
                    chapadielko1.height = 200;
                    chapadielko2.Y = 200;
                    chapadielko2.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko4.Y = 200;
                    chapadielko4.height = 200;
                }
            }
            // chapadlo 02
            if (chapadielko2.Y >= 0 && random == 1) {
                chapadielko2.height += 50;
                chapadielko2.Y -= 50;
      
                if (chapadielko2.Y < 0) {
                    chapadielko1.Y = 200;
                    chapadielko1.height = 200;
                    chapadielko2.Y = 200;
                    chapadielko2.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko4.Y = 200;
                    chapadielko4.height = 200;
                }
            }
            // chapadlo 03
            if (chapadielko3.Y >= 0 && random == 2) {
                chapadielko3.height += 50;
                chapadielko3.Y -= 50;
   
                if (chapadielko3.Y < 0) {
                    chapadielko1.Y = 200;
                    chapadielko1.height = 200;
                    chapadielko2.Y = 200;
                    chapadielko2.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko4.Y = 200;
                    chapadielko4.height = 200;
                }
            }
            // chapadlo 04
            if (chapadielko1.Y >= 0 && random == 3) {
                chapadielko4.height += 50;
                chapadielko4.Y -= 50;
                
                if (chapadielko4.Y < 0) {
                    chapadielko1.Y = 200;
                    chapadielko1.height = 200;
                    chapadielko2.Y = 200;
                    chapadielko2.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko3.Y = 200;
                    chapadielko3.height = 200;
                    chapadielko4.Y = 200;
                    chapadielko4.height = 200;
                }
            }
            break;
        }
    
    // chobotnica
    gameArea.context.drawImage(octo03, 0, 0, 613, 434);

    nadpis = new txt(gameArea.canvas.width / 2 - 10, 20, "60px", "black", "NADPIS");
    nadpis.drawMe();
}

// funkcia text
function txt(x, y, size, color, text) {
    this.X = x;
    this.Y = y;
    this.size = size;
    this.color = color;
    this.text = text;
    this.drawMe = function() {
      gameArea.context.fillStyle = color;
      gameArea.context.fillText(this.text, this.X, this.Y);
    };
}

//objekt pre chapadielko
function chapadlo(x, y, scale) {
    this.X = x;
    this.Y = y;
    this.visible = 0;
    this.width = scale / 2;
    this.height = scale;
    this.drawMe = function(version) {
      switch (true) {
        case version == 1:
            gameArea.context.drawImage(
                chapadlo01,
                this.X,
                this.Y,
                this.width,
                this.height
            );
            break;
        case version == 2:
            gameArea.context.drawImage(
                chapadlo02,
                this.X,
                this.Y,
                this.width,
                this.height
            );
            break;
        case version == 3:
            gameArea.context.drawImage(
                chapadlo03,
                this.X,
                this.Y,
                this.width,
                this.height
            );
            break;
        }
    };
}

// premenná pre canvas
var gameArea = {
    canvas: document.querySelector("canvas"), //ziskanie elementu canvas

    createCanvas: function() {
      this.context = this.canvas.getContext("2d"); //ziskanie contextu - obsahu canvas
      this.canvas.width = 613.9;
      this.canvas.height = 434;
    },

    // cistenie canvas
    clear: function() {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }
};