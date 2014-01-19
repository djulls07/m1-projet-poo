#ifndef PLATEAUP4_H
#define PLATEAUP4_H
#include "Plateau.h"


class PlateauP4 : public Plateau
{
    public:
        PlateauP4();
	PlateauP4(std::string names[]);
        virtual ~PlateauP4();
	virtual int game(int n);
	virtual int endGame();
	virtual bool checkCaseJouable(Position p);
	virtual void jouerPion(Position p, Joueur *j);
	virtual std::string afficher();
	virtual int run();
	virtual int checkDiagonales();
	virtual int checkDiagoG();
	virtual int checkDiagoD();
	virtual int checkDiag(Position p, bool b);
	virtual int checkLignes();
	virtual int checkColonnes();

    protected:
    private:
};

#endif // PLATEAUP4_H
