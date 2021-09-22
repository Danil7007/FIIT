package com.organizer.pozorovatelia;

import com.organizer.triedy.Zapas;

public class PrvyZapasPozorovatel extends Pozorovatel{
    private Zapas posledny;

    @Override
    public void update(Zapas data) {
        this.posledny = data;
    }
}
