#ifndef PLATEAUO_H
#define PLATEAUO_H

#include "Plateau.h"
#include "CaseO.h"


class PlateauO : public Plateau
{
    public:
        PlateauO();
	PlateauO(std::string names[]);
        virtual ~PlateauO();
	virtual CaseO* getCase(Position p);
	int run();
    protected:
	std::vector<std::vector <CaseO*> > grille;
    private:
	int checkCaseJouableHorizontale(Position p, int c);
	int checkCaseJouableVerticale(Position p, int c);
	int checkCaseJouableDiagonale(Position p, int c);
	virtual bool checkCaseJouable(Position p);
	int checkCouleurJouable(int c);
	void retournerHorizontale(Position p, int c, int disposition);
	void retournerVerticale(Position p, int c, int disposition);
	void retournerDiagonale(Position p, int c, int disposition);
	int jouerPionO(Position p, Joueur* j);
	virtual void jouerPion(Position p, Joueur* j);
	virtual void game(int joueur);
	int gameO(int joueur);
	virtual int endGame();
	virtual std::string afficher();
	
};

#endif // PLATEAUO_H
