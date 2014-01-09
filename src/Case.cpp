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

Pion *Case::getPion()
{
    return this->p;
}

void Case::setPion(Pion *p)
{
    this->p = p;
}
