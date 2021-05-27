package com.organizer.classes.employees;

import java.io.Serializable;

public interface Zamestnanci {
    String meno = "";

    default void prichodDoPrace() {

    }

    default void odchodZPrace() {

    }

    default String reaguj() {
        return "Zijem";
    }
}
