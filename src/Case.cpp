#include "../include/Case.h"

Case::Case()
{
    //ctor
}

Case::Case(int x, int y): pos(x,y)
{
  //ctor
  this->p = 0;
}

Case::~Case()
{
    //dtor
  if (this->hasPion()) delete(this->p);
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

std::string Case::afficher()
{
  std::string s = "0";
  if (this->p != 0) s = this->p->afficher();
  return s;
}

bool Case::hasPion()
{
  if (this->p != 0) return true;
  return false;
}
