package com.organizer.triedy.turnaje;

import com.organizer.triedy.Den;
import com.organizer.triedy.Hrac;
import com.organizer.triedy.Kategoria;
import com.organizer.triedy.Turnaj;

import java.util.ArrayList;
import java.util.Date;

public class TurnajB extends Turnaj {
    private static TurnajA turnaj;
    private TurnajB(int pocetDni, boolean leto, int velkostPavuka, Date zaciatokTurnaja, ArrayList<Hrac> hraci) {
        super();
        this.kategoria = new Kategoria('B', leto); // instanciuje kategoriu
        this.dni = new ArrayList<Den>(pocetDni);
        Turnaj.velkostPavuka = velkostPavuka;
        this.zaciatokTurnaja = zaciatokTurnaja;
        this.hraci = hraci;
    }

    public static Turnaj vytvorObjekt(int pocetDni, boolean leto, int velkostPavuka, Date zaciatokTurnaja, ArrayList<Hrac> hraci){
        if(turnaj == null){
            turnaj = new TurnajA(pocetDni,leto,velkostPavuka,zaciatokTurnaja,hraci);
        }
        return turnaj;
    }

}
