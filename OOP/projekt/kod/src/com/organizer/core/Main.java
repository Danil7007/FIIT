package com.organizer.core;

import com.organizer.classes.Prevadzka;
import com.organizer.classes.orders.ObjednavkaZakaznika;
import com.organizer.messages.ProgramoveVypisy;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import java.io.BufferedInputStream;
import java.io.ObjectInputStream;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

public class Main extends Application {

    //TODO: rolak extends sveter
    //TODO: exceptions

    public void start(Stage stage) throws Exception{
        stage.setTitle("Lokalna handmade vyroba lokalnych handmade svetrov vyrabanych lokalne a handmade BIO RAW VEGAN FEMININE");

        //Label label = new Label("Čo ti jebe ja mam traktor!!!");
        Button button = new Button("Klik 2 kliky 3 kliky...");
        Scene scene = new Scene(button,20,30);
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args)  {
        Application.launch(args);


        /*
        Prevadzka prevadzka = Prevadzka.getInstance();

        ObjednavkaZakaznika objednavka1 = new ObjednavkaZakaznika();
        objednavka1.pridajPolozku("vesta", "zlta", "bavlna", "XS", 1);
        prevadzka.getAktivneObjednavky().add(objednavka1);

        ObjednavkaZakaznika objednavka2 = new ObjednavkaZakaznika();
        objednavka2.pridajPolozku("vesta", "zlta", "bavlna", "XS", 1);
        prevadzka.getAktivneObjednavky().add(objednavka2);

        ObjednavkaZakaznika objednavka3 = new ObjednavkaZakaznika();
        objednavka3.pridajPolozku("vesta", "zlta", "bavlna", "XS", 1);
        prevadzka.getAktivneObjednavky().add(objednavka3);

        prevadzka.zamestnajManazerov(2);

        prevadzka.rozdeleniePrace();

         */


        Prevadzka prevadzka = Prevadzka.getPrevadzka();
        //prevadzka = DataHandler.loadData(); //TODO: edit serializable


        Scanner keyboard = new Scanner(System.in);
        int key;

        do {
            System.out.print(ProgramoveVypisy.highlight + ProgramoveVypisy.run + ProgramoveVypisy.white);
            System.out.println(ProgramoveVypisy.exit);

            key = keyboard.nextInt();

            switch (key) {
                case 0:
                    break;
                case 1: // operator
                    prevadzka = Funkcionalita.caseOperator(prevadzka);
                    break;
                case 2: // manazer
                    prevadzka = Funkcionalita.caseManazer(prevadzka);
                    break;
                case 3: // zamestnanec
                    break;
                case 4: // zakaznik
                    prevadzka = Funkcionalita.caseZakaznik(prevadzka);
                    break;
                default:
                    break;
            }

        } while (key != 0);



        //DataHandler.saveData(prevadzka);

    }



}
