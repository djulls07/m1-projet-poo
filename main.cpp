#include <iostream>
#include "include/PlateauP4.h"
#include "include/PlateauO.h"
#include "include/PlateauFoM.h"
#include "include/Echequier.h"

using namespace std;

int main(int argc, char **argv)
{
  string j[2];
  int t;
  bool b;
  int nb;
  int v;
  
  if (argc != 2) {
    cerr << "Besoin d'un arg (1->4) pour choix jeu !" << endl;
    exit(1);
  }
  string choix(argv[1]);
  if (choix == "1") {
    cout << "Choix nom joueurs, Joueur 1 ?" << endl;
    cin >> j[0];
    cout << "joueur 1 : " << j[0] << endl;
    cout << "Choix nom joueurs, Joueur 2 ?" << endl;
    cin >> j[1];
    cout << "Joueur 2 : " << j[1] << endl;
    PlateauP4 *p = new PlateauP4(j);
    p->run();
    delete(p);
    
  } else if (choix == "2") {
    //five or more
    b = false;

    cout << "Votre Nom ?" << endl;
    cin >> j[0];
    cout << "joueur : " << j[0] << endl;

    cout << "Taille plateau voulu ?" << endl;
    t = lireEntier(5,15);

    cout << "Variante ( 1=non et 2=oui )" << endl;
    v = lireEntier(1,2) ;
    if (v == 2) b = true;

    cout << "Nombre de couleurs differentes ?" <<endl;
    nb = lireEntier(1,10);

    PlateauFoM *p = new PlateauFoM(j[0], t, b, nb);
    int pts = p->run();
    delete(p);

  } else if (choix == "3") {
    //othello
    cout << "Choix nom joueurs, Joueur 1 ?" << endl;
    cin >> j[0];
    cout << "joueur 1 : " << j[0] << endl;
    cout << "Choix nom joueurs, Joueur 2 ?" << endl;
    cin >> j[1];
    cout << "Joueur 2 : " << j[1] << endl;
    PlateauO *p = new PlateauO(j);
    p->run();
    delete(p);
  } else {
    cout << "Choix nom joueurs, Joueur 1 ?" << endl;
    cin >> j[0];
    cout << "joueur 1 : " << j[0] << endl;
    cout << "Choix nom joueurs, Joueur 2 ?" << endl;
    cin >> j[1];
    cout << "Joueur 2 : " << j[1] << endl;
    Echequier *e = new Echequier(j);
    e->run();
    delete(e);
    //echec
  }
  return 0;
}
