package com.organizer.triedy.pavuk;

import com.organizer.triedy.Turnaj;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

public class Pavuk implements Serializable {

    private static int velkostPavuka;
    private static int pocetKol;
    private ArrayList<Kolo> kola = new ArrayList<Kolo>(0);
    private final ArrayList<Runda> rundy = new ArrayList<Runda>(0);
    private Turnaj turnaj;

    // konstruktor
    public Pavuk(int velkost, Turnaj turnaj) {
        velkostPavuka = velkost;
        pocetKol = zistiPocetKol();
        this.turnaj = turnaj;
    }

    // metoda
    public static int zistiPocetKol() { // zisti kolko kol sa bude hrat
        int velkost = velkostPavuka;
        pocetKol = 0;
        while (velkost % 2 == 0) {
            velkost /= 2;
            pocetKol++;
        }
        return pocetKol;
    }

    // na vypis vsetkych zapasov pavuka
    public static void vypisPavuk(Pavuk pavuk) {
        // pre pocet kol
        for (int i = 0; i < pavuk.getKola().size(); i++) {
            System.out.print("\u001B[4m\u001B[33m" + "\nKolo:" + "\u001B[0m" + " " + (i + 1));
            Kolo kolo = pavuk.getKola().get(i);
            // pre pocet zapasov v kole
            for (int i1 = 0; i1 < kolo.getZapasy().size(); i1++) {
                System.out.println("\n\n Zapas: " + (i1 + 1));
                // pre pocet hracov v zapase
                for (int i2 = 0; i2 < kolo.getZapasy().get(i1).getHraci().size(); i2++) {

                    // vypis ako pri kurt.vypisZapasy() --------------
                    // verzus
                    if ((i2 == kolo.getZapasy().get(i1).getHraci().size() / 2) && kolo.getZapasy().get(i1).getDvojhra()) {
                        System.out.print("\n\t\t-- VS --\n"); //todo skontrolovat ci LOMITKO funguje
                    }
                    // tab
                    if (kolo.getZapasy().get(i1).getDvojhra() && kolo.getZapasy().get(i1).getHraci().size() == 2) {
                        System.out.print("\t"); // ak su 2/2
                    } else if (kolo.getZapasy().get(i1).getDvojhra() && kolo.getZapasy().get(i1).getHraci().size() > 2 && i2 % 2 == 0) {
                        System.out.print("\t"); //ak su >2
                    }
                    // hrac
                    System.out.print((i2 + 1) + ". Hrac: " + kolo.getZapasy().get(i1).getHraci().get(i2).getMeno());
                    // lomitko
                    if (kolo.getZapasy().get(i1).getDvojhra() && kolo.getZapasy().get(i1).getHraci().size() > 2 && i2 % 2 == 0) {
                        System.out.print(" / ");
                    }
                    // -------------------------
                }
            }
            System.out.print("\n\n");
        }
    }


    // pre vypis podla rund
    public static void vypisRundy(Pavuk pavuk) {
        // pre pocet rund
        for (int i = 0; i < pavuk.getRundy().size(); i++) {
            System.out.print("\u001B[4m\u001B[33m" + "\nRunda:" + "\u001B[0m" + " " + (i + 1) + ", datum & cas rundy: " + pavuk.getRundy().get(i).getCas().getDate() + ". " + pavuk.getRundy().get(i).getCas().getMonth() + ". " + pavuk.getRundy().get(i).getCas().getHours() + ":" + pavuk.getRundy().get(i).getCas().getMinutes());
            // pre pocet zapasov v runde
            for (int i1 = 0; i1 < pavuk.getRundy().get(i).getZapasy().size(); i1++) {
                System.out.print("\n\u001B[35m" + "Na kurte: " + (pavuk.getRundy().get(i).getZapasy().get(i1).getCobain().getPoradie() + 1) + ", Kolo: " + pavuk.getRundy().get(i).getZapasy().get(i1).getKolo() + "\u001B[0m" + ", zapas: " + (i1 + 1) + "\n");
                // pre pocet hracov v zapase
                for (int i2 = 0; i2 < pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().size(); i2++) {

                    // VYPIS -------------------------
                    // verzus
                    if ((i2 == pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().size() / 2) && pavuk.getRundy().get(i).getZapasy().get(i1).getDvojhra()) {
                        System.out.print("\n\t\t-- VS --\n");
                    }
                    // tab
                    if (pavuk.getRundy().get(i).getZapasy().get(i1).getDvojhra() && pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().size() == 2) {
                        System.out.print("\t"); // ak su 2/2
                    } else if (pavuk.getRundy().get(i).getZapasy().get(i1).getDvojhra() && pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().size() > 2 && i2 % 2 == 0) {
                        System.out.print("\t"); //ak su >2
                    }
                    // KONTROLA CI NENI BYE !!
                    if (!pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().get(i2).getMeno().toLowerCase().equals("bye")) {
                        // hrac
                        System.out.print((i2 + 1) + ". Hrac: " + pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().get(i2).getMeno());
                    } else {
                        System.out.print(" --- ");
                    }
                    // lomitko
                    if (pavuk.getRundy().get(i).getZapasy().get(i1).getDvojhra() && pavuk.getRundy().get(i).getZapasy().get(i1).getHraci().size() > 2 && i2 % 2 == 0) {
                        System.out.print(" / ");
                    }
                    // --------------------------------
                }
            }
        }
    }


