#include <limits>
#include <cstdlib>
#include "../include/Echequier.h"

using namespace std;

Echequier::Echequier(string names[]): Plateau(8, 8)
{
  int i;
  int j;
  this->grille = vector <vector <CaseE*> >(tailleH, vector<CaseE*>(tailleV));
  for (i=0; i<tailleH; i++) {
    for (j=0; j<tailleV; j++) {
      this->grille[i][j] = new CaseE(i,j);
      // Initialisation des cases
      // Noirs
      // Pions
      if (i == 0) {
	switch (j) {
	  // Tours
	case 0 :
	case 7 : {
	  this->grille[i][j]->setPion(new Piece(3, 2));
	  break;
	}
	  // Cavaliers
	case 1 :
	case 6 : {
	  this->grille[i][j]->setPion(new Piece(1, 2));
	  break;
	}
	  // Fous
	case 2 :
	case 5 : {
	  this->grille[i][j]->setPion(new Piece(2, 2));
	  break;
	}
	  //Dame
	case 3 : {
	  this->grille[i][j]->setPion(new Piece(4, 2));
	  break;
	}
	  //Roi
	case 4 : {
	  this->roiNoir = Position(i, j);
	  this->grille[i][j]->setPion(new Piece(5, 2));
	  break;
	}
	}
      } else if (i == 1)
	this->grille[i][j]->setPion(new Piece(0, 2));
      
      // Blancs
      // Pions
      else if (i == 6)
	this->grille[i][j]->setPion(new Piece(0, 1));
      else if (i == 7) {
	switch (j) {
	  // Tours
	case 0 :
	case 7 : {
	  this->grille[i][j]->setPion(new Piece(3, 1));
	  break;
	}
	  // Cavaliers
	case 1 :
	case 6 : {
	  this->grille[i][j]->setPion(new Piece(1, 1));
	  break;
	}
	  // Fous
	case 2 :
	case 5 : {
	  this->grille[i][j]->setPion(new Piece(2, 1));
	  break;
	}
	  //Dame
	case 3 : {
	  this->grille[i][j]->setPion(new Piece(4, 1));
	  break;
	}
	  //Roi
	case 4 : {
	  this->roiBlanc = Position(i, j);
	  this->grille[i][j]->setPion(new Piece(5, 1));
	  break;
	}
	}
      }
    }
  }

  this->dernierCoup = Position(0, 0);
  this->pep = false;
  this->fin = false;
  this->j1 = Joueur(names[0], 0, 1);
  this->j2 = Joueur(names[1], 0, 2);
}

Echequier::~Echequier()
{
  for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleV; j++) {
      delete(this->grille[i][j]);
    }
  }
}

CaseE* Echequier::getCase(Position p)
{
   if (this->estValide(p)) {
    return this->grille[p.getX()][p.getY()];
  }
}

bool Echequier::menaceeParRoi(Position p, int c) 
{
  if (c == 1) { 
    if (std::abs(p.getX() - roiNoir.getX()) <= 1 && std::abs(p.getY() - roiNoir.getY()) <= 1)
      return true;
  } else
    if (std::abs(p.getX() - roiBlanc.getX()) <= 1 && std::abs(p.getY() - roiBlanc.getY()) <= 1)
      return true;
  return false;
}

void Echequier::mangerPion(Position miam) 
{
  Joueur* j;
  if (this->getCase(miam)->getPion()->getCouleur() == 1)
    j = &j1;
  else
    j = &j2;
  if (this->getCase(miam)->getPion()->isRoi())
    this->fin = true;
  j->getLPions().push_back(this->getCase(miam)->getPion());
  this->getCase(miam)->setPion(0);
}

void Echequier::deplacerPion(Position depart, Position arrivee)
{
  if (this->getCase(arrivee)->hasPion())
    this->mangerPion(arrivee);
  this->getCase(depart)->getPion()->isMoved();
  this->getCase(arrivee)->setPion(this->getCase(depart)->getPion());
  this->getCase(depart)->setPion(0);
}

