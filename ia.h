#ifndef IA_H
#define IA_H
#include "player.h"

class IA : public Player{
    int iaType = 0;
public:
    IA();
    int getiaType();
    void setiaType(int ia);
};

#endif // IA_H
