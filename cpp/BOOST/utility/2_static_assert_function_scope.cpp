/*
Lets see BOOST_STATIC_ASSERT at function scope
*/

#include <iostream>
#include <boost/static_assert.hpp>

template <int i>
void accepts_values_between_1_and_10() {
	BOOST_STATIC_ASSERT(i >= 1 && i <= 10); //Make sure that the arguments and operators used must be known at compile time.
						//For eg: i is known here at compile time.
}

int main() {
	accepts_values_between_1_and_10<-89>(); //--> This should cause an exception.
	return 0;
}
