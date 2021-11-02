/**********************************************/
/**** Snehulienka Test Set v20170319-1420 ****/
/********************************************/

/*********************/
/**** NASTAVENIA ****/
/*******************/

// nastavi mnozstvo znakov ktore sa pokusi zapisat na rolku A (n*10) min. 1200
// nastavte na nizsiu hodnotu ak by vam v Turing hadzal "Program presiahol časový limit."
#define TEST_BORDER_A_ROLL_MAX 2000

// nastavi pocet pokusov o zapisanie na rolku B (n*4 tj 2500*4 = 10k) min. 3000
// nastavte na nizsiu hodnotu ak by vam v Turing hadzal "Program presiahol časový limit."
#define TEST_BORDER_B_ROLL_MAX 5000

// nastavte na 1 pre jednoduchsie debugovanie v pripade chyb v test_vydaj_ovocia_2510
#define DBG_2513_VYDAJ_OVOCIA 0

/**********************/
/******* TESTY *******/
/********************/

#ifdef MAX_NAME_LEN
  #undef MAX_NAME_LEN
#endif
#define MAX_NAME_LEN 100

void test_novy_sklad(int rows, int cols) {
  printf("sklad [%d, %d]:\n", rows, cols); 
  novy_sklad(rows, cols);
}

void test_zisti_id(char *name, int ok) {
  int buf;
  (buf = zisti_id(name)) == ok ? printf("%s: %d - //OK\n", name, buf) : printf("%s: %d - 'WRONG (should be %d)'\n", name, buf, ok);
}

void test_prijem_ovocia(char *name, int amount, int size, int ok) {
  int buf;
  (buf = prijem_ovocia(name, amount, size)) == ok ? printf("prijem_ovocia: %s (%dks %d) = %dx - //OK\n", name, amount, size, buf) : printf("prijem_ovocia: %s (%dks %d) = %dx - 'WRONG (should be %d)'\n", name, amount, size, buf, ok);
}

void test_vydaj_ovocia(char *name, int amount, int size, int ok) {
  int buf;
  (buf = vydaj_ovocia(name, amount, size)) == ok ? printf("vydaj_ovocia: %s (%dks min size: %d)  = %dx - //OK\n", name, amount, size, buf) : printf("vydaj_ovocia: %s (%dks min size: %d)  = %dx - 'WRONG (should be %d)'\n", name, amount, size, buf, ok);
}

void test_vypis_id() {
  char name[MAX_NAME_LEN];
  int id;

  novy_sklad(4, 4);
  strcpy(name, "Psenica");
  printf("%s: %d\n", name, zisti_id(name));
  strcpy(name, "Raz");
  printf("%s: %d\n", name, zisti_id(name));
  strcpy(name, "x");
  printf("%s: %d\n", name, zisti_id(name));
  strcpy(name, "DusenyVtakopysk");
  printf("%s: %d\n", name, zisti_id(name));
  
  id = 0; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 1; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 10; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 11; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 12; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 13; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 14; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 28; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 5000; printf("vypis_id '%d': ", id); vypis_id(id);
  id = 9999; printf("vypis_id '%d': ", id); vypis_id(id); 
  vypis_sklad();
}

void test_vydaj_ovocia_2513_dbg() {
  int i, amount, size;
  char name[MAX_NAME_LEN];
  
  printf("/************* test_vydaj_ovocia_2513_dbg *************/\n");
  
  test_novy_sklad(25, 13);
  strcpy(name, "ovocie1"); amount = 3; size = 9;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie1"); amount = 3; size = 1;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie2"); amount = 3; size = 8;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie3"); amount = 3; size = 2;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie4"); amount = 3; size = 7;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie5"); amount = 3; size = 3;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie6"); amount = 3; size = 6;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie7"); amount = 3; size = 4;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie8"); amount = 3; size = 5;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie9"); amount = 3; size = 5;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie10"); amount = 3; size = 4;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie11"); amount = 3; size = 6;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie12"); amount = 3; size = 3;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie13"); amount = 3; size = 7;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie14"); amount = 3; size = 2;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie15"); amount = 3; size = 8;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie16"); amount = 3; size = 1;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie17"); amount = 3; size = 9;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie18"); amount = 3; size = 2;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie19"); amount = 3; size = 3;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie20"); amount = 3; size = 4;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie21"); amount = 3; size = 5;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie22"); amount = 3; size = 2;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie23"); amount = 3; size = 1;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  strcpy(name, "ovocie24"); amount = 4; size = 1;
  printf("prijem_ovocia: %s (%dks %d) = %dx\n", name, amount, size, prijem_ovocia(name, amount, size));
  printf("\n");
  
  for (i = 1; i <= 24; i++) {
    sprintf(name+6, "%d", i);
    printf("%s: %d\n", name, zisti_id(name));
  }
} 

