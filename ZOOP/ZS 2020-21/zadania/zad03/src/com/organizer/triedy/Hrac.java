package com.organizer.triedy;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

public class Hrac implements Serializable {
    private String meno;
    private int odohrateZapasyDvojhra;
    private int odohrateZapasyStvorhra;

    public Hrac() { // konstruktor
        meno = "";
        odohrateZapasyDvojhra = 0;
        odohrateZapasyStvorhra = 0;
    }

    public Hrac(String meno) {
        this.meno = meno;
    }

    // METODY

    // nacitanie hracov
    public static ArrayList<Hrac> nacitajHracov(int pocetHracov) {
        Scanner keyboard = new Scanner(System.in);
        ArrayList<Hrac> hraci = new ArrayList<Hrac>(0);
        for (int i = 0; i < pocetHracov; ++i) {
            System.out.println("Zadaj meno hraca (no." + (i + 1) + ".):");
            String meno = keyboard.nextLine();
            hraci.add(new Hrac(meno));
        }
        return hraci;
    }

    // GET & SET -------------------------------------------------------

    public String getMeno() {
        return meno;
    }

    public void setMeno(String meno) {
        this.meno = meno;
    }

    public int getOdohrateZapasyDvojhra() {
        return odohrateZapasyDvojhra;
    }

    public void setOdohrateZapasyDvojhra(int odohrateZapasyDvojhra) {
        this.odohrateZapasyDvojhra = odohrateZapasyDvojhra;
    }

    public int getOdohrateZapasyStvorhra() {
        return odohrateZapasyStvorhra;
    }

    public void setOdohrateZapasyStvorhra(int odohrateZapasyStvorhra) {
        this.odohrateZapasyStvorhra = odohrateZapasyStvorhra;
    }
}
