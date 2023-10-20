package org.multithreading;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumerReentrant {
    public static final String EOF = "EOF";

    public static void main(String[] args) {
        var buffer = new ArrayList<String>();
        var lock = new ReentrantLock();
        ExecutorService executorService = Executors.newFixedThreadPool(3);
        executorService.execute(new ProducerReentrant(buffer, ThreadColors.ANSI_RED, lock));
        executorService.execute(new ConsumerReentrant(buffer, ThreadColors.ANSI_GREEN, lock));
        executorService.execute(new ConsumerReentrant(buffer, ThreadColors.ANSI_PURPLE, lock));

        executorService.shutdown();
    }
}

/*
Next we will use an ArrayBlockingQueue which is inherently threadsafe.
See ConcurrentProducerConsumer.java next
 */