int Echequier::promouvoirPion() {
  int x;
  cout << "Votre petit Pion mérite une promotion!\n1 - Cavalier\n2 - Fou\n3 - Tour\n4 - Dame" << endl;
  while(true) {
    try {
      cin >> x;
      if (x < 1 || x > 4) throw 0;
      return x;
    } catch (int e) {
      if (e == 0) {
	cout << "Tu ne voudrais pas promouvoir ton Pion en balai à chiottes?!\n" 
	     << "1 - Cavalier\n2 - Fou\n3 - Tour\n4 - Dame" << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	continue;
      }
    }
  }
}

bool Echequier::priseEnPassant(Position p)
{
  int c = this->getCase(this->dernierCoup)->getPion()->getCouleur();
  if (c == 1) {
    if (p.createModPos(-1, 0) == dernierCoup && this->pep)
      return true;
  } else 
    if (p.createModPos(1, 0) == dernierCoup && this->pep)
      return true;
  return false;
} 

bool Echequier::estEnnemi(Position p, int c)
{
  if (this->estValide(p) &&
      this->getCase(p)->hasPion() &&
      this->getCase(p)->getPion()->getCouleur() != c)
    return true;
  return false;
}

Position Echequier::estClouee(Position p)
{
  Position roi, tmp;
  int i, pasI, maxI, j, pasJ, maxJ;
  int c;
  if (!this->getCase(p)->hasPion())
    return Position(-1, -1);
  c = this->getCase(p)->getPion()->getCouleur();
  if(c == 1)
    roi = this->roiBlanc;
  else
    roi = this->roiNoir;

  if (!(roi == p)) {
    // Ligne
    if (roi.getX() == p.getX()) {
      // On verifie l'alignement avec le roi
      maxI = roi.getY() - p.getY();
      pasI = maxI < 0 ? -1 : 1;
      i = pasI;
      tmp = p.createModPos(0, i);
      while (maxI != i) {
	if (this->getCase(tmp)->hasPion())
	  return Position(-1, -1);
	i += pasI;
	tmp = p.createModPos(0, i);
      }
      // On verifie l'alignement Roi - Piece - Ennemi qui peut prendre en ligne
      pasI =  p.getY() - roi.getY() < 0 ? -1 : 1;
      i = pasI;
      tmp = p.createModPos(0, i);
      while (this->estValide(tmp)) {
	if (this->getCase(tmp)->hasPion()) {
	  if (this->getCase(tmp)->getPion()->getCouleur() != c)
	    if (this->getCase(tmp)->getPion()->prendEnLigne())
	      return tmp;
	  return Position(-1, -1);
	}
	i += pasI;
	tmp = p.createModPos(0, i);
      }
    }

    // Colonne
    if (roi.getY() == p.getY()) {
      // On verifie l'alignement avec le roi
      maxI = roi.getX() - p.getX();
      pasI = maxI < 0 ? -1 : 1;
      i = pasI;
      tmp = p.createModPos(i, 0);
      while (maxI != i) {
	if (this->getCase(tmp)->hasPion())
	  return Position(-1, -1);
	i += pasI;
	tmp = p.createModPos(i, 0);
      }
      // On verifie l'alignement Roi - Piece - Ennemi qui peut prendre en ligne
      pasI =  p.getX() - roi.getX() < 0 ? -1 : 1;
      i = pasI;
      tmp = p.createModPos(i, 0);
      while (this->estValide(tmp)) {
	if (this->getCase(tmp)->hasPion()) {
	  if (this->getCase(tmp)->getPion()->getCouleur() != c)
	    if (this->getCase(tmp)->getPion()->prendEnLigne())
	      return tmp;
	  return Position(-1, -1);
	}
	i += pasI;
	tmp = p.createModPos(i, 0);
      }
    }
    
    // Diagonales
    if (std::abs(p.getX() - roi.getX()) == std::abs(p.getY() - roi.getY())) {
      // On verifie l'alignement avec le roi
      maxI = roi.getX() - p.getX();
      pasI = maxI < 0 ? -1 : 1;
      i = pasI;
      maxJ = roi.getY() - p.getY();
      pasJ = maxJ < 0 ? -1 : 1;
      j = pasJ;
      tmp = p.createModPos(i, j);
      while (maxI != i && maxJ != j) {
	if (this->getCase(tmp)->hasPion())
	  return Position(-1, -1);
	i += pasI;
	j += pasJ;
	tmp = p.createModPos(i, j);
      }
      // On verifie l'alignement Roi - Piece - Ennemi qui peut prendre en diagonale
      pasI =  p.getX() - roi.getX() < 0 ? -1 : 1;
      i = pasI;
      pasJ =  p.getY() - roi.getY() < 0 ? -1 : 1;
      j = pasJ;
      tmp = p.createModPos(i, j);
      while (this->estValide(tmp)) {
	if (this->getCase(tmp)->hasPion()) {
	  if (this->getCase(tmp)->getPion()->getCouleur() != c)
	    if (this->getCase(tmp)->getPion()->prendEnDiagonale())
	      return tmp;
	  return Position(-1, -1);
	}
	i += pasI;
	j += pasJ;
	tmp = p.createModPos(i, j);
      }
    }
  }

  return Position(-1, -1);
}

