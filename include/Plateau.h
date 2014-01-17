#ifndef PLATEAU_H
#include "../include/Case.h"
#include "../include/Joueur.h"
#include <vector>
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
  virtual void afficher(); //pour debug
  
  virtual int endGame() = 0;
  virtual void game(int n) = 0;

 protected:
  
  unsigned int tailleH;
  unsigned int tailleV;
  std::vector<std::vector <Case*> > grille;
  Joueur j1;
  Joueur j2;
  
 private:

};

#endif // PLATEAU_H
