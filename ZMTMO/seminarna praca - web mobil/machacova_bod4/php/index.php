<?php
require "./translator_sk.php";
session_start();
if(isset($_SESSION["lang"]) OR !empty($_SESSION["lang"])){
    $lang = $_SESSION["lang"];
}
else{
    $lang = "sk";
}
?>

<!DOCTYPE html>

<html lang=<?php echo $lang;?>>

<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

	<!--- favicon --->
	<link rel="icon" type="image/png" href="../assets/pictures/EM_png.png">
	<link rel="stylesheet" type="text/css" href="../css/style.css" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0" />

	<title>HUAWEI P20 Lite</title>


</head>

<body>

    <?php $name=basename(__FILE__, ".php");  require "../html/header.html";?>

	<div class="container">
		<div> 
			<h2 class="intro_nadpis">
            <?php if($lang == "sk"){
                    echo $uvod;
                    } 
                    elseif($lang == "en"){
                    echo $uvod_en
                    ;
                    }
                ?>
			</h2>
		</div>

		<img id="uvodna_fotka" src="../assets/pictures/mobil_front.png">

		<p>
				
		</p>
		<p>
				<?php if($lang == "sk"){
                    echo $paragraph;
                    } 
                    elseif($lang == "en"){
                    echo $paragraph_en;
                    }
                ?>
		</p>
		<p>
				Napriek svojej malej veľkosti má Huawei P20 Lite 5,84-palcový displej, vďaka prístupu na 
				celú hranu. Prejavuje sa to v trochu netradičnom pomere strán 19: 9.
		</p>
		<p>
				Rovnako ako zvyšok sveta smartfónov, aj spoločnosť Huawei prešla na filozofiu dizajnu na celej 
				obrazovke. Model P20 Lite má pomerne malú bradu, minimálne bočné rámy a výrez v hornej časti 
				displeja, ktorý obsahuje prednú kameru a slúchadlo - Huawei P20 Lite môže používať snímače 
				fotoaparátu uložené v tomto záreze na čítanie vašej tváre a odomknutie telefónu. 
		</p>
		<p>
				Aj keď sa zdá, že funkcia Face Unlock pracuje rýchlo a presne (dokonca aj v tme, na rozdiel 
				od iných rádií Face ID), nezdá sa, že by bola taká vyspelá alebo bezpečná ako riešenie 
				spoločnosti Apple.
		</p>
		<p>
				Stále však nemožno poprieť, že riešenie spoločnosti Huawei pracuje rýchlo na odomknutí telefónu. 
				Nastavte zariadenie P20 Lite tak, aby sa prebudilo, keď ho vyzdvihnete, a nebudete musieť vôbec 
				premýšľať o jeho odomknutí.
		</p>
		
		<h2 class="intro_nadpis">
				ZOBRAZENIE
		</h2>

		<p>
				Okrajový displej s uhlopriečkou 5,84 palca, rozlíšenie 1080 x 2280.
		</p>
		<p>
				Aj keď to umožňuje pôsobivé plátno pri listovaní domácou obrazovkou a natívnymi aplikáciami, zdá 
				sa, že nie vždy má praktické využitie. Mnohé aplikácie zostávajú pre tento druh displeja 
				neoptimalizované, s Androidom pochopiteľne pomalším ako iOS.
		</p>
		<p>
				YouTube vám v predvolenom nastavení ponúka pravidelný obdĺžnikový obrázok s hrubými čiernymi 
				okrajmi na oboch stranách.
		</p>
		<p>
				Hry nie sú vždy úplne optimalizované pre tento druh zobrazenia.
		</p>
		<p>
				Napriek tomu je samotný displej schopný a atraktívny. Je to LTPS TFT, čo znamená, že je ostrý a 
				presný, aj keď mu chýba kontrast AMOLED. Ďalšou vecou, ktorú P20 Lite zdieľa s P20, je rozlíšenie. 
				Zatiaľ čo vlajková loď telefónov s Androidom často vyhľadáva rozlíšenie QHD, model Huawei P20 išiel 
				s rozlíšením 1080 x 2240 a neutrpel na diaľku. P20 Lite nasleduje oblek s obrazovkou 1080 x 2280 a 
				je dosť dobrý na to, aby bol schopný vykonávať všetky úlohy.
		</p>

		<h2 class="intro_nadpis">
				BATÉRIA
		</h2>

		<img id="kamera" src="../assets/pictures/mobil_back_kamera.png">
		
		<p>
				3 000 mAh batéria a rýchle nabíjanie vám dá 40% za 30 minút.
				Huawei P20 Lite obsahuje batériu 3 000 mAh, čo je pre telefón tohto druhu normálne. 
				Je to rovnaké ako podobne vybavené Honor 9 Lite , s predvídateľne podobnými výsledkami.				
		</p>
		<p>
				Spoločnosť Huawei taktiež poskytuje rozsiahlu sadu nástrojov na optimalizáciu, 
				ktoré vám pomôžu doladiť vaše nastavenie, zamerať sa na aplikácie a návyky náročné na energiu. 
				Aj keď sa snažíte dosiahnuť celý deň, môžete s tým urobiť niekoľko vecí - vrátane dvoch režimov 
				úspory energie a schopnosti znížiť rozlíšenie obrazovky.
		</p>

		<h2 class="intro_nadpis">
				FOTOAPARÁT
		</h2>

		<p>
				Kamera s rozlíšením 16 MP + 2 MP umožňuje režim širokouhlej clony, objektív má AR.
				Pri modeli Huawei P20 Lite nezískate ten istý režim AI s fotoaparátom ako model Huawei P20 
				a Huawei P20 Pro , takže si budete musieť sami zvoliť optimálne nastavenia pre fotografovanie.
				Spoločnosť Huawei vybavila model P20 Lite nastavením dvojitého fotoaparátu. Ako predtým, 
				sekundárna šošovka 2MP je tu čisto na to, aby pomohla primárnej šošovke 16MP s informáciami 
				o hĺbke, hlavne pre zahrnutý režim so širokou clonou.				
		</p>
		<p>
				Rovnako ako v prípade Honor 9 Lite a Honor 7X vám režim so širokou clonou umožňuje upraviť úroveň 
				efektu bokeh na vašich fotografiách po nasnímaní, medzi f / 0,95 a f / 16.
				Okrem obvyklých fotografických nastavení - vrátane režimu Pro na jemné doladenie každého 
				jednotlivého nastavenia - je k dispozícii vyhradený režim objektívu AR. Ak nič iné, je to ďalší 
				príklad toho, ako solídny softvér na sledovanie tváre spoločnosti Huawei je.				
		</p>
		<p>
				Získate tiež režim vodotlače, ktorý pečiatkuje každý obrázok jeho umiestnením a časom štýlovým 
				písmom a režim skenovania dokumentu, ktorý rýchlo nájde a zarovná text pre rýchle uchovávanie 
				záznamov.
		</p>

		<h2 class="intro_nadpis">
				FILMY, HUDBA A HRY
		</h2>

		<p>
				Väčšina médií nevyužíva širšiu obrazovku
				Konektor pre slúchadlá a jeden silný reproduktor
				64 GB úložného priestoru a microSD až 256 GB				
		</p>

		<video id="cod" controls poster="../assets/pictures/interface_cod.jpg">
			<source src="../assets/video/cod.mp4" type="video/mp4">
		  Your browser does not support the video tag.
		</video>

		<p>
				Vo väčšine prípadov Huawei jednoducho v podstate predstiera, že priestor na oboch stranách 
				zárezu na hornej strane obrazovky neexistuje. PUBG, Bullet Hell Monday, Fancy Pants Adventure, 
				Data Wing, Oceanhorn, NOVA Legacy, Guns of Boom a aj Super Mario Run pracujú týmto spôsobom - 
				žiadna hra nevyužila celú obrazovku. Herný výkon je však jednoznačne ohromujúci. 
		</p>
		<p>
				Čo sa týka videa, Netflix prijíma rovnaký prístup ako vyššie uvedené hry, zatiaľ čo služba 
				YouTube prehráva videá vo svojom pôvodnom formáte 16: 9 s ešte silnejšími čiernymi okrajmi.
				Pokiaľ ide o audio, negatívom je, že dostanete jeden reproduktor, ktorý takmer úplne nemá basy. 
				Je to dosť jasné, ale zvuk je zreteľne nevyvážený.
				Pozitívnejšie je, že tu je 3,5 mm konektor pre slúchadlá, čo je viac, ako sa dá povedať pre Huawei 
				P20 alebo Huawei P20 Pro .
				Všeobecnejšie povedané, získate tu 64 GB interného ukladacieho priestoru, čo je dobré pre veľa 
				médií. Ak to nestačí, karta microSD podporuje až 256 GB.				
		</p>
        
        <?php
        require "../html/footer.html";
        ?>

</body>

</html>
