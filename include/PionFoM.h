#ifndef PION_FOM
#define PION_FOM
#include "Pion.h"
#include "fonctions.h"

class PionFoM : public Pion
{
 public:
  PionFoM();
  PionFoM(unsigned int c);
  ~PionFoM();
  virtual std::string afficher();
  
};


#endif