void auto_test_zisti_id() {
  printf("/************* auto_test_zisti_id *************/\n");
  
  novy_sklad(4, 4);
  test_zisti_id("kiwi", 0);
  test_zisti_id("ki", 5);
  test_zisti_id("wi", 8);
  test_zisti_id("k", 11);
  test_zisti_id("i", 13);
  test_zisti_id("w", 15);
  test_zisti_id("Popokatepetl", 17);
  test_zisti_id("po", 30);
  test_zisti_id("p", 33);
  test_zisti_id("o", 35);
  test_zisti_id("PterodaktylNaCibulke", 37);
  test_zisti_id("kiwi", 0);
  test_zisti_id("Popokatepetl", 17);
  test_zisti_id("PterodaktylNaCibulke", 37);
}

void auto_jk_manual_test_vypis_id() {
  printf("/************* auto_jk_manual_test_vypis_id *************/\n");
  
  printf("\n'ak vam nefunguje dobre rolkaA a neprejde vam auto_test_zisti_id'\n");
  printf("'tak nasledujuce \"spravne vysledky\" vam velmi nepomozu'\n");
  printf("'ale ak mate dobre spraveny vypis a vypisuje vam vsetky rolky aj sklad'\n");
  printf("'tak si to mozte lahko skontrolovat aj sami'\n");
  printf("'ak nemate tak si spravte nech vam to vypisuje vsetko (a cviciaci to moze pekne skontrolovat)'\n");
  printf("\n'vypis_id by malo spravne vypisat tieto 3 \"ovocia\" ak rolku A mazete:'\n");
  printf("//vypis_id '0': Psenica\n");
  printf("//vypis_id '12': x\n");
  printf("//vypis_id '14': DusenyVtakopysk\n");
  
  printf("\n'alebo tieto 3 \"ovocia\" ak rolku A nemazete:'\n");
  printf("//vypis_id '0': kiwi\n");
  printf("//vypis_id '11': k\n");
  printf("//vypis_id '13': i\n");
  printf("\n'na ostatnych id sa ziadne \"ovocie\" nenachadza'\n");

  test_vypis_id();
}

void auto_test_prijem_ovocia() {
  printf("/************* auto_test_prijem_ovocia *************/\n");
  
  test_novy_sklad(50, 2);
  test_prijem_ovocia("autobus", 1, 50, 0);
  test_prijem_ovocia("ovocie", 1, 1, 1);
  test_prijem_ovocia("zelenina", 50, 2, 49);
  test_prijem_ovocia("ovocie", 100, 1, 1);
  test_prijem_ovocia("trolejbus", 2, 75, 0);
  printf("\n");

  test_novy_sklad(2, 49);
  test_prijem_ovocia("autobus", 1, 50, 0);
  test_prijem_ovocia("ovocie", 1, 1, 1);
  test_prijem_ovocia("zelenina", 50, 2, 48);
  test_prijem_ovocia("ovocie", 100, 1, 1);
  test_prijem_ovocia("trolejbus", 2, 75, 0);
  printf("\n");
  
  test_novy_sklad(5, 3);
  test_prijem_ovocia("autobus", 1, 50, 0);
  test_prijem_ovocia("ovocie", 1, 1, 1);
  test_prijem_ovocia("zelenina", 50, 2, 5);
  test_prijem_ovocia("ovocie", 100, 1, 4);
  test_prijem_ovocia("trolejbus", 2, 75, 0);
  printf("\n");
}

