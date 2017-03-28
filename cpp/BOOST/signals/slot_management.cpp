// It is possible for boost::signals2 to track slots. If a slot function object is destroyed, signal will not call the slot.
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
using std::cout;
using std::endl;

struct NewsItem {};

struct NewsSlot {
    void operator() (const NewsItem&) {
        cout << "NewsSlot got NewsItem" << endl;
    }
};

int main(int argc, char *argv[]) {
    typedef boost::signals2::signal<void(const NewsItem&)> signal_type;
    signal_type sig;

    boost::shared_ptr<NewsSlot> news_slot(new NewsSlot());
    // Before connecting the slot, you need to call slot::track(shared_ptr(slot))
    auto conn = sig.connect(signal_type::slot_type(
                                &NewsSlot::operator(), news_slot.get(), _1).track(news_slot));


    NewsItem item;
    sig(item);

    // resetting news_slot ptr.
    news_slot.reset();
    sig(item); // slot will not get called.
    return 0;
}


