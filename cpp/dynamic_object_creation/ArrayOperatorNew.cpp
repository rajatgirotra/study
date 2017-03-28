    //: C13:ArrayOperatorNew.cpp
    // Operator new for arrays
    #include <new> // Size_t definition
    #include <fstream>
    using namespace std;
    ofstream trace("ArrayOperatorNew.out");

    class Widget {
      enum { sz = 10 };
      int i[sz];
    public:
      Widget() { trace << "*"; }
      ~Widget() { trace << "~"; }
      void* operator new(size_t sz) {
        trace << "Widget::new: "
             << sz << " bytes" <<" Size of Widget Class = "<<sizeof(Widget)<<endl;
        return ::new char[sz];  /* To call the default new */
      }
      void operator delete(void* p) {
        trace << "Widget::delete" << endl;
        ::delete []p;  /* To call the default delete */
      }
      void* operator new[](size_t sz) {
        trace << "Widget::new[]: "
             << sz << " bytes" <<" Size of Widget Class = "<<sizeof(Widget)<<endl;
        return ::new char[sz];
      }
      void operator delete[](void* p) {
        trace << "Widget::delete[]" << endl;
        ::delete []p;
      }
    };

    int main() {
      trace << "new Widget" << endl;
      Widget* w = new Widget;
      trace << "\ndelete Widget" << endl;
      delete w;
      trace << "\nnew Widget[25]" << endl;
      Widget* wa = new Widget[25];
      trace << "\ndelete []Widget" << endl;
      delete []wa;
    } ///:~


