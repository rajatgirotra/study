/*
 * The next thing is that just like you can specify collection types for the left and right views, you can do the same for
 * the relations view. By default, the collections type of the relations view is the collection type of the left view.
 * But many others are supported like:
 *
 * left_based
 * right_based
 * set_of_relation<KeyComp>
 * multiset_of_relation<KeyComp>
 * unordered_set_of_relation<HashFunctor, EqualKey>
 * unordered_multiset_of_relation<HashFunctor, EqualKey>
 * list_of_relation
 * vector_of_relation
 * unconstrained_set_of_relation
 *
 * I dont really know under what circumstances will i need to use it.
 *
 * I'll any show how to tag your left and right views.
 */

#include <iostream>
#include <string>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>

using namespace std;
using namespace boost::bimaps;

struct spanish {}; //my tags to use in bimap
struct english {};

int main()
{
    typedef boost::bimap <
        boost::bimaps::unordered_set_of< boost::bimaps::tagged <std::string, spanish> >,
        boost::bimaps::unordered_set_of< boost::bimaps::tagged <std::string, english> >,
        list_of_relation
    > translator;

    translator trans; //create the bimap object.

    //trans.insert ///??? No no no, the relation view is not a set view any more. It is a list. so use push_back instead of insert.

    trans.push_back(translator::value_type("Hola", "Hello"));
    trans.push_back(translator::value_type("adios", "goodbye"));
    trans.push_back(translator::value_type("rosa", "Rose"));
    trans.push_back(translator::value_type("mosa", "table"));

    //lets use the tag names with the left and right views.
    //translator::left_const_iterator iter = trans.left.find("adios");
    translator::map_by<spanish>::const_iterator iter = trans.by<spanish>().find("adios");

    if(iter != trans.by<spanish>().end())
    {
        cout << "Spanish word: " << iter->get<spanish>() << "  in english means: " << iter->get<english>() << endl;
    }

    return 0;
}

