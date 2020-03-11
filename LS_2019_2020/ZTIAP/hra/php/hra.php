<?php
?>

<!DOCTYPE html>
    <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <link rel="stylesheet" type="text/css" href="../css/style.css">
        </head>
        <body onload="init()">

            <header>
                <h1 class = "nadpis" >W H A C K - A - P U S</h1>
            </header>

            <canvas id="myCanvas" ></canvas>
            <!---<script src="../js/startGame.js"></script>
            <script src="../js/updateGameArea.js"></script>
            <script src="../js/gameArea.js"></script>
            <script src="../js/loadMenu.js"></script>--->
            <script src="../js/script.js"></script>

            <?php
                if (file_exists("../score.txt")) {
                    $score = file("../score.txt", FILE_IGNORE_NEW_LINES);
                }
            ?>

                <table>
                    <tr>
                        <th>
                            best score
                        </th>
                    </tr>
                    <tr>
                        <td>
                            date & score
                        </td>
                    </tr>

                    <?php
                    if (!empty($score)) {
                        foreach ($score as $s) {
                            echo "<tr>"."<td>" . $s . "</td>"."</tr>";
                        }
                    } else {
                        echo "Nie sú k dispozícií skóre";
                    }
                    ?>

                </table>
            

            <h1 class="credits">V01.001 (C) EMMA MACHACOVA </br> MUSIC BY TOBBY FOX</h1>

            
        </body>

</html>
