#include "../include/Joueur.h"


Joueur::Joueur()
{
    //ctor
}
Joueur::Joueur(std::string nom, int nbPions, int couleur)
{
    //ctor
    this->nom = nom;
    this->lPions = std::vector<Pion>(nbPions, Pion(couleur));
    this->couleur = couleur;
}

Joueur::~Joueur()
{
    //dtor
}
