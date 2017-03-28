/*
 * In 2.cpp, we saw how to use the relation view to insert a relation in a bimap. Here we will see how to use the
 * left and right views to insert elements. Fairly straight forward.
 */

#include <boost/bimap.hpp>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

//Function to print a set
template <typename SetType>
void printS(const SetType& m)
{
    typedef typename SetType::const_iterator Iter;
    for(Iter iter = m.begin(); iter != m.end(); ++iter)
    {
        cout << iter->left << " --> " << iter->right << endl;
    }
}


int main() 
{
    typedef boost::bimap<int, string> bm_type;
    bm_type myBm;

    //To insert somethingi in the bimap you can use either the left view, 
    //or the right view, or the relation view.
    //Here we'll use the left and right views.
    typedef bm_type::left_value_type left_relation;
    typedef bm_type::right_value_type right_relation;
    myBm.left.insert(left_relation(1, "one"));
    myBm.right.insert(right_relation("two", 2));
 
    assert(myBm.right.find("two")->second == 2);
    //Still dont know how to store a value X or Y of a bimap into the proper type??
    //bimap::<some_unknown_type> x = myBm.left.at(1);
    //I know i can say std::string s =  myBm.left.at(1);
    //but dont know how to get the type from bimap.
    //std::string s =  myBm.left.at(1);

    //print bimap using relation views.
    cout << "Relation view:"<< endl;
    printS(myBm);
    return 0;
}


