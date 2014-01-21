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
  std::string n = intToString(this->couleur);
  return "\033[3"+n+"m"+n+"\033[0m";
}
