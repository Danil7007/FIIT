package com.organizer.core;

import com.organizer.triedy.Turnaj;
import com.organizer.triedy.pavuk.Pavuk;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println("Tournament Organizer v.001.01");
        Scanner keyboard = new Scanner(System.in);
        int input;
        boolean pokracuj = false;
        Turnaj turnaj = null;
        Pavuk pavuk = null;

        while (!pokracuj) {
            System.out.println("Zelate si turnaj nacitat (n) alebo vytvorit (v)?");
            char nv = keyboard.next().charAt(0);
            if (nv == 'n') {
                turnaj = DataHandler.loadData();
                if (turnaj == null) {
                    System.out.println("Nepodarilo sa nacitat!");
                } else {
                    pavuk = turnaj.getPavuk();
                    pokracuj = true;
                }
            } else if (nv == 'v') {
                turnaj = Turnaj.vytvorTurnaj();
                pavuk = turnaj.getPavuk();
                pavuk.vytvorKola();
                pokracuj = true;
            } else {
                System.out.println("Zly vstup, skus to znova");
            }
        }

        System.out.println("--- MANUAL\n--- pre vypis (1)\n--- pre nieco (2)\n--- pre ukoncenie (0)");
        while ((input = Character.getNumericValue(keyboard.next().charAt(0))) != 0) {
            switch (input) {
                case 1:
                    Pavuk.vypisPavuk(pavuk);
                    break;
                case 2:
                    break;
                default:
                    System.out.println("Neplatny vstup");
                    break;
            }
            System.out.println("--- MANUAL\n--- pre vypis (1)\n--- pre nieco (2)\n--- pre ukoncenie (0)");
        }
        System.out.println("Chystate sa vypnut program. Udaje mozno neboli ulozene praje ulozit? (y/n)");

        if (keyboard.next().charAt(0) == 'y') {
            DataHandler.saveData(turnaj);
            System.out.println("Ulozene, dovi");
        } else {
            System.out.println("Neulozene, dovi");
        }


    }
}
