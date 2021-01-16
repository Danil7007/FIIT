package com.organizer.triedy.pavuk;

import com.organizer.triedy.Zapas;

import java.util.ArrayList;
import java.util.Date;

public class Runda extends Kolo {
    private Date cas;
    private Kolo kolo;

    // konstruktory

    public Runda() {
        super();
        zapasy = new ArrayList<Zapas>(0);
    }

    public Runda(Kolo kolo) {
        super();
        zapasy = new ArrayList<Zapas>(0);
        this.kolo = kolo;
    }

    // metoda na pridelenie casov zapasom v jednej runde
    public void pridelCasy() {
        for (int i = 0; i < zapasy.size(); i++) {
            zapasy.get(i).setZaciatokZapasu(cas);
        }
    }

    public Date getCas() {
        return cas;
    }

    // GET SET ---------------------------------------------------------------------
    public void setCas(Date cas) {
        this.cas = cas;
    }

    public Kolo getKolo() {
        return kolo;
    }

    public void setKolo(Kolo kolo) {
        this.kolo = kolo;
    }
}
