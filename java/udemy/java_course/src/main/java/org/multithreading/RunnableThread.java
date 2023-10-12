package org.multithreading;

import static org.multithreading.ThreadColors.*;

public class RunnableThread implements Runnable {
    @Override
    public void run() {
        System.out.println(ANSI_BLUE + "This is printing from inside a RunnableThread class. thread name is: "
                + Thread.currentThread().getName());
    }
}
