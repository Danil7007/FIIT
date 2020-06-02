<?php

session_start();
if (isset($_SESSION["lang"]) or !empty($_SESSION["lang"])) {
    $lang = $_SESSION["lang"];
} else {
    $lang = "sk";
}
?>

<!DOCTYPE html>

<html lang=<?php echo $lang; ?>>

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
    <link rel="stylesheet" type="text/css" href="../css/style.css" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

    <title><?php echo $hw; ?></title>

    <!----------------------------------------------------------------->
    <script type="text/javascript">
        function displayNextImage() {
            x = (x === images.length - 1) ? 0 : x + 1;
            document.getElementById("parametre").src = images[x];
        }

        function displayPreviousImage() {
            x = (x <= 0) ? images.length - 1 : x - 1;
            document.getElementById("parametre").src = images[x];
        }

        function startTimer() {
            setInterval(displayNextImage, 2500);
        }

        var images = [],
            x = -1;
        images[0] = "../assets/pictures/mobil_front.png";
        images[1] = "../assets/pictures/mobil_back.png";
        images[2] = "../assets/pictures/mobil_front_02.png";
    </script>
    <!----------------------------------------------------------------->

</head>

<body onload="startTimer()">

    <?php $name = basename(__FILE__, ".php");
    require "../html/header.html"; ?>

    <div class="container">

        <h2 class="intro_nadpis" style="float:left;">
            <?php {
                echo $sp;
            } ?>
        </h2>

        <!-------SKRIPT-------->
        <img id="parametre" class="huawei" src="../assets/pictures/mobil_front.png">
        <!--------------------->

        <article style="width: 59%; float:left">
            <table class="parametre" style="width: 100%;">

                <tr class="f_riadok">
                    <th><?php {
                            echo $th1;
                        } ?></th>
                    <td><?php {
                            echo $th1_1;
                        } ?></td>
                    <td><?php {
                            echo $hw1;
                        } ?></td>
                </tr>
                <tr>
                    <th><?php {
                            echo $th2;
                        } ?></th>
                    <td><?php {
                            echo $th2_1;
                        } ?></td>
                    <td><?php {
                            echo $hw2;
                        } ?></td>
                </tr>
                <tr>
                    <th></th>
                    <td><?php {
                            echo $th2_2;
                        } ?></td>
                    <td><?php {
                            echo $hw3;
                        } ?></td>
                </tr>
                <tr class="f_riadok2">
                    <th><?php {
                            echo $th3;
                        } ?></th>
                    <td><?php {
                            echo $th3_1;
                        } ?></td>
                    <td><?php {
                            echo $hw4;
                        } ?></td>
                </tr>
                <tr class="f_riadok2">
                    <th></th>
                    <td><?php {
                            echo $th3_2;
                        } ?></td>
                    <td><?php {
                            echo $hw5;
                        } ?></td>
                </tr>
                <tr class="f_riadok2">
                    <th></th>
                    <td><?php {
                            echo $th3_3;
                        } ?></td>
                    <td><?php {
                            echo $hw6;
                        } ?></td>
                </tr>
                <tr class="f_riadok2">
                    <th></th>
                    <td><?php {
                            echo $th3_4;
                        } ?></td>
                    <td><?php {
                            echo $hw7;
                        } ?></td>
                </tr>
                <tr>
                    <th><?php {
                            echo $th4;
                        } ?></th>
                    <td><?php {
                            echo $th4_1;
                        } ?></td>
                    <td><?php {
                            echo $hw8;
                        } ?></td>
                </tr>
                <tr>
                    <th></th>
                    <td><?php {
                            echo $th4_2;
                        } ?></td>
                    <td><?php {
                            echo $hw9;
                        } ?></td>
                </tr>
                <tr>
                    <th></th>
                    <td><?php {
                            echo $th4_3;
                        } ?></td>
                    <td><?php {
                            echo $hw10;
                        } ?></td>
                </tr>
            </table>
        </article>



    </div>

    <?php
    require "../html/footer.html";
    ?>

</body>

</html>