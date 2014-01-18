#ifndef CASE_H
#include "../include/Position.h"
#include "../include/Pion.h"
#include <string>
#define CASE_H


class Case
{
    public:
        Case();
        Case(int x, int y);
        virtual ~Case();
        virtual Position getPosition();
	virtual void setPosition(int x, int y);
        virtual Pion *getPion();
        virtual void setPion(Pion *p);
	virtual std::string afficher();
    protected:
        Position pos;
        Pion *p;
    private:
};

#endif // CASE_H
