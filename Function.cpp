#include "Structures.h"
#include "Function.h"

void BlendModeFunc::UpdateBlendMode(int type)
{
    switch (type)
    {
    case None:
        Novice::SetBlendMode(kBlendModeNone);
        break;
    case Normal:
        Novice::SetBlendMode(kBlendModeNormal);
        break;
    case Add:
        Novice::SetBlendMode(kBlendModeAdd);
        break;
    case Subtract:
        Novice::SetBlendMode(kBlendModeSubtract);
        break;
    case Multiply:
        Novice::SetBlendMode(kBlendModeMultiply);
        break;
    case Screen:
        Novice::SetBlendMode(kBlendModeScreen);
        break;
    case Exclusion:
        Novice::SetBlendMode(kBlendModeExclusion);
        break;
    default:
        Novice::SetBlendMode(kBlendModeNone);
        break;
    }
}

void BlendModeFunc::ResetBlendMode()
{
    Novice::SetBlendMode(kBlendModeNormal);
}