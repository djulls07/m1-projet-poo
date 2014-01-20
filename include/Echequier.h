#ifndef ECHEQUIER_H
#include "CaseE.h"
#include "Joueur.h"
#include "Position.h"
#include "Piece.h"
#include "Plateau.h"
#include <vector>
#include <string>
#define ECHEQUIER_H


class Echequier : public Plateau
{
 public:

    Echequier(std::string names[]);
    virtual ~Echequier();
    
    virtual CaseE *getCase(Position p);
    virtual std::string afficher();
    virtual bool checkCaseJouable(Position p);
    virtual void jouerPion(Position p, Joueur *j);
    virtual int run();
    
    //virtual int endGame() = 0; //abs
  
 protected:
    std::vector<std::vector <CaseE*> > grille;
    Position dernierCoup;
    Position roiBlanc;
    Position roiNoir;
    bool fin;
    bool pep;
    
 private:
    bool menaceeParRoi(Position p, int c);
    void mangerPion(Position miam);
    void deplacerPion(Position depart, Position arrive);
    int promouvoirPion();
    bool priseEnPassant(Position p);
    bool estEnnemi(Position p, int c);
    bool estEchec(Position p, int c);
    bool deplacePiecePion(Position depart, Position arrivee);
    bool deplacePieceCavalier(Position depart, Position arrivee);
    bool deplacePieceFou(Position depart, Position arrivee);
    bool deplacePieceTour(Position depart, Position arrivee);
    bool deplacePieceDame(Position depart, Position arrivee);
    bool deplacePieceRoi(Position depart, Position arrivee);
    bool deplacePiece(Position depart, Position arrivee);
    void winner(int joueur);
    void abandon(int joueur);
    int game(int joueur);
    int endGame();
};

#endif // ECHEQUIER_H
