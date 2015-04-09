//
//  ASEVector.c
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/9.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#include "aseVector.h"
#include <math.h>

void aseVectorCopy(aseVec3 * out, const aseVec3 * in)
{
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

void aseVectorAdd(aseVec3 * out, const aseVec3 * a, const aseVec3 * b)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void aseVectorSubtract(aseVec3 * out, const aseVec3 * a, const aseVec3 * b)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}

void aseCrossProduct(aseVec3 * out, const aseVec3 * a, const aseVec3 * b)
{
    out->x = a->y * b->z - a->z * b->y;
    out->y = a->z * b->x - a->x * b->z;
    out->z = a->x * b->y - b->y * a->x;
}

float aseDotProduct(const aseVec3 * a, const aseVec3 * b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void aseVectorLerp(aseVec3 * out, const aseVec3 * a, const aseVec3 * b, float t)
{
    out->x = (a->x * (1 - t) + b->x * t);
    out->y = (a->y * (1 - t) + b->y * t);
    out->z = (a->z * (1 - t) + b->z * t);
}

void aseVectorScale(aseVec3 * v, float scale)
{
    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}

void aseVectorInverse(aseVec3 * v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void aseVectorNormalize(aseVec3 * v)
{
    float length = aseVectorLength(v);
    if (length != 0)
    {
        length = 1.0 / length;
        v->x *= length;
        v->y *= length;
        v->z *= length;
    }
}

int aseVectorCompare(const aseVec3 * a, const aseVec3 * b)
{
    if (a == b)
        return 1;
    
    if (a->x != b->x || a->y != b->y || a->z != b->z)
        return 0;
    return 1;
}

float aseVectorLength(const aseVec3 * in)
{
    return (float)sqrt(in->x * in->x + in->y * in->y + in->z * in->z);
}

float aseVectorLengthSquared(const aseVec3 * in)
{
    return (in->x * in->x + in->y * in->y + in->z * in->z);
}

float ksVectorDistance(const aseVec3 * a, const aseVec3 * b)
{
    aseVec3 v;
    aseVectorSubtract(&v, a, b);
    return aseVectorLength(&v);
}

float aseVectorDistanceSquared(const aseVec3 * a, const aseVec3 * b)
{
    aseVec3 v;
    aseVectorSubtract(&v, a, b);
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}