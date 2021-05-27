package com.organizer.classes.orders;

import com.organizer.messages.ProgramoveVypisy;

import java.util.ArrayList;

public class ObjednavkaZakaznika {
    private boolean vybavena = false;
    private ArrayList<PolozkaObjednavky> polozky;
    private float cenaObjednavky = 0;

    public ObjednavkaZakaznika() {
        this.polozky = new ArrayList<PolozkaObjednavky>(0);
    }

    public void pridajPolozku (String nazovPolozky, String farba, String material, String velkost, int damske) {

        if (PolozkaObjednavky.skontrolujInput(nazovPolozky, farba, material, velkost, damske)) {
            PolozkaObjednavky novaPolozka = new PolozkaObjednavky(nazovPolozky, farba, material, velkost, damske);
            this.getPolozky().add(novaPolozka);
            this.cenaObjednavky += novaPolozka.getCenaPolozky();

            System.out.println(ProgramoveVypisy.okay);
        }
        else {
            System.out.println(ProgramoveVypisy.errorColor + ProgramoveVypisy.errorInput + ProgramoveVypisy.white);
        }

    }

    public void vypisObjednavku () {
        for (int i=0; i < getPolozky().size(); i++) {
            System.out.print("Typ: " + getPolozky().get(i).getNazovPolozky() + ", ");
            System.out.print("materiál: " + getPolozky().get(i).getMaterial() + ", ");
            System.out.print("farba: " + getPolozky().get(i).getFarba() + ", ");
            System.out.print("veľkosť: " + getPolozky().get(i).getVelkost() + ", ");
            if (getPolozky().get(i).getDamske() == 1) {
                System.out.print("strih: dámsky, ");
            }
            else {
                System.out.print("strih: pánsky, ");
            }
            System.out.println("cena: " + getPolozky().get(i).getCenaPolozky() + " EUR");
        }
        System.out.println("SPOLU: " + this.getCenaObjednavky() + " EUR");
    }

    // get set

    public ArrayList<PolozkaObjednavky> getPolozky() {
        return polozky;
    }

    public void setPolozky(ArrayList<PolozkaObjednavky> polozky) {
        this.polozky = polozky;
    }

    public void setVybavena(boolean vybavena) {
        this.vybavena = vybavena;
    }

    public float getCenaObjednavky() {
        return cenaObjednavky;
    }

    public void setCenaObjednavky(float cenaObjednavky) {
        this.cenaObjednavky = cenaObjednavky;
    }
}
