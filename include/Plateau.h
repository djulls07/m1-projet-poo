#ifndef PLATEAU_H
#include "../include/Case.h"
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
  virtual void echangeCase(Position a, Position b);

 protected:
  
  unsigned int tailleH;
  unsigned int tailleV;
  std::vector<std::vector <Case*> > grille;
  
 private:

};

#endif // PLATEAU_H
