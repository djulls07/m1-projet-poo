#ifndef CASE_H
#include "../include/Position.h"
#include "../include/Pion.h"
#define CASE_H


class Case
{
    public:
        Case();
        Case(int x, int y);
        virtual ~Case();
        virtual Position getPosition();
        virtual Pion *getPion();
        virtual void setPion(Pion *p);
    protected:
        Position pos;
        Pion *p;
    private:
};

#endif // CASE_H
