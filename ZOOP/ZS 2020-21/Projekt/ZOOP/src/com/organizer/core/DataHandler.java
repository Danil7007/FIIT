package com.organizer.core;

import com.organizer.triedy.Turnaj;

import java.io.*;
import java.util.Scanner;

// uloženie a načítanie suboru obsahuúceho data turnaja
// pomocou Serializable interface

public class DataHandler {
    private static final String pathName = System.getProperty("user.dir");  // ziska cestu k priečinku v ktorom sa vykonáva

    public static void saveData(Turnaj turnaj) {
        try {
            File subor = new File(pathName);
            subor.createNewFile();
            Scanner scanner = new Scanner(System.in);
            System.out.println("Zadaj meno suboru pre ulozenie:");
            FileOutputStream fileOut = new FileOutputStream(subor + "/" + scanner.next() + ".ser", false);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(turnaj);
            objectOut.close();
            fileOut.close();
        } catch (IOException e) {
            System.out.println("Subor sa nepodarilo ulozit pretoze:");
            e.printStackTrace();
        }
    }

    public static Turnaj loadData() { // nacitanie dat

        Turnaj turnaj = null;
        try {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Zadaj meno ulozeneho suboru:");
            FileInputStream fileIn = new FileInputStream(pathName + "/" + scanner.next() + ".ser");
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);
            turnaj = (Turnaj) objectIn.readObject();
            objectIn.close();
            fileIn.close();
        } catch (ClassNotFoundException | IOException e) { // odchyt chybneho hlasenia
            System.out.println("Subor sa nepodarilo nacitat pretoze:");
            e.printStackTrace();
        }
        return turnaj;
    }
}
