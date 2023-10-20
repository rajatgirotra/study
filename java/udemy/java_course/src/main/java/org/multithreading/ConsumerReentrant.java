package org.multithreading;

import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

public class ConsumerReentrant implements Runnable {
    private final List<String> buffer;
    private final String color;
    private final ReentrantLock lock;

    public ConsumerReentrant(List<String> buffer, String color, ReentrantLock lock) {
        this.buffer = buffer;
        this.color = color;
        this.lock = lock;
    }

    @Override
    public void run() {
        Random random = new Random();
        while(true) {
            lock.lock();
            try {
                if(buffer.isEmpty()) {
                    continue;
                }
                // if we reach here, we can consume from buffer.
                String item = buffer.get(0);
                if(item.equals(ProducerConsumer.EOF)) {
                    System.out.println(this.color + "Exiting...");
                    break;
                } else {
                    System.out.println(this.color + "consuming " + item);
                    buffer.remove(0);
                }
            } finally {
                lock.unlock();
            }
        }
    }
}
