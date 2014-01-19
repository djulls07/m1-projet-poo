#ifndef POSITION_H
#include <string>
#define POSITION_H


class Position
{
    public:
        Position();
        Position(int x, int y);
        virtual ~Position();
        virtual int getX();
        virtual int getY();
        virtual bool estEgal(Position a);
	virtual bool operator==(Position a);
	virtual void setX(int x);
	virtual void setY(int y);
	virtual Position createModPos(int incrX, int incrY);
    protected:
    private:
        int x;
        int y;
};

#endif // POSITION_H
