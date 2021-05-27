package com.organizer.core;

import com.organizer.classes.Prevadzka;

import java.io.*;
import java.util.Scanner;

// uloženie a načítanie suboru obsahuúceho data prevadzky
// pomocou Serializable interface

//TODO: Data handler

public class DataHandler {
    private static final String pathName = System.getProperty("user.dir");  // ziska cestu k priečinku v ktorom sa vykonáva

    public static void saveData(Prevadzka prevadzka) {
        try {
            File subor = new File(pathName);
            subor.createNewFile();
            //Scanner scanner = new Scanner(System.in);
            //System.out.println("Zadaj meno suboru pre ulozenie:");
            //FileOutputStream fileOut = new FileOutputStream(subor + "/" + scanner.next() + ".ser", false);
            FileOutputStream fileOut = new FileOutputStream(pathName+"/" + "subor" + ".ser", false);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(prevadzka);
            objectOut.close();
            fileOut.close();
        } catch (IOException e) {
            System.out.println("Subor sa nepodarilo ulozit pretoze:");
            e.printStackTrace();
        }
    }

    public static Prevadzka loadData()  { // nacitanie dat

        Prevadzka prevadzka = null;
        try {
            //FileInputStream fileIn = new FileInputStream(pathName + "/" + scanner.next() + ".ser");
            FileInputStream fileIn = new FileInputStream(pathName+"/"+ "subor" + ".ser");
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);
            prevadzka = (Prevadzka) objectIn.readObject();
            objectIn.close();
            fileIn.close();
        } catch (ClassNotFoundException e) {
            System.out.println("Subor sa nepodarilo nacitat pretoze nema pozadovany format");
        }
        catch (IOException i) { // odchyt chybneho hlasenia
            System.out.println("Subor sa nepodarilo nacitat pretoze subor nexistuje");
        }
        return prevadzka;
    }
}
