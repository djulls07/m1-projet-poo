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
  Joueur(std::string name, int nbPions, int couleur);
  virtual ~Joueur();
 protected:
  std::vector<Pion> lPions;
  std::string nom;
  int couleur;
 private:
};

#endif // JOUEUR_H
