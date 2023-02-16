/* create a stack like data structure with the two operations:
 * push() --> pushes an element to the stack
 * pop() --> must pop the most frequent element from the stack. If more than one elements have a tie, return the element based on their insertion order.
 *
 * Very trivial. just maintain a std::map<frequency, vector<elements with that frequency>>
 */

#include <iostream>
#include <deque>
#include <map>
#include <array>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <iterator>

using namespace std;

struct FreqStack {
  private:
    std::map<int, std::deque<int>> m_stacks;
    std::unordered_map<int, int> m_count;

  public:
      void push(int val) {
          auto& count = m_count[val];
          ++count;
          auto& stack = m_stacks[count];
          stack.emplace_back(val);
      }

      int pop() {
          if(m_stacks.empty()) 
              throw std::runtime_error("no more elements to pop");

          int res = m_stacks.rbegin()->second.back();
          m_stacks.rbegin()->second.pop_back();
          if(m_stacks.rbegin()->second.empty()) {
              m_stacks.erase(m_stacks.rbegin()->first);
          }
          --m_count[res];
          return res;
      }
};

int main() {
	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_int_distribution dist(0, 9);
	std::array<int, 8> arr;

	auto gen = [&]() {
		return dist(engine);
	};

	std::generate(begin(arr), end(arr), gen);
	
	cout <<"Input array: ";
	std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
  cout << endl;

  FreqStack fq;
  for(auto&& val : arr) fq.push(val);

  try {
      while(true) {
          cout << "popped: " << fq.pop() << endl;
      }
  }catch(const std::exception& e) {
      cout << "Exception caught: " << e.what() << endl;
  }

  fq.push(5);
  fq.push(2);
  cout << "popped: " << fq.pop() << endl;
  fq.push(5);
  fq.push(2);
  cout << "popped: " << fq.pop() << endl;
}
