#include "../include/CaseO.h"
#include <iostream>
using namespace std;

CaseO::CaseO(int x, int y) : Case(x, y)
{
  cout << "CaseO Init IN" << endl;
  this->jouable = 0;
  cout << "CaseO Init Jouable" << endl;
  this->disposition = vector <int>(2);
  this->disposition[0] = 0;
  cout << "CaseO Init disposition[0]" << endl;
  this->disposition[1] = 0;
  cout << "CaseO Init OUT" << endl;
}

CaseO::~CaseO()
{

}

int CaseO::isJouable()
{
  return this->jouable;
}

void CaseO::setJouable()
{
  this->jouable = 1;
}

void CaseO::setPasJouable()
{
  this->jouable = 0;
}

void CaseO::setPion(Pion * p)
{
  Case::setPion(p);
  this->setPasJouable();
}


void CaseO::setDisposition(int c, int d)
{
  if (c == 1 || c == 0)
    this->disposition[c] = d;
}

int CaseO::getDisposition(int c)
{
  int ret = 0;
  if (c == 1 || c == 0)
    ret = this->disposition[c];
  return ret;
}


std::string CaseO::afficher()
{
  std::string s = " ";
  if (this->hasPion()) s = this->p->afficher();
  return s;
}
