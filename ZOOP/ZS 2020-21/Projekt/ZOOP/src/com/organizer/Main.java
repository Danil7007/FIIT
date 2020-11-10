package com.organizer;

import com.organizer.core.Kolo;
import com.organizer.core.Pavuk;
import com.organizer.triedy.Turnaj;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Zadaj kategoriu:");
        Turnaj turnaj = Turnaj.vytvorTurnaj(keyboard.next().charAt(0));
        Pavuk pavuk = turnaj.getPavuk();
        pavuk.vytvorKola();
        for(int i = 0; i<pavuk.getKola().size();i++){
            System.out.println("Kolo:"+i);
            Kolo kolo = pavuk.getKola().get(i);
            for(int i1 = 0;i1 < kolo.getZapasy().size();i1++){
                System.out.println("Zapas:"+i1);
                for(int i2 = 0;i2<kolo.getZapasy().get(i1).getHraci().size();i2++){
                    System.out.println(i2+"Hrac:"+kolo.getZapasy().get(i1).getHraci().get(i2).getMeno());

                }
            }
        }
       }
}
