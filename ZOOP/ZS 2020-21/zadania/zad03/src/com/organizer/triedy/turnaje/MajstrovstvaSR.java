package com.organizer.triedy.turnaje;

import com.organizer.triedy.Den;
import com.organizer.triedy.Hrac;
import com.organizer.triedy.Kategoria;
import com.organizer.triedy.Turnaj;
import com.organizer.triedy.pavuk.Pavuk;

import java.util.ArrayList;
import java.util.Date;


public class MajstrovstvaSR extends TurnajA {

    public MajstrovstvaSR(int pocetDni, boolean leto, int velkostPavuka, Date zaciatokTurnaja, ArrayList<Hrac> hraci) {
        super(); //demonstracia viacnasobneho dedenia
        this.kategoria = new Kategoria('A', leto); // instanciuje kategoriu
        this.dni = new ArrayList<Den>(pocetDni);
        Turnaj.velkostPavuka = velkostPavuka;
        this.zaciatokTurnaja = zaciatokTurnaja;
        this.hraci = hraci;
    }

    public static Turnaj vytvorTurnaj(char typ) {
        Date datum = new Date();
        datum.setMonth(3);
        datum.setDate(12);
        datum.setHours(8);
        datum.setMinutes(0);
        datum.setSeconds(0);
        ArrayList<Hrac> hrac = Hrac.nacitajHracov(velkostPavuka);
        Pavuk pavuk;
        MajstrovstvaSR MS = new MajstrovstvaSR(3, true, velkostPavuka, datum, hrac);
        pavuk = new Pavuk(velkostPavuka, MS);
        MS.setPavuk(pavuk);
        return MS;
    }

}
