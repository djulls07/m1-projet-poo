#include "../include/PlateauP4.h"
#include <iostream>

using namespace std;

PlateauP4::PlateauP4()
{
}

PlateauP4::PlateauP4(string names[]) : Plateau(7,6)
{
  //ctor
  int i;
  int j;
  for (i=0; i<tailleH; i++) {
    for (j=0; j<tailleV; j++)
      this->grille[i][j] = new Case(i,j);
  }
  this->j1 = Joueur(names[0], 21, 0);
  this->j2 = Joueur(names[1], 21, 1);
}


PlateauP4::~PlateauP4()
{    
  //dtor
  for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleV; j++)
      delete(this->grille[i][j]);
  }
}

/* Methode pour joueur un pion sur la grille 
   n=0 -> joueur1 et n=1 -> joueur2 */
void PlateauP4::game(int n)
{
  Joueur *j;
  //A qui le tour !
  if (!n) j = &j1;
  else j = &j2;
  
}

int PlateauP4::endGame()
{
  //check si jeu doit finir ( gagant egalité etc...)
}
