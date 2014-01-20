#ifndef CASEE_H
#include "Position.h"
#include "Piece.h"
#include "Case.h"
#include <string>
#define CASEE_H


class CaseE : public Case
{
    public:
        CaseE(int x, int y);
        virtual ~CaseE();
        virtual Piece *getPion();
        virtual void setPion(Piece *p);
	virtual std::string afficher();
	virtual bool hasPion();
    protected:
        Piece *p;
    private:
};

#endif // CASEE_H
