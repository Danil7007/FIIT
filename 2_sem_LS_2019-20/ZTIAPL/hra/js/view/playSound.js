// prehravanie vybrateho zvuku
function playSound(src) {
    if (typeof audio != "undefined") {
      // zapauzuje audio keby nahodou už nejaké hralo
      audio.pause();
      delete audio;
    }
  
    // deklaracia audia
    audio = new Audio();
  
    // pridelí cestu k súboru ktorý sa má prehrať
    audio.src = src;
    // nastaví hlasitosť na polovicu
    audio.volume = 0.5;
    // spustí prehrávanie audia
    audio.play();
    // v prípade že ma byť zvuk stíšený stíš novo vytvorený zvuk
    if (gameArea.mute == 1) {
      audio.muted = true;
    }
    // loop, keď sa zastaví audio, znova sa zapne nejaké iné
    audio.onended = function () {
      selectSound();
      delete audio;
    };
}