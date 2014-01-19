#include "../include/Joueur.h"

Joueur::Joueur()
{
    //ctor
}
Joueur::Joueur(std::string name, int nbPions, int couleur)
{
    //ctor
  this->nom = name;
  this->lPions = std::vector<Pion*>();
  for (int i(0); i<nbPions; i++) {
    this->lPions.push_back(new Pion(couleur));
  }
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

std::string Joueur::getNomCouleur()
{
  std::string s;
  if (this->couleur == 1)
    s = "\033[31m"+this->nom+"\033[0m";
  else 
    s = "\033[33m"+this->nom+"\033[0m";
  return s;
}