void auto_test_vydaj_ovocia_53() {
  printf("/************* auto_test_vydaj_ovocia_53 *************/\n");

  test_novy_sklad(5, 3);
  test_prijem_ovocia("ovocie", 1, 1, 1);
  test_prijem_ovocia("zelenina", 50, 2, 5);
  test_prijem_ovocia("ovocie", 100, 1, 4);

  test_vydaj_ovocia("zelenina", 2, 1, 2);
  test_vydaj_ovocia("zelenina", 2, 2, 2);
  test_vydaj_ovocia("zelenina", 2, 3, 0);
  test_vydaj_ovocia("zelenina", 5, 2, 1);
  printf("\n");
}

void auto_test_vydaj_ovocia_530() {
  printf("/************* auto_test_vydaj_ovocia_530 *************/\n");

  test_novy_sklad(5, 30);
  test_prijem_ovocia("ovocie", 1, 1, 1);
  test_prijem_ovocia("zelenina", 50, 2, 50);
  test_prijem_ovocia("ovocie", 100, 1, 49);
  
  test_vydaj_ovocia("zelenina", 150, 2, 50);
  test_vydaj_ovocia("ovocie", 50, 2, 0);
  test_vydaj_ovocia("ovocie", 50, 1, 50);
  printf("\n");

  test_prijem_ovocia("ovocie", 5, 10, 5);
  test_prijem_ovocia("zelenina", 5, 9, 5);
  test_prijem_ovocia("psenica", 5, 8, 5);
  test_prijem_ovocia("raz", 5, 3, 4);
  test_prijem_ovocia("mach", 5, 1, 3);

  test_vydaj_ovocia("zelenina", 3, 10, 0);
  test_vydaj_ovocia("zelenina", 3, 9, 3);
  test_vydaj_ovocia("zelenina", 3, 8, 2);
  test_vydaj_ovocia("ovocie", 10, 10, 5);
  test_vydaj_ovocia("raz", 5, 3, 4);
  printf("\n");
}

void auto_test_vydaj_ovocia_2513() {
  printf("/************* auto_test_vydaj_ovocia_2513 *************/\n");

  test_novy_sklad(25, 13);
  test_prijem_ovocia("ovocie", 3, 9, 3);
  test_prijem_ovocia("ovocie", 3, 1, 3);
  test_prijem_ovocia("ovocie", 3, 8, 3);
  test_prijem_ovocia("ovocie", 3, 2, 3);
  test_prijem_ovocia("ovocie", 3, 7, 3);
  test_prijem_ovocia("ovocie", 3, 3, 3);
  test_prijem_ovocia("ovocie", 3, 6, 3);
  test_prijem_ovocia("ovocie", 3, 4, 3);
  test_prijem_ovocia("ovocie", 3, 5, 3);
  test_prijem_ovocia("ovocie", 3, 5, 3);
  test_prijem_ovocia("ovocie", 3, 4, 3);
  test_prijem_ovocia("ovocie", 3, 6, 3);
  test_prijem_ovocia("ovocie", 3, 3, 3);
  test_prijem_ovocia("ovocie", 3, 7, 3);
  test_prijem_ovocia("ovocie", 3, 2, 3);
  test_prijem_ovocia("ovocie", 3, 8, 3);
  test_prijem_ovocia("ovocie", 3, 1, 3);
  test_prijem_ovocia("ovocie", 3, 9, 3);
  test_prijem_ovocia("ovocie", 3, 2, 3);
  test_prijem_ovocia("ovocie", 3, 3, 3);
  test_prijem_ovocia("ovocie", 3, 4, 3);
  test_prijem_ovocia("ovocie", 3, 5, 2);
  test_prijem_ovocia("ovocie", 3, 2, 3);
  test_prijem_ovocia("ovocie", 3, 1, 3);
  test_prijem_ovocia("ovocie", 4, 1, 4);

  test_vydaj_ovocia("ovocie", 20, 1, 20);
  test_vydaj_ovocia("ovocie", 5, 1, 5);
  test_vydaj_ovocia("ovocie", 1, 6, 1); // dbg - vacsi kus je dalej v rolkeB
  test_vydaj_ovocia("ovocie", 1, 7, 1);
  test_vydaj_ovocia("ovocie", 2, 9, 2);
  test_vydaj_ovocia("ovocie", 2, 5, 2); // dbg - vacsi kus je skor v rolkeB
  test_vydaj_ovocia("ovocie", 1, 8, 1);
  test_vydaj_ovocia("ovocie", 2, 1, 2);
  test_vydaj_ovocia("ovocie", 20, 8, 3);
  test_vydaj_ovocia("ovocie", 50, 5, 7);
  test_vydaj_ovocia("ovocie", 50, 3, 12);
  printf("\n");
}

