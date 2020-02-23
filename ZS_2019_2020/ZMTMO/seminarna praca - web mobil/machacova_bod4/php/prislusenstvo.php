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

<body>

	<?php $name = basename(__FILE__, ".php");
	require "../html/header.html"; ?>

	<div class="container">

		<?php
		require "../html/nav_prislusenstvo.html";
		?>

		<div class="text_prislusenstvo">
			<p>
				<?php {
					echo $pri_paragraph1;
				}
				?>
			</p>
			<p>
				<?php {
					echo $pri_paragraph2;
				}
				?>
			</p>
		</div>

	</div>

	<?php
	require "../html/footer.html";
	?>

</body>

</html>