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
					echo $itf_zvonenia;
				}
				?>
			</h2>
		</div>

		<div class="flexbox">

			<div class="item">
				<p>
					<?php {
						echo $r1;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Bounce.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r2;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Cartoon.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r3;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Classic_Bell.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r4;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Day_lily.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r5;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Digital_Ringtone.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r6;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Dream.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r7;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Dream_It_Possible.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r8;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Eastern.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r9;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Flipped.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r10;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Flow.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r11;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Forest_Day.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r12;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Free.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r13;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Harp.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r14;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Hello_Ya.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
			<div class="item">
				<p>
					<?php {
						echo $r15;
					}
					?>
				</p>
				<audio controls>
					<source src="../assets/ringtones/ringtones/Huawei_Tune_Clean.ogg" type="audio/ogg">
					<?php {
						echo $itf_support;
					}
					?>
				</audio>
			</div>
		</div>

		<div>
			<h2 class="intro_nadpis">
				<?php {
					echo $itf_rozhranie;
				}
				?>
			</h2>
		</div>

		<p>
			<?php {
				echo $itf_paragraph1;
			}
			?>
		</p>

		<div style="margin-top: 7%">
			<img style="width: 31%; margin-left: 4.5%;" src="../assets/pictures/interface02.jpg">
			<img style="width: 31%;" src="../assets/pictures/interface01.jpg">
			<img style="width: 31%; margin-right: auto;" src="../assets/pictures/interface03.jpg">
		</div>


	</div>

	<?php
	require "../html/footer.html";
	?>

</body>

</html>