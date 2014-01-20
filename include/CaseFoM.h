#ifndef CASE_FOM
#define CASE_FOM
#include "Case.h"
#include "PionFoM.h"
#include "fonctions.h"

class CaseFoM : public Case
{
 public:
  CaseFoM();
  CaseFoM(int x, int y);
  virtual ~CaseFoM();
  virtual bool hasPion();
  virtual std::string afficher();
  virtual PionFoM *getPion();
  virtual void setPion(PionFoM *p);
  
 protected:
  PionFoM *p;
};

#endif
