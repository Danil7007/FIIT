// efekt capnutia
function playSoundEffect() {
    soundEffect = new Audio("../assets/music/slap.mp3");
    soundEffect.volume = 0.3;
    if (gameArea.mute == 1) {
      soundEffect.muted = true;
    }
    soundEffect.play();
    soundEffect.onended = function () {
      delete soundEffect;
    };
}