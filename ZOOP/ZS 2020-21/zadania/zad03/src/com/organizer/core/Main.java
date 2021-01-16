package com.organizer.core;

import com.organizer.triedy.Turnaj;
import com.organizer.triedy.pavuk.Pavuk;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        uvodnyText();
        Scanner keyboard = new Scanner(System.in);
        int input;
        boolean pokracuj = false; // na ukoncovanie vstupu
        Turnaj turnaj = null;
        Pavuk pavuk = null;

        // nacitanie zo suboru?
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
                turnaj = Turnaj.vytvorTurnaj(); // volanie metody
                pavuk = turnaj.getPavuk();
                pavuk.vytvorKola(); // volanie metody
                pokracuj = true;
            } else {
                System.out.println("Zly vstup, skus to znova");
            }
        }

        // todo --- pre zadanie vysledkov(5)
        // todo implementovat stvorhry?

        // menu
        System.out.println("\n\u001B[36m" + "--- MANUAL\u001B[0m\n--- pre vypis pavuka (1)\n--- pre vypis zapasov na kurte (2)\n--- pre vypis rund (3)\n--- pre vypis zisku (4)\n--- pre ulozenie (5)\n--- pre ukoncenie (0)");
        while ((input = Character.getNumericValue(keyboard.next().charAt(0))) != 0) {
            switch (input) {
                case 1: // staticka metoda na vypis pavuka
                    Pavuk.vypisPavuk(pavuk);
                    break;
                case 2: // vypisanie podla kurtov
                    System.out.println("Zadaj cislo kurtu");
                    turnaj.getZoznamKurtov().get(keyboard.nextInt() - 1).vypisZapasy();
                    break;
                case 3: // vypis podla rund
                    Pavuk.vypisRundy(pavuk);
                    break;
                case 4:
                    System.out.println("Zisk je "+turnaj.vypocitajZisk()+" EUR slovenskych\n");
                    break;
                case 5: // ulozenie dat
                    DataHandler.saveData(turnaj);
                    break;
                default:
                    System.out.println("Neplatny vstup");
                    break;
            }
            System.out.println("\u001B[36m" + "--- MANUAL\u001B[0m\n--- pre vypis pavuka (1)\n--- pre vypis zapasov na kurte (2)\n--- pre vypis rund (3)\n--- pre vypis zisku (4)\n--- pre ulozenie (5)\n--- pre ukoncenie (0)");
        }

        // upozornenie
        System.out.println("Chystate sa vypnut program. Udaje mozno neboli ulozene praje ulozit? (y/n)");

        // ulozenie ?
        if (keyboard.next().charAt(0) == 'y') {
            DataHandler.saveData(turnaj);
            System.out.println("Ulozene, dovi");
        } else {
            System.out.println("Neulozene, dovi");
        }

    }

    public static final void uvodnyText(){
        System.out.println("\u001B[35m" + "Tournament Organizer v.001.05" + "\u001B[0m");
    }
}
