package com.organizer.triedy;

import com.organizer.triedy.pavuk.Pavuk;

//abstraktná trieda slúži ako predpis triedy,
// nemôže vytvárať inštancie a môže obsahovať abstraktné ako aj ne-abstraktné metody
abstract public class Turnaje {
    Pavuk pavuk;

    abstract public Pavuk getPavuk(); //abstraktná metoda slúži ako predpis metody použitej v triede ktorá ju dedí,
    // abstraktná metoda nemá implementáciu v abstraktnej triede ale jej implementáciu zabezpečuje trieda,
    // ktorá rozširuje danú abstraktnú triedu

    public void setPavuk(Pavuk pavuk) {
        this.pavuk = pavuk;
    }

}