bool Echequier::deplacementClouee(Position depart, Position arrivee, Position cloueur)
{
  if (!this->estValide(cloueur))
    return true;
  if (depart.getX() == cloueur.getX() && arrivee.getX() == cloueur.getX())
    return true;
  if (depart.getY() == cloueur.getY() && arrivee.getY() == cloueur.getY())
    return true;
  if (std::abs(depart.getX() - cloueur.getX()) == std::abs(depart.getY() - cloueur.getY()) &&
      std::abs(arrivee.getX() - cloueur.getX()) == std::abs(arrivee.getY() - cloueur.getY()) &&
      std::abs(depart.getX() - arrivee.getX()) == std::abs(depart.getY() - arrivee.getY()))
    return true;
  return false;
}

bool Echequier::estEchec(Position p, int c)
{
  int i, j;
  Position tmp;
  // Pion
  // Blanc
  if (c != 1) {
    if (this->estEnnemi(p.createModPos(1, 1), c) &&
	this->getCase(p.createModPos(1, 1))->getPion()->isPion() ||
	this->estEnnemi(p.createModPos(1, -1), c) &&
	this->getCase(p.createModPos(1, -1))->getPion()->isPion())
      return true;

  // Noir
  } else {
    if (this->estEnnemi(p.createModPos(-1, 1), c) &&
	this->getCase(p.createModPos(-1, 1))->getPion()->isPion() ||
	this->estEnnemi(p.createModPos(-1, -1), c) &&
	this->getCase(p.createModPos(-1, -1))->getPion()->isPion())
      return true;
  }

  // Cavalier
  if (this->estEnnemi(p.createModPos(-2, 1), c) &&
      this->getCase(p.createModPos(-2, 1))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(-2, -1), c) &&
      this->getCase(p.createModPos(-2, -1))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(2, 1), c) &&
      this->getCase(p.createModPos(2, 1))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(2, -1), c) &&
      this->getCase(p.createModPos(2, -1))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(-1, 2), c) &&
      this->getCase(p.createModPos(-1, 2))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(1, 2), c) &&
      this->getCase(p.createModPos(1, 2))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(1, -2), c) &&
      this->getCase(p.createModPos(1, -2))->getPion()->isCavalier() ||
      this->estEnnemi(p.createModPos(-1, -2), c) &&
      this->getCase(p.createModPos(-1, -2))->getPion()->isCavalier())
    return true;

  // Diagonale
  i = 1;
  j = 1;
  while(true) {
    tmp = p.createModPos(i, j);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnDiagonale())
	  return true;
      break;
    }
    i++;
    j++;
  }

  i = 1;
  j = 1;
  while(true) {
    tmp = p.createModPos(-i, j);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnDiagonale())
	  return true;
      break;
    }
    i++;
    j++;
  }

  i = 1;
  j = 1;
  while(true) {
    tmp = p.createModPos(i, -j);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnDiagonale())
	  return true;
      break;
    }
    i++;
    j++;
  }

  i = 1;
  j = 1;
  while(true) {
    tmp = p.createModPos(-i, -j);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnDiagonale())
	  return true;
      break;
    }
    i++;
    j++;
  }

  // Ligne
  i = 1;
  while(true) {
    tmp = p.createModPos(i, 0);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnLigne())
	  return true;
      break;
    }
    i++;
  }

  i = 1;
  while(true) {
    tmp = p.createModPos(-i, 0);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnLigne())
	  return true;
      break;
    }
    i++;
  }

  i = 1;
  while(true) {
    tmp = p.createModPos(0, i);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnLigne())
	  return true;
      break;
    }
    i++;
  }

  i = 1;
  while(true) {
    tmp = p.createModPos(0, -i);
    if (!this->estValide(tmp))
      break;
    if (this->getCase(tmp)->hasPion()) {
      if (this->getCase(tmp)->getPion()->getCouleur() != c)
	if (this->getCase(tmp)->getPion()->prendEnLigne())
	  return true;
      break;
    }
    i++;
  }

  return false;
}

