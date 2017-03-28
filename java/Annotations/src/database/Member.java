/*
 * Please read SQLInteger.java first.
 */
package database;

import main.Constraints;
import main.DBTable;
import main.SQLInteger;
import main.SQLString;

@DBTable(name="MEMBER")
public class Member {

    /* The firstName and lastName annotation are special. In Java, if you define an annotation with an element
     * "value", then as long as that is the only element you specify in your annotation, you don't need a key value
     * pair. Just specify the value as is.
     */
    @SQLString(30)
    private String firstName;
    
    @SQLString(50)
    private String lastName;
    
    @SQLInteger
    private Integer age;
    
    //Since here we use the Constraints element as well, we say "value=40" and not just 40.
    @SQLString(value = 40, constraints=@Constraints(primaryKey=true))
    private String handle;
    
    private static int memberCount;
    
    public String getFirstName() {
        return firstName;        
    }
    
    public String getLastName() {
        return lastName;
    }
    
    public Integer getAge() {
        return age;
    }
    
    public String getHandle() {
        return handle;
    }
    
    public String toString() {
        return handle;
    }
}

/*
Now we are in good shape to write our annotation processor.
Please read TableCreator.java next.
*/