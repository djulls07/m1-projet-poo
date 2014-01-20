#include <limits>
// Constructeur
// estMat
// game
// estPat
// run
// Interface
// JoueurE
// CaseE
// Piece (renommer fichier)
// afficher
// var : Position dernierCoup
// var : bool pep
// var : Position roiBlanc
// var : Position roiNoir

bool Echequier::menaceeParRoi(Poisiton p, int c) 
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
  if (this->getCase(arrivee)->getPion()->getCouleur() == 1)
    j = &j1;
  else
    j = &j2;
  this->j->getLPions().push_back(this->getCase(arrivee)->getPion());
  this->getCase(arrivee)->setPion(0);
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
    if (p.createModPos(1, 0) == dernierCoup && this->pep)
      return true;
  } else 
    if (p.createModPos(-1, 0) == dernierCoup && this->pep)
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
	// Promotion
	if (arrivee.getX() == 0) {
	  this->mangerPion(depart);
	  this->getCase(arrivee)->setPion(new PionE(this->promouvoirPion(), 1));
	  this->pep = false;
	  return true;
	}
	this->deplacerPion(depart, arrivee);
	this->pep = false;
	return true;
      }
    // Double coup
    } else if (arrivee == depart.createModPos(-2, 0) &&
	       !(this->getCase(depart)->getPion()->wasMoved()) &&
	       !(this->getCase(depart.createModPos(-1, 0))->hasPion())) {
      if (!(this->getCase(arrivee)->hasPion())) {
	this->deplacerPion(depart, arrivee);
	this->pep = true;
	return true;
      }
    } else if (arrivee == depart.createModPos(-1, 1) || arrivee == depart.createModPos(-1, -1)) {
      if (this->getCase(arrivee)->hasPion() &&
	  this->getCase(arrivee)->getPion()->getCouleur() != this->getCase(depart)->getPion()->getCouleur()) {
	// Promotion
	if (arrivee.getX() == 0) {
	  this->mangerPion(depart);
	  this->mangerPion(arrivee);
	  this->getCase(arrivee)->setPion(new PionE(this->promouvoirPion(), 1));
	  this->pep = false;
	  return true;
	}
	this->deplacerPion(depart, arrivee);
	this->pep = false;
	return true;
      // Prise en passant
      } else if (this->priseEnPassant(arrivee)) {
	this->deplacerPion(depart, arrivee);
	this->mangerPion(arrivee.createModPos(1, 0));
	this->pep = false;
	return true;
      }
    }
    
  // Noir
  } else {
    if (arrivee == depart.createModPos(1, 0)) {
      if (!(this->getCase(arrivee)->hasPion())) {
	// Promotion
	if (arrivee.getX() == 7) {
	  this->mangerPion(depart);
	  this->getCase(arrivee)->setPion(new PionE(this->promouvoirPion(), 2));
	  this->pep = false;
	  return true;
	}
	this->deplacerPion(depart, arrivee);
	this->pep = false;
	return true;
      }
    // Double coup
    } else if (arrivee == depart.createModPos(2, 0) &&
	       !(this->getCase(depart)->getPion()->wasMoved()) &&
	       !(this->getCase(depart.createModPos(1, 0))->hasPion())) {
      if (!(this->getCase(arrivee)->hasPion())) {
	this->deplacerPion(depart, arrivee);
	this->pep = true;
	return true;
      }
    } else if (arrivee == depart.createModPos(1, 1) || arrivee == depart.createModPos(1, -1)) {
      if (this->getCase(arrivee)->hasPion() &&
	  this->getCase(arrivee)->getPion()->getCouleur() != this->getCase(depart)->getPion()->getCouleur()) {
	// Promotion
	if (arrivee.getX() == 7) {
	  this->mangerPion(depart);
	  this->mangerPion(arrivee);
	  this->getCase(arrivee)->setPion(new PionE(this->promouvoirPion(), 2));
	  this->pep = false;
	  return true;
	}
	this->deplacerPion(depart, arrivee);
	this->pep = false;
	return true;
      // Prise en passant
      } else if (this->priseEnPassant(arrivee)) {
	this->deplacerPion(depart, arrivee);
	this->mangerPion(arrivee.createModPos(-1, 0));
	this->pep = false;
	return true;
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
      this->deplacerPion(depart, arrivee);
      return true;
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
	this->deplacerPion(depart, arrivee);
	return true;
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
	this->deplacerPion(depart, arrivee);
	return true;
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
	this->deplacerPion(depart, arrivee);
	return true;
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
  Postion p;
  if (arrivee.getX() - depart.getX() >= -1 &&
      arrivee.getX() - depart.getX() <= 1 &&
      arrivee.getY() - depart.getY() >= -1 &&
      arrivee.getY() - depart.getY() <= 1) {
    if (this->estEnnemi(arrivee, c)) {
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
      this->dernierCoup(arrivee);
    return ret;
  }
}

int Echequier::game(int joueur) {
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
	 << "Pièce à bouger?\n"
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
