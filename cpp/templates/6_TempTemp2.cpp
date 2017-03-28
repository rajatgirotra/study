#include <iostream>
using namespace std;

template<class T, unsigned int size>
class Array
{
  private:
    T data[size];
    unsigned int count;
    unsigned int capacity;

  public:
    Array()
    {
      count = 0;
    }

    ~Array()
    {
    }

    void push_back(const T& roT)
    {
        if(count < size)
         data[count++] = roT;
    }

    T pop_back(unsigned int p_count)
    {
        if(count > 0)
        return data[--count];
    }

    T* begin() { return data; }
    T* end()    { return data + count; }

};

template<class T, unsigned int size, template<class, unsigned int> class Seq>
class Container
{
  private:
    Seq<T, size> seq;

  public:
    void append(const T& roT) { seq.push_back(roT); }
    T* begin() { return seq.begin(); }
    T* end() { return seq.end(); }
};

int main()
{
  static const unsigned int INIT = 10;
  Container<int, INIT, Array> oContainer;
  for(int i = 0; i < 10; ++i)
    oContainer.append(i * 10);

  int* poInt = oContainer.begin();
  while(poInt != oContainer.end())
    cout<<*poInt++<<endl;

  return 0;
}

/*

Once again, parameter names are not needed in the declaration of Seq inside Containers declaration, but we need two parameters to declare the data member seq, hence the appearance of the non-type parameter N at the top level.


*/
