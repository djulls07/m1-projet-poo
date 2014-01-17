#include "../include/Joueur.h"


Joueur::Joueur()
{
    //ctor
}
Joueur::Joueur(std::string nom, int nbPions, int couleur)
{
    //ctor
    this->nom = nom;
    for(int i(0); i<nbPions; i++)
        this->lPions.push_back(Pion(couleur));
}

Joueur::~Joueur()
{
    //dtor
}
