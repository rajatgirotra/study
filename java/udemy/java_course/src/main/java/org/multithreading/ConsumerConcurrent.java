package org.multithreading;

import java.util.List;
import java.util.Random;
import java.util.concurrent.ArrayBlockingQueue;

public class ConsumerConcurrent implements Runnable {
    private final ArrayBlockingQueue<String> buffer;
    private final String color;

    public ConsumerConcurrent(ArrayBlockingQueue<String> buffer, String color) {
        this.buffer = buffer;
        this.color = color;
    }

    @Override
    public void run() {
        Random random = new Random();
        while(true) {
            synchronized (buffer) {
                try {
                    if(buffer.isEmpty()) {
                        continue;
                    }
                    // if we reach here, we can consume from buffer.
                    String item = buffer.peek();
                    if(item.equals(ProducerConsumer.EOF)) {
                        System.out.println(this.color + "Exiting...");
                        break;
                    } else {
                        System.out.println(this.color + "consuming " + item);
                        buffer.take();
                    }
                } catch(InterruptedException e) {
                    System.out.println("ConsumerConcurrent interrupted");
                }
            }
        }
    }
}
