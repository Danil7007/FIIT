package com.organizer.triedy.pavuk;

import com.organizer.triedy.Hrac;
import com.organizer.triedy.Zapas;

import java.io.Serializable;
import java.util.ArrayList;

public class Kolo implements Serializable {
    private ArrayList<Zapas> zapasy;

    //todo: spravit update kola aby sa odstranili z arraylistu hraci co prehrali aby sme vytvorili dalsie kolo a odhad so spravnymi hracmi
    public static ArrayList<Zapas> vytvorKolo(ArrayList<Hrac> hraci, boolean dvojhra) {
        ArrayList<Zapas> zapasy = new ArrayList<Zapas>(0); //konkretne kolo - zoznam zapasov toho kola

        if (dvojhra)
            for (int i = 0; i < hraci.size(); i -= -2) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0);
                Zapas zapas = new Zapas();
                zapas.setDvojhra(true);
                hraci2.add(hraci.get(i));
                hraci2.add(hraci.get(i + 1));
                zapas.setHraci(hraci2);
                zapasy.add(zapas);
            }
        if (!dvojhra)
            for (int i = 0; i < hraci.size(); i -= -4) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0);
                Zapas zapas = new Zapas();
                zapas.setDvojhra(true);
                hraci2.add(hraci.get(i));
                hraci2.add(hraci.get(i + 1));
                zapas.setHraci(hraci2);
                zapasy.add(zapas);
            }
        return zapasy;
    }

    public static ArrayList<Zapas> vytvorOdhad(ArrayList<Hrac> hraci, boolean dvojhra) {
        ArrayList<Zapas> odhady = new ArrayList<Zapas>(0);
        if (dvojhra)
            for (int i = 0; i < hraci.size(); i -= -4) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0);
                Zapas zapas = new Zapas();
                zapas.setDvojhra(true);
                hraci2.add(hraci.get(i));
                hraci2.add(hraci.get(i + 1));
                hraci2.add(hraci.get(i + 2));
                hraci2.add(hraci.get(i + 3));
                zapas.setHraci(hraci2);
                odhady.add(zapas);
            }
        if (!dvojhra)
            for (int i = 0; i < hraci.size(); i -= -8) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0);
                Zapas zapas = new Zapas();
                zapas.setDvojhra(true);
                hraci2.add(hraci.get(i));
                hraci2.add(hraci.get(i + 1));
                hraci2.add(hraci.get(i + 2));
                hraci2.add(hraci.get(i + 3));
                hraci2.add(hraci.get(i + 4));
                hraci2.add(hraci.get(i + 5));
                hraci2.add(hraci.get(i + 6));
                hraci2.add(hraci.get(i + 7));
                zapas.setHraci(hraci2);
                odhady.add(zapas);
            }
        return odhady;
    }

    //--------------------------------------------------------------------------------
    // GET SET

    public ArrayList<Zapas> getZapasy() {
        return zapasy;
    }

    public void setZapasy(ArrayList<Zapas> zapasy) {
        this.zapasy = zapasy;
    }
}
