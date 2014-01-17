#include "../include/Plateau.h"
#include <iostream>
using namespace std;

Plateau::Plateau()
{
  //ctor
}

Plateau::Plateau(unsigned int h, unsigned int v) : tailleH(h), tailleV(v)
{
  //ctor
  this->grille = vector <vector <Case*> >(tailleH, vector<Case*>(tailleV));
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
}

/* Verifie la validité d'une case par rapport au plateau */
bool Plateau::estValide(Position p)
{
  if (this->tailleH > p.getX() && this->tailleV > p.getY())
    return true;
  return false;
}


/* deplace le pion a la position depart vers arrive, le pion de la
 * case d'arrive doit avoir ete retirié avant ou il sera perdu
 */
void Plateau::deplacerPion(Position depart, Position arrive)
{
  Case c;
  try {
    if (depart==arrive) {
      cout << "Aucun déplacement nécessaire.\n" << endl;
      throw 7;
    }
    this->echangeCase(depart, arrive);//echange case verifie la validité des pos
  } catch (int e) {
    cout << "Exception as occured in deplacerPion: " << e << endl;
    return;
  }
}

void Plateau::afficher()
{
  unsigned int i,j;
  for (i=0; i < this->tailleV; i++) {
    for (j=0; j< this->tailleH; j++)
      cout << "| " << this->grille[j][i]->getPosition().getX() << 
	"/" << this->grille[j][i]->getPosition().getY() << " |";
    cout << endl;
  }
}

void Plateau::echangeCase(Position a, Position b)
{
  Case *c1;
  Case *c2;
  Case *tmp;
  if (this->estValide(a) && this->estValide(b)) {
    c1 = this->grille[a.getX()][a.getY()];
    c2 = this->grille[b.getX()][b.getY()];
    tmp = c2;
    c2 = c1;
    c1 = tmp;
  }
}
