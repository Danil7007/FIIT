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
            document.getElementById("huawei").src = images[x];
            document.getElementById("alcatel").src = obr[x];
        }

        function displayPreviousImage() {
            x = (x <= 0) ? images.length - 1 : x - 1;
            document.getElementById("huawei").src = images[x];
            document.getElementById("alcatel").src = obr[x];
        }

        function startTimer() {
            setInterval(displayNextImage, 3500);
        }

        var images = [],
            x = -1;
        images[0] = "../assets/pictures/mobil_back.png";
        images[1] = "../assets/pictures/mobil_front.png";

        var obr = [],
            x = -1;
        obr[0] = "../assets/pictures/alcatel_back.png";
        obr[1] = "../assets/pictures/alcatel.png";
    </script>
    <!----------------------------------------------------------------->

</head>

<body onload="startTimer()">

    <?php $name = basename(__FILE__, ".php");
    require "../html/header.html"; ?>

    <div class="container">

        <!-- VRCHNY NADPIS -->
        <div>
            <h2 class="intro_nadpis" style="text-align: center;">
                <?php {
                    echo $porovnanie;
                } ?>
            </h2>
        </div>

        <!-- NADPISY MOBILOV -->
        <div>
            <div class="mobil1" style="border: 1px solid white;">
                <h2 class="intro_nadpis" style="text-align: center; margin-bottom: 0;">
                    <?php {
                        echo $hw;
                    } ?>
                </h2>
            </div>
            <div class="dropdown">
                <div class="mobil2" style="border: 1px solid white;">
                    <div class="dropbtn">
                        <h2 class="intro_nadpis" style="text-align: center; margin-bottom: 0;">
                            <?php {
                                echo $alc;
                            } ?>
                        </h2>
                        <div class="dropdown-content">
                            <a href="porovnania_alcatel.php"><?php {
                                                                    echo $alc;
                                                                } ?></a>
                            <a href="#"><?php {
                                            echo $unsp;
                                        } ?></a>
                            <a href="#"><?php {
                                            echo $unsp;
                                        } ?></a>
                        </div>
                    </div>
                </div>
            </div>
            </br>
            <!--------------------->

            <!------- FOTKY ------->
            <div>
                <div class="mobil1">
                    <!-------SKRIPT-------->
                    <img id="huawei" src="../assets/pictures/mobil_back.png">
                    <!--------------------->
                </div>
                <div class="mobil2">
                    <!-------SKRIPT-------->
                    <img id="alcatel" src="../assets/pictures/alcatel_back.png">
                    <!--------------------->
                </div>
            </div>
            <!--------------------->
            <div>
                <table style="width: 100%;">

                    <tr class="f_riadok">
                        <th style="width:16%;"><?php {
                                                    echo $th1;
                                                } ?></th>
                        <td style="width:16%;"><?php {
                                                    echo $th1_1;
                                                } ?></td>
                        <td style="width:16%;"><?php {
                                                    echo $hw1;
                                                } ?></td>
                        <td class="stred"> </td>
                        <th style="width:16%;"><?php {
                                                    echo $th1;
                                                } ?></th>
                        <td style="width:16%;"><?php {
                                                    echo $th1_1;
                                                } ?></td>
                        <td style="width:16%;"><?php {
                                                    echo $alc1;
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
                        <td class="stred"> </td>
                        <th><?php {
                                echo $th2;
                            } ?></th>
                        <td><?php {
                                echo $th2_1;
                            } ?></td>
                        <td><?php {
                                echo $alc2;
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
                        <td class="stred"> </td>
                        <th></th>
                        <td><?php {
                                echo $th2_2;
                            } ?></td>
                        <td><?php {
                                echo $alc3;
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
                        <td class="stred"> </td>
                        <th><?php {
                                echo $th3;
                            } ?></th>
                        <td><?php {
                                echo $th3_1;
                            } ?></td>
                        <td><?php {
                                echo $alc4;
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
                        <td class="stred"> </td>
                        <th></th>
                        <td><?php {
                                echo $th3_2;
                            } ?></td>
                        <td><?php {
                                echo $alc5;
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
                        <td class="stred"> </td>
                        <th></th>
                        <td><?php {
                                echo $th3_3;
                            } ?></td>
                        <td><?php {
                                echo $alc6;
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
                        <td class="stred"> </td>
                        <th></th>
                        <td><?php {
                                echo $th3_4;
                            } ?></td>
                        <td><?php {
                                echo $alc7;
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
                        <td class="stred"> </td>
                        <th><?php {
                                echo $th4;
                            } ?></th>
                        <td><?php {
                                echo $th4_1;
                            } ?></td>
                        <td><?php {
                                echo $alc8;
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
                        <td class="stred"> </td>
                        <th></th>
                        <td><?php {
                                echo $th4_2;
                            } ?></td>
                        <td><?php {
                                echo $alc9;
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
                        <td class="stred"> </td>
                        <th></th>
                        <td><?php {
                                echo $th4_3;
                            } ?></td>
                        <td><?php {
                                echo $alc10;
                            } ?></td>
                    </tr>
                    <tr class="f_riadok">
                        <th><?php {
                                echo $th5;
                            } ?></th>
                        <td><?php {
                                echo $th5_1;
                            } ?></td>
                        <td><?php {
                                echo $hw11;
                            } ?></td>
                        <td class="stred"> </td>
                        <th><?php {
                                echo $th5;
                            } ?></th>
                        <td><?php {
                                echo $th5_1;
                            } ?></td>
                        <td><?php {
                                echo $alc11;
                            } ?></td>
                    </tr>
                </table>
            </div>

        </div>
    </div>

    <?php
    require "../html/footer.html";
    ?>

</body>

</html>