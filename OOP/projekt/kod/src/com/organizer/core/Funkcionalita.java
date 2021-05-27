package com.organizer.core;

import com.organizer.classes.Prevadzka;
import com.organizer.classes.orders.ObjednavkaZakaznika;
import com.organizer.messages.ProgramoveVypisy;

import java.io.Serializable;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Funkcionalita implements Serializable {

    public static Prevadzka caseOperator(Prevadzka prevadzka) {
        System.out.print(ProgramoveVypisy.highlight + ProgramoveVypisy.caseOperatorRun + ProgramoveVypisy.white);
        int key;

        do {
            System.out.print(ProgramoveVypisy.caseOperatorSwitch);
            System.out.println(ProgramoveVypisy.caseOperatorExit);

            Scanner keyboard = new Scanner(System.in);
            key = keyboard.nextInt();

            switch (key) {
                case 0:
                    break;
                case 1: // vytvorenie prevadzky
                    if (prevadzka == null) {
                        prevadzka = Prevadzka.getInstance();
                        System.out.println(ProgramoveVypisy.okay);
                    }
                    else {
                        System.out.println(ProgramoveVypisy.errorDuplicitnaInicializacia);
                    }
                    break;
                case 2: // zamestnanie manazerov
                    if (prevadzka == null) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorInicializacia + ProgramoveVypisy.white);
                    }
                    else {
                        System.out.println(ProgramoveVypisy.pocetManazerov);
                        int pocet = keyboard.nextInt();
                        prevadzka.zamestnajManazerov(pocet);
                        System.out.println(ProgramoveVypisy.okay);
                    }
                    break;
                case 3: // zamestnanie vyroby
                    if (prevadzka == null) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorInicializacia + ProgramoveVypisy.white);
                    }
                    else if (prevadzka.getPocetManazerov() == 0) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorManazeri + ProgramoveVypisy.white);
                    }
                    else {
                        prevadzka.zamestnajZamestnancovVyroby();
                        System.out.println(ProgramoveVypisy.okay);
                    }
                    break;
                case 4: // kontrola
                    if (prevadzka == null) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorInicializacia + ProgramoveVypisy.white);
                    }
                    else if (prevadzka.getPocetManazerov() == 0) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorManazeri + ProgramoveVypisy.white);
                    }
                    else {
                        prevadzka.personal();
                    }
                    break;
                default:
                    break;
            }

        } while (key != 0);

        return prevadzka;
    }

    public static Prevadzka caseManazer(Prevadzka prevadzka) {

        // kontrola ci existuje prevadzka a ci existuju manazeri
        if (prevadzka == null) {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorInicializacia + ProgramoveVypisy.white);
            return null;
        }
        else if (prevadzka.getPocetManazerov() == 0) {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorManazeri + ProgramoveVypisy.white);
            return prevadzka;
        }

        // premenne
        Scanner keyboard = new Scanner(System.in);
        int key;

        // vypisy
        System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.caseManazerRun + ProgramoveVypisy.white);
        System.out.println(ProgramoveVypisy.caseManazerIdentify);

        // identifikacia
        for (int i = 0; i < prevadzka.getPocetManazerov(); i++) {
            System.out.println("-> " + prevadzka.getManazeri().get(i).getMeno() + " (" + i + ")");
        }
        int id = keyboard.nextInt();
        // kontrola identifikacie
        if (0 <= id && id < prevadzka.getPocetManazerov() ) {
            System.out.print(ProgramoveVypisy.caseManazerWellcome);
            prevadzka.getManazeri().get(id).prichodDoPrace(); // nastavenie prichodu
            System.out.println(prevadzka.getManazeri().get(id).getMeno());
        }
        else {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorLogin + ProgramoveVypisy.white);
            return prevadzka;
        }

        // hlavny cyklus
        do {
            // vypisy
            System.out.print(ProgramoveVypisy.caseManazerSwitch);
            System.out.println(ProgramoveVypisy.caseManazerExit);

            // switch funkcii
            key = keyboard.nextInt();
            switch (key) {
                case 0:
                    break;
                case 1: // vykonanie dochadzky
                    if (prevadzka.getManazeri().get(id).getPocetZamestnancov() == 0) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorZamestnanci + ProgramoveVypisy.white);
                        break;
                    }
                    System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.caseManazerDochadzka + ProgramoveVypisy.white);
                    prevadzka.getManazeri().get(id).vykonajDochadzku();
                    break;
                case 2: // individualna dochadzka
                    String meno = "";
                    if (prevadzka.getManazeri().get(id).getPocetZamestnancov() == 0) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorZamestnanci + ProgramoveVypisy.white);
                        break;
                    }
                    else {
                        System.out.println(ProgramoveVypisy.caseManazerDoplnenieDochadzky);
                        meno = keyboard.nextLine(); //TODO co sa tu robi?
                        meno = keyboard.nextLine();
                    }
                    prevadzka.getManazeri().get(id).vykonajDochadzku(meno);
                    break;
                case 3: // zmaestnanie
                    System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.zamestnajVyrobu + ProgramoveVypisy.white);
                    System.out.println(ProgramoveVypisy.zamestnaj2);
                    int pocet = keyboard.nextInt();
                    prevadzka.getManazeri().get(id).zamestnaj(pocet);
                    System.out.println(ProgramoveVypisy.okay);
                    break;
                case 4: // hlasenie
                    if (prevadzka.getManazeri().get(id).getPocetZamestnancov() == 0) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorZamestnanci + ProgramoveVypisy.white);
                        break;
                    }
                    System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.caseManazerHlasenie + ProgramoveVypisy.white);
                    prevadzka.getManazeri().get(id).vykonajHlasenie();
                    break;
                case 5: // hlasenie o ulohach
                    if (prevadzka.getManazeri().get(id).getUlohy().size() == 0) {
                        System.out.println(ProgramoveVypisy.caseManazerBezObjednavok);
                    }
                    else {
                        System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.caseManazerHlasenie + ProgramoveVypisy.white);
                        prevadzka.getManazeri().get(id).vykonajHlasenieObjednavok();
                    }
                    break;
                default:
                    break;
            }


        } while (key != 0);

        return prevadzka;
    }

    public static Prevadzka caseZakaznik(Prevadzka prevadzka) {

        // kontrola ci existuje prevadzka  manazeri
        if (prevadzka == null) {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorInicializacia + ProgramoveVypisy.white);
            return prevadzka;
        }
        else if (prevadzka.getPocetManazerov() == 0) {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorManazeri + ProgramoveVypisy.white);
            return prevadzka;
        }

        // premenne
        Scanner keyboard = new Scanner(System.in);
        int key;
        ObjednavkaZakaznika objednavka = null;

        // vypisy
        System.out.print(ProgramoveVypisy.highlight + ProgramoveVypisy.caseZakaznikRun + ProgramoveVypisy.white);

        // hlavny cyklus
        do {
            // vypisy
            System.out.print(ProgramoveVypisy.caseZakaznikSwitch);
            System.out.println(ProgramoveVypisy.caseZakaznikExit);


            // switch funkcii
            key = keyboard.nextInt();
            switch (key) {
                case 0:
                    break;
                case 1: // pridanie do objednavky
                    // ak nie je vytvorena -> vytvor
                    if (objednavka == null) {
                        objednavka = new ObjednavkaZakaznika();
                    }

                    System.out.println(ProgramoveVypisy.caseZakaznikTovar);
                    String inp1 = keyboard.nextLine(); //TODO: co sa tu robi?
                    inp1 = keyboard.nextLine();
                    System.out.println(ProgramoveVypisy.caseZakaznikFarba);
                    String inp2 = keyboard.nextLine();
                    System.out.println(ProgramoveVypisy.caseZakaznikMaterial);
                    String inp3 = keyboard.nextLine();
                    System.out.println(ProgramoveVypisy.caseZakaznikVelkost);
                    String inp4 = keyboard.nextLine();
                    System.out.println(ProgramoveVypisy.caseZakaznikDamske);
                    int inp5 = keyboard.nextInt();
                    objednavka.pridajPolozku(inp1, inp2, inp3, inp4, inp5);

                    if (objednavka.getPolozky().size() == 0) {
                        objednavka = null;
                    }

                    break;
                case 2: // odstranenie z objednavky
                    //TODO: odsstranenie polozky
                    break;
                case 3: // potvrdenie objednavky
                    if (objednavka == null) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.caseZakaznikNeexistuje + ProgramoveVypisy.white);
                        break;
                    }
                    if (objednavka != null) {
                        System.out.println("Výsledná cena: " + objednavka.getCenaObjednavky() + " EUR");
                        System.out.println(ProgramoveVypisy.caseZakaznikPotvrdenie);
                        char a = keyboard.next().charAt(0);
                        if (Character.toUpperCase(a) == 'A') {
                            // TODO: udaje zakaznika
                            prevadzka.getAktivneObjednavky().add(objednavka);
                            objednavka = null;
                            System.out.println(ProgramoveVypisy.okay);
                        }
                    }
                    break;
                case 4: // zobrazenie objednavky
                    if (objednavka == null) {
                        System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.caseZakaznikNeexistuje + ProgramoveVypisy.white);
                        break;
                    }
                    System.out.println(ProgramoveVypisy.caseZakaznikZobrazenie);
                    objednavka.vypisObjednavku();
                    break;
                default:
                    break;
            }

        } while (key != 0);

        prevadzka.rozdeleniePrace(); // po odhaseni uzivatela
        return prevadzka;
    }
}
