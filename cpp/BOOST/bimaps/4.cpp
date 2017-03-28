/*
 * Difference b/w std::map and bimap left and right views.
 * An iterator for an std::map<X,Y> when dereferenced gives std::pair<const X, Y> so you can say
 * map.find(2)->second = some_new_value;
 *
 * However this is not possible in a bimap. because dereferening the left or right iterator will give you a type
 * which is signature compatible with std::pair<const X, const Y>.
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

    //This will cause a compilation issue ---> THIS IS THE IMPORTANT LINE
    myBm.left.find(1)->second = "TWO"; 

    //print bimap using relation views.
    cout << "Relation view:"<< endl;
    printS(myBm);
    return 0;
}


