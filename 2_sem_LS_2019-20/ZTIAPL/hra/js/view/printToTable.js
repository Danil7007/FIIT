function printToTable() {
    removeTable();
    // získanie elementu tabulky z html
    var table = document.querySelector("tbody");
  
    // pre každý element v poli skore vytvor nový riadok v tabulke
    for (var i = 0; i < score.values.length; i++) {
      if (score.values[i].date != null && score.values[i].score != null) {
        // vytvorenie tr a td
        var row = document.createElement("tr");
        var cell = document.createElement("td");
  
        // vloženie skóre do políčka v správnom tvare
        cell.textContent =
          score.values[i].date +
          " " +
          score.values[i].score +
          " Mode: " +
          score.values[i].gameMode;
  
        // vloženie políčka (a riadku) do html
        row.appendChild(cell);
        table.appendChild(row);
      }
    }
}