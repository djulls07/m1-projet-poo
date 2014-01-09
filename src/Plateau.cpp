#include "../include/Plateau.h"
#include <iostream>
using namespace std;

Plateau::Plateau()
{
    //ctor
}

/* Constructeur pour plateau rempli de case vide mais ayant leur coordonnees. */
Plateau::Plateau(unsigned int tailleH, unsigned int tailleV)
{
    //ctor
    this->tailleH = tailleH;
    this->tailleV = tailleV;
    for (unsigned int i(0); i<tailleH; i++) {
        for (unsigned int j(0); j<tailleV; j++) {
            this->lCases.push_back(Case(j, i));
        }
    }
}

Plateau::~Plateau()
{
    //dtor
}

unsigned int Plateau::getTailleH()
{
    return this->tailleH;
}

unsigned int Plateau::getTailleV()
{
    return this->tailleV;
}

/* retourne incide de la case (de position p.x/p.y) dans vector */
int Plateau::getCaseFromPosition(Position p)
{
    std::vector<Case> &lc = this->lCases;
    for (unsigned int i(0); i<this->lCases.size(); i++) {
        if (lc[i].getPosition().estEgal(p)) return i;
    }
    return -1;
}

/* deplace le pion a la position depart vers arrive, le pion de la
 * case d'arrive doit avoir ete retirié avant ou il sera perdu
 */

void Plateau::deplacerPion(Position depart, Position arrive)
{
    try {
        int c1 = getCaseFromPosition(depart);
        int c2 = getCaseFromPosition(arrive);
        if (c1 == -1 || c2 == -1) throw 7;
        this->lCases[c2].setPion(this->lCases[c1].getPion());
    } catch (int e) {
        cout << "Exception as occured in deplacerPion: " << e << endl;
    }
}

void Plateau::afficher()
{
    unsigned int i,j;
    for (i=0; i < this->lCases.size(); i++) {
        for (j=0; j< this->tailleH; j++)
            cout << "| " << this->lCases[j+i].getPosition().getX() <<  "/" << this->lCases[j+i].getPosition().getY() << " |";
    i = i+j-1;
    cout << endl;
    }
}

