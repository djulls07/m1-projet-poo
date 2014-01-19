#include "../include/fonctions.h"
std::string intToString(int i)
{
    std::stringstream ss;   // <-- also note namespace qualification
    ss << i;
    return ss.str();
}
