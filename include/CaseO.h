#ifndef CASEO_H
#include "../include/Position.h"
#include "../include/Pion.h"
#include "./Case.h"
#include <vector>
#include <string>
#define CASEO_H

class CaseO : public Case
{
    public:
        CaseO(int x, int y);
        virtual ~CaseO();
	virtual int isJouable();
	virtual void setJouable();
	virtual void setPasJouable();
        virtual void setPion(Pion *p);
	virtual void setDisposition(int c, int d);
	virtual int getDisposition(int c);
	virtual std::string afficher();
    protected:
	std::vector<int> disposition;
	int jouable;
    private:
};

#endif // CASEO_H
