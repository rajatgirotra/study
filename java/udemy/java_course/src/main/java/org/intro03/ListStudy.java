package org.intro03;

import java.util.*;
/*
 * List is an interface and has many classes implementing the List interface
 * 1) ArrayList -> like std::vector (contiguous)
 * 2) LinkedList --> like std::list (doubly linked list)
 * 3) List.of() is a function which gives you a nested class java.util.ImmutableCollections$ListN. This list is immutable
 */

 enum Fruits {
    MANGO,
    APPLE,
    BANANA;
 }

 record GroceryItem(String name, String type, int count) {
    public GroceryItem(String name) {
        this(name, "DAIRY", 1);
    }

    @Override
    public String toString() {
        return String.format("%d %s in %s", this.count, name.toUpperCase(), type);
    }
 }

public class ListStudy {
    public static void main(String[] args) {
        var groceryArray = new GroceryItem[3];
        groceryArray[0] = new GroceryItem("milk");
        groceryArray[1] = new GroceryItem("apples", "PRODUCE", 5);
        groceryArray[2] = new GroceryItem("oranges", "PRODUCE", 5);
        System.out.println(Arrays.toString(groceryArray));

        var arr = new ArrayList<>(); // this is a raw ArrayList. i.e. it con store any Object (i.e. heterogenous).
        arr.add(10);
        arr.add(Integer.valueOf(10));
        arr.add(Fruits.APPLE);
        arr.add(new GroceryItem("Butter"));
        arr.add("Yogurt");
        System.out.println(arr);

        // to create a homogenous list, use generics (we will study later what generics are)
        var arr2 = new ArrayList<Fruits>();
        arr2.add(Fruits.BANANA);
        arr2.add(Fruits.APPLE);
        // arr2.add(100); // error
        System.out.println(arr2);

        // ArrayList have size which is dynamically managed as you add/remove from ArrayList
        System.out.println(String.format("ArrayList.size(): %d", arr.size()));

        var firstList = new ArrayList<String>();
        firstList.add("earth");

        String[] items = {"jupyter", "venus", "mars", "pluto"};
        var secondList = List.of(items);
        System.out.println("List.of() type: " + secondList.getClass().getName());

        firstList.addAll(secondList);
        System.out.println("FirstList: " + firstList);
        System.out.println("Third item in ArrayList: " + firstList.get(2));

        System.out.println("index of earth: " + firstList.indexOf("earth"));
        System.out.println("index of earth: " + firstList.lastIndexOf("earth"));

        if(firstList.contains("mars")) {
            System.out.println("mars is present");
        }

        // remove pluto.
        firstList.remove(firstList.size()-1);
        System.out.println(firstList);

        firstList.clear(); // remove all
        firstList.addAll(List.of(items));
        firstList.addAll(Arrays.asList("saturn", "mercury"));
        System.out.println("firstList before sort: " + firstList);
        firstList.sort(Comparator.naturalOrder());
        System.out.println("firstList after sort: " + firstList);

        String[] namesArr = {"A", "B", "C", "D"};
        var namesList = Arrays.asList(namesArr); // namesList is an ArrayList<String> backed by namesArr. Any change will impact namesArr
        //namesList.add("E"); //exception now as ArrayList is backed by an array of fixed size.
        System.out.println(Arrays.toString(namesArr)); 
        namesList.set(0, "E");
        System.out.println(Arrays.toString(namesArr)); 

        var anotherList = Arrays.asList("Hi", "How", "Are", "You");
        // anotherList.add("I");
        System.out.println(anotherList);
        
    }
}

/*
 * basically Arrays.asList() returns a fixed size List, BUT IT IS MUTABLE.
 * List.of() returns an IMMUTABLE LIST. Cannot change size and contents.
 */