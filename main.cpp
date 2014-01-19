#include <iostream>
#include <sstream>
#include "include/PlateauP4.h"
#include "include/PlateauO.h"

using namespace std;


string intToString(int i)
{
  std::stringstream ss;   // <-- also note namespace qualification
  ss << i;
  return ss.str();
}

int main()
{
  string j[2];
  
  cin >> j[0];
  cout << "joueur 1 : " << j[0] << endl;
  cin >> j[1];  cout << "Partie terminee" << endl;

  cout << "Joueur 2 : " << j[1] << endl;
  PlateauO *p = new PlateauO(j);
  p->run();
  delete(p); 
  return 0;
}