// Pion
bool Echequier::deplacePiecePion(Position depart, Position arrivee)
{
  // Blanc
  if (this->getCase(depart)->getPion()->getCouleur() == 1) {
    if (arrivee == depart.createModPos(-1, 0)) {
      if (!(this->getCase(arrivee)->hasPion())) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  // Promotion
	  if (arrivee.getX() == 0) {
	    this->mangerPion(depart);
	    this->getCase(arrivee)->setPion(new Piece(this->promouvoirPion(), 1));
	    this->pep = false;
	    return true;
	  }
	  this->deplacerPion(depart, arrivee);
	  this->pep = false;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      }
    // Double coup
    } else if (arrivee == depart.createModPos(-2, 0) &&
	       !(this->getCase(depart)->getPion()->wasMoved()) &&
	       !(this->getCase(depart.createModPos(-1, 0))->hasPion())) {
      if (!(this->getCase(arrivee)->hasPion())) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  this->pep = true;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      }
    } else if (arrivee == depart.createModPos(-1, 1) || arrivee == depart.createModPos(-1, -1)) {
      if (this->getCase(arrivee)->hasPion() &&
	  this->getCase(arrivee)->getPion()->getCouleur() != this->getCase(depart)->getPion()->getCouleur()) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  // Promotion
	  if (arrivee.getX() == 0) {
	    this->mangerPion(depart);
	    this->mangerPion(arrivee);
	    this->getCase(arrivee)->setPion(new Piece(this->promouvoirPion(), 1));
	    this->pep = false;
	    return true;
	  }
	
	  this->deplacerPion(depart, arrivee);
	  this->pep = false;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      // Prise en passant
      } else if (this->priseEnPassant(arrivee)) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  this->mangerPion(arrivee.createModPos(1, 0));
	  this->pep = false;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      }
    }
    
  // Noir
  } else {
    if (arrivee == depart.createModPos(1, 0)) {
      if (!(this->getCase(arrivee)->hasPion())) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  // Promotion
	  if (arrivee.getX() == 7) {
	    this->mangerPion(depart);
	    this->getCase(arrivee)->setPion(new Piece(this->promouvoirPion(), 2));
	    this->pep = false;
	    return true;
	  }
	  this->deplacerPion(depart, arrivee);
	  this->pep = false;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      }
    // Double coup
    } else if (arrivee == depart.createModPos(2, 0) &&
	       !(this->getCase(depart)->getPion()->wasMoved()) &&
	       !(this->getCase(depart.createModPos(1, 0))->hasPion())) {
      if (!(this->getCase(arrivee)->hasPion())) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  this->pep = true;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      }
    } else if (arrivee == depart.createModPos(1, 1) || arrivee == depart.createModPos(1, -1)) {
      if (this->getCase(arrivee)->hasPion() &&
	  this->getCase(arrivee)->getPion()->getCouleur() != this->getCase(depart)->getPion()->getCouleur()) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  // Promotion
	  if (arrivee.getX() == 7) {
	    this->mangerPion(depart);
	    this->mangerPion(arrivee);
	    this->getCase(arrivee)->setPion(new Piece(this->promouvoirPion(), 2));
	    this->pep = false;
	    return true;
	  }
	  this->deplacerPion(depart, arrivee);
	  this->pep = false;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      // Prise en passant
      } else if (this->priseEnPassant(arrivee)) {
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  this->mangerPion(arrivee.createModPos(-1, 0));
	  this->pep = false;
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
      }
    }
  }
  return false;
}

