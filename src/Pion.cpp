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
  if (this->couleur == 1)
    return "\033[31m1\033[0m";
  return "\033[33m2\033[0m";
}

int Pion::getCouleur()
{
  return this->couleur;
}

void Pion::setCouleur(int c)
{
  this->couleur = c;
}
