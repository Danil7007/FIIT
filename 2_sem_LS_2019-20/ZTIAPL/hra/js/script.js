// globalne premenne
var redrawInterval;
var myStorage = window.localStorage; // premenná browseru do ktorej sa ukladá skóre (trvalé)
var sec = 0;
var count = 0;
var done = 0;
var btns = new Array();

// inicializačná funkcia ----------------------------------------------------------------------------------------

function init() {
  // prednacitanie assetov
  preloadAssets();

  // získanie elementu canvas
  gameArea.createCanvas();

  // pridanie event listeneru, kt. počúva kde bola myška kliknutá
  gameArea.canvas.addEventListener("click", mouseClicked);

  // draw menu, timeout aby sa stihli načítať assety
  setTimeout(drawMenu, 400);

  // vytvorenie mute tlačítka a pauza menu
  muteBtn = new btn(10, 50, 10, 40);
  pauzickaBtn = new btn(60, 100, 10, 40);

  goBackBtn = new btn(0, gameArea.canvas.width, 0, gameArea.canvas.height);

  menuBtn_01 = new btn(195, 445, 80, 140);
  menuBtn_02 = new btn(195, 445, 200, 260);
  menuBtn_03 = new btn(195, 445, 290, 360);

  endBtn_01 = new btn(45, 290, 300, 365);
  endBtn_02 = new btn(325, 575, 300, 365);

  resumeBtn = new btn(
    gameArea.canvas.width / 2 - 100,
    gameArea.canvas.width / 2 + 100,
    gameArea.canvas.height / 2 - 125,
    gameArea.canvas.height / 2 - 75
  );
  quitBtn = new btn(
    gameArea.canvas.width / 2 - 100,
    gameArea.canvas.width / 2 + 100,
    gameArea.canvas.height / 2 - 25,
    gameArea.canvas.height / 2 + 25
  );

  // pridanie ich do pola
  btns.push(
    muteBtn,
    pauzickaBtn,
    menuBtn_01,
    menuBtn_02,
    menuBtn_03,
    endBtn_01,
    endBtn_02,
    resumeBtn,
    quitBtn
  );

  // tieto maju byt aktivne
  muteBtn.active = true;
  pauzickaBtn.active = true;

  // skore
  score = new skore();

  // získanie skóre kt. sa nachádza v local storage
  score.getScore();

  // vypísanie skrrr do tabulky
  printToTable();
}

// prednačítnie všetkých obrázkov -------------------------------------------------------------------------------

function preloadAssets() {
  // pozadie 02
  this.background02_01 = new Image(); //vytvorenie objektu "obrázok"
  this.background02_01.src = "../assets/pictures/bg/bg02_01.png"; //pridanie objektu cestu k súboru
  this.background02_02 = new Image();
  this.background02_02.src = "../assets/pictures/bg/bg02_02.png";
  this.background02_03 = new Image();
  this.background02_03.src = "../assets/pictures/bg/bg02_03.png";

  // pozadie 01
  this.background01_01 = new Image();
  this.background01_01.src = "../assets/pictures/bg/bg01_01.png";
  this.background01_02 = new Image();
  this.background01_02.src = "../assets/pictures/bg/bg01_02.png";
  this.background01_03 = new Image();
  this.background01_03.src = "../assets/pictures/bg/bg01_03.png";

  // menu
  this.menu01 = new Image();
  this.menu01.src = "../assets/pictures/bg/menu01.png";
  this.menu02 = new Image();
  this.menu02.src = "../assets/pictures/bg/menu02.png";

  // chapadielka
  this.chapadlo01 = new Image();
  this.chapadlo01.src = "../assets/pictures/octo/chapadlo01.png";
  this.chapadlo02 = new Image();
  this.chapadlo02.src = "../assets/pictures/octo/chapadlo02.png";
  this.chapadlo03 = new Image();
  this.chapadlo03.src = "../assets/pictures/octo/chapadlo03.png";

  // chobotnica
  this.octo01 = new Image();
  this.octo01.src = "../assets/pictures/octo/octo01.png";
  this.octo02 = new Image();
  this.octo02.src = "../assets/pictures/octo/octo02.png";
  this.octo03 = new Image();
  this.octo03.src = "../assets/pictures/octo/octo03.png";

  // lodka
  this.boat01 = new Image();
  this.boat01.src = "../assets/pictures/boat/boat01.png";
  this.boat02 = new Image();
  this.boat02.src = "../assets/pictures/boat/boat02.png";

  // zivoty
  this.lives01 = new Image();
  this.lives01.src = "../assets/pictures/lives/lives01.png";
  this.lives02 = new Image();
  this.lives02.src = "../assets/pictures/lives/lives02.png";
  this.lives03 = new Image();
  this.lives03.src = "../assets/pictures/lives/lives03.png";

  // pena
  this.imgPena = new Image();
  this.imgPena.src = "../assets/pictures/particles/pena.png";

  // ikonky
  this.mute = new Image();
  this.mute.src = "../assets/pictures/mute.png";
  this.mute02 = new Image();
  this.mute02.src = "../assets/pictures/mute02.png";
  this.pause = new Image();
  this.pause.src = "../assets/pictures/pause.png";
}


