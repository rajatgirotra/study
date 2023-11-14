package org.input_output;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Player implements Serializable {
    private final String name;
    private final int score;
    private final List<String> weapons = new ArrayList<>();

    public Player(String name, int score) {
        this.name = name;
        this.score = score;
        weapons.addAll(List.of("Riffle", "Sonar Gun", "BioWeapon"));
    }

    @Override
    public String toString() {
        return "Player{" +
                "name='" + name + '\'' +
                ", score=" + score +
                ", weapons=" + weapons +
                '}';
    }
}
