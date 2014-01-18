#include "../include/Joueur.h"

Joueur::Joueur()
{
    //ctor
}
Joueur::Joueur(std::string name, int nbPions, int couleur)
{
    //ctor
  this->nom = name;
  this->lPions = std::vector<Pion*>(nbPions, new Pion(couleur));
  this->couleur = couleur;
}

Joueur::~Joueur()
{
  //dtor
  for (int i(0); i<this->lPions.size(); i++) this->lPions.pop_back();
}

std::string Joueur::getNom()
{
  return this->nom;
}

std::vector<Pion*> Joueur::getLPions()
{
  return this->lPions;
}

int Joueur::getCouleur()
{ 
  return this->couleur;
}
