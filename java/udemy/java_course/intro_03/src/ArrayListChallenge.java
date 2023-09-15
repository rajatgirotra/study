/*Your grocery list should be an ArrayList.
You should use methods on the ArrayList, to add items, remove items, check if an item is already in the list, and print a sorted list.
You should print the list, sorted alphabetically, after each operation.
You shouldn't allow duplicate items in the list.
*/

package intro_03.src;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class ArrayListChallenge {
    private static void addItems(List<String> lst) {
        System.out.println("Add item(s), separated by commas");
        String[] itemsArr = scanner.nextLine().split(", ");
        for(var item : itemsArr) {
            item = item.trim();
            if(!lst.contains(item)) {
                lst.add(item);
            }
        }
    }

    private static void removeItems(List<String> lst) {
        System.out.println("Remove item(s), separated by commas");
        String[] itemsArr = scanner.nextLine().split(", ");
        for(var item : itemsArr) {
            item = item.trim();
            var idx = lst.indexOf(item);
            if(idx >= 0) {
                lst.remove(idx);
            }
        }        
    }

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
    
    var lst = new ArrayList<String>();
    var quit = false;
    while (!quit) {
        System.out.println("""

                Available Options:

                0 - to shutdown

                1 - to add item(s) to a list (comma delimited list)

                2 - to remove any items (comma delimited list)

                """);
        System.out.print("Enter a number for which action you want to do: ");
        
        var choice = Integer.parseInt(scanner.nextLine());
        switch(choice) {
            default -> quit = true;
            case 1 -> addItems(lst);
            case 2 -> removeItems(lst);
        }
        lst.sort(Comparator.naturalOrder());
        System.out.println("List: " + lst);
    };
  }  
}

/* Under the hood, ArrayLists uses Array only in disguise
 * 
 * Similarly we have LinkedList (which is a doubly linked list).
 * However LinkedList also implements pther interfaces like Queue<> and Deque<>
 * 
 */