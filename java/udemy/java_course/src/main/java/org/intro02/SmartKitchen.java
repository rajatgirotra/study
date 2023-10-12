package org.intro02;

class Applicance {
    public void doWork(boolean work) {}
}

class Refrigerator extends Applicance {
    private boolean hasWorkToDo;

    public Refrigerator(boolean hasWorkToDo) {
        this.hasWorkToDo = hasWorkToDo;
    }

    @Override
    public void doWork(boolean work) {
        this.hasWorkToDo = work;
    }

    public void orderFood() {
        if(this.hasWorkToDo) {
            System.out.println("Ordering food from refrigerator");
        }
    }

}

class CoffeeMaker extends Applicance {
    private boolean hasWorkToDo;

    public CoffeeMaker(boolean hasWorkToDo) {
        this.hasWorkToDo = hasWorkToDo;
    }

    @Override
    public void doWork(boolean work) {
        this.hasWorkToDo = work;
    }


    public void brewCoffee() {
        if(this.hasWorkToDo) {
            System.out.println("Brewing extra hot latte just for you!!");
        }
    }
}

class DishWasher extends Applicance {
    private boolean hasWorkToDo;

    public DishWasher(boolean hasWorkToDo) {
        this.hasWorkToDo = hasWorkToDo;
    }

    @Override
    public void doWork(boolean work) {
        this.hasWorkToDo = work;
    }

    public void doDishes() {
        if(this.hasWorkToDo) {
            System.out.println("Super hot and super cleaned dishes will be ready soon!");
        }
    }
}

public class SmartKitchen {
    private Refrigerator refrigerator;
    private CoffeeMaker coffeeMaker;
    private DishWasher dishWasher;

    public SmartKitchen(Refrigerator refrigerator, CoffeeMaker coffeeMaker, DishWasher dishWasher) {
        this.refrigerator = refrigerator;
        this.coffeeMaker = coffeeMaker;
        this.dishWasher = dishWasher;
    }

    public void pourMilk(boolean work) {
        this.refrigerator.doWork(work);
    }

    public void addWater(boolean work) {
        this.coffeeMaker.doWork(work);
    }

    public void loadDishwasher(boolean work) {
        this.dishWasher.doWork(work);
    }

    public void setKitchenState(boolean ref, boolean cm, boolean dw) {
        this.pourMilk(ref);
        this.addWater(cm);
        this.loadDishwasher(dw);
    }

    public void doKitchenWork() {
        this.refrigerator.orderFood();
        this.coffeeMaker.brewCoffee();
        this.dishWasher.doDishes();
    }

    public static void main(String[] args) {
        Refrigerator ref = new Refrigerator(false);
        CoffeeMaker cm = new CoffeeMaker(false);
        DishWasher dw = new DishWasher(false);
        SmartKitchen kitchen = new SmartKitchen(ref, cm, dw);
        kitchen.setKitchenState(true, false, true);
        kitchen.doKitchenWork();

    }
    
}