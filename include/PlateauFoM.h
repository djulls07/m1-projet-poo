#ifndef PLATEAU_FOM
#include "fonctions.h"
#include "Plateau.h"
#include "CaseFoM.h"
#include <cstdlib>
#include <ctime>
#define PLATEAU_FOM

class PlateauFoM : public Plateau
{
 public:
  PlateauFoM(std::string name, int t, bool var, int nbC);
  virtual ~PlateauFoM();
  
  virtual std::string afficher();
  virtual CaseFoM *getCase(Position p);

  /* ici verifie que la grille non pleine et l'alignement pr points.*/
  virtual int endGame();
  
  virtual int game(int n);
  
  /* ici jouable = valide et sans pion */
  virtual bool checkCaseJouable(Position p);
  
  /* cas general */
  virtual void jouerPion(Position p, Joueur *j);

  /* cas hangement color */
  virtual void jouerPionC(Position p, int color);

  /* cas deplacement */
  virtual void jouerPionD(Position p1, Position p2);

  virtual Position getChoixPos(std::string s1, std::string s2);

  /* demande une coouleur au joueur ( in [1, nbCouleurs] )*/
  virtual int getChoixColor();
  
  virtual void posePionRandom();
  virtual bool posePion(Position p, int couleur);
  virtual int randCouleur();
  virtual int run();
  
  /* renvoi 1 si 1 alignement trouvé */
  virtual bool verifAlign(Position p);
  /*virtual void verifAlignLC(int c, bool b);
  virtual void verifAlignD();
  virtual void verifAlignDG(Position p);
  virtual void verifAlignDD(Position p);*/
  virtual int count(Position p, int x, int y);
  virtual bool calculChemin(Position p1, Position p2);
  virtual void retraitAlign(Position p1, Position p2);
  virtual bool subCalculChemin(Position ici, int entree, Position direction, std::vector <std::vector <bool> > *memory);
  virtual int subCalcul(Position p, Position direction);

 protected:
  bool variante;
  int nbCouleurs;
  int points;
  std::vector<Position> vp;
  std::vector<std::vector <CaseFoM*> > grille;
};

#endif
