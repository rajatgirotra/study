package org.multithreading;

import java.util.List;
import java.util.Random;
import static org.multithreading.ProducerConsumer.EOF;

public class MyProducer implements Runnable {
    private final List<String> buffer; // String objects will be produced and stored here.
    private final String color;

    public MyProducer(List<String> buffer, String color) {
        this.buffer = buffer;
        this.color = color;
    }

    @Override
    public void run() {
        String[] objects = {"1", "2", "3", "4", "5"};
        Random random = new Random();
        for(String s : objects) {
            System.out.println(this.color + "Adding " + s + " to buffer.");
            synchronized (this.buffer) {
                // produce an item
                buffer.add(s);
            }
            try {
                Thread.sleep(random.nextInt(2000));
            } catch(InterruptedException e) {
                System.out.println(this.color + "MyProducer interrupted");
            }
        }
        synchronized (this.buffer) {
            // produce an item
            buffer.add(EOF);
        }
    }
}
