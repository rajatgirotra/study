#include <iostream>
#include <cstddef>
#include <fstream>
#include <new>
using namespace std;
ofstream out("Framis.out");

class Framis
{
  static const unsigned int sz = 20;
  unsigned char c[sz];

  public:
  static const unsigned int psize = 100;
  static unsigned char pool[];
  static bool isAllocated[];

  Framis()
  {
    out<<"Framis::Framis()"<<endl;
  }

  ~Framis()
  {
    out<<"Framis::~Framis()"<<endl;
  }

  void* operator new(size_t sz);

  void operator delete(void*);

};

unsigned char Framis::pool[ psize * sizeof(Framis)];
bool Framis::isAllocated[psize] = {false};

void* Framis::operator new(size_t size)
{
  int i;
  for(i = 0; i < psize; ++i)
  {
    if(!isAllocated[i])
    {
      out<<"SIZE = "<<size<<endl;
      isAllocated[i] = true;
      out<<"Allocating  block "<<i<<endl;
      return (pool + (i * sizeof(Framis)));
    }
  }
  out<<"Out of Memory"<<endl;
  throw bad_alloc();
}

void Framis::operator delete(void* m)
{
  if (!m)
    return;

  int block = static_cast<unsigned char*>(m) - static_cast<unsigned char*>(pool);
  block /= sizeof(Framis);

  if(isAllocated[block])
  {
    isAllocated[block] = false;
    out<<"Freeing Block "<<block<<endl;
  }
}


int main()
{

  Framis* poFramis[Framis::psize];

  try
  {
    for(int i = 0; i < Framis::psize; ++i)
    {
      poFramis[i] = new Framis;
    }

    new Framis;
  } catch(bad_alloc&)
  { out<<"Caught: Out of memory"<<endl; }

  delete poFramis[10];
  poFramis[10] = 0;

  Framis* x = new Framis;
  delete x;

  for(int i=0; i< Framis::psize; ++i)
    delete poFramis[i];

  Framis* poTemp = new Framis[5];
delete []poTemp;
}

