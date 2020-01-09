<?php 
if (!empty($_POST["firstname"]) OR !empty($_POST["lastname"]) OR !empty($_POST["text"])){
    $firstname = $_POST["firstname"];
    $lastname = $_POST["lastname"];
    $text = $_POST["nazor"];
    $date = date("h:i:s a Y/m/d");

    $komentar = $date." - ".$lastname." ".$firstname." : ".$text."\n";
    $kom_subor = fopen("komentare.txt", "a") OR die(":(");

    fwrite($kom_subor, $komentar);
    fclose($kom_subor);
}
header("Location:{$_SERVER["HTTP_REFERER"]}");
?>