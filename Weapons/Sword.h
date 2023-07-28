#ifndef _SWORD_
#define _SWORD_

#include <raylib.h>

class Sword
{

public:
    int framesSwung;
    Image image;

    Sword();

    void swing();

};

#endif