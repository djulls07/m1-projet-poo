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
    if((e=endGame()) == 0) return this->points;
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
    verifAlign(p);
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
    if (true){//calculChemin(p1, p2)) {
      this->getCase(p2)->
	setPion(new PionFoM(this->getCase(p1)->getPion()->getCouleur()));
      this->getCase(p1)->setPion(0);
      verifAlign(p2);
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

bool PlateauFoM::verifAlign(Position p)
{  
  CaseFoM *depart = this->getCase(p);
  int v1 = count(p,0,1);
  int v2 = count(p, 0, -1);
  int h1 = count(p,1,0);
  int h2 = count(p, -1,0);
  int d11 = count(p,-1,-1);
  int d12 = count(p,1,1);
  int d21 = count(p,1,-1);
  int d22 = count (p,-1,1);
  int nb = 0;
  
  if ((v1+v2+1) >= 5) {
    retraitAlign(p.createModPos(0,-v1),
		 p.createModPos(0,v2));
    points += v1+v2+1;
    nb++;
  }
  if ((h1+h2+1) >= 5) {
    retraitAlign(p.createModPos(-h2, 0),
      p.createModPos(h1, 0));
    points += h2+h1+1;
    nb++;
  }
  if ((d11+d12+1) >= 5) {
    retraitAlign(p.createModPos(-d11, -d11),
		 p.createModPos(d12, d12));
    points += d11+d12+1;
    nb++;
  }
  if ((d22+d21+1) >= 5) {
    retraitAlign(p.createModPos(d21, -d21),
		 p.createModPos(d22, d22));
    points += d21+d22+1;
    nb++;
  }

  this->points = this->points*nb;
}



int PlateauFoM::count(Position p, int x, int y)
{
  
  CaseFoM *c;
  Position dp;
  int i = 1;
  int count = 0;
  CaseFoM *depart = this->getCase(p);
  int couleur = depart->getPion()->getCouleur();
  
  while((c=this->getCase(p.createModPos(x*i, y*i))) != 0) {
    if (c->hasPion()) {
      if (couleur == c->getPion()->getCouleur()) {
	count++;
      }
    } else {
      break;
    }
    i++;
  }
  return count;
}

bool PlateauFoM::calculChemin(Position p1, Position p2)
{
  Position direction = Position(p2.getX() - p1.getX(), p2.getY() - p1.getY());
  return this->subCalculChemin(p1, 5, direction);
}

int PlateauFoM::subCalcul(Position p, Position direction) {
  int ret = 0;
  if (std::abs(direction.getY()) < std::abs(direction.getX())) {
    if (direction.getY() < 0) {
      ret += 301;
      if (direction.getX() > 0) {
        ret += 4020;
      } else
        ret += 2040;
    } else {
      ret += 103;
      if (direction.getX() > 0) {
        ret += 4020;
      } else
        ret += 2040;
    }
  } else {
    if (direction.getX() > 0) {
      ret += 402;
      if (direction.getY() < 0) {
        ret += 3010;
      } else
        ret += 1030;
    } else {
      ret += 204;
      if (direction.getY() < 0) {
        ret += 3010;
      } else
        ret += 1030;
    }
  }
  return ret;
}
 
	

bool PlateauFoM::subCalculChemin(Position ici, int entree, Position direction)
{
  int ordre;
  int cond = 0;
  Position tmp;
  if (!this->estValide(ici))
    return false;
  if (direction == Position(0, 0))
    return true;
  ordre = subCalcul(ici, direction);
  while (ordre) {
    // Nord
    if (ordre%10 == 1 && entree != 0) {
      tmp = ici.createModPos(0, -1);
      if (this->estValide(tmp) && !this->getCase(tmp)->hasPion())
	if (this->subCalculChemin(tmp, 2, direction.createModPos(0, 1)))
	  return true;
      // Est
    } else if (ordre%10 == 2 && entree != 1) {
      tmp = ici.createModPos(1, 0);
      if (this->estValide(tmp) && !this->getCase(tmp)->hasPion())
	if (this->subCalculChemin(tmp, 3, direction.createModPos(-1, 0)))
	  return true;
      // Sud
    } else if (ordre%10 == 3 && entree != 2) {
      tmp = ici.createModPos(0, 1);
      if (this->estValide(tmp) && !this->getCase(tmp)->hasPion())
	if (this->subCalculChemin(tmp, 0, direction.createModPos(0, -1)))
	  return true;
      // Ouest
    } else if (ordre%10 == 4 && entree != 3) {
      tmp = ici.createModPos(-1, 0);
      if (this->estValide(tmp) && this->getCase(tmp)->hasPion())
	if (this->subCalculChemin(tmp, 1, direction.createModPos(1, 0)))
	  return true;
    }
    ordre = ordre/10;
  }
  return false;
}



void PlateauFoM::retraitAlign(Position pos1, Position pos2)
{
  int a = 0;
  int i = 1;
  Position p1;
  Position p2;
  if (pos1.getX() <= pos2.getX()) {
    Position p1(pos1);
    Position p2(pos2);
  } else {
    Position p1(pos2);
    Position p2(pos1);
  }
  
  if (p1.getX() == p2.getX()) {
    //col
    if(p1.getY() < p2.getY()) {
      for (int i(p1.getY()); i<=p1.getY()-p2.getY(); i++)
	this->getCase(Position(p1.getX(), i))->setPion(0);
    }else {
      for (int i(p2.getY()); i<=p2.getY()-p1.getY(); i++)
	this->getCase(Position(p1.getX(), i))->setPion(0);
    }
  } else if (p1.getY() == p2.getY()) {
    //lig
    if(p1.getX() < p2.getX()) {
      for (int i(p1.getX()); i<=p1.getX()-p2.getX(); i++)
	this->getCase(Position(p1.getY(), i))->setPion(0);
    }else {
      for (int i(p2.getX()); i<=p2.getX()-p1.getX(); i++)
	this->getCase(Position(p1.getY(), i))->setPion(0);
    }
  } else {
    if (p1.getY() > p2.getY()) {
      //diag /
      for (int i(0); i<p2.getX()-p1.getX(); i++)
	this->getCase(Position(p1.getX()+i, p1.getX()-i))->setPion(0);
    } else {
      //diag \
      for (int i(0); i<p2.getX()-p1.getX(); i++)
	this->getCase(Position(p1.getX()-i, p1.getX()+i))->setPion(0);
    }
  }
}

CaseFoM *PlateauFoM::getCase(Position p)
{
  if (p.getX()>=0 && p.getX()<tailleH && p.getY()>=0 && p.getY()<tailleH)
    return this->grille[p.getX()][p.getY()];
  else 
    return 0;
}
