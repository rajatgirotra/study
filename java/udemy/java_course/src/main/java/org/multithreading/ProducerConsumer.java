package org.multithreading;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/*
Have one producer thread which produces String objects which are consumed by 2 consumer threads.
Once the consumer reads "EOF", the consumer thread can exit.
 */
public class ProducerConsumer {
    public static final String EOF = "EOF";

    public static void main(String[] args) {
        var buffer = new ArrayList<String>();
        ExecutorService executorService = Executors.newFixedThreadPool(3);
        executorService.execute(new MyProducer(buffer, ThreadColors.ANSI_RED));
        executorService.execute(new MyConsumer(buffer, ThreadColors.ANSI_GREEN));
        executorService.execute(new MyConsumer(buffer, ThreadColors.ANSI_PURPLE));

        executorService.shutdown();
    }
}

/*
Next we look at ProducerConsumerReentrant.java which is ditto as this one. Except that the Producers and Consumers
use Reentrant lock from java.util.concurrent package instead of using synchronized.
 */