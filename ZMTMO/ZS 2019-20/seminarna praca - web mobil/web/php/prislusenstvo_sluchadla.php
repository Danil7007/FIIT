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

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

    <!--- favicon --->
    <link rel="icon" type="image/png" href="../assets/pictures/EM_png.png">
    <link rel="stylesheet" type="text/css" href="../css/style.css" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

    <title>HUAWEI P20 Lite</title>

    <!----------------------------------------------------------------->
    <script type="text/javascript">
        function displayNextImage() {
            x = (x === images.length - 1) ? 0 : x + 1;
            document.getElementById("pris_sluchadla").src = images[x];
        }

        function displayPreviousImage() {
            x = (x <= 0) ? images.length - 1 : x - 1;
            document.getElementById("pris_sluchadla").src = images[x];
        }

        function startTimer() {
            setInterval(displayNextImage, 2500);
        }

        var images = [],
            x = -1;
        images[0] = "../assets/pictures/sluchatka_stuple.png";
        images[1] = "../assets/pictures/sluchatka_jack_02.png";
    </script>
    <!----------------------------------------------------------------->

</head>

<body onload="startTimer()">

    <!--- vyber jazyka --->
    <?php if ($lang == "sk") {
        require "./translator_sk.php";
    } elseif ($lang == "en") {
        require "./translator_en.php";
    }
    ?>

    <?php $name = basename(__FILE__, ".php");
    require "../html/header.html"; ?>

    <div class="container">

    <?php
        require "../html/nav_prislusenstvo.html";
        ?>

        <img id="pris_sluchadla" src="../assets/pictures/sluchatka_stuple.png">

        <div class="text_prislusenstvo">
            <div>
                <h2 class="intro_nadpis" style="text-align: left;">
                    <?php {
                        echo $pri_sony;
                    }
                    ?>
                </h2>
            </div>
            <p>
                <?php {
                    echo $pri_paragraph3;
                }
                ?>
            </p>
            <p>
                <strong>
                    <?php {
                        echo $pri_klucove;
                    }
                    ?>
                </strong>
            </p>
            <ul style="margin-left:5%;">
                <li>
                    <?php {
                        echo $pri_sl1;
                    }
                    ?>
                </li>
                <li>
                    <?php {
                        echo $pri_sl2;
                    }
                    ?>
                </li>
                <li>
                    <?php {
                        echo $pri_sl3;
                    }
                    ?>
                </li>
                <li>
                    <?php {
                        echo $pri_sl4;
                    }
                    ?>
                </li>
                <li>
                    <?php {
                        echo $pri_sl5;
                    }
                    ?>
                </li>
            </ul>

        </div>

        <a x-ms-format-detection="none" target="_new" href="https://www.alza.sk/sony-mdr-ex155ap-biele-d5226649.htm">
            <?php {
                echo $pri_sl_link;
            }
            ?>
        </a>

    </div>

    <?php
    require "../html/footer.html";
    ?>

</body>

</html>