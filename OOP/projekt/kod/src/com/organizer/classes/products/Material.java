package com.organizer.classes.products;

public class Material {
    private static float cenaZaKlbko;
    private String farba;
    private String nazovMaterialu;

    public Material() {
        this.farba = "";
        cenaZaKlbko = 0;
        this.nazovMaterialu = "";
    }

    public Material(String material) {
        this.nazovMaterialu = material;

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
    }

    // GET & SET ----------------------------------------------------------------

    public static float getCenaZaKlbko() {
        return cenaZaKlbko;
    }

    public static void setCenaZaKlbko(float cenaZaKlbko) {
        Material.cenaZaKlbko = cenaZaKlbko;
    }

    public String getFarba() {
        return farba;
    }

    public void setFarba(String farba) {
        this.farba = farba;
    }

    public String getNazovMaterialu() {
        return nazovMaterialu;
    }

    public void setNazovMaterialu(String nazovMaterialu) {
        this.nazovMaterialu = nazovMaterialu;
    }
}
