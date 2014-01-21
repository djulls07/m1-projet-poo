#include "../include/CaseFoM.h"

CaseFoM::CaseFoM()
{
  
}

CaseFoM::CaseFoM(int x, int y) : Case(x,y)
{
  this->p = 0;
}

CaseFoM::~CaseFoM()
{
  if (this->hasPion()) delete(this->p);
}

PionFoM *CaseFoM::getPion()
{
    return this->p;
}

void CaseFoM::setPion(PionFoM *p)
{
    this->p = p;
}

void CaseFoM::delPion()
{
  delete(this->p);
  this->p = 0;
}

std::string CaseFoM::afficher()
{
  std::string s = " ";
  if (this->p != 0) s = this->p->afficher();
  return s;
}

bool CaseFoM::hasPion()
{
  if (this->p != 0) return true;
  return false;
}
