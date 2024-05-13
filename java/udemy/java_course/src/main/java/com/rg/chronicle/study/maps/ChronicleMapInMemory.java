package com.rg.chronicle.study.maps;

import net.openhft.chronicle.map.*;

import java.io.File;

public class ChronicleMapInMemory {
    public static void main(String[] args) {
        // constructing a ChronicleMap must be done through its builder ChronicleMapBuilder

        /*
        cityPostalCodes is an in-memory map only accessible from the JVM that created it. When the process terminates, the map is gone.
         */
        try (var cityPostalCodes = ChronicleMapBuilder.of(CharSequence.class, PostalCodeRange.class)
                .name("city-postal-codes-map")
                .averageKey("Amsterdam")
                .entries(50_000)
                .create()) {
            // the map allows concurrent access within the JVM. No need to create separate ChronicleMap instances in the same JVM.
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }


        /*
        cityPostalCodesPersisted will now be persisted to disk
         */
        var mapFile = new File("/tmp/city-postal-codes-map");
        try (var cityPostalCodesPersisted = ChronicleMapBuilder.of(CharSequence.class, PostalCodeRange.class)
                .name("city-postal-codes-map")
                .averageKey("Amsterdam") // used by ChronicleMap to calculate the size of the memory-mapped file
                // similarly averageValue() can be used to calculate the size of the memory-mapped file
                .entries(50_000)
                .createPersistedTo(mapFile)) {
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }

    }

    /*
    ChronicleMapBuilder also has a recoverPersistedTo() method that allows you to recover a persisted map from a file.
    This method is not thread safe and should not wait for this method to finish before using the map. this method will try to fix the corrupted
    state of your map if the map got corrupted due to a crash or a bug in the ChronicleMap library. The second argument to the function is a boolean
    called "sameBuilderConfigAndLibraryVersion".

    true: set it to true, if this version of builder object and the map library is same as the one which created the map initially. This way the api knows that if
    the header/metadata inside the map is corrupted, it can easily fix it by using the same builder object and library version.

    false: set it to false, if this version of builder object and the map library is different from the one which created the map initially.
     ChronicleMap will just assume that the map header/metadata in not corrupted, but if it is, the API will throw a ChronicleHashRecoveryFailedException

     Normally, the header never gets corrupted during normal read/write operations.
     Only hardware, memory, or disk corruption, or a bug in the file system, could lead to Chronicle Map header memory corruption.
     */
}

/*
An example of creating a ChronicleMap of a social 
 */