// Cavalier
bool Echequier::deplacePieceCavalier(Position depart, Position arrivee)
{
  if (arrivee == depart.createModPos(-2, 1) ||
      arrivee == depart.createModPos(-2, -1) ||
      arrivee == depart.createModPos(2, 1) ||
      arrivee == depart.createModPos(2, -1) ||
      arrivee == depart.createModPos(-1, 2) ||
      arrivee == depart.createModPos(1, 2) ||
      arrivee == depart.createModPos(1, -2) ||
      arrivee == depart.createModPos(-1, -2)) {
    if (!(this->getCase(arrivee)->hasPion() &&
	this->getCase(arrivee)->getPion()->getCouleur() == this->getCase(depart)->getPion()->getCouleur())) {
      if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	this->deplacerPion(depart, arrivee);
	return true;
      }
      cout << "Cette pièce est clouée" << endl;
    }
  }
  return false;
}

// Fou
bool Echequier::deplacePieceFou(Position depart, Position arrivee)
{
  int i, j, pasI, pasJ;
  Position p;
  
  if (std::abs(arrivee.getX() - depart.getX()) == std::abs(arrivee.getY() - depart.getY())) {
    i = arrivee.getX() - depart.getX() < 0 ? -1 : 1;
    j = arrivee.getY() - depart.getY() < 0 ? -1 : 1;
    pasI = i;
    pasJ = j;
    while (true) {
      
      p = depart.createModPos(i, j);
      if (!(p == arrivee) && this->getCase(p)->hasPion())
	return false;
      if (p == arrivee) {
	if (this->getCase(p)->hasPion() && 
	    this->getCase(p)->getPion()->getCouleur() == this->getCase(depart)->getPion()->getCouleur())
	  return false;
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
	return false;
      }
      i += pasI;
      j += pasJ;
    }
  }
  return false;
}

// Tour
bool Echequier::deplacePieceTour(Position depart, Position arrivee)
{
  int i, j, pasI, pasJ;
  Position p;
  
  if (arrivee.getX() == depart.getX() && arrivee.getY() != depart.getY() ||
      arrivee.getX() != depart.getX() && arrivee.getY() == depart.getY()) {
    i = arrivee.getX() - depart.getX() < 0 ? -1 : (arrivee.getX() - depart.getX() == 0? 0: 1);
    j = arrivee.getY() - depart.getY() < 0 ? -1 : (arrivee.getY() - depart.getY() == 0? 0: 1);
    pasI = i;
    pasJ = j;
    while (true) {
      
      p = depart.createModPos(i, j);
      if (!(p == arrivee) && this->getCase(p)->hasPion())
	return false;
      if (p == arrivee) {
	if (this->getCase(p)->hasPion() && 
	    this->getCase(p)->getPion()->getCouleur() == this->getCase(depart)->getPion()->getCouleur())
	  return false;
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
	return false;
      }
      i += pasI;
      j += pasJ;
    }
  }
  return false;
}

