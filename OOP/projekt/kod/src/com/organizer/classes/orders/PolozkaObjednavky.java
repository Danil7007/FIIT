package com.organizer.classes.orders;

import com.organizer.classes.products.Material;

public class PolozkaObjednavky {
    private String farba;
    private String material;
    private String velkost;
    private String nazovPolozky;
    private int damske;
    private float cenaPolozky;

    public PolozkaObjednavky(String nazovPolozky, String farba, String material, String velkost, int damske) {
        this.farba = farba.toLowerCase();
        this.material = material.toLowerCase();
        this.velkost = velkost.toUpperCase();
        this.nazovPolozky = nazovPolozky.toLowerCase();
        this.damske = damske;
        this.cenaPolozky = vypocitajCenuPolzky(velkost, damske, material);
    }

    public PolozkaObjednavky() {

    }

    public static boolean skontrolujInput(String nazovPolozky, String farba, String material, String velkost, int damske) {

        switch (material.toLowerCase()) { // kontrola materialu
            case "bavlna":
                break;
            case "merino":
                break;
            case "moher":
                break;
            case "hodvab":
                break;
            default:
               return false;
        }

        switch (nazovPolozky.toLowerCase()) { // kontrola polozky
            case "vesta":
                break;
            case "sveter":
                break;
            default:
                return false;
        }

        switch (velkost.toUpperCase()) { // kontrola velkosti
            case "XS":
            case "S":
            case "M":
            case "L":
            case "XL":
                break;
            default:
                return false;
        }

        switch (damske) { // kontrola strihu
            case 1:
                break;
            case 0:
                break;
            default:
                return false;
        }

        return true;
    }

    public float vypocitajCenuPolzky (String velkost, int damske, String material) {

        int spotrebaKlbiek = 0;
        int rozdiel = 0;
        float cenaZaKlbko = 0;

        switch (material) {
            case "bavlna":
                cenaZaKlbko = 5;
                break;
            case "hodvab":
                cenaZaKlbko = 18;
                break;
            case "merino":
                cenaZaKlbko = 11;
                break;
            case "moher":
                cenaZaKlbko = 14;
                break;
            default:
                break;
        }

        if (damske == 1) {
            switch (velkost) {
                case "XS":
                    spotrebaKlbiek = 6 + rozdiel;
                    break;
                case "S":
                    spotrebaKlbiek = 7 + rozdiel;
                    break;
                case "M":
                    spotrebaKlbiek = 8 + rozdiel;
                    break;
                case "L":
                    spotrebaKlbiek = 9 + rozdiel;
                    break;
                case "XL":
                    spotrebaKlbiek = 10 + rozdiel;
                    break;
                default:
                    break;
            }
        } else {
            switch (velkost) {
                case "XS":
                    spotrebaKlbiek = 8 + rozdiel;
                    break;
                case "S":
                    spotrebaKlbiek = 10 + rozdiel;
                    break;
                case "M":
                    spotrebaKlbiek = 12 + rozdiel;
                    break;
                case "L":
                    spotrebaKlbiek = 14 + rozdiel;
                    break;
                case "XL":
                    spotrebaKlbiek = 16 + rozdiel;
                    break;
                default:
                    break;
            }
        }

        return (2 * cenaZaKlbko * spotrebaKlbiek);

    }


    // get set
    public String getVelkost() {
        return velkost;
    }

    public String getNazovPolozky() {
        return nazovPolozky;
    }

    public String getMaterial() {
        return material;
    }

    public String getFarba() {
        return farba;
    }

    public void setVelkost(String velkost) {
        this.velkost = velkost;
    }

    public void setMaterial(String material) {
        this.material = material;
    }

    public void setFarba(String farba) {
        this.farba = farba;
    }

    public int getDamske() {
        return damske;
    }

    public void setDamske(int damske) {
        this.damske = damske;
    }

    public void setNazovPolozky(String nazovPolozky) {
        this.nazovPolozky = nazovPolozky;
    }

    public float getCenaPolozky() {
        return cenaPolozky;
    }

    public void setCenaPolozky(float cenaPolozky) {
        this.cenaPolozky = cenaPolozky;
    }
}
