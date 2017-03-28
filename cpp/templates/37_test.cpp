#include <iostream>
using namespace std;

template <unsigned int R, unsigned int C, typename T>
void init1 ( T arr[R][C] )
{
   int i, j;
   for(i = 0; i < R; ++i)
      for(j = 0; j <C; ++j)
        arr[i][j] *= 2;
}

template <unsigned int R, unsigned int C, typename T>
void init2 ( T (&arr)[R][C] )
{
   int i, j;
   cout<<"R = "<<R<<endl;
   cout<<"C = "<<C<<endl;
   for(i = 0; i < R; ++i)
      for(j = 0; j <C; ++j)
        arr[i][j] *= 2;
}

int main()
{
   int x[2][3];
   int i, j;
   for(i = 0; i < 2; ++i)
     for(j = 0; j <3; ++j)
        x[i][j] = (i + j);

    
   for(i = 0; i < 2; ++i)
   {
     for(j = 0; j <3; ++j)
        cout<<x[i][j];
     cout<<endl;
   }

   cout<<endl;
   init1<2, 3>(x);
   init2(x);

   for(i = 0; i < 2; ++i)
   {
     for(j = 0; j <3; ++j)
        cout<<x[i][j];
     cout<<endl;
   }

   return 0;
}
   

