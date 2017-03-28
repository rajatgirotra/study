/*
 * Another exercise,
 * We want to count the number of occurences of each word in text and then print them out in order of appearance.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <map>
#include <boost/tokenizer.hpp>

using namespace std;

struct counter
{
    private:
        unsigned int c;
    public:
        counter() : c(0) {}
        counter& operator++ () { ++c; return *this; }
        unsigned int operator++ (int) { return c++; }
        operator const unsigned int () const { return c; }
};

typedef counter counter_type;

int main()
{
    typedef boost::bimap <
        boost::bimaps::unordered_set_of<std::string>, //left view, use hash for speed.
        boost::bimaps::list_of<counter_type> //right view, use list. This will when we traverse the right view, we
                                            // get the count of words in appearance order.
        > word_counter;

    word_counter wc;

    std::string text=
        "Relations between data in the STL are represented with maps."
        "A map is a directed relation, by using it you are representing "
        "a mapping. In this directed relation, the first type is related to "
        "the second type but it is not true that the inverse relationship "
        "holds. This is useful in a lot of situations, but there are some "
        "relationships that are bidirectional by nature.";

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

    tokenizer token(text, boost::char_separator<char>("!~`#,.? \t\n\":-;'"));

    for(tokenizer::iterator iter = token.begin(); iter != token.end(); ++iter)
    {
        ++wc.left[*iter];
    }

    //Print in order of appearcne, using the right view which is sequenced.
    for(word_counter::right_const_iterator it = wc.right.begin(); it != wc.right.end(); ++it)
    {
        cout << "Word is: " << it->second << "    Count is: " << it->first << endl;
    }
    return 0;
}

