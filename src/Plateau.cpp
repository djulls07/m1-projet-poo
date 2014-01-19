#include "../include/Plateau.h"
#include <iostream>
using namespace std;

Plateau::Plateau()
{
  //ctor
  this->fin = -1;
}

Plateau::Plateau(unsigned int h, unsigned int v) : tailleH(h), tailleV(v)
{
  //ctor
  this->grille = vector <vector <Case*> >(tailleH, vector<Case*>(tailleV));
  this->fin = -1;
}

Plateau::~Plateau()
{
  //dtor
}

unsigned int Plateau::getTailleH()
{
  return this->tailleH;
}

unsigned int Plateau::getTailleV()
{
  return this->tailleV;
}

/* Retourne la case du plateau correspondant a la psition*/
Case *Plateau::getCase(Position p)
{
  if (this->estValide(p)) {
    return this->grille[p.getX()][p.getY()];
  }
  else return 0;
}

/* Verifie la validité d'une case par rapport au plateau */
bool Plateau::estValide(Position p)
{
  if (this->tailleH > p.getX() && p.getX() >= 0 && p.getY() >= 0 && this->tailleV > p.getY())
    return true;
  else 
    return false;
}


/* deplace le pion a la position depart vers arrive, le pion de la
 * case d'arrive doit avoir ete retirié avant ou il sera perdu
 */
void Plateau::deplacerPion(Position depart, Position arrive)
{
  Pion *p1;
  Pion *p2;
  Pion *p;
  try {
    if (depart==arrive) {
      cout << "Aucun déplacement nécessaire.\n" << endl;
      throw 7;
    }
    p1 = this->getCase(depart)->getPion();
    p2 = this->getCase(arrive)->getPion();
    this->getCase(depart)->setPion(p2);
    this->getCase(arrive)->setPion(p1);
  } catch (int e) {
    cout << "Exception as occured in deplacerPion: " << e << endl;
    return;
  }
}
