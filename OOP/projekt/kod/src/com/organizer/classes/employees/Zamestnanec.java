package com.organizer.classes.employees;

public class Zamestnanec implements Zamestnanci {
    protected String meno;
    protected boolean vPraci;
    protected float mzda;

    public Zamestnanec() {
        this.meno = "";
        this.vPraci = false;
    }

    public Zamestnanec(String meno) {
        this.meno = meno;
    }

    public void prichodDoPrace() { // override Zamestnanci
        this.vPraci = true;
    }

    public void odchodZPrace() { // override Zamestnanci
        this.vPraci = false;
    }


    // GET & SET ----------------------------------------------------------------

    public String getMeno() {
        return meno;
    }

    public float getMzda() {
        return mzda;
    }

    public void setMeno(String meno) {
        this.meno = meno;
    }

    public void setMzda(float mzda) {
        this.mzda = mzda;
    }

    public void setvPraci(boolean vPraci) {
        this.vPraci = vPraci;
    }
}
