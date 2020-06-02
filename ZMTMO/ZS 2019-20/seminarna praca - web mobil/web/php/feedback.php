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


</head>

<body>

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

		<div>
			<h2 class="intro_nadpis">
				<?php {
					echo $fdb_feedback;
				} ?>
			</h2>
		</div>

		<form action="/action_page.php">
			<fieldset>
				<legend>
					<?php {
						echo $fdb_legend;
					} ?>
				</legend>
				<p>
					<?php {
						echo $fdb_meno;
					} ?>
				</p>
				<input type="text" name="firstname" placeholder="Meno" required><br>
				<p>
					<?php {
						echo $fdb_priezvisko;
					} ?>
				</p>
				<input type="text" name="lastname" placeholder="Priezvisko" required><br><br>
				<p>
					<?php {
						echo $fdb_nazor;
					} ?>
				</p>
				<input id="nazor" type="text" placeholder="Prosím vyplniť" name="nazor" required>
				<br>
				<input id="odoslat" type="submit" value="OK">
			</fieldset>
		</form>

	</div>

	<?php
	require "../html/footer.html";
	?>

</body>

</html>