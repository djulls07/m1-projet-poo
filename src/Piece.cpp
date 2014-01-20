#include "../include/Piece.h"
#include <cstdlib>

Piece::Piece(int t, unsigned int color) : Pion(color)
{
  this->deplace = false;
  // Types :
  // 0 : Pion
  // 1 : Cavalier
  // 2 : Fou
  // 3 : Tour
  // 4 : Dame
  // 5 : Roi
  this->type = t;
}

Piece::~Piece()
{

}

int Piece::getType()
{
  return this->type;
}

bool Piece::isCavalier()
{
  if (this->type == 1)
    return true;
  return false;
}

bool Piece::isPion()
{
  if (this->type == 0)
    return true;
  return false;
}

bool Piece::isFou()
{
  if (this->type == 2)
    return true;
  return false;
}

bool Piece::isTour()
{
  if (this->type == 3)
    return true;
  return false;
}

bool Piece::isDame()
{
  if (this->type == 4)
    return true;
  return false;
}

bool Piece::isRoi()
{
  if (this->type == 5)
    return true;
  return false;
}

bool Piece::prendEnDiagonale()
{
  if (this->isDame() || this->isFou())
    return true;
  return false;
}

bool Piece::prendEnLigne()
{
  if (this->isDame() || this->isTour())
    return true;
  return false;
}

bool Piece::wasMoved()
{
  return deplace;
}

void Piece::isMoved()
{
  this->deplace = true;
}

std::string Piece::afficher()
{
  if (this->couleur == 1) {
    if (this->isPion())
      return "\033[31mPio\033[0m";
    if (this->isCavalier())
      return "\033[31mCav\033[0m";
    if (this->isFou())
      return "\033[31mFou\033[0m";
    if (this->isTour())
      return "\033[31mTou\033[0m";
    if (this->isDame())
      return "\033[31mDam\033[0m";
    if (this->isRoi())
      return "\033[31mRoi\033[0m";
  } else {
    if (this->isPion())
      return "\033[33mPio\033[0m";
    if (this->isCavalier())
      return "\033[33mCav\033[0m";
    if (this->isFou())
      return "\033[33mFou\033[0m";
    if (this->isTour())
      return "\033[33mTou\033[0m";
    if (this->isDame())
      return "\033[33mDam\033[0m";
    if (this->isRoi())
      return "\033[33mRoi\033[0m";
  }
}
