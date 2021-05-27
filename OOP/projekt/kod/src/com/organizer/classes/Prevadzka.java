package com.organizer.classes;

import com.organizer.classes.employees.Manazer;
import com.organizer.classes.employees.ZamestnanecVyroby;
import com.organizer.classes.orders.ObjednavkaZakaznika;
import com.organizer.messages.ProgramoveVypisy;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

public class Prevadzka implements Serializable {
    private ArrayList<Manazer> manazeri;
    //private ArrayList<ZamestnanecVyroby> zamestnanci;
    private int pocetZamestnancov;
    private int pocetManazerov;
    private String nazovPrevadzky;
    //TODO: private Sklad sklad;
    private ArrayList<ObjednavkaZakaznika> aktivneObjednavky;
    //TODO: private ArrayList<Objednavka> vybaveneObjednavky;

    // singleton
    private static Prevadzka prevadzka = null;

    private Prevadzka () {
        //this.zamestnanci = new ArrayList<ZamestnanecVyroby>(0);
        this.manazeri = new ArrayList<Manazer>(0);
        this.aktivneObjednavky = new ArrayList<ObjednavkaZakaznika>(0);
        this.nazovPrevadzky = "";
        this.pocetManazerov = 0;
        this.pocetZamestnancov = 0;
    }


    // metody

    public static Prevadzka getInstance() {
        if (prevadzka == null) {
            prevadzka = new Prevadzka();
        }
        return prevadzka;
    }

    public void rozdeleniePrace () {
        int index;
        int j = 0;
        for (int i = (aktivneObjednavky.size() - 1); i >= 0; i--) {

            if (i == 0) {
                index = 0;
            }
            else {
                index = i % this.pocetManazerov;
            }
            ObjednavkaZakaznika objednavka = this.aktivneObjednavky.get(j);
            // predanie objednavky manazerovi
            //System.out.println(this.getManazeri().get(index).getMeno());
            //System.out.println(objednavka.getPolozky().get(0).getNazovPolozky());
            this.getManazeri().get(index).preberObjednavku(objednavka);
            j++;
        }

        for (int i = (aktivneObjednavky.size() - 1); i >= 0; i--) {
            // odstranenie z aktivnych
            this.aktivneObjednavky.remove(this.aktivneObjednavky.get(i));
        }

    }

    public void zamestnajManazerov(int pocet) {
        System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.zamestnajManazerov + ProgramoveVypisy.white);
        Scanner keyboard = new Scanner(System.in);
        this.setPocetManazerov(this.getPocetManazerov() + pocet);
        for (int i = 0; i < pocet; i++) {
            System.out.println(ProgramoveVypisy.zamestnajManazera + (i+1) + " : ");
            String meno = keyboard.nextLine();
            this.getManazeri().add(new Manazer(meno));
        }
    }

    public void zamestnajZamestnancovVyroby() {
        Scanner keyboard = new Scanner(System.in);
        System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.zamestnajVyrobu + ProgramoveVypisy.white);
        for (int i = 0; i < this.getPocetManazerov(); i++) {
            System.out.print(ProgramoveVypisy.pocetPodriadenych);
            System.out.println(this.getManazeri().get(i).getMeno() + " ?");
            int pocet = keyboard.nextInt();
            this.getManazeri().get(i).zamestnaj(pocet);
            //this.getZamestnanci().addAll(this.getManazeri().get(i).getZamestnanci());
            this.setPocetZamestnancov(this.getPocetZamestnancov() + this.getManazeri().get(i).getPocetZamestnancov());
        }
    }

    public void personal() {
        System.out.println(ProgramoveVypisy.highlight + ProgramoveVypisy.personal + ProgramoveVypisy.white);
        for (int i = 0; i < this.getPocetManazerov(); i++) {

            if (this.getManazeri().get(i).getVPraci() == true) {
                System.out.println("Manažér " + this.getManazeri().get(i).getMeno() + " je v práci");
            }
            else {
                System.out.println("Manažér " + this.getManazeri().get(i).getMeno() + " nie je v práci");
            }

            System.out.print("\t");
            this.getManazeri().get(i).vykonajHlasenie();
        }
    }

    public void vypisManazerov() {
        for (int i = 0; i < this.getPocetManazerov(); i++) {
            System.out.println(this.getManazeri().get(i).getMeno());
        }
    }


    // GET & SET ----------------------------------------------------------------

    public int getPocetZamestnancov() {
        return pocetZamestnancov;
    }

    /*public ArrayList<ZamestnanecVyroby> getZamestnanci() {
        return zamestnanci;
    }*/

    public ArrayList<Manazer> getManazeri() {
        return manazeri;
    }

    public int getPocetManazerov() {
        return pocetManazerov;
    }

    public String getNazovPrevadzky() {
        return nazovPrevadzky;
    }

    public void setPocetZamestnancov(int pocetZamestnancov) {
        this.pocetZamestnancov = pocetZamestnancov;
    }

    /*public void setZamestnanci(ArrayList<ZamestnanecVyroby> zamestnanci) {
        this.zamestnanci = zamestnanci;
    }*/

    public void setManazeri(ArrayList<Manazer> manazeri) {
        this.manazeri = manazeri;
    }

    public void setNazovPrevadzky(String nazovPrevadzky) {
        this.nazovPrevadzky = nazovPrevadzky;
    }

    public ArrayList<ObjednavkaZakaznika> getAktivneObjednavky() {
        return aktivneObjednavky;
    }

    public static Prevadzka getPrevadzka() {
        return prevadzka;
    }

    public void setAktivneObjednavky(ArrayList<ObjednavkaZakaznika> aktivneObjednavky) {
        this.aktivneObjednavky = aktivneObjednavky;
    }

    public static void setPrevadzka(Prevadzka prevadzka) {
        Prevadzka.prevadzka = prevadzka;
    }

    public void setPocetManazerov(int pocetManazerov) {
        this.pocetManazerov = pocetManazerov;
    }

}
