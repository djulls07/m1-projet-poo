#ifndef PLATEAU_H
#include "../include/Case.h"
#include <vector>
#define PLATEAU_H


class Plateau
{
    public:
        Plateau();
        Plateau(unsigned int tailleH, unsigned int tailleV);
        virtual ~Plateau();
        virtual unsigned int getTailleH();
        virtual unsigned int getTailleV();
        virtual void deplacerPion(Position depart, Position arrive);
        virtual int getCaseFromPosition(Position p);
        virtual void afficher(); //pour debug

    protected:
        unsigned int tailleH;
        unsigned int tailleV;
        std::vector<Case> lCases;

    private:
};

#endif // PLATEAU_H
