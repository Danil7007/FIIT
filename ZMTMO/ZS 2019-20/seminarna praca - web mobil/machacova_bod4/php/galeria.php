<?php
require "./translator_sk.php";
session_start();
if (isset($_SESSION["lang"]) or !empty($_SESSION["lang"])) {
    $lang = $_SESSION["lang"];
} else {
    $lang = "sk";
}

$files = scandir("../assets/pictures");
$images = array();
foreach ($files as $a) {
    if (!empty($a)) {
        $images[] = $a;
    }
}
?>
<!DOCTYPE html>

<html lang="sk">

<!--- vyber jazyka --->
<?php if ($lang == "sk") {
    require "./translator_sk.php";
} elseif ($lang == "en") {
    require "./translator_en.php";
}
?>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

    <!--- favicon --->
    <link rel="icon" type="image/png" href="../assets/pictures/EM_png.png">

    <link rel="stylesheet" type="text/css" href="../css/style2.css" />

    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

    <title><?php echo $hw; ?></title>

</head>

<body>

    <?php $name = basename(__FILE__, ".php");
    require "../html/header.html" ?>

    <div class="container">
        <br>
        <article>
            <?php
            $e = 0;
            foreach ($images as $i) {
                if ($i != '.' and $i != '..') {
                    echo '<img class="gallery" src="../assets/pictures/' . $i . '">';
                    ++$e;
                }
            }
            ?>
        </article>
    </div>

    <?php
    require "../html/footer.html";
    ?>

</body>

</html>