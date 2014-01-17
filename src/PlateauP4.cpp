#include "../include/PlateauP4.h"
#include <iostream>

using namespace std;

PlateauP4::PlateauP4(){}

PlateauP4::PlateauP4(string names[]) : Plateau(7,6)
{
  //ctor
  int i;
  int j;
  for (i=0; i<tailleH; i++) {
    for (j=0; j<tailleV; j++)
      this->grille[i][j] = new Case(i,j);
  }
  this->j1(names[0], 21, 0);
  this->j2(names[1], 21, 1);
}


PlateauP4::~PlateauP4()
{    
  //dtor
  for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleV; j++)
      delete(this->grille[i][j]);
  }
}

/* Methode pour joueur un pion sur la grille */
PlateauP4::game()
{
  
}
