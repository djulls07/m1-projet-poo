#include <iostream>
#include "include/PlateauP4.h"
#include "include/PlateauO.h"

using namespace std;

int main()
{
  string j[2];
  
  cin >> j[0];
  cout << "joueur 1 : " << j[0] << endl;
  cin >> j[1];
  cout << "Joueur 2 : " << j[1] << endl;
  PlateauP4 *p = new PlateauP4(j);
  p->run();
  delete(p); 
  return 0;
}
