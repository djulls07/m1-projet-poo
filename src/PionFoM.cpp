#include "../include/PionFoM.h"
PionFoM::PionFoM()
{
}

PionFoM::PionFoM(unsigned int c) : Pion(c)
{
  //ctor
}

PionFoM::~PionFoM()
{
  //dtor
}

std::string PionFoM::afficher()
{
 return intToString(this->couleur);
}
