package org.multithreading;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ConcurrentProducerConsumer {
    public static final String EOF = "EOF";

    public static void main(String[] args) {
        var buffer = new ArrayBlockingQueue<String>(6); // size of the buffer. This is not expandable queue.
        ExecutorService executorService = Executors.newFixedThreadPool(3);
        executorService.execute(new ProducerConcurrent(buffer, ThreadColors.ANSI_RED));
        executorService.execute(new ConsumerConcurrent(buffer, ThreadColors.ANSI_GREEN));
        executorService.execute(new ConsumerConcurrent(buffer, ThreadColors.ANSI_PURPLE));

        executorService.shutdown();
    }

}

/*
Please read 3_README.txt next
 */