void vydaj_ovocia_2513_vypis_sklad() {  
  printf("'Takto by mal vyzerat vas sklad:'\n");
  printf("--- --- --- --- --- --- --- --- --- --- --- ---  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- ---  66  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- ---  66  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- ---  66  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- ---  66  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- ---  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- ---  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- ---  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- ---  66  66  66  66  66  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- ---  66  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- ---  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- ---  66 \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("--- --- --- --- --- --- --- --- ---  66  66  66  66 \n");
  printf("--- --- --- --- --- --- --- --- ---  66  66 --- --- \n");
  printf("--- --- --- --- --- --- --- --- --- --- --- --- --- \n");
  printf("'A takto vas sklad realne vyzera:'\n");
}

void auto_test_borderline() {
  int i, amount, size, ks, buf, ok;
  char name[MAX_NAME_LEN];
  
  printf("/************* auto_test_borderline *************/\n");
  printf("'Ak vam to nespadne tak je to OK'\n");
  printf("'Ak to spadne tak nemate osetrenu rolku A/B ked prekroci MAX (10k)'\n");
  printf("'Ak vam Turing vyhodi \"Program presiahol časový limit.\"'\n");
  printf("'tak to skuste spustit v inom prostredi alebo zmenit nastavenia testu v hlavicke programu'\n");
  
  test_novy_sklad(100, 100);
  
  // snaha preplnit rolku B
  TEST_BORDER_B_ROLL_MAX > 3000 ? amount = TEST_BORDER_B_ROLL_MAX : (amount = 3000);
  strcpy(name, "ovocie"); size = 1; ok = 2499; // 2499-2500 ak mate MAX 10k podla zadania projektu
  buf = prijem_ovocia(name, amount, size); printf("prijem_ovocia: %s (%dks %d) = %dx - //OK (program nespadol, rolka B - OK)\n", name, amount, size, buf);

  test_vydaj_ovocia("ovocie", 1, 1, 1);
  test_prijem_ovocia("ovocie", 100, 10, 0);
  test_prijem_ovocia("ovocie", 2, 2, 0);
  
  strcpy(name, "ovocie"); ks = 5000; size = 1;
  (buf = vydaj_ovocia(name, ks, size), ok = buf) ? printf("vydaj_ovocia: %s (%dks min size: %d)  = %dx - //OK\n", name, ks, size, buf) : printf("vydaj_ovocia: %s (%dks min size: %d)  = %dx - 'WRONG (should be %d)'\n", name, ks, size, buf, ok);

  // snaha preplnit rolku A
  TEST_BORDER_A_ROLL_MAX > 1200 ? ks = TEST_BORDER_A_ROLL_MAX : (ks = 1200);
  amount = 1; size = 1; buf = 0; ok = 0;
  for(i = 0; i < ks; i++) {
    sprintf(name, "%d", (int)1e9 +i);
    prijem_ovocia(name, amount, size);
  }
  printf("prijem_ovocia: %d kusov //OK (program nespadol, rolka A - OK)\n", i);
  printf("'Ha! Nespadlo to ... takze je to' //OK\n");
  //printScrollA(0);
}

void auto_test_vydaj_ovocia() {
  auto_test_vydaj_ovocia_53();
  auto_test_vydaj_ovocia_530();

  #if DBG_2513_VYDAJ_OVOCIA
  test_vydaj_ovocia_2513_dbg();
  vypis_sklad();
  #endif
  
  auto_test_vydaj_ovocia_2513();
  
  vydaj_ovocia_2513_vypis_sklad();

  vypis_sklad();
}

int main() {
  
  auto_test_zisti_id();
  auto_test_prijem_ovocia();
  
  auto_jk_manual_test_vypis_id();
  auto_test_vydaj_ovocia();

  auto_test_borderline();
  
  return 0;
}