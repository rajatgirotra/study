package org.multithreading;

import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

import static org.multithreading.ProducerConsumer.EOF;

public class ProducerReentrant implements Runnable {
    private final List<String> buffer; // String objects will be produced and stored here.
    private final String color;

    private final ReentrantLock lock;

    public ProducerReentrant(List<String> buffer, String color, ReentrantLock lock) {
        this.buffer = buffer;
        this.color = color;
        this.lock = lock;
    }

    @Override
    public void run() {
        String[] objects = {"1", "2", "3", "4", "5"};
        Random random = new Random();
        for(String s : objects) {
            System.out.println(this.color + "Adding " + s + " to buffer.");
            lock.lock();
            try {
                buffer.add(s);
                try {
                    Thread.sleep(random.nextInt(2000));
                } catch(InterruptedException e) {
                    System.out.println(this.color + "MyProducer interrupted");
                }
            } finally {
                lock.unlock();
            }
        }
        lock.lock();
        try {
            buffer.add(EOF);
        } finally {
            lock.unlock();
        }
    }
}
