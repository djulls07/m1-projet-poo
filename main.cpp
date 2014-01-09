#include <iostream>
#include "include/PlateauP4.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    PlateauP4* p = new PlateauP4();
    cout << p->getTailleV() << endl;
    p->afficher();
    delete(p);
    return 0;
}
