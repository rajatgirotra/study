package c08;

public interface Months {
	int JANUARY   = 1,
		FEBRUARY  = 2,
		MARCH     = 3,
		APRIL     = 4,
		MAY       = 5,
		JUNE      = 6,
		JULY      = 7,
		AUGUST    = 8,
		SEPTEMBER = 9,
		OCTOBER   = 10,
		NOVEMBER  = 11,
		DECEMBER  = 12;	
}

/*
You can use the constants from outside the package by importing c08.*
or c08.Months just as you would with any other package, and
referencing the values with expressions like Months.JANUARY. Of
course, what you get is just an int, so there isn’t the extra type safety that
C++’s enum has, but this (commonly used) technique is certainly an
improvement over hard-coding numbers into your programs.
*/