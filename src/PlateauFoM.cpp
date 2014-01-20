#include "../include/PlateauFoM.h"

using namespace std;

PlateauFoM::PlateauFoM(string name, int t, bool var, int nbC) : Plateau()
{
  //ctor
  this->grille = vector <vector <CaseFoM*> >(t, vector<CaseFoM*>(t));
  this->tailleH = t;
  this->tailleV = t;
  if (nbC < 0) this->nbCouleurs = 2;
  else this->nbCouleurs = nbC;
  if (var !=1 ) this->variante = 0;
  else this->variante = 1;
  for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleH; j++) {
      this->grille[i][j] = new CaseFoM(i,j);
    }
  }
  this->j1 = Joueur(name, 0, 1);
  this->points = 0;
  srand(time(NULL));
  this->vp = vector<Position>();
}


PlateauFoM::~PlateauFoM()
{
  //dtor
  for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleH; j++)
      delete(this->grille[i][j]);
  }
}

int PlateauFoM::endGame()
{
  //alignement et attribution points
  if (verifAlign()) return 2; //si 1 alignement alors le jeu n'est pas fini.

  //plateau plein ou pas
  for (int i(0); i<this->tailleH; i++) {
    for (int j(0); j<this->tailleH; j++) {
      if (!this->getCase(Position(i,j))->hasPion()) {
	return 1;
      }
    }    
  }
  return 0;
}

int PlateauFoM::run()
{
  int e;
  while(1) {
    game(0);
    cout << afficher();
    if((e=endGame()) == 0) return this->points;
    cout << e << endl;
    if (e == 2) cout << afficher();
    game(0);
    if((e=endGame()) == 0) return this->points;
    if (e == 2) cout << afficher();
    game(0);
    if((e=endGame()) == 0) return this->points;
    cout << afficher();
    game(1);
    cout << afficher();
    if ((e=endGame()) == 0) return this->points;
    this->afficher();
  }
}

//0 ordi
//1 joueur
int PlateauFoM::game(int n)
{
  int x;
  int y;

  switch(n) {
  
  case 0:
    //ordi
    posePionRandom();
      break;
  case 1:
    jouerPion(getChoixPos("Choix X(abs) case a jouer", 
			  "Choix Y(ord) case a jouer").createModPos(-1, -1),
	      &this->j1);
    break;
  default:
    break;
    
  }
  return 0;
}

void PlateauFoM::jouerPion(Position p, Joueur *j)
{
  if (this->variante)
    jouerPionC(p, getChoixColor());
  else 
    jouerPionD(p, getChoixPos("Choix destination X(abs)", 
			      "Choix destination Y(ord)").createModPos(-1,-1));
}

void PlateauFoM::jouerPionC(Position p, int color)
{
  //TODO:
  if (this->getCase(p)->hasPion()) {
    this->getCase(p)->getPion()->setCouleur(color);
  } else {
    cout << "Choisissez une case avec un pion a Color-Switch"<<endl;
    jouerPionC(getChoixPos("Choix destination X(abs)", 
			   "Choix destination Y(ord)").createModPos(-1,-1),
	       color);
  }
}

void PlateauFoM::jouerPionD(Position p1, Position p2)
{
  //TODO:
  if (this->getCase(p1)->hasPion() && !this->getCase(p2)->hasPion()) {
    if (calculChemin(p1, p2)) {
      this->getCase(p2)->
	setPion(new PionFoM(this->getCase(p1)->getPion()->getCouleur()));
      this->getCase(p1)->setPion(0);
    }  
  } else {
    cout<<"Vous devez jouer une case contenant un pion vers une case vide"<<endl;
    p1 = getChoixPos("Choix case source X(abs)",
		     "Choix Case source Y(ord)").createModPos(-1,-1);
    p2 = getChoixPos("Choix destination X(abs)", 
		     "Choix destination Y(ord)").createModPos(-1,-1);
    jouerPionD(p1,p2);
  }
}

Position PlateauFoM::getChoixPos(string s1, string s2)
{
  int x, y;
  
  cout << s1 <<endl;
  x = lireEntier(1, tailleH);
  cout << s2 << endl;
  y = lireEntier(1, tailleH);
  return Position (x, y);
}

int PlateauFoM::getChoixColor()
{
  cout << "Choix Couleur ? ( [1, " << this->nbCouleurs << "]" << endl;
  return lireEntier(1, this->nbCouleurs);
}

void PlateauFoM::posePionRandom()
{
  vector<Position> v;
  int monRand;
  for (int i(0); i<tailleH; i++) {
    for (int j(0); j<tailleH; j++) {
      if (!(this->getCase(Position(i,j))->hasPion()))
	v.push_back(Position(i, j));
    }
  }
  monRand = rand() % v.size();
  if (!posePion(v[monRand], randCouleur())) {
    cout << "Error poser pion" << endl;
  }
}

/* return vrai si possible de poser pion ( case vide et valide )*/
bool PlateauFoM::posePion(Position p, int couleur)
{
  if (this->checkCaseJouable(p)) {
    this->getCase(p)->setPion(new PionFoM(couleur));
    return true;
  }
  return false;
}
int PlateauFoM::randCouleur()
{
  return ((rand() % this->nbCouleurs)+1);
}

bool PlateauFoM::checkCaseJouable(Position p) //valide et sans pion
{
  if (this->estValide(p))
    if (!this->getCase(p)->hasPion()) return true;
  return false;
}

