#ifndef JOUEUR_H
#include <vector>
#include "Pion.h"
#include <iostream>
#include <string>
#define JOUEUR_H


class Joueur
{
 public:
  Joueur();
  Joueur(std::string nom, int nbPions, int couleur);
  virtual ~Joueur();
 protected:
  std::vector<Pion> lPions;
  std::string nom;
 private:
};

#endif // JOUEUR_H
