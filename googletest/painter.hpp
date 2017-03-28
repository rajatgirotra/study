#pragma once
#include <iostream>
using std::cout;
using std::endl;
class Painter
{
private:
    Turtle& m_turtle;

public:
    Painter(Turtle& arg) : m_turtle(arg) {}
    inline void TestOne() {
        m_turtle.PenDown();
        // m_turtle.PenUp();
    }
    inline void TestTwo() {
        m_turtle.Forward(0);
        m_turtle.Forward(20);
        m_turtle.Forward(20);
    }
    inline void TestThree() {
        m_turtle.Forward(20);
        m_turtle.Forward(20);
        m_turtle.Forward(20);
    }
    inline void TestFour() {
        m_turtle.Forward(20);
        m_turtle.Forward(0);
        m_turtle.Forward(20);
    }
    inline void TestFive() {
        m_turtle.Forward(0);
        m_turtle.Forward(20);
        m_turtle.Forward(20);
    }
    inline void TestSix() {
        //m_turtle.GoTo(0,0);
        m_turtle.GoTo(2,3);
        m_turtle.GoTo(0,0);
        m_turtle.GoTo(4,5);
        m_turtle.GoTo(0,0);
        m_turtle.GoTo(2,3);
        m_turtle.GoTo(4,5);
    }
    inline void TestSeven() {
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;        
    }
    inline void TestEight() {
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;        
    }
    inline void TestNine() {
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;
        cout << "Painter::TestSeven(): " << m_turtle.GetX() << endl;        
    }

};
