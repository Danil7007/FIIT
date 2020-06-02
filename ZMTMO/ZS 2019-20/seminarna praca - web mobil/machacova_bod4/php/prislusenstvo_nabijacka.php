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

</head>

<body onload="startTimer()">

    <?php $name = basename(__FILE__, ".php");
    require "../html/header.html"; ?>

    <div class="container">

        <?php
        require "../html/nav_prislusenstvo.html";
        ?>

        <img id="pris_nabijacka" src="../assets/pictures/nabijacka.png">

        <div class="text_prislusenstvo">
            <div>
                <h2 class="intro_nadpis" style="text-align: left;">
                    <?php {
                        echo $pri_nabijacka;
                    }
                    ?>
                </h2>
            </div>
            <p>
                <?php {
                    echo $pri_paragraph6;
                }
                ?>
                <p>
                    <strong>
                        <?php {
                            echo $pri_klucove3;
                        }
                        ?>
                        <p>
                    </strong>
                </p>
                <ul style="margin-left:5%">
                    <li>
                        <?php {
                            echo $pri_na1;
                        }
                        ?>
                    </li>
                    <li>
                        <?php {
                            echo $pri_na2;
                        }
                        ?>
                    </li>
                    <li>
                        <?php {
                            echo $pri_na3;
                        }
                        ?>
                    </li>
                    <li>
                        <?php {
                            echo $pri_na4;
                        }
                        ?>
                    </li>
                    <li>
                        <?php {
                            echo $pri_na5;
                        }
                        ?>
                    </li>
                    <li>
                        <?php {
                            echo $pri_na6;
                        }
                        ?>
                    </li>
                    <li>
                        <?php {
                            echo $pri_na7;
                        }
                        ?>
                    </li>
                </ul>

        </div>

        <a x-ms-format-detection="none" target="_new" href="https://www.alza.cz/huawei-original-cestovni-dobijec-cp84-vcetne-usb-c-datoveho-kabelu-white-d5550364.htm?layoutAutoChange=1">
            <?php {
                echo $pri_na_link;
            }
            ?>
        </a>

    </div>

    <?php
    require "../html/footer.html";
    ?>

</body>

</html>