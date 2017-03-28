#include <iostream>
using namespace std;

template<class T>
class Array
{
  private:
    static const unsigned int INIT = 10;

    T* data;
    unsigned int count;
    unsigned int capacity;

  public:
    Array()
    {
      count = 0;
      data = new T[capacity = INIT];
    }

    ~Array()
    {
      delete[] data;
    }

    void push_back(const T& roT)
    {
      if(count == capacity)
      { 
        unsigned int newCapacity = 2 * capacity;
        T* newData = new T[newCapacity];
        for(int i = 0; i < count; ++i)
          newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
      }
      data[count++] = roT;
    }

    T pop_back(unsigned int p_count)
    {
      if(p_count >= count)
      {
        cout<<"Error!!. Trying to pop from a non available area"<<endl;
        return (T)0;
      }
      else
        return data[--count];
    }

    T* begin() { return data; }
    T* end()    { return data + count; }

};

template<class T, template<class> class Seq>
class Container
{
  private:
    Seq<T> seq;

  public:
    void append(const T& roT) { seq.push_back(roT); }
    T* begin() { return seq.begin(); }
    T* end() { return seq.end(); }
};

int main()
{
  Container<int, Array> oContainer;
  for(int i = 0; i < 10; ++i)
    oContainer.append(i * 10);

  int* poInt = oContainer.begin();
  while(poInt != oContainer.end())
    cout<<*poInt++<<endl;

  return 0;
}

/*

The Array class template is a trivial sequence container. The Container template takes two parameters: the type that it holds, and a sequence data structure to do the holding. The following line in the implementation of the Container class requires that we inform the compiler that Seq is a template:

  Seq<T> seq;
 
If we hadnt declared Seq to be a template template parameter, the compiler would complain here that Seq is not a template, since were using it as such. In main( ) a Container is instantiated to use an Array to hold integers, so Seq stands for Array in this example.

*/
