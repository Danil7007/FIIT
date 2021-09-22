package com.organizer.triedy;

import java.io.Serializable;
import java.util.ArrayList;

public class Kurt implements Serializable {
    private ArrayList<Zapas> zapasy;
    private int pocetZapasovNaKurte;
    private int poradie;

    public Kurt() { // konstruktor
        zapasy = new ArrayList<Zapas>(0);
        pocetZapasovNaKurte = zapasy.size();
    }

    public void vypisZapasy() {
        System.out.print("\u001B[35m" + "\nNa kurte " + (this.poradie + 1) + " sa hra:" + "\n" + "\u001B[0m");
        // pre pocet zapasov
        for (int i1 = 0; i1 < zapasy.size(); i1++) {
            System.out.print("\u001B[4m\u001B[33m" + "\nKolo:" + "\u001B[0m" + " " + (zapasy.get(i1).getKolo()) + ", zapas no. " + (i1 + 1) + "\n");
            // pre pocet hracov v zapase
            for (int i2 = 0; i2 < zapasy.get(i1).getHraci().size(); i2++) {
                // verzus (ked je ich viac ako dva v dvojhre a je to medzi medzi)
                if ((i2 == zapasy.get(i1).getHraci().size() / 2) && zapasy.get(i1).getDvojhra()) {
                    System.out.print("\n\t\t-- VS --\n");
                }
                // vypis hracov -----
                // tabulatory
                if (zapasy.get(i1).getDvojhra() && zapasy.get(i1).getHraci().size() == 2) {
                    System.out.print("\t"); // ak su 2/2
                } else if (zapasy.get(i1).getDvojhra() && zapasy.get(i1).getHraci().size() > 2 && i2 % 2 == 0) {
                    System.out.print("\t"); //ak su >2
                }
                // konkretny hrac
                System.out.print((i2 + 1) + ". Hrac: " + zapasy.get(i1).getHraci().get(i2).getMeno());

                // lomitko
                if (zapasy.get(i1).getDvojhra() && zapasy.get(i1).getHraci().size() > 2 && i2 % 2 == 0) {
                    System.out.print(" / ");
                }
                // ---------
            }
        }
        System.out.print("\n\n");
    }

    // GET SET -----------------------------------------------------------------------
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

    public int getPoradie() {
        return poradie;
    }

    public void setPoradie(int poradie) {
        this.poradie = poradie;
    }
}
