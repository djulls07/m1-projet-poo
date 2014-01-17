#include "../include/Case.h"

Case::Case()
{
    //ctor
}

Case::Case(int x, int y): pos(x,y)
{
    //ctor
}

Case::~Case()
{
    //dtor
}

Position Case::getPosition()
{
    return this->pos;
}

void Case::setPosition(int x, int y)
{
  this->pos.setX(x);
  this->pos.setY(y);
}

Pion *Case::getPion()
{
    return this->p;
}

void Case::setPion(Pion *p)
{
    this->p = p;
}
