package org.multithreading;

import java.util.Random;
import java.util.concurrent.ArrayBlockingQueue;
import static org.multithreading.ProducerConsumer.EOF;

public class ProducerConcurrent implements Runnable {
    private final ArrayBlockingQueue<String> buffer; // String objects will be produced and stored here.
    private final String color;

    public ProducerConcurrent(ArrayBlockingQueue<String> buffer, String color) {
        this.buffer = buffer;
        this.color = color;
    }

    @Override
    public void run() {
        String[] objects = {"1", "2", "3", "4", "5"};
        Random random = new Random();
        for(String s : objects) {
            try {
                System.out.println(this.color + "Adding " + s + " to buffer.");
                synchronized (buffer) {
                    buffer.put(s);
                }
                Thread.sleep(random.nextInt(2000));
            } catch(InterruptedException e) {
                System.out.println(this.color + "MyProducer interrupted");
            }
        }
        try {
            synchronized (buffer) {
                buffer.put(EOF);
            }
        } catch (InterruptedException e) {
            System.out.println(this.color + "MyProducer interrupted");
        }
    }

}
