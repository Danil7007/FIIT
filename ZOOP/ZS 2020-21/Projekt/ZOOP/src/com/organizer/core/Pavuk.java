package com.organizer.core;

import com.organizer.triedy.Hrac;
import com.organizer.triedy.Turnaj;

import java.util.ArrayList;
import java.util.Scanner;

public class Pavuk {

    private static int velkostPavuka;
    private static int pocetKol;
    private ArrayList<Kolo> kola = new ArrayList<Kolo>(0);
    private Turnaj turnaj;

    public Pavuk(int velkost,Turnaj turnaj) {
        this.velkostPavuka = velkost;
        pocetKol = zistiPocetKol();
        this.turnaj = turnaj;
    }

    public static int zistiPocetKol(){
        int velkost = velkostPavuka;
        pocetKol = 0;
        while (velkost % 2 == 0) {
            velkost /= 2;
            pocetKol++;
        }
        return pocetKol;
    }

    public void vytvorKola(){
        System.out.println("pre dvojhru 1 pre stvorhru 0");
        Scanner keyboard = new Scanner(System.in);
        boolean dvojhra = (keyboard.nextInt() == 1);

        Kolo kolo = new Kolo();
        kolo.setZapasy(Kolo.vytvorKolo(turnaj.getHraci(),dvojhra));
        kola.add(kolo);
        //todo: pridat kolu poradie aby sme vedeli ci a kolko kol este mozeme robit
        Kolo koloOdhad = new Kolo();
        koloOdhad.setZapasy(Kolo.vytvorOdhad(turnaj.getHraci(),dvojhra));
        kola.add(koloOdhad);

    }

    public static int getVelkostPavuka() {
        return velkostPavuka;
    }

    public ArrayList<Kolo> getKola() {
        return kola;
    }

    public static int getPocetKol() {
        return pocetKol;
    }

    public Turnaj getTurnaj() {
        return turnaj;
    }

    public static void setVelkostPavuka(int velkostPavuka) {
        Pavuk.velkostPavuka = velkostPavuka;
    }

    public void setKola(ArrayList<Kolo> kola) {
        this.kola = kola;
    }

    public static void setPocetKol(int pocetKol) {
        Pavuk.pocetKol = pocetKol;
    }

    public void setTurnaj(Turnaj turnaj) {
        this.turnaj = turnaj;
    }
}
