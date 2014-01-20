#include "../include/PlateauO.h"
#include <iostream>
#include <limits>
using namespace std;

PlateauO::PlateauO(string names[]): Plateau(8,8)
{
  //ctor
  int i;
  int j;
  this->grille = vector <vector <CaseO*> >(tailleH, vector<CaseO*>(tailleV));
  for (i=0; i<tailleH; i++) {
    for (j=0; j<tailleV; j++) {
      this->grille[i][j] = new CaseO(i,j);
      // Initialisation des cases
      if (i == 2 || i == 5) {
	if (j > 1 && j < 6)
	  this->grille[i][j]->setJouable();
      } else if (i == 3) {
	if (j == 2 || j == 5)
	  this->grille[i][j]->setJouable();
	else if (j == 3)
	  this->grille[i][j]->setPion(new Pion(1));
	else if (j == 4)
	  this->grille[i][j]->setPion(new Pion(2));
      } else if (i == 4) {
	if (j == 2 || j == 5)
	  this->grille[i][j]->setJouable();
	else if (j == 3)
	  this->grille[i][j]->setPion(new Pion(2));
	else if (j == 4)
	  this->grille[i][j]->setPion(new Pion(1));
      }
    }
  }

  this->j1 = Joueur(names[0], 40, 1);
  this->j2 = Joueur(names[1], 40, 2);
}

PlateauO::~PlateauO()
{    //dtor
  /*for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleV; j++) {
      delete(this->grille[i][j]);
      cout << "i:" << i << " j:" << j << endl;
    }
    }*/
  
  cout << "SHIT" << endl;
  j1.~Joueur();
  cout << "dtor" << endl;
}

CaseO* PlateauO::getCase(Position p)
{
   if (this->estValide(p)) {
    return this->grille[p.getX()][p.getY()];
  }
  
}

int PlateauO::checkCaseJouableHorizontale(Position p, int c) 
{
  int i;
  int ret = 0;
  if (p.getX()-2 >= 0 && 
      this->getCase(p.createModPos(-1, 0))->hasPion() &&
      this->getCase(p.createModPos(-1, 0))->getPion()->getCouleur() != c) {
    for (i = 2; p.getX()-i >= 0; i++) {
      if (!this->getCase(p.createModPos(-i, 0))->hasPion())
	break;
      if (this->getCase(p.createModPos(-i, 0))->getPion()->getCouleur() == c) {
	ret += 1;
	break;
      }
    }
  }

  if (p.getX()+2 < tailleH && 
      this->getCase(p.createModPos(1, 0))->hasPion() && 
      this->getCase(p.createModPos(1, 0))->getPion()->getCouleur() != c) {
    for (i = 2; p.getX()+i < tailleH; i++) {
      if (!this->getCase(p.createModPos(i, 0))->hasPion())
	break;
      if (this->getCase(p.createModPos(i, 0))->getPion()->getCouleur() == c) {
	ret += 2;
	break;
      }
    }
  }
  return ret;
}

int PlateauO::checkCaseJouableVerticale(Position p, int c) 
{
  int i;
  int ret = 0;
  if (p.getY()-2 >= 0 && 
      this->getCase(p.createModPos(0, -1))->hasPion() &&
      this->getCase(p.createModPos(0, -1))->getPion()->getCouleur() != c) {
    for (i = 2; p.getY()-i >= 0; i++) {
      if (!this->getCase(p.createModPos(0, -i))->hasPion())
	break;
      if (this->getCase(p.createModPos(0, -i))->getPion()->getCouleur() == c) {
	ret += 4;
	break;
      }
    }
  }

  if (p.getY()+2 < tailleV && 
      this->getCase(p.createModPos(0, 1))->hasPion() && 
      this->getCase(p.createModPos(0, 1))->getPion()->getCouleur() != c) {
    for (i = 2; p.getY()+i < tailleV; i++) {
      if (!this->getCase(p.createModPos(0, i))->hasPion())
	break;
      if (this->getCase(p.createModPos(0, i))->getPion()->getCouleur() == c) {
	ret += 8;
	break;
      }
    }
  }
  return ret;
}

