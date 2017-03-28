/*
 * FileNamingStyle.java
 *
 * Created on 09 November 2001, 13:31
 *
 * Copyright (c) Rolfe & Nolan Systems Limited. All rights reserved.
 *
 */

package com.rolfeandnolan.ccp.utils;

import org.apache.log4j.Category;

/**
 * Defines the file naming styles to be used by the system
 * that is {@link #FIXED}, {@link #REUTERS}, {@link #DATEBODY}.
 *
 * @author  patrick.liardet
 * @version 1.0
 */
public class FileNamingStyle {

    private static final Category cat = Category.getInstance(
    FileNamingStyle.class.getName());

    int style;
    String namingStyle;
    
    public static final int FIXED_INT = 100;
    public static final int REUTERS_INT = 200;
    public static final int DATEBODY_INT = 300;
    
    /** The <code>FIXED</code> naming style denotes a static filename without
     * any date oriented change
     */
    final static public FileNamingStyle FIXED = new FileNamingStyle(FIXED_INT, "FIXED");

    /** The <code>REUTERS</code> naming style denotes a dynamic filename with
     * a date extension
     */
    final static public FileNamingStyle REUTERS = new FileNamingStyle(REUTERS_INT, "REUTERS");

    /** The <code>DATEBODY</code> naming style denotes a dynamic filename with
     * a date extension
     */
    final static public FileNamingStyle DATEBODY = new FileNamingStyle(DATEBODY_INT, "DATEBODY");
    
    protected FileNamingStyle(int style, String namingStyle) {
        this.style = style;
        this.namingStyle = namingStyle;
    }

    /**
    * Returns the string representation of this FileNamingStyle.
    */
    final public String toString() {
        return namingStyle;
    }

    /** Test for equality
     */
    final public boolean equals(FileNamingStyle f) {
        return (style == f.style);
    }
        
    /** Test for equality
     */
    final public boolean equals(String f) {
        return (namingStyle.equalsIgnoreCase(f));
    }

    /**
    * Returns the integer representation of this FileNamingStyle.
    */
    public final int toInt() {
        return style;
    }

    /**
    * Convert the string passed as argument to a FileNamingStyle. If the
    * conversion fails, then this method returns the value of
    * <code>FIXED</code>.  
    */

    public static FileNamingStyle toFileNamingStyle(String s) {
        if(s == null)
            return FileNamingStyle.FIXED;
        if (s.equalsIgnoreCase("FIXED")) return FileNamingStyle.FIXED;
        if (s.equalsIgnoreCase("REUTERS")) return FileNamingStyle.REUTERS;
        if (s.equalsIgnoreCase("DATEBODY")) return FileNamingStyle.DATEBODY;

        //default
        return FileNamingStyle.FIXED;
    }
    
    /** Return all possible FileNamingStyles as an array of FileNamingStyle objects
     */
    public static FileNamingStyle[] getFileNamingStyles() {
        return new FileNamingStyle[] { FileNamingStyle.FIXED, 
        FileNamingStyle.DATEBODY, FileNamingStyle.REUTERS};
    }
}