// Dame
bool Echequier::deplacePieceDame(Position depart, Position arrivee)
{
  int i, j, pasI, pasJ;
  Position p;
  
  if (arrivee.getX() == depart.getX() && arrivee.getY() != depart.getY() ||
      arrivee.getX() != depart.getX() && arrivee.getY() == depart.getY() ||
      std::abs(arrivee.getX() - depart.getX()) == std::abs(arrivee.getY() - depart.getY())) {
    i = arrivee.getX() - depart.getX() < 0 ? -1 : (arrivee.getX() - depart.getX() == 0? 0: 1);
    j = arrivee.getY() - depart.getY() < 0 ? -1 : (arrivee.getY() - depart.getY() == 0? 0: 1);
    pasI = i;
    pasJ = j;
    while (true) {
      
      p = depart.createModPos(i, j);
      if (!(p == arrivee) && this->getCase(p)->hasPion())
	return false;
      if (p == arrivee) {
	if (this->getCase(p)->hasPion() && 
	    this->getCase(p)->getPion()->getCouleur() == this->getCase(depart)->getPion()->getCouleur())
	  return false;
	if (this->deplacementClouee(depart, arrivee, this->estClouee(depart))) {
	  this->deplacerPion(depart, arrivee);
	  return true;
	}
	cout << "Cette pièce est clouée" << endl;
	return false;
      }
      i += pasI;
      j += pasJ;
    }
  }
  return false;
}

// Roi
bool Echequier::deplacePieceRoi(Position depart, Position arrivee)
{
  int c = this->getCase(depart)->getPion()->getCouleur();
  Position p;
  if (arrivee.getX() - depart.getX() >= -1 &&
      arrivee.getX() - depart.getX() <= 1 &&
      arrivee.getY() - depart.getY() >= -1 &&
      arrivee.getY() - depart.getY() <= 1) {
    if (this->estEnnemi(arrivee, c) || !this->getCase(arrivee)->hasPion()) {
      if (!this->menaceeParRoi(arrivee, c)) {
	if (!(this->estEchec(arrivee, c))) {
	  this->deplacerPion(depart, arrivee);
	  return true;
	}
	cout << "Vous ne voulez pas mourir tout de suite?!" << endl;
      } else 
	cout << "Le Roi adverse vous barre la route!" << endl;
    }

  // Roquer
  } else if (!this->getCase(depart)->getPion()->wasMoved()) {
    // Blanc
    if (depart.getX() == 7 && arrivee.getX() == 7) {
      if (arrivee.getY() - depart.getY() == 2) {
	p = Position(7, 7);
	if (this->getCase(p)->hasPion() &&
	    this->getCase(p)->getPion()->isTour() &&
	    !this->getCase(p)->getPion()->wasMoved()) {
	  if (!this->getCase(depart.createModPos(0, 1))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, 1), c) &&
	      !this->getCase(depart.createModPos(0, 2))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, 2), c)) {
	    this->deplacerPion(depart, arrivee);
	    this->deplacerPion(p, p.createModPos(0, -2));
	    return true;
	  }
	}
      } else if (arrivee.getY() - depart.getY() == -2) {
	p = Position(7, 0);
	if (this->getCase(p)->hasPion() &&
	    this->getCase(p)->getPion()->isTour() &&
	    !this->getCase(p)->getPion()->wasMoved()) {
	  if (!this->getCase(depart.createModPos(0, -1))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, -1), c) &&
	      !this->getCase(depart.createModPos(0, -2))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, -2), c) &&
	      !this->getCase(depart.createModPos(0, -3))->hasPion()) {
	    this->deplacerPion(depart, arrivee);
	    this->deplacerPion(p, p.createModPos(0, 3));
	    return true;
	  }
	}
      }

    // Noir
    } else if (depart.getX() == 0 && arrivee.getX() == 0) {
      if (arrivee.getY() - depart.getY() == 2) {
	p = Position(0, 7);
	if (this->getCase(p)->hasPion() &&
	    this->getCase(p)->getPion()->isTour() &&
	    !this->getCase(p)->getPion()->wasMoved()) {
	  if (!this->getCase(depart.createModPos(0, 1))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, 1), c) &&
	      !this->getCase(depart.createModPos(0, 2))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, 2), c)) {
	    this->deplacerPion(depart, arrivee);
	    this->deplacerPion(p, p.createModPos(0, -2));
	    return true;
	  }
	}
      } else if (arrivee.getY() - depart.getY() == -2) {
	p = Position(0, 0);
	if (this->getCase(p)->hasPion() &&
	    this->getCase(p)->getPion()->isTour() &&
	    !this->getCase(p)->getPion()->wasMoved()) {
	  if (!this->getCase(depart.createModPos(0, -1))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, -1), c) &&
	      !this->getCase(depart.createModPos(0, -2))->hasPion() &&
	      !this->estEchec(depart.createModPos(0, -2), c) &&
	      !this->getCase(depart.createModPos(0, -3))->hasPion()) {
	    this->deplacerPion(depart, arrivee);
	    this->deplacerPion(p, p.createModPos(0, 3));
	    return true;
	  }
	}
      }
    }	    	
  }

  return false;
}
	
