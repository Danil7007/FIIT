<?php

session_start();
if (isset($_SESSION["lang"]) or !empty($_SESSION["lang"])) {
	$lang = $_SESSION["lang"];
} else {
	$lang = "sk";
}
if (file_exists("komentare.txt")) {
	$komentare = file("komentare.txt", FILE_IGNORE_NEW_LINES);
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

<body>

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

		<form action="action_page.php" method="POST">
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
				<input type="text" name="firstname" placeholder="<?php {
																		echo $fdb_meno;
																	} ?>" required><br>
				<p>
					<?php {
						echo $fdb_priezvisko;
					} ?>
				</p>
				<input type="text" name="lastname" placeholder="<?php {
																	echo $fdb_priezvisko;
																} ?>" required><br><br>
				<p>
					<?php {
						echo $fdb_nazor;
					} ?>
				</p>
				<input id="nazor" type="text" placeholder="<?php {
																echo $fdb_pf;
															} ?>" name="nazor" required>
				<br>
				<input id="odoslat" type="submit" value="OK">
			</fieldset>
		</form>
		<br>
		<h2 class="intro_nadpis">
			<?php {
				echo $fdb_komentare;
			} ?>
		</h2>
		<?php
		if (!empty($komentare)) {
			foreach ($komentare as $k) {
				echo "<p>" . $k . "</p>";
			}
		} else {
			echo "Nie sú k dispozícií komentáre";
		}
		?>

	</div>

	<?php
	require "../html/footer.html";
	?>

</body>

</html>