int PlateauO::checkCaseJouableDiagonale(Position p, int c) 
{
  int i;
  int ret = 0;
  if (p.getX()-2 >= 0 && p.getY()-2 >= 0 &&
      this->getCase(p.createModPos(-1, -1))->hasPion() &&
      this->getCase(p.createModPos(-1, -1))->getPion()->getCouleur() != c) {
    for (i = 2; p.getX()-i >= 0 && p.getY()-i >= 0; i++) {
      if (!this->getCase(p.createModPos(-i, -i))->hasPion())
	break;
      if (this->getCase(p.createModPos(-i, -i))->getPion()->getCouleur() == c) {
	ret += 16;
	break;
      }
    }
  }

  if (p.getX()+2 < tailleH && p.getY()+2 < tailleV && 
      this->getCase(p.createModPos(1, 1))->hasPion() && 
      this->getCase(p.createModPos(1, 1))->getPion()->getCouleur() != c) {
    for (i = 2; p.getX()+i < tailleH && p.getY()+i < tailleV; i++) {
      if (!this->getCase(p.createModPos(i, i))->hasPion())
	break;
      if (this->getCase(p.createModPos(i, i))->getPion()->getCouleur() == c) {
	ret += 32;
	break;
      }
    }
  }

  if (p.getX()-2 >= 0 && p.getY()+2 < tailleV &&
      this->getCase(p.createModPos(-1, 1))->hasPion() &&
      this->getCase(p.createModPos(-1, 1))->getPion()->getCouleur() != c) {
    for (i = 2; p.getX()-i >= 0 && p.getY()+i < tailleV; i++) {
      if (!this->getCase(p.createModPos(-i, i))->hasPion())
	break;
      if (this->getCase(p.createModPos(-i, i))->getPion()->getCouleur() == c) {
	ret += 64;
	break;
      }
    }
  }
  
  if (p.getX()+2 < tailleH && p.getY()-2 >= 0 && 
      this->getCase(p.createModPos(1, -1))->hasPion() && 
      this->getCase(p.createModPos(1, -1))->getPion()->getCouleur() != c) {
    for (i = 2; p.getY()-i >= 0 && p.getX()+i < tailleH ; i++) {
      if (!this->getCase(p.createModPos(i, -i))->hasPion())
	break;
      if (this->getCase(p.createModPos(i, -i))->getPion()->getCouleur() == c) {
	ret += 128;
	break;
      }
    }
  }

  return ret;
}

bool PlateauO::checkCaseJouable(Position p)
{
  if (this->getCase(p)->isJouable())
    return true;
  return false;
   
}

int PlateauO::checkCouleurJouable(int c) 
{
  int ret;
  int ok = 0;
  int i, j;
  Position p;
  for (i = 0; i < tailleH; i++) {
    for (j = 0; j < tailleV; j++) {
      p = Position(i, j);
      if (this->checkCaseJouable(p)) {
	ret = this->checkCaseJouableHorizontale(p, c+1) +
	  this->checkCaseJouableVerticale(p, c+1) +
	  this->checkCaseJouableDiagonale(p, c+1);
	this->getCase(p)->setDisposition(c, ret);
	if (ret > 0)
	  ok = 1;
      }	
    }
  }
  return ok;
}



void PlateauO::retournerHorizontale(Position p, int c, int disposition)
{
  int i;
  if (p.getX()-1 >= 0) {
    if (this->getCase(p.createModPos(-1, 0))->hasPion()) {
      if (disposition%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(-i, 0))->hasPion() &&
	       this->getCase(p.createModPos(-i, 0))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(-i, 0))->getPion()->setCouleur(c);
	  //cout << "retournerHorizontale1 i:" << i << " "  << p.getX()-i << " " << p.getY() << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(-1, 0))->setJouable();
  }
  
  if (p.getX()+1 < tailleH) {
    if (this->getCase(p.createModPos(1, 0))->hasPion()) {
      if ((disposition/2)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(i, 0))->hasPion() &&
	       this->getCase(p.createModPos(i, 0))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(i, 0))->getPion()->setCouleur(c);
	  //cout << "retournerHorizontale2 i:" << i << " "  << p.getX()+i << " " << p.getY() << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(1, 0))->setJouable();
  }
}

