#include "main.h"

std::tuple<int, int> reload(int spareBullets, int bulletsInClip, int clipSize)
{
    if (spareBullets > 0 && (bulletsInClip < clipSize))
    {
        int bulletAmtToAdd = clipSize - bulletsInClip;
        if (bulletAmtToAdd > spareBullets)
        {
            bulletAmtToAdd = spareBullets;
        }
        bulletsInClip += bulletAmtToAdd;
        spareBullets -= bulletAmtToAdd;
    }
    return std::make_tuple(bulletsInClip, spareBullets);
}