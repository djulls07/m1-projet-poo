#include "../include/Position.h"


Position::Position() 
{
  //ctor
}

Position::Position(int x, int y) 
{
  this->x = x;
  this->y = y;
}

Position::~Position()
{
  //dtor
}

int Position::getX()
{
  return x;
}

int Position::getY()
{
  return y;
}

bool Position::estEgal(Position a)
{
  if (a.x == this->x && a.y == this->y) return true;
  else return false;
}

bool Position::operator==(Position a)
{
  return estEgal(a);
}

void Position::setX(int x)
{
  this->x = x;
}

void Position::setY(int y)
{
  this->y = y;
}

Position Position::createModPos(int incrX, int incrY)
{
  return Position(this->x+incrX, this->y+incrY);
}
