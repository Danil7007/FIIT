package com.organizer.triedy.turnaje;

import com.organizer.triedy.Den;
import com.organizer.triedy.Hrac;
import com.organizer.triedy.Kategoria;
import com.organizer.triedy.Turnaj;

import java.util.ArrayList;
import java.util.Date;

public class TurnajB extends Turnaj {

    public TurnajB(int pocetDni, boolean leto, int velkostPavuka, Date zaciatokTurnaja, ArrayList<Hrac> hraci) {
        super();
        this.kategoria = new Kategoria('B', leto); // instanciuje kategoriu
        this.dni = new ArrayList<Den>(pocetDni);
        this.velkostPavuka = velkostPavuka;
        this.zaciatokTurnaja = zaciatokTurnaja;
        this.hraci = hraci;
    }

}
