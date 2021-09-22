function removeTable() {
    var rows = document.querySelector("table").rows.length;
    console.log(rows);
    for(i = 2;i<rows;i++){
      document.querySelector("tbody").deleteRow(2);
    }
}