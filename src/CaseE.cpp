#include "../include/CaseE.h"

CaseE::CaseE(int x, int y): Case(x, y)
{
  this->p = 0;
  //ctor
}

CaseE::~CaseE()
{
    //dtor
  if (this->p !=0) delete(this->p);
}

Piece *CaseE::getPion()
{
    return this->p;
}

void CaseE::setPion(Piece *p)
{
    this->p = p;
}

std::string CaseE::afficher()
{
  std::string s = "   ";
  if (this->p != 0) s = this->p->afficher();
  return s;
}

bool CaseE::hasPion()
{
  if (this->p != 0) return true;
  return false;
}
