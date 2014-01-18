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
    protected:
        unsigned int couleur;
    private:
};

#endif // PION_H
