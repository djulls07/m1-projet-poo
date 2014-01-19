#ifndef PLATEAU_H
#include "../include/Case.h"
#include "../include/Joueur.h"
#include <vector>
#include <string>
#define PLATEAU_H


class Plateau
{
 public:

  Plateau();
  Plateau(unsigned int h, unsigned int v);
  virtual ~Plateau();

  virtual unsigned int getTailleH();
  virtual unsigned int getTailleV();
  virtual Case *getCase(Position p);
  virtual bool estValide(Position p);
  virtual void deplacerPion(Position depart, Position arrive);
  virtual std::string afficher() = 0;
  
  virtual int endGame() = 0; //abs
  virtual int game(int n) = 0; //abs
  virtual bool checkCaseJouable(Position p) = 0;
  virtual void jouerPion(Position p, Joueur *j) = 0;
  virtual int run () = 0;
  
 protected:
  
  unsigned int tailleH;
  unsigned int tailleV;
  std::vector<std::vector <Case*> > grille;
  Joueur j1;
  Joueur j2;
  
 private:

};

#endif // PLATEAU_H
