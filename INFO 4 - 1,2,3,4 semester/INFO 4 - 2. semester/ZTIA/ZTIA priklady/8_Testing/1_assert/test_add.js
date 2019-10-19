assert(add(2,2)==4, "01 Chyba sčítania vo funkcii add(a, b)")
assert(add(3)==undefined, "02 Funk. add má vrátiť undefined")
assert(add(2,2,2)==4, "Funkcia add má sčítať len prvé dva parametre")
assert(add("2", "3")==undefined, "Funkcia má sčítať len čísla")
