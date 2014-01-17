#ifndef PLATEAUP4_H
#define PLATEAUP4_H

#include "Plateau.h"


class PlateauP4 : public Plateau
{
    public:
        PlateauP4();
	PlateauP4(std::string names[]);
        virtual ~PlateauP4();
	virtual void game(int n);
	virtual int endGame();
    protected:
    private:
};

#endif // PLATEAUP4_H