void PlateauO::retournerVerticale(Position p, int c, int disposition)
{
  int i;
  if (p.getY()-1 >= 0) {
    if (this->getCase(p.createModPos(0, -1))->hasPion()) {
      if ((disposition/4)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(0, -i))->hasPion() &&
	       this->getCase(p.createModPos(0, -i))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(0, -i))->getPion()->setCouleur(c);
	  //cout << "retournerVerticale1 i:" << i << " "  << p.getX() << " " << p.getY()-i << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(0, -1))->setJouable();
  }
  
  if (p.getY()+1 < tailleV) {
    if (this->getCase(p.createModPos(0, 1))->hasPion()) {
      if ((disposition/8)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(0, i))->hasPion() &&
	       this->getCase(p.createModPos(0, i))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(0, i))->getPion()->setCouleur(c);
	  //cout << "retournerVerticale2 i:" << i << " "  << p.getX() << " " << p.getY()+i << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(0, 1))->setJouable();
  }
  return;
}

void PlateauO::retournerDiagonale(Position p, int c, int disposition) 
{
  int i;
  if (p.getX()-1 >= 0 && p.getY()-1 >= 0) {
    if (this->getCase(p.createModPos(-1, -1))->hasPion()) {
      if ((disposition/16)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(-i, -i))->hasPion() &&
	       this->getCase(p.createModPos(-i, -i))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(-i, -i))->getPion()->setCouleur(c);
	  //cout << "retournerDiagonale1 i:" << i << " "  << p.getX()-i << " " << p.getY()-i << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(-1, -1))->setJouable();
  }
  
  if (p.getX()+1 < tailleH && p.getY()+1 < tailleV) {
    if (this->getCase(p.createModPos(1, 1))->hasPion()) {
      if ((disposition/32)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(i, i))->hasPion() &&
	       this->getCase(p.createModPos(i, i))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(i, i))->getPion()->setCouleur(c);
	  //cout << "retournerDiagonale2 i:" << i << " "  << p.getX()+i << " " << p.getY()+i << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(1, 1))->setJouable();
  }

  if (p.getX()-1 >= 0 && p.getY()+1 < tailleV) {
    if (this->getCase(p.createModPos(-1, 1))->hasPion()) {
      if ((disposition/64)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(-i, i))->hasPion() &&
	       this->getCase(p.createModPos(-i, i))->getPion()->getCouleur() != c) {
	  this->getCase(p.createModPos(-i, i))->getPion()->setCouleur(c);
	  //cout << "retournerDiagonale3 i:" << i << " "  << p.getX()-i << " " << p.getY()+i << endl;
	  i++;
	}
      }
    } else
      this->getCase(p.createModPos(-1, 1))->setJouable();
  }

  if (p.getX()+1 < tailleH && p.getY()-1 >= 0) {
    if (this->getCase(p.createModPos(1, -1))->hasPion()) {
      if ((disposition/128)%2 == 1) {
	i = 1;
	while (this->getCase(p.createModPos(i, -i))->hasPion() &&
	       this->getCase(p.createModPos(i, -i))->getPion()->getCouleur() != c) {
	  getCase(p.createModPos(i, -i))->getPion()->setCouleur(c);
	  //cout << "retournerDiagonale4 i:" << i << " "  << p.getX()+i << " " << p.getY()-i << endl;
	  i++;
	}
      }
    } else
      getCase(p.createModPos(1, -1))->setJouable();
  }

  return;
}

void PlateauO::jouerPion(Position p, Joueur* j)
{
  this->getCase(p)->setPion(new Pion(j->getCouleur()));
  j->getLPions().pop_back();
}

