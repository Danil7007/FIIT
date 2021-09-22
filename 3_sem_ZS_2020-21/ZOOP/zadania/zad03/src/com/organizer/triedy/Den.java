package com.organizer.triedy;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

public class Den implements Serializable {
    private Date datum; //access modifiers
    private ArrayList<Zapas> dennyRozpisZapasov;
    private int poradie;

    public Den() {
        datum = new Date();
        ArrayList<Zapas> dennyRozpisZapasov = new ArrayList<Zapas>(1);
    }


    // GET SET -------------------------------------------------------------------------

    public ArrayList<Zapas> getDennyRozpisZapasov() {
        return dennyRozpisZapasov;
    }

    public void setDennyRozpisZapasov(ArrayList<Zapas> dennyRozpisZapasov) {
        this.dennyRozpisZapasov = dennyRozpisZapasov;
    }

    public Date getDatum() {
        return datum;
    }

    public void setDatum(Date datum) {
        this.datum = datum;
    }

    public int getPoradie() {
        return poradie;
    }

    public void setPoradie(int poradie) {
        this.poradie = poradie;
    }
}
