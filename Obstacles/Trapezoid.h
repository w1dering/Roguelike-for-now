#ifndef _TRAPEZOID_
#define _TRAPEZOID_

#include <raylib.h>

class Trapezoid
{
public:
    Vector2 TL;
    Vector2 TR;
    Vector2 BL;
    Vector2 BR;
    int orientation;
    Trapezoid(Vector2 tl, Vector2 tr, Vector2 bl, Vector2 br, int orientation) // 0 up, 1 left, 2 down, 3 right
    {
        TL = Vector2{tl.x - 1, tl.y - 1};
        TR = Vector2{tr.x + 1, tr.y - 1};
        BL = Vector2{bl.x - 1, bl.y + 1};
        BR = Vector2{br.x + 1, br.y + 1};
        this->orientation = orientation;
    }

    bool isPointIn(Vector2 point)
    {
        switch (orientation)
        {
        case 0:
            return CheckCollisionPointRec(point, Rectangle{TL.x, TL.y, TR.x - TL.x, BL.y - TL.y}) ||
                   CheckCollisionPointTriangle(point, TL, BL, Vector2{TL.x, BL.y}) ||
                   CheckCollisionPointTriangle(point, TR, BR, Vector2{TR.x, BR.y});
        case 1:
            return CheckCollisionPointRec(point, Rectangle{TL.x, TL.y, TR.x - TL.x, BL.y - TL.y}) ||
                   CheckCollisionPointTriangle(point, TL, TR, Vector2{TR.x, TL.y}) ||
                   CheckCollisionPointTriangle(point, BL, BR, Vector2{BR.x, BL.y});
        case 2:
            return CheckCollisionPointRec(point, Rectangle{BL.x, TL.y, BR.x - BL.x, BL.y - TL.y}) ||
                   CheckCollisionPointTriangle(point, TL, BL, Vector2{BL.x, TL.y}) ||
                   CheckCollisionPointTriangle(point, TR, BR, Vector2{BR.x, TR.y});
        case 3:
            return CheckCollisionPointRec(point, Rectangle{TL.x, TR.y, TR.x - TL.x, BR.y - TR.y}) ||
                   CheckCollisionPointTriangle(point, TL, TR, Vector2{TR.x, TL.y}) ||
                   CheckCollisionPointTriangle(point, BL, BR, Vector2{BR.x, BL.y});
        }
        cout << "trapezoid IsPointIn ended" << endl;
        return false;
    }
};

#endif