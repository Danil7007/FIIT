package com.organizer.classes.employees;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

import com.organizer.classes.orders.ObjednavkaZakaznika;
import com.organizer.messages.*;

public class Manazer extends Zamestnanec implements Serializable {
    private ArrayList<ZamestnanecVyroby> zamestnanci; // jeho podriadeni
    private int pocetZamestnancov;
    private ArrayList<ObjednavkaZakaznika> ulohy;

    // konstruktory
    public Manazer(String meno) { // pretazeny konstruktor
        super();
        this.meno = meno;
        this.mzda = 20;
        this.pocetZamestnancov = 0;
        this.zamestnanci = new ArrayList<ZamestnanecVyroby>(0);
        this.ulohy = new ArrayList<ObjednavkaZakaznika>(0);
    }

    public Manazer() {
        super();
        this.mzda = 20;
        this.pocetZamestnancov = 0;
        this.zamestnanci = new ArrayList<ZamestnanecVyroby>(0);
        this.ulohy = new ArrayList<ObjednavkaZakaznika>(0);
    }


    // metody

    public void zamestnaj(int pocet) { // zamestnanie podriadenych zamestnancov
        Scanner keyboard = new Scanner(System.in);
        this.setPocetZamestnancov(this.getPocetZamestnancov() + pocet);
        for (int i = 0; i < pocet; i++) {
            System.out.println(ProgramoveVypisy.zamestnaj + (i+1) + " : ");
            String meno = keyboard.nextLine();
            this.getZamestnanci().add(new ZamestnanecVyroby(meno));
        }
    }

    public void vykonajDochadzku () { // dochadzka zamestnancov vyroby
        int pocet = this.getPocetZamestnancov();
        Scanner keyboard = new Scanner(System.in);
        for (int i = 0; i < pocet; i++) {
            // vypisy
            System.out.print(ProgramoveVypisy.dochadzka);
            System.out.print(this.getZamestnanci().get(i).getMeno());
            System.out.println(ProgramoveVypisy.dochadzka2);
            // input
            char pritomny = keyboard.next().charAt(0);
            // evidencia
            if (Character.toUpperCase(pritomny) == 'A') {
                this.getZamestnanci().get(i).prichodDoPrace();
                System.out.println(ProgramoveVypisy.pritomny);
            }
            else {
                System.out.println(ProgramoveVypisy.nepritomny);
            }
        }
    }

    public void vykonajDochadzku (String meno) { // pretazena metoda
        int pocet = this.getPocetZamestnancov();
        int id = pocet + 1;

        Scanner keyboard = new Scanner(System.in);

        for (int i = 0; i < pocet; i++) {

            if (this.getZamestnanci().get(i).meno.equals(meno)) {
                id = i;
                break;
            }
        }
        if (0 <= id && id < pocet) {
            System.out.print(ProgramoveVypisy.dochadzka);
            System.out.print(this.getZamestnanci().get(id).getMeno());
            System.out.println(ProgramoveVypisy.dochadzka2);

            char pritomny = keyboard.next().charAt(0);
            if (Character.toUpperCase(pritomny) == 'A') {
                this.getZamestnanci().get(id).prichodDoPrace();
                System.out.println(ProgramoveVypisy.pritomny);
            }
            else {
                System.out.println(ProgramoveVypisy.nepritomny);
            }
        }
        else {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorDochadzka + ProgramoveVypisy.white);
        }
    }

    public void prichodDoPrace() { // override Zamestnanec
        this.vPraci = true;
    }

    public void odchodZPrace () { // override Zamestnanec
        this.hromadnyOdchod();
        this.vPraci = false;
    }

    public void hromadnyOdchod () {
        int pocet = this.getPocetZamestnancov();
        for (int i = 0; i < pocet; i++) {
            this.getZamestnanci().get(i).odchodZPrace(); // odchod vs. zamestnancov
        }
    }

    public void vykonajHlasenie () {
        System.out.print(ProgramoveVypisy.prezentujSa);
        System.out.print(this.getMeno());

        if (this.getPocetZamestnancov() > 0) { // ak ma podriadenych

            System.out.println(ProgramoveVypisy.podriadeni);

            for (int i = 0; i<this.getPocetZamestnancov(); i++){
                System.out.print("\t"+ProgramoveVypisy.dochadzka3);
                System.out.print(this.getZamestnanci().get(i).getMeno());
                if (this.getZamestnanci().get(i).vPraci == true) {
                    System.out.println(ProgramoveVypisy.pritomny2);
                }
                else {
                    System.out.println(ProgramoveVypisy.nepritomny2);
                }
            }
        }
        // ak nema podriadenych
        else {
            System.out.println("\n\t" + ProgramoveVypisy.bezPodriadenych);
        }
    }

    public void vykonajHlasenieObjednavok () {
        System.out.println(ProgramoveVypisy.objednavky);
        for (int i = 0; i < this.ulohy.size(); i++) {
            //System.out.print("\t");
            this.ulohy.get(i).vypisObjednavku();
        }
    }

    public void preberObjednavku (ObjednavkaZakaznika objednavka) {
        this.ulohy.add(objednavka);
    }


    // GET & SET ----------------------------------------------------------------

    @Override
    public float getMzda() {
        return super.getMzda();
    }

    @Override
    public String getMeno() {
        return super.getMeno();
    }

    public ArrayList<ZamestnanecVyroby> getZamestnanci() {
        return zamestnanci;
    }

    public int getPocetZamestnancov() {
        return pocetZamestnancov;
    }

    public void setZamestnanci(ArrayList<ZamestnanecVyroby> zamestnanci) {
        this.zamestnanci = zamestnanci;
    }

    @Override
    public void setMeno(String meno) {
        super.setMeno(meno);
    }

    @Override
    public void setMzda(float mzda) {
        super.setMzda(mzda);
    }

    @Override
    public void setvPraci(boolean vPraci) {
        super.setvPraci(vPraci);
    }

    public void setPocetZamestnancov(int pocetZamestnancov) {
        this.pocetZamestnancov = pocetZamestnancov;
    }

    public ArrayList<ObjednavkaZakaznika> getUlohy() {
        return ulohy;
    }

    public void setUlohy(ArrayList<ObjednavkaZakaznika> ulohy) {
        this.ulohy = ulohy;
    }

    public boolean getVPraci() {
        return this.vPraci;
    }
}

