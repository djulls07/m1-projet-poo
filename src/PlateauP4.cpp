#include "../include/PlateauP4.h"
#include <sstream>

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
  string s;
  int col;

  //A qui le tour !
  if (!n) j = &j1;
  else j = &j2; 

  cout << "Joueur " << n+1 << "( " << j->getNom() << 
    " ) choix colonne ? ( 1 -7 )" << endl;
  while(1) {
    try {
      cin >> col;
      if (col < 1 || col > 7) throw 7;
      break;
    } catch (int e) {
      cout << "Erreur, besoin d'un nombre entre 1 et 7, essaye encore !" << endl;
      continue;
    }
  }
  col--;
  if (this->checkCaseJouable(Position(col,0))) {
    this->jouerPion(Position(col,0), j);
  }
}

int PlateauP4::endGame()
{
  //check si jeu doit finir ( gagant egalité etc...)
  
  return 0;
}

bool PlateauP4::checkCaseJouable(Position p)
{
  //pour le puissance 4 la seul info importante est abscisse(Position.getX()).
  if (this->grille[p.getX()][0]->getPion() == 0)
    return true;
  return false;
}

void PlateauP4::jouerPion(Position p, Joueur *j)
{
  int i(0);
  if (j->getLPions().size() > 0) {
    while(i < 6 && this->getCase(Position(p.getX(),i))->getPion() == 0)i++;
    //Pion *pion = j->getRandPion();
    //A REFAIRE MAYBE SANS LE NEW MAIS AVEC un .back sur le vector...
    //this->getCase(Position(p.getX(), i-1))->setPion(new Pion(j->getCouleur()));
    this->getCase(Position(p.getX(), i-1))->setPion(j->getLPions().back());
    j->getLPions().pop_back();
  }
}

string PlateauP4::afficher()
{
  string s = "";
  for (int i(0); i < this->tailleV; i++) {
    for (int j(0); j< this->tailleH; j++) {
      s += this->grille[j][i]->afficher() + " | ";
    }
    s += "\n";
  }
  return s;
}
