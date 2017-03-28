package database;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;

import main.Constraints;
import main.DBTable;
import main.SQLInteger;
import main.SQLString;

public class TableCreator {
    public static void main(String[] args) throws Exception {
        //We get the class names on which we want to run our processor
        //as command line arguments.
        if(args.length < 1) {
            System.out.println("No class name provided to TableCreator annotation processor");
            System.exit(0);
        }
        for(String className : args) {
            Class<?> clazz = Class.forName(className);
            
            //Get the DBTable Annotation on this class first.
            DBTable dbTable = clazz.getAnnotation(DBTable.class);
            if(dbTable == null) {
                System.out.println("Missing DBTable annotation on class  " + className);
                continue;
            }
            
            String tableName = dbTable.name();
            if(tableName.length() < 1) {
                //If no name is provided, default to class name.
                tableName = clazz.getSimpleName().toUpperCase();
            }
            
            //Next iterate over the fields in this class and process the declared annotations
            //on them, but create an array list for holding the column definitions.
            List<String> colDef = new ArrayList<String>();
           
            for(Field field : clazz.getDeclaredFields()) {
                //Get a list of annotations on this field.
                Annotation[] annotations = field.getDeclaredAnnotations();
                if(annotations.length < 1) {
                    System.out.println("Field: " + field.getName() + " has no defined annotations");
                    continue;
                }
                
                //Iterate over the annotations now.
                for(Annotation ann : annotations) {
                    String name = null;
                    if(ann instanceof SQLInteger) {
                        SQLInteger sqlInt = (SQLInteger)ann;
                        //get the field name.
                        name = sqlInt.name();
                        if(name.length() < 1) {
                            name = field.getName().toUpperCase();                            
                        }
                        name = name + " INT " + getConstraints(sqlInt.constraints());
                        colDef.add(name);
                    }
                    
                    if(ann instanceof SQLString) {
                        SQLString sqlString = (SQLString)ann;
                        //get the field name.
                        name = sqlString.name();
                        if(name.length() < 1) {
                            name = field.getName().toUpperCase();                            
                        }
                        name = name + " VARCHAR(" + sqlString.value() + ") " + getConstraints(sqlString.constraints());
                        colDef.add(name);
                    }
                }
            }
            //Now Sysout the entire command.
            StringBuilder sb = new StringBuilder();
            sb.append("CREATE TABLE ").append(tableName).append(" (");
            for(String col : colDef) {
                sb.append("\n     " + col + ",");
            }
            //Remove the last trailing comma.
            
            String command = sb.substring(0, sb.length() - 1) + " );";
            System.out.println("Command to create table: \n" + command);            
        }        
    }
    
    public static String getConstraints(final Constraints con) {
        StringBuilder sb = new StringBuilder();
        if(!con.allowNull()) {
            sb.append("  NOT NULL");
        }
        if(con.primaryKey()) {
            sb.append(" PRIMARY KEY");
        }
        if(con.unique()) {
            sb.append(" UNIQUE");
        }
        return sb.toString();
    }
}
