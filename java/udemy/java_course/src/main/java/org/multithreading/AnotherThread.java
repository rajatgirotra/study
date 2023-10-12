package org.multithreading;

import org.jetbrains.annotations.NotNull;

import static org.multithreading.ThreadColors.ANSI_PURPLE;
import static org.multithreading.ThreadColors.ANSI_RED;

public class AnotherThread extends Thread {
    public AnotherThread(@NotNull String name) {
        super("=== Another Thread ===");
    }

    @Override
    public void run() {
        System.out.println(ANSI_PURPLE + "Hello from thread: " + currentThread().getName());
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            System.out.println(ANSI_RED + "Thread [" + currentThread().getName() + "] interrupted");
            return;
        }
        System.out.println(ANSI_PURPLE + "Exiting gracefully from thread: " + currentThread().getName());
    }
}
