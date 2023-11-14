package org.input_output;

import java.io.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class DummyRecord implements Serializable {
    @Serial // this annotation just means that this function will be used during serialization and de-serialization process.
    private static final long serialVersionUID = 1L;
    private final static int version = 2;
    private String name;
    private long score;
    private long bigscore;
    private final transient long accountId;
    private List<String> weapons = new ArrayList<>();

    public DummyRecord(long accountId, String name, int score, List<String> weapons) {
        this.name = name;
        this.score = score;
        this.accountId = accountId;
        this.weapons = weapons;
    }

    @Override
    public String toString() {
        return "DummyRecord{" +
                "accountId=" + accountId +
                ", name='" + name + '\'' +
                ", score=" + score +
                ", bigscore=" + bigscore +
                ", weapons=" + weapons +
                '}';
    }

//    @Serial // this annotation just means that this function will be used during serialization and de-serialization process.
//    private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {
//        stream.defaultReadObject(); // perform default de-serialization.
//        bigscore = (bigscore == 0) ? 1_000_000_000L : bigscore;
//    }

    @Serial // this annotation just means that this function will be used during serialization and de-serialization process.
    // must override readObject if writeObject is overloaded to read in the same order as they are written.
    @SuppressWarnings("unchecked")
    private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {
        var serializedVer = stream.readInt();
        weapons = (List<String>)stream.readObject();
        name = stream.readUTF();
        score = stream.readInt();
//        bigscore = (bigscore == 0) ? score : bigscore;
    }

    @Serial
    private void writeObject(ObjectOutputStream stream) throws IOException {
        // you can do your own things here.
        // like serialize static fields and transient fields.
        System.out.println("--> Customized Writing");
        stream.writeInt(version);
        stream.writeObject(weapons);
        stream.writeUTF(name);
        stream.writeLong(score);
    }

}
