/*
 * And now the moment of truth. Bimap is much more than just a left or right view of two collections as an std::map.
 * 
 * 1] We already know a bimap is a collection of two sequences of types X and Y.
 * 2] Now we can also choose what types of collections are X and Y. a simple map, a multimap, a boost::unordered_map
 *    or boost::unordered_multimap.
 * 3] So now based on what our collection type is, the view type needn't be just the simple std::map. It will be based on the collection type.
 * 4] The collection type is specified as following:
 *
 *    typedef bimap < set_of<string>, set_of<int> > bimap_type;  // left and right views will be std::map
 *    typedef bimap < multiset_of<string>, multiset_of<int> > bimap_type;  // left and right views will be std::multimap
 *    typedef bimap < unordered_set_of<string>, unordered_set_of<int> > bimap_type;  // left and right views will be std::unordered_map
 *    typedef bimap < unordered_multiset_of<string>, unordered_multiset_of<int> > bimap_type;  // left and right views will be std::unordered_multimap
 *
 *    typedef bimap < list_of<string>, list_of<int> > bimap_type;  // left and right views will be of type list_map
 *    typedef bimap < vector_of<string>, vector_of<int> > bimap_type;  // left and right views will be of type vector_map
 *    typedef bimap < unconstrained_set_of<string>, unconstrained_set_of<int> > bimap_type;  // cannot be viewed.
 *    list_of and vector_of map views are not associated with any existing STL associative containers. 
 *    They are two examples of unsorted associative containers. unconstrained_set_of allow the user to ignore a view. This will be explained later.
 *
 *  5] Let us see things in action now.
 *
 *  6] If you dont specify a <collectionType_of>; to tell what type of collection you want to use, then default is collection of type set.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <boost/bimap.hpp>
#include <map>

using namespace std;
using namespace boost::bimaps;

template <typename MapType, typename CompatibleKey, typename CompatibleData>
void use_map(MapType& m, const CompatibleKey& key, const CompatibleData& data)
{
    typedef typename MapType::value_type map_value_type;
    typedef typename MapType::const_iterator const_iterator;
    
    m.insert(map_value_type(key, data));

    const_iterator iter = m.find(key);
    if(iter != m.end())
    {
        assert(iter->second == data);
        assert(iter->first == key);

        cout << iter->first << " --> " << iter->second << endl;
    }
    m.erase(key);
}

int main()
{
    typedef boost::bimap < set_of<string>, set_of<int> > bimap_type;
    bimap_type bm;

    //Standard std::map
    {
        std::map<string, int> m;
        use_map(m, "One", 1);
    }

    //bimap where collections are set_of
    //left map
    {
        typedef bimap_type::left_map left_map_type;
        left_map_type& m = bm.left;
        use_map(m, "One", 1);
    }

    //bimap where collections are set_of
    //right map
    {
        typedef bimap_type::right_map right_map_type;
        right_map_type& m = bm.right;
        use_map(m, 1, "One");
    }
    return 0;
}