bool Echequier::deplacePiece(Position depart, Position arrivee)
{
  bool ret;
  if (this->getCase(depart)->hasPion()) {
    switch (this->getCase(depart)->getPion()->getType()) {
    // Pion
    case 0 : {
      ret = this->deplacePiecePion(depart, arrivee);
      break;
    }

    // Cavalier
    case 1 : {
      ret = this->deplacePieceCavalier(depart, arrivee);
      if (ret)
	this->pep = false;
      break;
    }

    // Fou
    case 2 : {
      ret = this->deplacePieceFou(depart, arrivee);
      if (ret)
	this->pep = false;
      break;
    }

    // Tour
    case 3 : {
      ret = this->deplacePieceTour(depart, arrivee);
      if (ret)
	this->pep = false;
      break;
    }

    // Dame
    case 4 : {
      ret = this->deplacePieceDame(depart, arrivee);
      if (ret)
	this->pep = false;
      break;
    }

    // Roi
    case 5 : {
      ret = this->deplacePieceRoi(depart, arrivee);
      if (ret) {
	this->pep = false;
	if (this->getCase(arrivee)->getPion()->getCouleur() == 1)
	  roiBlanc = arrivee;
	else
	  roiNoir = arrivee;
      }
      break;
    }

    default :
      cout << "Type de pièce inconnu" << endl;
      ret = false;
    }
    
    if (ret)
      this->dernierCoup = arrivee;
    return ret;
  }
}

bool Echequier::checkCaseJouable(Position p)
{
  return true;
}

void Echequier::jouerPion(Position p, Joueur *j) 
{
  
}

void Echequier::winner(int joueur)
{
  if (!joueur) {
    cout << "Bravo " << j1.getNomCouleur() << "! Tu as gagné!" << endl;
  } else {
    cout << "Bravo " << j2.getNomCouleur() << "! Tu as gagné!" << endl;
  }
}

void Echequier::abandon(int joueur)
{
  if (!joueur) {
    cout << j1.getNomCouleur() << " a abandonné" << endl;
    this->winner(1);
  } else {
    cout << j2.getNomCouleur() << " a abandonné" << endl;
    this->winner(2);
  }
}

