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
		<div>
			<h2 class="intro_nadpis">
				<?php {
					echo $index_uvod;
				} ?>
			</h2>
		</div>

		<img id="uvodna_fotka" src="../assets/pictures/mobil_front.png">

		<p>
			<?php {
				echo $index_paragraph1;
			}
			?>
		</p>
		<p>
			<?php {
				echo $index_paragraph2;
			}
			?>
		</p>
		<p>
			<?php {
				echo $index_paragraph3;
			}
			?>
		</p>
		<p>
			<?php {
				echo $index_paragraph4;
			}
			?>
		</p>
		<p>
			<?php {
				echo $index_paragraph5;
			}
			?>
		</p>

		<h2 class="intro_nadpis">
			<?php {
				echo $index_zobrazenie;
			}
			?>
		</h2>

		<p>
			<?php {
				echo $index_paragraph6;
			}
			?>
		</p>
		<p>
			<?php {
				echo $index_paragraph7;
			}
			?>
		</p>

		<h2 class="intro_nadpis">
			<?php {
				echo $index_bateria;
			}
			?>
		</h2>

		<img id="kamera" src="../assets/pictures/mobil_back_kamera.png">

		<p>
			<?php {
				echo $index_paragraph8;
			}
			?>
		</p>

		<h2 class="intro_nadpis">
			<?php {
				echo $index_fotoaparat;
			}
			?>
		</h2>

		<p>
			<?php {
				echo $index_paragraph9;
			}
			?>
		</p>
		<p>
			<?php {
				echo $index_paragraph10;
			}
			?>
		</p>

		<h2 class="intro_nadpis">
			<?php {
				echo $index_hry;
			}
			?>
		</h2>

		<video id="cod" controls poster="../assets/pictures/interface_cod.jpg">
			<source src="../assets/video/cod.mp4" type="video/mp4">
		</video>

		<p>
			<?php {
				echo $index_paragraph11;
			}
			?>
		</p>

		<?php
		require "../html/footer.html";
		?>

</body>

</html>