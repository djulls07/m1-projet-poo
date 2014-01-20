#include "../include/fonctions.h"
#include <limits>

std::string intToString(int i)
{
    std::stringstream ss;   // <-- also note namespace qualification
    ss << i;
    return ss.str();
}

int lireEntier(int min, int max)
{
  int n = -1;
  while(1) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    try {
      std::cin >> n;
      if (n<min || n>max) throw 7;
      break;
    } catch(int e) {
      std::cout << "Besoin d'un nombre dans [" << min << 
	"," << max <<"]" << std::endl;
      continue;
    }
  }
  return n;
}
