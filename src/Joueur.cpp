#include "../include/Joueur.h"

Joueur::Joueur()
{
    //ctor
}
Joueur::Joueur(std::string name, int nbPions, int couleur)
{
    //ctor
  this->nom = name;
  this->lPions = std::vector<Pion>(nbPions, Pion(couleur));
  this->couleur = couleur;
}

Joueur::~Joueur()
{
    //dtor
}
