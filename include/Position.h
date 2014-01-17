#ifndef POSITION_H
#define POSITION_H


class Position
{
    public:
        Position();
        Position(int x, int y);
        virtual ~Position();
        virtual int getX();
        virtual int getY();
        bool estEgal(Position a);
	bool operator==(Position a);
	void setX(int x);
	void setY(int y);
    protected:
    private:
        int x;
        int y;
};

#endif // POSITION_H