    //--------------------------------------------------------------------------------
    // GET SET

    public static int getVelkostPavuka() {
        return velkostPavuka;
    }

    public static void setVelkostPavuka(int velkostPavuka) {
        Pavuk.velkostPavuka = velkostPavuka;
    }

    public static int getPocetKol() {
        return pocetKol;
    }

    public static void setPocetKol(int pocetKol) {
        Pavuk.pocetKol = pocetKol;
    }

    public ArrayList<Kolo> getKola() {
        return kola;
    }

    public void setKola(ArrayList<Kolo> kola) {
        this.kola = kola;
    }

    public Turnaj getTurnaj() {
        return turnaj;
    }

    public void setTurnaj(Turnaj turnaj) {
        this.turnaj = turnaj;
    }

    public ArrayList<Runda> getRundy() {
        return rundy;
    }

    //--------------------------------------------------------------------------------

    // vytvori kola pre pavuk
    public void vytvorKola() {
        boolean cntn = false; // continue
        boolean dvojhra = true;
        System.out.println("pre dvojhru 1 pre stvorhru 0");
        Scanner keyboard = new Scanner(System.in);
        do { // nastavi dvojhru (kontrola zleho vstupu)
            int dv = Character.getNumericValue(keyboard.nextLine().charAt(0));
            if (dv == 1 || dv == 0) {
                dvojhra = (dv == 1);
                cntn = true;
            } else {
                System.out.println("\u001B[4m\u001B[31mZadali ste zlý vstup.\nPre dvojhru 1 pre stvorhru 0\u001B[0m");
            }
            dv = 10;
        } while (!cntn);

        int poradie = 3; // prve dva su uz vytvorene
        Kolo kolo = new Kolo(); // prve kolo
        kolo.setPoradie(1);
        kolo.setZapasy(Kolo.vytvorKolo(turnaj.getHraci(), dvojhra, turnaj.getZoznamKurtov(), kolo));
        kolo.pridelKurty(turnaj.getZoznamKurtov(), this.rundy);
        kola.add(kolo);
        Kolo koloOdhad = new Kolo(); // druhe kolo
        koloOdhad.setPoradie(2);
        koloOdhad.setZapasy(Kolo.vytvorOdhad(turnaj.getHraci(), dvojhra, turnaj.getZoznamKurtov(), koloOdhad));
        koloOdhad.pridelKurty(turnaj.getZoznamKurtov(), this.rundy);
        kola.add(koloOdhad);
        // velkost pavuka po prvych 2 kolach
        int tempVelkost = (velkostPavuka / 2) / 2;
        int pocetZvyskychKol = 0;
        while (tempVelkost % 2 == 0) {
            pocetZvyskychKol++;
            tempVelkost /= 2;
        } // vyratanie kolko kol zostava
        // pre pocet zvysnych kol doplni kola do pavuka
        for (int i = pocetZvyskychKol; i > 0; i--) {
            Kolo dopln = new Kolo();
            dopln.setPoradie(poradie);
            dopln.setZapasy(Kolo.doplnKoloPavuka(pocetZvyskychKol, dopln));
            dopln.pridelKurty(turnaj.getZoznamKurtov(), this.rundy);
            kola.add(dopln);
            pocetZvyskychKol--;
            poradie++;
        }
        // pridelovanie casu rundam
        Date cas = turnaj.getZaciatokTurnaja(); // od kolkej sa hra
        int maxZapasovTurnaja = turnaj.getKategoria().getMaxDvojhry(); // pre dvojhru
        // pre pocet rund
        for (int i = 0; i < rundy.size(); ++i) {
            rundy.get(i).setCas(cas); // nastavi cas runde
            rundy.get(i).pridelCasy(); // nastavi cas zapasom v runde
            Date cas2 = (Date) cas.clone(); // aby sa neprestavoval uz naastaveny cas rundy
            // prechod do dalsieho dna
            if (i != 0 && (cas2.getHours() >= 22 || i % maxZapasovTurnaja == 0)) {
                cas2.setDate(cas.getDate() + 1);
                cas2.setHours(turnaj.getZaciatokTurnaja().getHours());
                cas2.setMinutes(turnaj.getZaciatokTurnaja().getMinutes());
                cas2.setSeconds(0);
            }
            // zvysenie casu o trvanie zapasov (2h cca) pre nasledujuce zapasy cakajuce v poradi
            cas2.setHours(cas2.getHours() + turnaj.getKategoria().getOdhadTrvania());
            cas = (Date) cas2.clone();
            cas2 = null;
        }
    }
}
