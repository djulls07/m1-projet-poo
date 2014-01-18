#include "../include/Pion.h"

Pion::Pion()
{
    //ctor
}

Pion::Pion(unsigned int i) : couleur(i)
{
  //ctor
}

Pion::~Pion()
{
    //dtor
}

std::string Pion::afficher()
{
  if (this->couleur == 0)
    return "1";
  return "2";
}
