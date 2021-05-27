package com.organizer.classes.products;

public class Sveter {
    private String velkost;
    private boolean damske;
    private int spotrebaKlbiek;
    private float cenaMaterialu;
    private Material materialSvetra;

    public Sveter() {
        this.velkost = "";
        this.cenaMaterialu = 0;
        this.spotrebaKlbiek = 0;
        this.damske = true;
    }

    public Sveter(String velkost, boolean damske, String material) {
        this.materialSvetra = new Material(material);

        this.velkost = velkost;
        this.damske = damske;

        if (damske) {
            switch (velkost) {
                case "XS":
                    this.spotrebaKlbiek = 6;
                    break;
                case "S":
                    this.spotrebaKlbiek = 7;
                    break;
                case "M":
                    this.spotrebaKlbiek = 8;
                    break;
                case "L":
                    this.spotrebaKlbiek = 9;
                    break;
                case "XL":
                    this.spotrebaKlbiek = 10;
                    break;
                default:
                    break;
            }
        } else {
            switch (velkost) {
                case "XS":
                    this.spotrebaKlbiek = 8;
                    break;
                case "S":
                    this.spotrebaKlbiek = 10;
                    break;
                case "M":
                    this.spotrebaKlbiek = 12;
                    break;
                case "L":
                    this.spotrebaKlbiek = 14;
                    break;
                case "XL":
                    this.spotrebaKlbiek = 16;
                    break;
                default:
                    break;
            }
        }

        this.cenaMaterialu = vypocitajCenu(this.spotrebaKlbiek);
    }

    protected float vypocitajCenu(int spotrebaKlbiek) {
        return (Material.getCenaZaKlbko() * spotrebaKlbiek);
    }


    // GET & SET ----------------------------------------------------------------

    public String getVelkost() {
        return velkost;
    }

    public void setVelkost(String velkost) {
        this.velkost = velkost;
    }

    public float getCenaMaterialu() {
        return cenaMaterialu;
    }

    public void setCenaMaterialu(float cenaMaterialu) {
        this.cenaMaterialu = cenaMaterialu;
    }

    public int getSpotrebaKlbiek() {
        return spotrebaKlbiek;
    }

    public void setSpotrebaKlbiek(int spotrebaKlbiek) {
        this.spotrebaKlbiek = spotrebaKlbiek;
    }

    public void setDamske(boolean damske) {
        this.damske = damske;
    }

    public Material getMaterialSvetra() {
        return materialSvetra;
    }

    public void setMaterialSvetra(Material materialSvetra) {
        this.materialSvetra = materialSvetra;
    }
}
