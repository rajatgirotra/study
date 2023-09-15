package intro_03.src;

import java.util.*;

public class IteratorExample {
    public static void main(String[] args) {
        var ll = new LinkedList<String>();
        ll.add("A"); ll.add("B"); ll.add("C"); ll.add("D");

        var iterator = ll.listIterator(0);
        while(iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
}

/* There are actually two iterator class'es 
 * Iterator and ListIterator
 * Iterator is only a forward iterator and supports only the remove() method.
 * ListIterator is a bidirectional iterator and supports not only remove() but methods like add(), set() also.
 * 
 * While traversing the list using an iterator or list iterator, if you use the list object to remove and element. you get a ConcurrentModificationException
 * 
 * Just remember that an iterator position is in the middle of elements.
*/