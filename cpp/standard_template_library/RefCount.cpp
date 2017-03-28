#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
using namespace std;

template <typename T>
class RefCount
{
  private:
      T* _poT;
      long* _count;

      const long& count() const
      {
          return *_count;
      }

  public:
      RefCount(T* poT = nullptr) : _poT(poT), _count(new long(1))
      {}

      ~RefCount()
      {
          reset();
      }

      //Reset
      void reset(T* poT = nullptr)
      {
          --(*_count);
          if(count() == 0)
          {
              delete _poT;
              delete _count;
          }
          _poT = poT;
          if(poT)
              _count = new long(1);
      }
        
      //Copy c'tor
      RefCount(const RefCount& rhs) : _poT(rhs._poT), _count(rhs._count)
      { }

      //Assignment operator
      RefCount& operator = (const RefCount& rhs)
      {
          --(*_count);
          if(count() == 0)
          {
              delete _poT;
              delete _count;
          }
	  _poT = rhs._poT;
          _count = rhs._count;
          ++(*_count); 
      }

      T& operator* () { return *_poT; }
      const T& operator* () const { return *_poT; }
      T* operator -> () { return _poT; }
      const T* operator -> () const { return _poT; }
};

struct X
{
    int id;
    X(const int& pId) : id(pId)
    {
        cout << "C'ting X with id: " << id << endl;
    }

    X(const X& rhs) : id(rhs.id)
    {
        cout << "Copy C'ting X with id: " << id << endl;
    }

    ~X()
    {
        cout << "D'ting X with id: " << id << endl;
    }

    void display() const { cout << "X::id = " << id << endl; }
};

int main()
{
    RefCount<X> xCount(new X(100));
    xCount.reset();
    cout << "Exiting main" << endl;
    return 0;
}

