package com.organizer.triedy;

import java.util.ArrayList;
import java.util.Date;

public class Zapas {
    private boolean dvojhra;
    private ArrayList<Hrac> hraci;
    private int kolo;
    private int cisloZapasu;
    private Kurt Cobain; // cislo kurtu TODO: anektodtky a mentálne kotrmelce
    private Date zaciatokZapasu;
    private Date koniecZapasu;

    /**
     * TODO: Debatovali sme o mentálnom konštrukte ktorý má zabezpečiť schopnosť programu pamätať si a upravovať predom alebo počas zadané hodnoty výsledku a víťaza
     */

    public Zapas() {

    }

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

    public void setDvojhra(boolean dvojhra) {
        this.dvojhra = dvojhra;
    }
}
