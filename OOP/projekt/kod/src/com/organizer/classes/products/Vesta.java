package com.organizer.classes.products;

public class Vesta extends Sveter {
    private String velkost;
    private boolean damske;
    private int spotrebaKlbiek;
    private float cenaMaterialu;
    private Material materialVesty;

    public Vesta() {

    }

    public Vesta (String velkost, boolean damske, String material) {
        this.materialVesty = new Material(material);

        this.velkost = velkost;
        this.damske = damske;

        if (damske) {
            switch (velkost) {
                case "XS":
                    this.spotrebaKlbiek = 4;
                    break;
                case "S":
                    this.spotrebaKlbiek = 5;
                    break;
                case "M":
                    this.spotrebaKlbiek = 6;
                    break;
                case "L":
                    this.spotrebaKlbiek = 7;
                    break;
                case "XL":
                    this.spotrebaKlbiek = 9;
                    break;
                default:
                    break;
            }
        } else {
            switch (velkost) {
                case "XS":
                    this.spotrebaKlbiek = 68;
                    break;
                case "S":
                    this.spotrebaKlbiek = 8;
                    break;
                case "M":
                    this.spotrebaKlbiek = 10;
                    break;
                case "L":
                    this.spotrebaKlbiek = 12;
                    break;
                case "XL":
                    this.spotrebaKlbiek = 14;
                    break;
                default:
                    break;
            }
        }

        this.cenaMaterialu = vypocitajCenu(this.spotrebaKlbiek);
    }

    // get / set

    @Override
    public float getCenaMaterialu() {
        return this.cenaMaterialu;
    }

    @Override
    public String getVelkost() {
        return this.velkost;
    }

    @Override
    public int getSpotrebaKlbiek() {
        return this.spotrebaKlbiek;
    }

    public Material getMaterialVesty() {
        return this.materialVesty;
    }

    @Override
    public void setDamske(boolean damske) {
        this.damske = damske;
    }

    @Override
    public void setCenaMaterialu(float cenaMaterialu) {
        this.cenaMaterialu = cenaMaterialu;
    }

    @Override
    public void setVelkost(String velkost) {
        this.velkost = velkost;
    }

    @Override
    public void setSpotrebaKlbiek(int spotrebaKlbiek) {
        this.spotrebaKlbiek = spotrebaKlbiek;
    }

    public void setMaterialVesty(Material materialVesty) {
        this.materialVesty = materialVesty;
    }



}
