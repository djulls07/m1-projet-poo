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

int PlateauP4::run()
{
  cout << afficher();
  while(!endGame()) {
    game(0);
    cout << afficher();
    if (endGame()) {
      break;
    }
    game(1);
    cout << afficher();
  }
}

int PlateauP4::endGame()
{
  int r = 0;
  //check si jeu doit finir ( gagant egalité etc...)
  if ((r=checkDiagonales()) != 0) return r;
  //if ((r=checkLignes()) != 0) return r;
  //if ((r=checkColonnes()) !=0) return r;
  return 0;
}

int PlateauP4::checkColonnes()
{
  int count;
  int couleur = -1;
  Case *c;
  int i = 0;
  int j = 0;
  for (i=0; i<tailleH; i++) {
    count = 0;
    //si puissance 4 en colonnes, alors la couleur gagnante on the top...
    c = this->getCase(Position(i,j++));
    while(c->getPion() == 0 && j<tailleV-3) 
      c = this->getCase(Position(i,j++));
    if (j<tailleV-3) {
      c = this->getCase(Position(i,j++));
      couleur = c->getPion()->getCouleur();
      count = 1;
    } else {
      continue;
    }
    while(c->getPion() != 0 && j<tailleV) {
      c = this->getCase(Position(i,j));
      if (c->getPion()->getCouleur() == couleur) count++;
      else break;
      if (count == 4) return couleur;
    }
  }
  return 0;
}

int PlateauP4::checkDiagonales()
{
  int d(checkDiagoG());
  if (d == 0) d = checkDiagoD();
  cout << "diago: " << d << endl;
  return d;
}
 

int PlateauP4::checkDiagoG()
{
  checkDiag(Position(0,2));
  checkDiag(Position(0,1));
  checkDiag(Position(0,0));
  
  checkDiag(Position(1,0));	
  checkDiag(Position(2,0));
  checkDiag(Position(3,0));

}

int PlateauP4::checkDiagoD()
{
  
}

int PlateauP4::checkDiago(const Position p)
{
  Case *c = this->getCase(p);
  if (p.getX() < 4) { //DiagoG
    
    while ( c != 0) {
      
    }
  } else { //DiagoD
    
  }
}

int PlateauP4::checkLignes()
{
  return 0;
}
  
bool PlateauP4::checkCaseJouable(Position p)
{ 
  if (this->grille[p.getX()][0]->getPion() == 0)
    return true;
  return false;
}

void PlateauP4::jouerPion(Position p, Joueur *j)
{
  int i(0);
  if (j->getLPions().size() > 0) {
    while(i < 6 && this->getCase(Position(p.getX(),i))->getPion() == 0)i++;
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
