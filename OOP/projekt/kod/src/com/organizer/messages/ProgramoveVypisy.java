package com.organizer.messages;

public class ProgramoveVypisy {

    // manazer
    public static String zamestnaj = "Zadaj meno zamestnanca č.";
    public static String zamestnaj2 = "Koľko zamestnancov si želáte zamestnať?";
    public static String zamestnajManazera = "Zadaj meno manažéra č.";
    public static String dochadzka = "Je prítomný zamestnanec ";
    public static String dochadzka2 = " ? (a/n) ";
    public static String dochadzka3 = "zamestnanec výroby ";
    public static String pritomny = "Zamestnanec sa dostavil do práce";
    public static String pritomny2 = ", je prítomný";
    public static String nepritomny = "Zamestnanec absentuje";
    public static String nepritomny2 = ", nie je prítomný";
    public static String prezentujSa = "Hlásenie manažéra: volám sa ";
    public static String podriadeni = ", moji podriadení zamestnanci sú: ";
    public static String objednavky = "Objednávkyy ktoré spravujem sú:";
    public static String bezPodriadenych = "momentálne mám 0 podriadených zamestnancov.";

    // general
    public static String pocetManazerov = "Koľko manažérov chcete zamestnať? ";
    public static String run = "\nSpustit program ako:\u001B[0m\n-> operator (1)\n-> manažér (2)\n-> zamestnanec (3)\n-> zákazník (4)";
    public static String exit = "\n-> pre ukončenie programu stlačte 0";
    public static String okay = "Operácia prebehla úspešne.";

    // prevadzka
    public static String pocetPodriadenych = "Koľko (ďalších) podriadených má mať manažér ";
    public static String personal = "\nHlásenie personálu prevádzky:";
    public static String zamestnajManazerov = "Zamestnávanie manažérov:";
    public static String zamestnajVyrobu = "Zamestnávanie pracovníkov výroby:";

    // caseOperator
    public static String caseOperatorRun = "Spustený mód operátor";
    public static String caseOperatorSwitch = "\n-> vytvorenie prevádzky (1)\n-> zamestnanie manažérov (2)\n-> zamestnanie zamestnancov výroby (3)\n-> kontrola pracovníkov (4)";
    public static String caseOperatorExit = "\n-> pre ukončenie módu operátor stlačte 0";

    // caseManazer
    public static String caseManazerRun = "\nSpustený mód manažér";
    public static String caseManazerDochadzka = "\nZadajte dochádzku";
    public static String caseManazerDoplnenieDochadzky= "Čiu dochádzku si želáte upraviť?";
    public static String caseManazerHlasenie = "\nVaše hlásenie znie:";
    public static String caseManazerSwitch = "\n-> vykonanie dochádzky všetkých zamestnancov (1)\n-> doplnenie dochádzky (2)\n-> zamestnanie zamestnancov (3)\n-> vykonanie hlásenia o dochádzke (4)\n-> vykonanie hlásenia o objednávkach (5)";
    public static String caseManazerExit = "\n-> pre ukončenie módu manažér stlačte 0";
    public static String caseManazerIdentify = "Identifikujte sa prosím";
    public static String caseManazerWellcome = "Vitajte naspäť ";
    public static String caseManazerBezObjednavok = "Momentálne nemáte pridelené žiadne objednávky";

    // case Zakaznik
    public static String caseZakaznikRun = "\nSpustený mód zákazník";
    public static String caseZakaznikSwitch = "\n-> pridanie do objednávky (1)\n-> odstránenie z objednávky (2)\n-> potvrdenie objednávky (3)\n-> zobrazenie objednávky (4)";
    public static String caseZakaznikExit = "\n-> pre ukončenie módu zákazník stlačte 0";
    public static String caseZakaznikTovar = "\nZadajte typ tovaru ktorý si želáte objednať (vesta, sveter): ";
    public static String caseZakaznikFarba = "Zadajte želanú farbu tovaru: ";
    public static String caseZakaznikVelkost = "Zadajte veľkosť tovaru (XS, S, M, L, XL): ";
    public static String caseZakaznikMaterial = "Zadajte želaný materiál (bavlna, hodvab, moher, merino): ";
    public static String caseZakaznikDamske = "Má byť želaný produkt dámsky (1) alebo pánsky (0) ? ";
    public static String caseZakaznikZobrazenie = "\nVaša objednávka je nasledujúca: ";
    public static String caseZakaznikPotvrdenie = "\nŽeláte si Vašu objednávku potvrdiť a odoslať? (a/n)";
    public static String caseZakaznikNeexistuje = "\nNemáte vytvorenú žiadnu objednávku";

    // error
    public static String errorDuplicitnaInicializacia = "CHYBA: Prevádzka už bola vytvorená";
    public static String errorInicializacia = "CHYBA: Prevádzka ešte nebola vytvorená";
    public static String errorManazeri = "CHYBA: Neboli zamestnaní manažéri.";
    public static String errorZamestnanci = "CHYBA: Neboli zamestnaní žiadni zamestnanci výroby.";
    public static String errorLogin = "CHYBA: Chyba pri identifikácií.";
    public static String errorDochadzka = "CHYBA: Zamestnanec nebol nájdený.";
    public static String errorInput = "CHYBA: Nebol zadaný správny vstup.";


    // colors
    public static String errorColor = "\u001B[0m\u001B[34m";
    public static String white = "\u001B[0m";
    public static String highlight = "\u001B[4m\u001B[36m";

}
