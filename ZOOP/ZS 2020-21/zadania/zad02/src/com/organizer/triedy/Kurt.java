package com.organizer.triedy;

import java.io.Serializable;
import java.util.ArrayList;

public class Kurt implements Serializable {
    private ArrayList<Zapas> zapasy;
    private int pocetZapasovNaKurte;


    public Kurt() {
        zapasy = new ArrayList<Zapas>(1);
        pocetZapasovNaKurte = zapasy.size();
    }

    // GET SET
    public ArrayList<Zapas> getZapasy() {
        return zapasy;
    }

    public void setZapasy(ArrayList<Zapas> zapasy) {
        this.zapasy = zapasy;
    }

    public int getPocetZapasovNaKurte() {
        return pocetZapasovNaKurte;
    }

    public void setPocetZapasovNaKurte(int pocetZapasovNaKurte) {
        this.pocetZapasovNaKurte = pocetZapasovNaKurte;
    }
}
