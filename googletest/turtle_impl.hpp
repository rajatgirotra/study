#pragma once

#include "turtle.hpp"

class TurtleProd : public Turtle
{
public:
  virtual ~TurtleProd() {}
  virtual void PenUp() override;
  virtual void PenDown() override;
  virtual void Forward(int distance) override;
  virtual void Turn(int degrees) override;
  virtual void GoTo(int x, int y) override;
  virtual int GetX() const override;
  virtual int GetY() const override;
};
