#!/bin/bash
#
# Meno: 	Machacova
# Kruzok: 	Piatok: 8:00 - Ing. J. Petrik
# Datum: 	01.12.2021
# Zadanie:	zadanie 07
# 
# Text zadania:
#
# V zadanych adresaroch uvedenych ako argumenty najdite textove subory,
# v ktorych obsahu sa vyskytuje ich meno. Prehladavajte vsetky zadane adresare
# a aj ich podadresare.
# Ak nebude uvedena ako argument ziadna cesta, prehladava sa aktualny pracovny
# adresar (teda .).
# Ak bude skript spusteny s prepinacom -d <hlbka>, prehlada adresare len do
# hlbky <hlbka> (vratane). Hlbka znamena pocet adresarov na ceste medzi
# startovacim adresarom a spracovavanym suborom. Hlbka 1 znamena, ze bude
# prezerat subory len v priamo zadanych adresaroch.
#
# Syntax:
# zadanie.sh [-h][-d <hlbka>] [cesta ...]
#
# Vystup ma tvar:
# Output: '<cesta k najdenemu suboru> <pocet riadkov s menom suboru>'
#
# Priklad vystupu:
# Output: '/public/testovaci_adresar/testdir1/test 19'
#
# Program musi osetrovat pocet a spravnost argumentov. Program musi mat help,
# ktory sa vypise pri zadani argumentu -h a ma tvar:
# Meno programu (C) meno autora
#
# Usage: <meno_programu> <arg1> <arg2> ...
#    <arg1>: xxxxxx
#    <arg2>: yyyyy
#
# Parametre uvedene v <> treba nahradit skutocnymi hodnotami.
# Ked ma skript prehladavat adresare, tak vzdy treba prehladat vsetky zadane
# adresare a vsetky ich podadresare do hlbky.
# Pri hladani maxim alebo minim treba vzdy najst maximum (minimum) vo vsetkych
# zadanych adresaroch (suboroch) spolu. Ked viacero suborov (adresarov, ...)
# splna maximum (minimum), treba vypisat vsetky.
#
# Korektny vystup programu musi ist na standardny vystup (stdout).
# Chybovy vystup programu by mal ist na chybovy vystup (stderr).
# Chybovy vystup musi mat tvar (vratane apostrofov):
# Error: 'adresar, subor, ... pri ktorom nastala chyba': popis chyby ...
# Ak program pouziva nejake pomocne vypisy, musia mat tvar:
# Debug: vypis ...
#
# Poznamky: (Kedze maximum a minimum v tomto zadani nie je spomenute, neimplementovala som ho.. Plus riadok 71 - tak som to chcela mat ale robi to chybu v SC, ktora sa sice ma podla dokumentacie ignorovat, ale bolo by to proti zadaniu)
#
# Riesenie:

usage () {
	echo "$0 (C) Emma Machacova"
	echo ""
	echo "V zadanych adresaroch uvedenych ako argumenty najde textove subory, v ktorych obsahu sa vyskytuje ich meno."
	echo "Prehladava vsetky zadane adresare a aj ich podadresare."
	echo "Ak nebude uvedena ako argument ziadna cesta, prehladava sa aktualny pracovny adresar (teda .)."
	echo ""
	echo "Usage: $0    [-h][-d <hlbka>] [cesta ...]"
	echo ""
	echo "-h:          Vypisanie help-u"
	echo "-d <hlbka>:  Ak bude skript spusteny s prepinacom -d <hlbka>, prehlada adresare len do hlbky <hlbka> (vratane)."
	echo "             Hlbka znamena pocet adresarov na ceste medzi startovacim adresarom a spracovavanym suborom."
	echo "             Hlbka 1 znamena, ze bude prezerat subory len v priamo zadanych adresaroch."
}

# vystupy
# OUTPUT_S="Output: '%s %s'\n"  # a takto by bol line 112 keby to nerobilo SC2059: grep -- "$(basename "$LINE")" "$LINE" >/dev/null && printf "$OUTPUT_S" "$LINE" "$(wc -l < "$LINE")"	
ERROR_ARG="Error: missing argument."
ERROR_OPT="Error: invalid option."

while getopts ':hd:' ARG; do
    case "$ARG" in
    h)      usage
			exit 0;;			# navratova hodnota
    d)      DEPTH=$OPTARG;;
    :)      echo "$ERROR_ARG" >&2
            usage >&2
            exit 1;;
    *)      echo "$ERROR_OPT" >&2
            usage >&2
            exit 1;;
    esac
done
unset ARG 

[ -z "$OPTIND" ] || shift $((OPTIND-1))		# test zaruci ze optind je nastaveny (vacsi ako 0)
WORKDIR=${1:-"."}							# ak existuje workdir, ulozi ho, inak nastavi .

# output findu pojde do premennej 								
[ -z "$DEPTH" ] && FIND_OUTPUT=$(find "$WORKDIR" -type f 2>&1)						# ak neexistuje depth	
# vrati true ak je to cislo, inak chyba
[ -z "$DEPTH" ] || [ "$DEPTH" -eq "$DEPTH" ] 2>/dev/null || { echo "Error: depth parameter '$DEPTH' is not number" >&2; usage >&2; exit 1; }
[ -z "$DEPTH" ] || FIND_OUTPUT=$(find "$WORKDIR" -maxdepth "$DEPTH" -type f 2>&1)	# ak existuje

# navratova hodnota
EXIT_VALUE=0

# while sa spusti len ked FO nebude prazdny
[ -z "$FIND_OUTPUT" ] ||\
while { IFS=$'\n' read -r LINE; } do 				# citanie lajnov vo FIND_OUTPUT
	# berie sa pravdivostna hodnota grepu, obsah suboru sa da do prec	
	# kontroluje sa, ci existuje LINE ako subor (lajna co zacina find: a nie je to subor)
	if { echo "$LINE" | grep "^find:*" >/dev/null && ! [ -a "$LINE" ]; }; then	
		echo "$LINE" | sed -r 's/^find:(.*)$/Error:\1/';
		EXIT_VALUE=1
	else 
		# -- lebo ak v nazve suboru su -nieco aby to nebralo ako flag
		grep -- "$(basename "$LINE")" "$LINE" >/dev/null && printf "Output: '%s %s'\n" "$LINE" "$(wc -l < "$LINE")"	
	fi
done < <(echo "$FIND_OUTPUT")	# redirekcia na konci zoberie std vystup zatvorky a da ju tam - aby to nebolo na zaciatku cez pajpu a subshell a pamatalo si to EXIT_VALUE

exit "$EXIT_VALUE"