int PlateauO::jouerPionO(Position p, Joueur* j) 
{
  int dispo = this->getCase(p)->getDisposition(j->getCouleur()-1);
  if (this->getCase(p)->isJouable() && dispo > 0) {
    jouerPion(p, j);
    this->retournerHorizontale(p, j->getCouleur(), dispo);
    this->retournerVerticale(p, j->getCouleur(), dispo);
    this->retournerDiagonale(p, j->getCouleur(), dispo);
    return 0;
  } else
    return 1;
}

/* Méthode qui vérifie qu'un joueur peut jouer et le fait jouer.
 *
 */
int PlateauO::game(int joueur) {
  int ok = 0;
  int x, y;
  Joueur *j;

  //A qui le tour !
  if (!joueur) j = &j1;
  else j = &j2;
  
  if (joueur == 1 || joueur == 0) {
    ok = this->checkCouleurJouable(joueur);
    if (!ok) {
      cout << j->getNom() << " tu n'as pas de possibilités!" << endl;
      return 1; 
    }
    cout << j->getNom() << " à toi de jouer (Joueur " << joueur+1 << ")! :\n" 
	 << "Choix case (Valeurs : 1 - 8) (Format -> X Y)" << endl;
    while(true) {
      try {
	cin >> x >> y;
	if (x < 1 || x > 8 || y < 1 || y > 8) throw 0;
	if (jouerPionO(Position(x-1, y-1), j)) throw 1;
	break;
      } catch (int e) {
	if (e == 0) {
	  cout << "Erreur : N'essaye pas de jouer en dehors du plateau petit coquin!\n" 
	       << "(Valeurs : 1 - 8) (Format -> X Y)" << endl;
	  cin.clear();
	  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  continue;
	} else if (e == 1) {
	  cout << "Erreur : Tu ne peux pas jouer la!\n" 
	       << "(Valeurs : 1 - 8) (Format -> X Y)" << endl;
	  continue;
	}
      }
    }
    cout << this->afficher();
    return 0;
  }
  cout << "Erreur joueur inconnu!" << endl;
  return 3;
}

int PlateauO::endGame() {
  int ptsJ1 = 0;
  int ptsJ2 = 0;
  Position p;
  for (int i(0); i < tailleV; i++) {
    for (int j(0); j < tailleH; j++) {
      p = Position(i, j);
      if (this->getCase(p)->hasPion()) {
	if (this->getCase(p)->getPion()->getCouleur() == 1)
	  ptsJ1++;
	else if (this->getCase(p)->getPion()->getCouleur() == 2)
	  ptsJ2++;
      }
    }
  }
  
  if (ptsJ1 > ptsJ2) 
    cout << "Bravo " << this->j1.getNomCouleur() << "! Tu as gagné (Joueur 1) avec " 
	 << ptsJ1 << " points contre "
	 << ptsJ2 << " points." << endl;
  else if (ptsJ1 < ptsJ2) 
    cout << "Bravo " << this->j2.getNomCouleur() << "! Tu as gagné (Joueur 2) avec " 
	 << ptsJ2 << " points contre "
	 << ptsJ1 << " points." << endl;
  else
    cout << "Egalité! " << ptsJ1 << " points partout." << endl;
  return 0;
}

int PlateauO::run() {
  int fin;
  cout << "Bienvenue dans Othello " << this->j1.getNom() << " et " << this->j2.getNom() << "!" << endl;
  cout << this->afficher();
  /*while (1) {
    fin = 0;
    fin += game(0);
    fin += game(1);
    if (fin > 2)
      return 1;
    else if (fin == 2)
      break;
      }*/
  fin = endGame();
  cout << "Belle partie! A la prochaine!" << endl;
  return fin;
}

string PlateauO::afficher()
{
  string s = "";
  s += "X\\Y  1   2   3   4   5   6   7   8\n";
  for (int i(0); i < this->tailleH; i++) {
    s += "------------------------------------\n ";
    s += intToString(i+1);
    s += " | ";
    for (int j(0); j < this->tailleV; j++) {
      s += this->getCase(Position(i, j))->afficher() + " | ";
    }
    s += "\n";
  }
  s += "------------------------------------\n";
  return s;
}
