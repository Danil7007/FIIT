package com.organizer.classes.employees;

import com.organizer.classes.orders.ObjednavkaZakaznika;
import com.organizer.classes.products.Sveter;

import java.io.Serializable;
import java.util.ArrayList;

public class ZamestnanecVyroby extends Zamestnanec implements Serializable {
    private ArrayList<ObjednavkaZakaznika> ulohy;

    public ZamestnanecVyroby(String meno) {
        super();
        this.meno = meno;
        this.mzda = 5;
        this.ulohy = new ArrayList<ObjednavkaZakaznika>(0);
    }

    public ZamestnanecVyroby() {
        super();
        this.mzda = 5;
    }

    public Sveter vytvorSveter () {
        Sveter sveter = new Sveter();
        return sveter;
    }


}