string PlateauFoM::afficher()
{ 
  string s = "";
  s += "X\\Y ";
  for (int i(0); i < tailleH; i++) {
    if (i<9)
      s += intToString(i+1) + "   ";
    else 
      s+=intToString(i+1) + "  ";
  }
  s+= "\n";
  for (int i(0); i < this->tailleV; i++) {
    for (int k(0);k<tailleV/2; k++)
      s += "----------";
    s += "\n";
    s += intToString(i+1);
    s += " | ";
    for (int j(0); j < this->tailleH; j++) {
      s += this->getCase(Position(j, i))->afficher() + " | ";
    }
    s += "\n";
  }
  for (int k(0);k<tailleV/2; k++)
    s += "----------";
  s += "\n Score = ";
  s += intToString(this->points) + " \n";
  return s;
}

bool PlateauFoM::verifAlign()
{
  for (int i(0); i< tailleH; i++) {
    verifAlignLC(i, true);
    verifAlignLC(i, false);
  }
  cout << "size:" <<vp.size();
  //verifAlignD();
  
  retraitAlign(); //retire les pions et add les points et vide this->vp
}

void PlateauFoM::verifAlignLC(int n, bool b)
{
  int count = 0;
  int couleur = 0;
  CaseFoM *c = 0;
  if (b) {
    //check LIGNES
    for (int i(0); i<tailleH; i++) {
      c = this->getCase(Position(i, n));
      if (c->hasPion()) {
	if (couleur == c->getPion()->getCouleur()) {
	  count++;
	} else {
	  if (count >= 5) {
	    for (int j(1); j<=count; j++) {
	      vp.push_back(Position(i-j, n));
	    }
	  }
	  count = 1;
	  couleur = c->getPion()->getCouleur();
	}
      } else {
	if (count >= 5) {
	  for (int j(1); j<=count; j++) {
	    vp.push_back(Position(i-j, n));
	  }
	}
	count = 0;
	couleur = 0;
      }
    }
  } else {
    //col
    for (int i(0); i<tailleH; i++) {
      c = this->getCase(Position(n, i));
      if (c->hasPion()) {
	if (couleur == c->getPion()->getCouleur()) {
	  count++;
	} else {
	  if (count >= 5) {
	    for (int j(1); j<=count; j++) {
	      vp.push_back(Position(n, i-j));
	    }
	    vp.push_back(Position(-1,-1));
	  }
	  count = 1;
	  couleur = c->getPion()->getCouleur();
	}
      } else {
	if (count >= 5) {
	  for (int j(1); j<=count; j++) {
	    vp.push_back(Position(n, i-j));
	  }
	  vp.push_back(Position(-1,-1));
	}
	count = 0;
	couleur = 0;
      }
    }
  }
}

void PlateauFoM::verifAlignD()
{
  for (int i(4); i<tailleH; i++)
    verifAlignDG(Position(i, 0));
  for (int i(0); i<=tailleH-5; i++)
    verifAlignDG(Position(0, i));
  for (int i(tailleH-5); i>=0; i--)
    verifAlignDD(Position(0, i));
  for (int i(0); i<tailleH-5; i++)
    verifAlignDD(Position(i, 0));
}

      
void PlateauFoM::verifAlignDG(Position p)
{
  int x = p.getX();
  int y = p.getY();
  int x1, y1;
  int color = 0;
  int count = 0;
  CaseFoM *c;
  int couleur = 0;

  while((c=this->getCase(Position(x--, y++))) != 0) {
    if (!c->hasPion()) {
      cout <<"Nohaspion";
      if (count >= 5) {
	x1 = c->getPosition().getX()+1; 
	y1 = c->getPosition().getY()-1;
	for (int i(0); i<count; i++) {
	  vp.push_back(Position(x1++,y1--));
	}
	vp.push_back(Position(-1,-1));
	count = 0;
      }
    } else {
      cout << "HASPION";
      if (couleur == c->getPion()->getCouleur()) {
	count++;
      } else {
	count = 1;
	couleur = c->getPion()->getCouleur();
      }
    }
  }
  if (count >= 5) {
    x1 = c->getPosition().getX()+1;
    y1 = c->getPosition().getY()-1;
    for (int i(0); i<count; i++) {
      vp.push_back(Position(x1++,y1--));
    }
    vp.push_back(Position(-1,-1));
  }
}

void PlateauFoM::verifAlignDD(Position p)
{
  int x = p.getX();
  int y = p.getY();
  int x1, y1;
  int color = 0;
  int count = 0;
  CaseFoM *c;
  int couleur = 0;

  while((c=this->getCase(Position(x++, y++))) != 0) {
    if (!c->hasPion()) {
      if (count >= 5) {
	x1 = c->getPosition().getX()-1;
	y1 = c->getPosition().getY()-1;
	for (int i(0); i<count; i++) {
	  vp.push_back(Position(x1--,y1--));
	}
	vp.push_back(Position(-1,-1));
	count = 0;
      }
    } else {
      if (couleur == c->getPion()->getCouleur()) {
	count++;
      } else {
	count = 1;
	couleur = c->getPion()->getCouleur();
      }
    }
  }
  if (count >= 5) {
    x1 = c->getPosition().getX()-1;
    y1 = c->getPosition().getY()-1;
    for (int i(0); i<count; i++) {
      vp.push_back(Position(x1--,y1--));
    }
    vp.push_back(Position(-1,-1));
  }
}

bool PlateauFoM::calculChemin(Position p1, Position p2)
{
  return true;
}

void PlateauFoM::retraitAlign()
{
  int a = 0;
  int i = 1;
  while(!vp.empty()) {
    if (vp.back().getX() < 0) {
      //fin d'un alignement
      this->getCase(vp.back())->setPion((PionFoM*)0);
      vp.pop_back();
      this->points += ((a*a)*(i++));
      a = 0;
    } else {
      a++;
      this->getCase(vp.back())->setPion(0);
      vp.pop_back();
    }
  }
}

CaseFoM *PlateauFoM::getCase(Position p)
{
  return this->grille[p.getX()][p.getY()];
}
