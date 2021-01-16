package com.organizer.triedy;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

public class Zapas implements Serializable {
    private boolean dvojhra;
    private ArrayList<Hrac> hraci;
    private int kolo;
    private int cisloZapasu;
    private Kurt Cobain; // cislo kurtu
    private Date zaciatokZapasu;
    private Date koniecZapasu;

    /**
     * TODO: pamätať si a upravovať predom alebo počas zadané hodnoty výsledku a víťaza
     */


    public ArrayList<Hrac> getHraci() {
        return hraci;
    }

    public void setHraci(ArrayList<Hrac> hraci) {
        this.hraci = hraci;
    }

    public Date getKoniecZapasu() {
        return koniecZapasu;
    }

    public void setKoniecZapasu(Date koniecZapasu) {
        this.koniecZapasu = koniecZapasu;
    }

    public Date getZaciatokZapasu() {
        return zaciatokZapasu;
    }

    public void setZaciatokZapasu(Date zaciatokZapasu) {
        this.zaciatokZapasu = zaciatokZapasu;
    }

    public int getCisloZapasu() {
        return cisloZapasu;
    }

    public void setCisloZapasu(int cisloZapasu) {
        this.cisloZapasu = cisloZapasu;
    }

    public int getKolo() {
        return kolo;
    }

    public void setKolo(int kolo) {
        this.kolo = kolo;
    }

    public Kurt getCobain() {
        return Cobain; //boss music starts
    }

    public void setCobain(Kurt cobain) {
        Cobain = cobain;
    }

    public boolean getDvojhra() {
        return this.dvojhra;
    }

    public void setDvojhra(boolean dvojhra) {
        this.dvojhra = dvojhra;
    }
}
