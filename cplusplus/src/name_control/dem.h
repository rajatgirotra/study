#pragma once
class Dem {
	public:
    static const int i = 10; // A
//    static const int i; // B
//		static int j;
};

//int x = -987; // this one you know will be error
const int x = -987; // this one you know will be fine.

//const int Dem::i = 100; // with A enabled above, you can't initialize twice if you already have an initializer in the class definition
//const int Dem::i = 100; // with B enabled above, this is const so should ideally have internal linkage. But since the class name itself has external linkage, so does Dem::i
//int Dem::j = 20; // again trivial. same reason as above. class has external linkage.

