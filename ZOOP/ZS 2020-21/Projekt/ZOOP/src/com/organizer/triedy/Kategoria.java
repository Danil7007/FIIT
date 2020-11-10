package com.organizer.triedy;

public class Kategoria {
    private char kategoria; // A B C D
    private boolean leto; // leto / zima
    private int maxDvojhry;
    private int maxStvorhry;
    private int maxZapasov; // limit zapasov
    private int vklad; // poplatok hraca
    private int odhadTrvania; // zapasu

    public Kategoria() {
        this.kategoria = ' ';
        this.maxDvojhry = 0;
        this.maxStvorhry = 0;
        this.maxZapasov = 0;
        this.vklad = 0;
        this.odhadTrvania = 0;
        this.leto = true;
    }

    public Kategoria (char kategoria, boolean leto) {
        if (kategoria == 'A' || kategoria == 'B' || kategoria == 'C' || kategoria == 'D') {
            this.kategoria = kategoria;
            this.leto = leto;
            switch (kategoria) {
                case 'A':
                    maxZapasov = 3;
                    maxDvojhry = 2;
                    maxStvorhry = 2;
                    if (leto) {
                        vklad = 17;
                    } else {
                        vklad = 24;
                    }
                    break;
                case 'B':
                    maxZapasov = 3;
                    maxDvojhry = 2;
                    maxStvorhry = 2;
                    if (leto) {
                        vklad = 13;
                    } else {
                        vklad = 20;
                    }
                    break;
                case 'C':
                    maxZapasov = 4;
                    maxDvojhry = 2;
                    maxStvorhry = 3;
                    if (leto) {
                        vklad = 11;
                    } else {
                        vklad = 17;
                    }
                    break;
                case 'D':
                    maxZapasov = 4;
                    maxDvojhry = 2;
                    maxStvorhry = 3;
                    if (leto) {
                        vklad = 9;
                    } else {
                        vklad = 13;
                    }
                    break;
            }
        }

    }

    // GET & SET -------------------------------------------------
    public char getKategoria() {
        return kategoria;
    }

    public void setKategoria(char kategoria) {
        this.kategoria = kategoria;
    }

    public int getMaxDvojhry() {
        return maxDvojhry;
    }

    public void setMaxDvojhry(int maxDvojhry) {
        this.maxDvojhry = maxDvojhry;
    }

    public int getMaxStvorhry() {
        return maxStvorhry;
    }

    public void setMaxStvorhry(int maxStvorhry) {
        this.maxStvorhry = maxStvorhry;
    }

    public int getMaxZapasov() {
        return maxZapasov;
    }

    public void setMaxZapasov(int maxZapasov) {
        this.maxZapasov = maxZapasov;
    }

    public int getVklad() {
        return vklad;
    }

    public void setVklad(int vklad) {
        this.vklad = vklad;
    }

    public int getOdhadTrvania() {
        return odhadTrvania;
    }

    public void setOdhadTrvania(int odhadTrvania) {
        this.odhadTrvania = odhadTrvania;
    }
}
