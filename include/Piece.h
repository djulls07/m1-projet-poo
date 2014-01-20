#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <vector>
#include "Position.h"
#include "Pion.h"

class Piece : public Pion
{
    public:
        Piece(int t, unsigned int color);
        virtual ~Piece();
	virtual std::string afficher();
	virtual int getType();
	virtual bool isCavalier();
	virtual bool isPion();
	virtual bool isFou();
	virtual bool isTour();
	virtual bool isDame();
	virtual bool isRoi();
	virtual bool prendEnDiagonale();
	virtual bool prendEnLigne();
	virtual bool wasMoved();
	virtual void isMoved();
     
    protected:
        bool deplace;
	int type;

    private:
};

#endif // PIECE_H
