#pragma once
#ifndef __PHYSX_2D_UTILS_H__
#define __PHYSX_2D_UTILS_H__


namespace PhysX2D
{
PHYSX_API Bool        Inters_SegVsSeg                ( const tVect2& A, const tVect2& B, const tVect2& C, const tVect2& D );
PHYSX_API Bool        Inters_SegVsSeg                ( const tVect2& A, const tVect2& B, const tVect2& C, const tVect2& D, tVect2& out );

};





#endif /*__PHYSX_2D_UTILS_H__*/