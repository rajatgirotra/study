package intro_01.design_patterns;

class SingletonConfig1 {
    private int value;
    private SingletonConfig1(int value) {
        this.value = value;
    }

    private static SingletonConfig1 obj;

    // not thread safe.
    public static SingletonConfig1 instance(int value) {
        if(obj == null) {
            obj = new SingletonConfig1(value);
        }
        return obj;
    }

    public int getValue() {
        return this.value;
    }
}

// make it thread safe using double locked pattern
class SingletonConfig2 {
    private int value;
    private SingletonConfig2(int value) {
        this.value = value;
    }

    private static SingletonConfig2 obj;

    // Problem. unnecessary locking even to access the singleton
    public static SingletonConfig2 instance(int value) {
        synchronized(SingletonConfig2.class) {
            if(obj == null) {
                obj = new SingletonConfig2(value);
            }
        }
        return obj;
    }

    public int getValue() {
        return this.value;
    }
}

// make it thread safe and avoid unecessary locking
class SingletonConfig3 {
    private int value;
    private SingletonConfig3(int value) {
        this.value = value;
    }

    private static SingletonConfig3 obj;

    // This is good. But still there is a problem. JVM might assign to obj variable even when
    // the SingletonConfig3 object is only half initialized. So we need to make the obj variable volatile.
    public static SingletonConfig3 instance(int value) {
        if(obj == null) {
            synchronized(SingletonConfig3.class) {
                if(obj == null) {
                    obj = new SingletonConfig3(value);
                }
            }
        }
        return obj;
    }

    public int getValue() {
        return this.value;
    }
}

// Use volatile now
class SingletonConfig4 {
    private int value;
    private SingletonConfig4(int value) {
        this.value = value;
    }

    // volatile tells JVM to read obj always from cache. (this will be at the cost of performance)
    // so try to better performance
    private static volatile SingletonConfig4 obj;

    public static SingletonConfig4 instance(int value) {
        if(obj == null) {
            synchronized(SingletonConfig4.class) {
                if(obj == null) {
                    obj = new SingletonConfig4(value);
                }
            }
        }
        return obj;
    }

    public int getValue() {
        return this.value;
    }
}

class SingletonConfig5 {
    private int value;
    private SingletonConfig5(int value) {
        this.value = value;
    }

    private static volatile SingletonConfig5 obj;

    public static SingletonConfig5 instance(int value) {
        SingletonConfig5 result = obj;
        if(result == null) {
            synchronized(SingletonConfig5.class) {
                if(result == null) {
                    result = obj = new SingletonConfig5(value);
                }
            }
        }
        return obj;
    }

    public int getValue() {
        return this.value;
    }
}

// still better solution. Use Java Enum. Guaranteed to be thread safe at he JVM level
// and much simpler
enum SingletonConfig6 {
    INSTANCE(100);

    private int value;
    private SingletonConfig6(int value) {
        this.value = value;
    }

    int getValue() {
        return this.value;
    }

    void setValue(int v) {
        this.value = v;
    }
}


public class SingletonPattern {
    public static void main(String[] args) {
        SingletonConfig6 obj = SingletonConfig6.INSTANCE;
        obj.setValue(-99);
        
        SingletonConfig6 obj2 = SingletonConfig6.INSTANCE;
        System.out.println("Obj2 value: " + obj2.getValue());

    }
}
