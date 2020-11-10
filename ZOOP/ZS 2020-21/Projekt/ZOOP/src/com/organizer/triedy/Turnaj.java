package com.organizer.triedy;

import com.organizer.core.Pavuk;
import com.organizer.triedy.turnaje.*;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

public class Turnaj implements Serializable {
    protected Kategoria kategoria;
    protected int pocetKurtov;
    protected int pocetDni;
    protected static int velkostPavuka;
    protected Date zaciatokTurnaja;
    protected ArrayList<Hrac> hraci;
    protected ArrayList<Zapas> zapasy;
    protected ArrayList<Den> dni;
    protected ArrayList<Kurt> zoznamKurtov;
    protected Pavuk pavuk;


    public Turnaj(){

    }

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
        this.velkostPavuka = velkostPavuka;
    }

    public Kategoria getKategoria() {
        return kategoria;
    }

    public void setKategoria(Kategoria kategoria) {
        this.kategoria = kategoria;
    }

    //--------------------------------------------------------------------------------

    public static Turnaj vytvorTurnaj(char typ) {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Ak leto zadaj 1 ak zima 0:");
        boolean leto = (keyboard.nextInt() == 1);
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
        switch (typ) {
            case 'A':
                TurnajA turnajA = new TurnajA(3, leto, velkostPavuka, datum, hrac);
                pavuk = new Pavuk(velkostPavuka,turnajA);
                turnajA.setPavuk(pavuk);
                return turnajA;
            case 'B':
                TurnajB turnajB = new TurnajB(3, leto, velkostPavuka, datum, hrac);
                pavuk = new Pavuk(velkostPavuka,turnajB);
                turnajB.setPavuk(pavuk);
                return turnajB;
            case 'C':
                TurnajC turnajC = new TurnajC(3, leto, velkostPavuka, datum, hrac);
                pavuk = new Pavuk(velkostPavuka,turnajC);
                turnajC.setPavuk(pavuk);
                return turnajC;
            case 'D':
                TurnajD turnajD = new TurnajD(3, leto, velkostPavuka, datum, hrac);
                pavuk = new Pavuk(velkostPavuka,turnajD);
                turnajD.setPavuk(pavuk);
                return turnajD;
            default:
                System.out.println("Neplatny vstup");
                return null;
        }

    }
}

