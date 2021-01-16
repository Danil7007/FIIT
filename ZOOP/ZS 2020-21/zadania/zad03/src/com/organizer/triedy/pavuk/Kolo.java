package com.organizer.triedy.pavuk;

import com.organizer.triedy.Hrac;
import com.organizer.triedy.Kurt;
import com.organizer.triedy.Zapas;
import org.jetbrains.annotations.NotNull;

import java.io.Serializable;
import java.util.ArrayList;

public class Kolo implements Serializable {
    protected ArrayList<Zapas> zapasy;
    protected int poradie;

    //todo: spravit update kola aby sa odstranili z arraylistu hraci co prehrali aby sme vytvorili dalsie kolo a odhad so spravnymi hracmi

    // metoda - parametre su arrazlist hracov, bool ci je dvojhra alebo stvorhra, zoznam kurtov, konkretne kolo
    public static ArrayList<Zapas> vytvorKolo(ArrayList<Hrac> hraci, boolean dvojhra, ArrayList<Kurt> kurty, Kolo kolo) {
        //konkretne kolo - zoznam zapasov toho kola
        ArrayList<Zapas> zapasy = new ArrayList<Zapas>(0); // novy zoznam zapasov
        // pridelovanie hracov do zapasu
        if (dvojhra) // dvojhra - po dvoch
            for (int i = 0; i < hraci.size(); i -= -2) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0); // arraylist hracov konkretneho zapasu
                Zapas zapas = new Zapas(); // vytvorí nový zápas
                zapas.setKolo(kolo.poradie); // nastaví zápasu kolo
                zapas.setDvojhra(true); // nastavit dvojhru
                hraci2.add(hraci.get(i)); // pridaj hraca zapasu
                hraci2.add(hraci.get(i + 1)); // pridaj zápasu druheho hráca
                zapas.setHraci(hraci2); // pridaj zoznam hracov do zápasu
                zapasy.add(zapas); // pridaj zapas do zoznamu zapasov
            }
        if (!dvojhra) // stvorhra - po styroch
            for (int i = 0; i < hraci.size(); i -= -4) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0);
                Zapas zapas = new Zapas();
                zapas.setKolo(kolo.poradie);
                zapas.setDvojhra(dvojhra);
                hraci2.add(hraci.get(i));
                hraci2.add(hraci.get(i + 1));
                hraci2.add(hraci.get(i + 2));
                hraci2.add(hraci.get(i + 3));
                zapas.setHraci(hraci2);
                zapasy.add(zapas);
            }
        return zapasy;
    }

    // ako vytvorKolo ale pre dvojnasobok hracov
    public static ArrayList<Zapas> vytvorOdhad(ArrayList<Hrac> hraci, boolean dvojhra, ArrayList<Kurt> kurty, Kolo kolo) {
        ArrayList<Zapas> odhady = new ArrayList<Zapas>(0);
        if (dvojhra)
            for (int i = 0; i < hraci.size(); i -= -4) {
                ArrayList<Hrac> hraci2 = new ArrayList<Hrac>(0);
                Zapas zapas = new Zapas();
                zapas.setKolo(kolo.getPoradie());
                zapas.setDvojhra(dvojhra);
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
                zapas.setKolo(kolo.getPoradie());
                zapas.setDvojhra(dvojhra);
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

    // pre kazde zvysne kolo vytvori zapasy (bez hracov - informacna funkcia)
    public static ArrayList<Zapas> doplnKoloPavuka(int pocetZvysnychKol, Kolo kolo) {
        ArrayList<Zapas> doplnujuce = new ArrayList<Zapas>(0); // zoznam zapasov
        int pocetZapasov = (int) Math.pow(2, (pocetZvysnychKol - 1)); // rovnica co namna zoslal duch matematiky ; (int) - cast to int -> informacia že vysledok má byť typu int
        // pre zvysny pocet zapasov
        for (int i = 0; i < pocetZapasov; i++) {
            Zapas z = new Zapas();
            z.setKolo(kolo.getPoradie());
            z.setHraci(new ArrayList<Hrac>(0));
            doplnujuce.add(z);
        }
        return doplnujuce;
    }

    // prideluje kurty zapasom
    public void pridelKurty(ArrayList<Kurt> kurty, @NotNull ArrayList<Runda> rundy) { // NotNull zabezpecuje ze nebude NULL - vlozil IntelliDJ :)
        int cislokurtu = 0;
        int cisloRundy = rundy.size();
        rundy.add(new Runda()); // vytvori rundu
        outside:
        // navestidlo
        for (int i = 0; i < zapasy.size(); i++) {
            for (Hrac hrac :
                    zapasy.get(i).getHraci()) {
                // zisti ci je BYE
                if (hrac.getMeno().toLowerCase().equals("bye")) {
                    continue outside; // pokial bye preskoc na navestidlo outside ale pokracuj v dalsej iteracii cyklu
                }
            }
            // cislovanie 1, 2, 3, 1, 2, 3 .....
            if (cislokurtu >= kurty.size()) {
                cislokurtu = 0;
                rundy.add(new Runda(this));
                cisloRundy++;
            }
            rundy.get(cisloRundy).getZapasy().add(zapasy.get(i)); // prideli runde zapasy
            zapasy.get(i).setCobain(kurty.get(cislokurtu)); // prideli zapasu kurt
            kurty.get(cislokurtu).getZapasy().add(zapasy.get(i)); // prideli kurtu zapasy
            cislokurtu++;
        }
    }

    //--------------------------------------------------------------------------------
    // GET SET

    public ArrayList<Zapas> getZapasy() {
        return zapasy;
    }

    public void setZapasy(ArrayList<Zapas> zapasy) {
        this.zapasy = zapasy;
    }

    public int getPoradie() {
        return poradie;
    }

    public void setPoradie(int poradie) {
        this.poradie = poradie;
    }
}
