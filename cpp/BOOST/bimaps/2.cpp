#include <boost/bimap.hpp>
#include <string>
#include <iostream>
using namespace std;

//Function to print a map
template <typename MapType>
void printM(const MapType& m)
{
    typedef typename MapType::const_iterator Iter;
    for(Iter iter = m.begin(); iter != m.end(); ++iter)
    {
        cout << iter->first << " --> " << iter->second << endl;
    }
}

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
    //Here we'll use the relation view
    typedef bm_type::value_type relation;
    myBm.insert(relation(1, "one"));
    myBm.insert(relation(2, "two"));

    //print bimap using left, right, and relation views.
    cout << "Left view:"<< endl;
    printM(myBm.left);
    
    cout << "\nRight view:"<< endl;
    printM(myBm.right);

    cout << "\nRelation view:"<< endl;
    printS(myBm);
    return 0;
}

// Note a few important things here:
// myBm.left is nothing but a bimap<X,Y>::left_map type
// myBm.right is nothing but a bimap<X,Y>::right_map type.
// So typedef bimap<X,Y>::left_map::const_iterator left_const_iterator is a const iterator type for the left map.
// Infact for ease of use, bimap defines some easy usage techniques.
// You can use bimap<X,Y>::left_<type> directly instead of bimap<X,Y>::left_map::<type>


