#ifdef _WIN32
   #error _WIN32
   #ifdef _WIN64
      //define something for Windows (64-bit only)
       #error _WIN64
   #endif
#elif __linux
   #error __linux
    // linux
#endif

int main()
{
    return 0;
}
