package com.organizer.triedy;

import com.organizer.triedy.pavuk.Pavuk;
import com.organizer.triedy.turnaje.TurnajA;
import com.organizer.triedy.turnaje.TurnajB;
import com.organizer.triedy.turnaje.TurnajC;
import com.organizer.triedy.turnaje.TurnajD;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

//abstraktná trieda slúži ako predpis triedy,
// nemôže vytvárať inštancie a môže obsahovať abstraktné ako aj ne-abstraktné metody

public abstract class Turnaj extends Turnaje implements Serializable {
    protected static int velkostPavuka;
    protected Kategoria kategoria;
    protected int pocetKurtov;
    protected int pocetDni;
    protected int zisk = 0;
    protected Date zaciatokTurnaja;
    protected ArrayList<Hrac> hraci;
    protected ArrayList<Zapas> zapasy;
    protected ArrayList<Den> dni;
    protected ArrayList<Kurt> zoznamKurtov;
    protected Pavuk pavuk;

    //priklad pretazenej metody
    public static Turnaj vytvorTurnaj() {
        boolean leto = true;
        boolean cnt = false;
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Zadaj kategoriu turnaja:");
        char typ = keyboard.next().charAt(0);
        System.out.println("Zadaj pocet kurtov:");
        int pocetKurtov = keyboard.nextInt();
        String tmp = keyboard.nextLine();
        System.out.println("Ak leto zadaj 1 ak zima 0:");
        do {
            int isLeto = Character.getNumericValue(keyboard.nextLine().charAt(0));
            if (isLeto == 1) {
                leto = true;
                cnt = true; // continue
            } else if (isLeto == 0) {
                leto = false;
                cnt = true;
            } else {
                System.out.println("\u001B[4m\u001B[31mZadali ste zlý vstup.\u001B[0m");
                System.out.println("Ak leto zadaj 1 ak zima 0:");
                isLeto = 10;
            }
        } while (!cnt);
        System.out.println("Zadaj velkost pavuka:");
        int velkostPavuka = keyboard.nextInt();
        Date datum = new Date();
        System.out.println("Zadaj cislo dna v mesiaci:");
        datum.setDate(keyboard.nextInt());
        System.out.println("Zadaj hodinu zaciatku turnaja:");
        datum.setHours(keyboard.nextInt());
        System.out.println("Zadaj minuty:");
        datum.setMinutes(keyboard.nextInt());
        datum.setSeconds(0);
        ArrayList<Hrac> hrac = Hrac.nacitajHracov(velkostPavuka);
        Pavuk pavuk;

        Turnaj turnaj;
        switch (Character.toUpperCase(typ)) {
            case 'A':
                turnaj = new TurnajA(3, leto, velkostPavuka, datum, hrac);
                break;
            case 'B':
                turnaj =  TurnajB.vytvorObjekt(3, leto, velkostPavuka, datum, hrac);
                break;
            case 'C':
                turnaj = new TurnajC(3, leto, velkostPavuka, datum, hrac);
                break;
            case 'D':
                turnaj = new TurnajD(3, leto, velkostPavuka, datum, hrac);
                break;
            default:
                System.out.println("Neplatny vstup");
                return null;
        }
        // vytvorenie kurtov
        turnaj.zoznamKurtov = new ArrayList<>(0);
        for (int i = 0; i < pocetKurtov; ++i) {
            Kurt kurt = new Kurt();
            kurt.setPoradie(i); // ocisluje kurty
            turnaj.zoznamKurtov.add(kurt); // naplni zoznam kurtov
        }
        // vytvorenie pavuka
        pavuk = new Pavuk(velkostPavuka, turnaj);
        turnaj.setPavuk(pavuk);
        return turnaj;
    }

    // tutok je pretazena
    public static Turnaj vytvorTurnaj(Turnaj truenaj) throws CloneNotSupportedException {
        Turnaj turnaj = truenaj.clone();
        return turnaj;

    }

    public Turnaj clone() throws CloneNotSupportedException {
        return (Turnaj) super.clone();
    }

    public int vypocitajZisk() {
        return (this.zisk = velkostPavuka*kategoria.getVklad());
    }

    //--------------------------------------------------------------------------------
    // GET SET

    public Pavuk getPavuk() {
        return pavuk;
    }

    public void setPavuk(Pavuk pavuk) {
        this.pavuk = pavuk;
    }

    public ArrayList<Hrac> getHraci() {
        return hraci;
    }

    public void setHraci(ArrayList<Hrac> hraci) {
        this.hraci = hraci;
    }

    public ArrayList<Zapas> getZapasy() {
        return zapasy;
    }

    public void setZapasy(ArrayList<Zapas> zapasy) {
        this.zapasy = zapasy;
    }

    public ArrayList<Den> getDni() {
        return dni;
    }

    public void setDni(ArrayList<Den> dni) {
        this.dni = dni;
    }

    public ArrayList<Kurt> getZoznamKurtov() {
        return zoznamKurtov;
    }

    public void setZoznamKurtov(ArrayList<Kurt> zoznamKurtov) {
        this.zoznamKurtov = zoznamKurtov;
    }

    public Date getZaciatokTurnaja() {
        return zaciatokTurnaja;
    }

    public void setZaciatokTurnaja(Date zaciatokTurnaja) {
        this.zaciatokTurnaja = zaciatokTurnaja;
    }

    public int getPocetDni() {
        return pocetDni;
    }

    public void setPocetDni(int pocetDni) {
        this.pocetDni = pocetDni;
    }

    public int getPocetKurtov() {
        return pocetKurtov;
    }

    public void setPocetKurtov(int pocetKurtov) {
        this.pocetKurtov = pocetKurtov;
    }

    public int getVelkostPavuka() {
        return velkostPavuka;
    }

    public void setVelkostPavuka(int velkostPavuka) {
        Turnaj.velkostPavuka = velkostPavuka;
    }

    public Kategoria getKategoria() {
        return kategoria;
    }

    public void setKategoria(Kategoria kategoria) {
        this.kategoria = kategoria;
    }
}