int Echequier::game(int joueur) {
  int ok = 0;
  int x, y, v, w;
  Joueur *j;

  //A qui le tour !
  if (!joueur) j = &j1;
  else j = &j2;
  
  if (joueur == 1 || joueur == 0) {
    //this->checkCaseJouable()
    
    this->afficher();
    cout << j->getNomCouleur() << " à toi de jouer (Joueur " << joueur+1 << ")! :" << endl; 
    cout << "Pour abandonner, jouer le roi sur place" << endl;
    while(true) {
      try {
	cout << "Pièce à bouger?\n"
	     << "Choix case (Valeurs : 1 - 8) (Format -> X Y)" << endl;
	cin >> x >> y;
	cout << "Destination?\n"
	     << "Choix case (Valeurs : 1 - 8) (Format -> X Y)" << endl;
	cin >> v >> w;
	if (x < 1 || x > 8 || y < 1 || y > 8 || v < 1 || v > 8 || w < 1 || w > 8) throw 0;
	if (!(this->getCase(Position(x-1, y-1))->hasPion())) throw 4;
	if (this->getCase(Position(x-1, y-1))->getPion()->getCouleur() != j->getCouleur()) throw 3;
	if (v == x && y == w)
	  if (this->getCase(Position(x-1, y-1))->getPion()->isRoi() && 
	      this->getCase(Position(x-1, y-1))->getPion()->getCouleur() == j->getCouleur()) {
	    this->fin = true;
	    return 1;
	  } else throw 2;
	if (!deplacePiece(Position(x-1, y-1), Position(v-1, w-1))) throw 1;
	break;
      } catch (int e) {
	if (e == 0) {
	  cout << "Erreur : N'essaye pas de jouer en dehors du plateau petit coquin!\n" << endl;
	  cin.clear();
	  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  continue;
	} else if (e == 1) {
	  cout << "Erreur : Tu ne peux pas jouer la!\n" << endl;
	  continue;
	} else if (e == 2) {
	  cout << "Erreur : Essairai tu de me prendre pour un jambon?!\n" << endl;
	  continue;
	} else if (e == 3) {
	  cout << "Erreur : Cette pièce ne t'appartient pas!\n" << endl;
	  continue;
	} else if (e == 4) {
	  cout << "Erreur : Ceci est une case vide ...\n" << endl;
	  cout << x << y << " " << this->getCase(Position(x-1, y-1))->hasPion()  << " " << this->getCase(Position(x-1, y-1))->afficher() << endl;
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

int Echequier::run() {
  int end;
  cout << "Bienvenue! Pret pour une partie d'échecs " << this->j1.getNomCouleur() 
       << " et " << this->j2.getNomCouleur() << "?" << endl;
  cout << this->afficher();
  while (1) {
    end = 0;
    if (this->estEchec(this->roiBlanc, 1)) {
      cout << "Echec!" << endl;
    }
    if (game(0) == 1) {
      this->abandon(0);
      break;
    }
    if (this->fin) {
      this->winner(0);
      break;
    }
    
    if (this->estEchec(this->roiNoir, 2)) {
      cout << "Echec!" << endl;
    }
    if (game(1) == 1) {
      this->abandon(1);
      break;
    }
    if (this->fin) {
      this->winner(1);
      break;
    }
    
  }
  return this->endGame();
}

string Echequier::afficher()
{
  string s = "";
  s += "X\\Y  1   2   3   4   5   6   7   8\n";
  for (int i(0); i < this->tailleH; i++) {
    s += "------------------------------------\n ";
    s += intToString(i+1);
    s += " |";
    for (int j(0); j < this->tailleV; j++) {
      s += this->getCase(Position(i, j))->afficher() + "|";
    }
    s += "\n";
  }
  s += "------------------------------------\n";
  return s;
}

int Echequier::endGame()
{
  cout << "Belle partie! A la prochaine!" << endl;
  return 0;
}
