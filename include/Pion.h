#ifndef PION_H
#define PION_H
#include <string>

class Pion
{
    public:
        Pion();
        Pion(unsigned int i);
        virtual ~Pion();
	virtual std::string afficher();
	virtual int getCouleur();
	virtual void setCouleur(int c);
    protected:
        unsigned int couleur;
    private:
};

#endif // PION_H
