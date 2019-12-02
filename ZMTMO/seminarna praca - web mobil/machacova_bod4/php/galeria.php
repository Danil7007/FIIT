<?php
require "./translator_sk.php";
session_start();
if(isset($_SESSION["lang"]) OR !empty($_SESSION["lang"])){
    $lang = $_SESSION["lang"];
}
else{
    $lang = "sk";
}

$files = scandir("../assets/pictures");
$images = array();
foreach($files as $a){
    if(!empty($a)){
        $images[] = $a;
    }
}
?>
<!DOCTYPE html>

<html lang="sk">

<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

	<!--- favicon --->
	<link rel="icon" type="image/png" href="../assets/pictures/EM_png.png">
    <link rel="stylesheet" type="text/css" href="../css/style.css" />
    <link rel="stylesheet" type="text/css" href="../css/galeria.css" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0" />

	<title>HUAWEI P20 Lite</title>

</head>

<body>

	<?php $name=basename(__FILE__, ".php"); require "../html//header.html"?>

	<div class="container">

		<article id="flex">
            <?php 
            $e = 0;
                foreach($files as $i){
                    echo '<img id="'.$e.'" src="../assets/pictures/'.$i.'">';
                    ++$e;
                }
            ?>


		</article>
	</div>
	
	<footer>
		<p> Copyright © 2019 Emma Macháčová. </p>
	</footer>

</body>

</html>