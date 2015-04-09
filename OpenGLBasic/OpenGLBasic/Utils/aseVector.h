//
//  ASEVector.h
//  OpenGLBasic
//
//  Created by Arthur on 15/4/9.
//

#ifndef __OpenGLBasic__ASEVector__
#define __OpenGLBasic__ASEVector__

#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} aseVec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} aseVec4;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} aseColor;

typedef unsigned char byte;

#ifdef __cplusplus
extern "C"{
#endif

    void aseVectorCopy(aseVec3 *out, const aseVec3 *in);
    void aseVectorAdd(aseVec3 * out, const aseVec3 * a, const aseVec3 * b);
    void aseVectorSubtract(aseVec3 * out, const aseVec3 * a, const aseVec3 * b);
    void aseVectorLerp(aseVec3 * out, const aseVec3 * a, const aseVec3 * b, float t);
    void aseCrossProduct(aseVec3 * out, const aseVec3 * a, const aseVec3 * b);
    float aseDotProduct(const aseVec3 * a, const aseVec3 * b);
    
    float aseVectorLengthSquared(const aseVec3 * in);
    float aseVectorDistanceSquared(const aseVec3 * a, const aseVec3 * b);
    
    void aseVectorScale(aseVec3 * v, float scale);
    void aseVectorNormalize(aseVec3 * v);
    void aseVectorInverse(aseVec3 * v);
    
    int aseVectorCompare(const aseVec3 * a, const aseVec3 * b);
    float aseVectorLength(const aseVec3 * in);
    float aseVectorDistance(const aseVec3 * a, const aseVec3 * b);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__OpenGLBasic__ASEVector__) */
