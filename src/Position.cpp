#include "../include/Position.h"


Position::Position() {
    //ctor
}

Position::Position(int x, int y) {
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
