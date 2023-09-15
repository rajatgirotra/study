/* create a Town class which has a name and a distance field from Sydney.
Sydney should be the first element in the list. Rest of the elements are:
Adelaide 1374
Alice Springs 2771
Brisbane 917
Darwin 3972
Melbourne 877
Perth 3923
 * Create a method to add Town objects in a LinkedList() ordered by the distance from the starting point
 */

package intro_03.src;

import java.util.Collections;
import java.util.LinkedList;
import java.util.Scanner;

record Town (String name, int distance) implements Comparable<Town> {
    public String getTown() { return name; }
    public int getDistance() { return distance; }

    @Override
    public int compareTo(Town rhs) {
        return ((this.getDistance() == rhs.getDistance() ? 0 : this.getDistance() < rhs.getDistance() ? -1 : 1)) ;
    }

    @Override
    public boolean equals(Object o) {
        return this.name.equalsIgnoreCase(((Town)o).name);
    }

    public static Town createTown(String name, int distance) {
        return new Town(name, distance);
    }

    @Override
    public String toString() {
        return String.format("%s (%d) ", this.name, this.distance);
    }
}

public class TownTest {

    private static boolean addTown(LinkedList<Town> places, Town town) {
        if(places.contains(town)) {
            System.out.println("Found Duplicate: " + town);
            return false;
        }
        places.add(town);
        return true;
    }

    private static void placesToVisit(LinkedList<Town> places) {
        addTown(places, Town.createTown("Sydney", 0));
        addTown(places, Town.createTown("Adelaide", 1374));
        addTown(places, Town.createTown("Alice Springs", 2771));
        addTown(places, Town.createTown("Brisbane", 917));
        addTown(places, Town.createTown("Darwin", 3972));
        addTown(places, Town.createTown("Melbourne", 877));
        addTown(places, Town.createTown("Perth", 3923));
        Collections.sort(places);
    }

    private static Scanner scanner = new Scanner(System.in);

    private static char getChoice() {
        String menu = """
                Available actions (select word or letter):
                (F)orward
                (B)ackward
                (L)ist Places
                (M)enu
                (Q)uit
                """;
        System.out.println(menu);
        System.out.print("Enter here: ");
        char choice = switch(scanner.nextLine().toLowerCase()) {
          default -> 'q';
          case "f", "forward" -> 'f';
          case "b", "backward" -> 'b';
          case "l", "list places" -> 'l';
          case "m", "menu" -> 'm';
        };
        return choice;
    }

    public static void main(String[] args) {
        var places = new LinkedList<Town>();
        placesToVisit(places);

        var listIterator = places.listIterator();
        while(true) {
            char ch = getChoice();
            if(ch == 'q') break;
            if(ch == 'f') System.out.println(listIterator.next());
            else if(ch == 'b') System.out.println(listIterator.previous());
            else if(ch == 'l') {
                System.out.println("Places to visit: ");
                while(listIterator.hasNext()) {
                    System.out.println(listIterator.next());
                }
            }
        }
        
    }
}
