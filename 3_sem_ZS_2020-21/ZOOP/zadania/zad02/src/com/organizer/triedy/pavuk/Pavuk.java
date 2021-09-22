package com.organizer.triedy.pavuk;

import com.organizer.triedy.Turnaj;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

public class Pavuk implements Serializable {

    private static int velkostPavuka;
    private static int pocetKol;
    private ArrayList<Kolo> kola = new ArrayList<Kolo>(0);
    private Turnaj turnaj;

    public Pavuk(int velkost, Turnaj turnaj) {
        velkostPavuka = velkost;
        pocetKol = zistiPocetKol();
        this.turnaj = turnaj;
    }

    public static int zistiPocetKol() {
        int velkost = velkostPavuka;
        pocetKol = 0;
        while (velkost % 2 == 0) {
            velkost /= 2;
            pocetKol++;
        }
        return pocetKol;
    }


    public static void vypisPavuk(Pavuk pavuk) {
        for (int i = 0; i < pavuk.getKola().size(); i++) {
            System.out.print("\nKolo:" + (i + 1));
            Kolo kolo = pavuk.getKola().get(i);
            for (int i1 = 0; i1 < kolo.getZapasy().size(); i1++) {
                System.out.print("\nZapas:" + (i1 + 1) + "\n");
                for (int i2 = 0; i2 < kolo.getZapasy().get(i1).getHraci().size(); i2++) {
                    if ((i2 == kolo.getZapasy().get(i1).getHraci().size() / 2) && kolo.getZapasy().get(i1).getDvojhra()) {
                        System.out.print("\n\t\t-- VS --\n"); //todo LOMITKO? ked je viac hracov ako ma byt v dvojhre tak pri parnom hracovi moze byt /
                    }
                    System.out.print("\t" + (i2 + 1) + ". Hrac:" + kolo.getZapasy().get(i1).getHraci().get(i2).getMeno());

                }
            }
            System.out.print("\n\n");
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

    //--------------------------------------------------------------------------------

    public void vytvorKola() {
        System.out.println("pre dvojhru 1 pre stvorhru 0");
        Scanner keyboard = new Scanner(System.in);
        boolean dvojhra = (keyboard.nextInt() == 1);

        Kolo kolo = new Kolo();
        kolo.setZapasy(Kolo.vytvorKolo(turnaj.getHraci(), dvojhra));
        kola.add(kolo);
        //todo: pridat kolu poradie aby sme vedeli ci a kolko kol este mozeme robit
        Kolo koloOdhad = new Kolo();
        koloOdhad.setZapasy(Kolo.vytvorOdhad(turnaj.getHraci(), dvojhra));
        kola.add(koloOdhad);

    }
}
