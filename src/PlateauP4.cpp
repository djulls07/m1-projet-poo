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
  this->j1 = Joueur(names[0], 21, 1);
  this->j2 = Joueur(names[1], 21, 2);
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
int PlateauP4::game(int n)
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
  int r = 0;
  //check si jeu doit finir ( gagant egalité etc...)
  if ((r=checkDiagonales()) != 0) return r;
  if ((r=checkLignes()) != 0) return r;
  if ((r=checkColonnes()) !=0) return r;
  return r;
}

int PlateauP4::checkColonnes()
{
  int count = 0;
  int couleur = -1;
  Case *c;
  int j;

  for (int i(0); i<tailleH; i++) {
    j = 0;
    count = 0;
    couleur = -1;
    c = this->getCase(Position(i, j++));
    if (c==0) cout << "NAAAHHH";
    if (c->hasPion()) {
      count++;
      couleur = c->getPion()->getCouleur();
    }
    while (j<tailleV) {
      c = this->getCase(Position(i,j++));
      if (c->hasPion()) {
	if (c->getPion()->getCouleur() == couleur) {
	  count++;
	  if (count == 4) return couleur;
	} else {
	  count = 1;
	  couleur = c->getPion()->getCouleur();
	}
      } else {
	count = 0;
	couleur = -1;
      }
    }
  }
  return 0;
}

int PlateauP4::checkDiagonales()
{
  int d = checkDiagoG();
  if (d == 0) d = checkDiagoD();
  return d;
}
 

int PlateauP4::checkDiagoG()
{
  /* diagonales gauche->droite */
  int t;
  if ((t=checkDiag(Position(0,2), true)) !=0) return t;
  if ((t=checkDiag(Position(0,1), true)) !=0) return t;
  if ((t=checkDiag(Position(0,0), true)) !=0) return t;
  if ((t=checkDiag(Position(1,0), true)) !=0) return t;
  if ((t=checkDiag(Position(2,0), true)) !=0) return t;
  if ((t=checkDiag(Position(3,0), true)) !=0) return t;
  return 0;
}

int PlateauP4::checkDiagoD()
{
  //diagonales droite->gauche
  int t;
  if ((t=checkDiag(Position(tailleH-1,2), false)) != 0) return t;
  if ((t=checkDiag(Position(tailleH-1,1), false)) != 0) return t;
  if ((t=checkDiag(Position(tailleH-1,0), false)) != 0) return t;
  if ((t=checkDiag(Position(tailleH-2,0), false)) != 0) return t;
  if ((t=checkDiag(Position(tailleH-3,0), false)) != 0) return t;
  if ((t=checkDiag(Position(tailleH-4,0), false)) != 0) return t;
  return 0;
}

int PlateauP4::checkDiag(Position p, bool b) //si true diago gauche->drt
{
  int count = 0;
  int couleur = -1;
  int x = p.getX();
  int y = p.getY();
  
  Case *c = this->getCase(p);
  if (c->hasPion()) {
    count++;
    couleur = c->getPion()->getCouleur();
  }
  if (b) { //DiagoG
    x++;
    y++;
    while ( (c = this->getCase(Position(x++, y++))) != 0 ) {
      if (c->hasPion()) {
	if (c->getPion()->getCouleur() == couleur) {
	  count++;
	  if (count == 4) return couleur;
	} else {
	  count = 1;
	  couleur = c->getPion()->getCouleur();
	}
      } else {
	count = 0;
	couleur = -1;
      }
    }
  } else { //DiagoD
    x--;
    y++;
    while ( (c = this->getCase(Position(x--, y++))) != 0 ) {
      if (c->hasPion()) {
	if (c->getPion()->getCouleur() == couleur) {
	  count++;
	  if (count == 4) return couleur;
	} else {
	  count = 1;
	  couleur = c->getPion()->getCouleur();
	}
      } else {
	count = 0;
	couleur = -1;
      }
    }
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
    while(i < 6 && !this->getCase(p.createModPos(0, i))->hasPion())i++;
    this->getCase(p.createModPos(0, i-1))->setPion(j->getLPions().back());
    j->getLPions().pop_back();
  }
}

string PlateauP4::afficher()
{ 
  string s = "";
  s += "X\\Y  1   2   3   4   5   6   7   8\n";
  for (int i(0); i < this->tailleV; i++) {
    s += "------------------------------------\n ";
    s += intToString(i+1);
    s += " | ";
    for (int j(0); j < this->tailleH; j++) {
      s += this->getCase(Position(i, j))->afficher() + " | ";
    }
    s += "\n";
  }
  s += "------------------------------------\n";
  return s;
}

int PlateauP4::run()
{
  int winner;
  string w;
  cout << afficher();
  while(!(winner=endGame())) {
    game(0);
    cout << afficher();
    if ((winner=endGame())) {
      break;
    }
    game(1);
    cout << afficher();
  }
  w = "Partie terminée, le vainqueur est -> ";
  if (winner == 1) w += j1.getNomCouleur();
  else if (winner == 2) w += j2.getNomCouleur();
  cout << w << endl;
  return 0;
}
