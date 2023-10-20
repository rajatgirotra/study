package org.multithreading;

import java.util.List;
import java.util.Random;

public class MyConsumer implements Runnable {
    private final List<String> buffer;
    private final String color;

    public MyConsumer(List<String> buffer, String color) {
        this.buffer = buffer;
        this.color = color;
    }

    @Override
    public void run() {
        Random random = new Random();
        while(true) {
            synchronized (this.buffer) {
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
            }
        }
    }
}
