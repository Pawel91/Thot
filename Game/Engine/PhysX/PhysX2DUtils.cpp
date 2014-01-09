#include "PhysX2DUtils.h"

Bool PhysX2D::Inters_SegVsSeg ( const tVect2& A, const tVect2& B, const tVect2& C, const tVect2& D )
{
    float alpha1    = A.y - B.y;
    float beta1        = B.x - A.x;
    float gama1        = A.x * B.y - B.x * A.y;

    float alpha2    = C.y - D.y;
    float beta2        = D.x - C.x;
    float gama2        = C.x * D.y - D.x * C.y;

#define val_dr1(x,y)    (alpha1 * (x) + beta1 * (y) + gama1)
#define val_dr2(x,y)    (alpha2 * (x) + beta2 * (y) + gama2)

    if(        val_dr1(C.x, C.y) * val_dr1(D.x, D.y) < 0 
        &&    val_dr2(A.x, A.y) * val_dr2(B.x, B.y) < 0 )
        return true;
    else
        return false;

#undef val_dr1
#undef val_dr2
}

Bool PhysX2D::Inters_SegVsSeg ( const tVect2& A, const tVect2& B, const tVect2& C, const tVect2& D, tVect2& out )
{
    float a1 = B.x - A.x;
    float b1 = C.x - D.x;
    float a2 = B.y - A.y;
    float b2 = C.y - D.y;
    float c1 = C.x - A.x;
    float c2 = C.y - A.y;

    float fDet = a1 * b2 - a2 * b1;

    if( fequals(fDet,0.f) )
        return false;

    float fDetX = c1 * b2 - b1 * c2;
    float fDetY = a1 * c2 - c1 * a2;

    //out.x = fDetX / fDet;
    //out.y = fDetY / fDet;

    float t = fDetX / fDet;
    float s = fDetY / fDet;

    if( t>=0.01f && t<=0.99f && s>=0.01 && s<=0.99f)
    {
        out = Lerp( A, B, t );
        return true;
    }
    else
    {
        return false;
    }
}