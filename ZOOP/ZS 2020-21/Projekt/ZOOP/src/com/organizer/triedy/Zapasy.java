package com.organizer.triedy;

import java.util.ArrayList;
import java.util.Date;

//rozhranie na rozdiel od abstraktnej triedy nemôže obsahovať implementovanú metodu - všetky musia byť abstraktné
public interface Zapasy {

    ArrayList<Hrac> getHraci();

    void setHraci(ArrayList<Hrac> hraci);

    Date getKoniecZapasu();

    void setKoniecZapasu(Date koniecZapasu);

    Date getZaciatokZapasu();

    void setZaciatokZapasu(Date zaciatokZapasu);

    int getCisloZapasu();

    void setCisloZapasu(int cisloZapasu);

    int getKolo();

    void setKolo(int kolo);

    Kurt getCobain();

    void setCobain(Kurt cobain);

    boolean getDvojhra();

    void setDvojhra(boolean dvojhra);

}
