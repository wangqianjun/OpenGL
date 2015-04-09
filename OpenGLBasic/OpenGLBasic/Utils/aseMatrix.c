//
//  ASEMatrix.c
//  OpenGLBasic
//
//  Created by Arthur on 15/4/9.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#include "aseMatrix.h"
#include <stdlib.h>
#include <math.h>

void * memcpy(void *, const void *, size_t);
void * memset(void *, int, size_t);

unsigned int aseNextPot(unsigned int n)
{
    n--;
    n |= n >> 1; n |= n >> 2;
    n |= n >> 4; n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

//
// Matrix math utility
//

void aseMatrixScale(aseMatrix4 * result, float sx, float sy, float sz)
{
    result->m[0][0] *= sx;
    result->m[0][1] *= sx;
    result->m[0][2] *= sx;
    result->m[0][3] *= sx;
    
    result->m[1][0] *= sy;
    result->m[1][1] *= sy;
    result->m[1][2] *= sy;
    result->m[1][3] *= sy;
    
    result->m[2][0] *= sz;
    result->m[2][1] *= sz;
    result->m[2][2] *= sz;
    result->m[2][3] *= sz;
}

void aseMatrixTranslate(aseMatrix4 * result, float tx, float ty, float tz)
{
    result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
    result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
    result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
    result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);
}

void aseMatrixRotate(aseMatrix4 * result, float angle, float x, float y, float z)
{
    float sinAngle, cosAngle;
    float mag = sqrtf(x * x + y * y + z * z);
    
    sinAngle = sinf ( angle * M_PI / 180.0f );
    cosAngle = cosf ( angle * M_PI / 180.0f );
    if ( mag > 0.0f )
    {
        float xx, yy, zz, xy, yz, zx, xs, ys, zs;
        float oneMinusCos;
        aseMatrix4 rotMat;
        
        x /= mag;
        y /= mag;
        z /= mag;
        
        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;
        
        rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
        rotMat.m[0][1] = (oneMinusCos * xy) - zs;
        rotMat.m[0][2] = (oneMinusCos * zx) + ys;
        rotMat.m[0][3] = 0.0F;
        
        rotMat.m[1][0] = (oneMinusCos * xy) + zs;
        rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
        rotMat.m[1][2] = (oneMinusCos * yz) - xs;
        rotMat.m[1][3] = 0.0F;
        
        rotMat.m[2][0] = (oneMinusCos * zx) - ys;
        rotMat.m[2][1] = (oneMinusCos * yz) + xs;
        rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
        rotMat.m[2][3] = 0.0F;
        
        rotMat.m[3][0] = 0.0F;
        rotMat.m[3][1] = 0.0F;
        rotMat.m[3][2] = 0.0F;
        rotMat.m[3][3] = 1.0F;
        
        aseMatrixMultiply( result, &rotMat, result );
    }
}

// result[x][y] = a[x][0]*b[0][y]+a[x][1]*b[1][y]+a[x][2]*b[2][y]+a[x][3]*b[3][y];
void aseMatrixMultiply(aseMatrix4 * result, const aseMatrix4 *a, const aseMatrix4 *b)
{
    aseMatrix4 tmp;
    int i;
    
    for (i = 0; i < 4; i++)
    {
        tmp.m[i][0] = (a->m[i][0] * b->m[0][0]) +
        (a->m[i][1] * b->m[1][0]) +
        (a->m[i][2] * b->m[2][0]) +
        (a->m[i][3] * b->m[3][0]) ;
        
        tmp.m[i][1] = (a->m[i][0] * b->m[0][1]) +
        (a->m[i][1] * b->m[1][1]) +
        (a->m[i][2] * b->m[2][1]) +
        (a->m[i][3] * b->m[3][1]) ;
        
        tmp.m[i][2] = (a->m[i][0] * b->m[0][2]) +
        (a->m[i][1] * b->m[1][2]) +
        (a->m[i][2] * b->m[2][2]) +
        (a->m[i][3] * b->m[3][2]) ;
        
        tmp.m[i][3] = (a->m[i][0] * b->m[0][3]) +
        (a->m[i][1] * b->m[1][3]) +
        (a->m[i][2] * b->m[2][3]) +
        (a->m[i][3] * b->m[3][3]) ;
    }
    
    memcpy(result, &tmp, sizeof(aseMatrix4));
}

void aseMatrixDotVector(aseVec4 * out, const aseMatrix4 * m, const aseVec4 * v)
{
    out->x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;
    out->y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;
    out->z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;
    out->w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;
}

void aseMatrixCopy(aseMatrix4 * target, const aseMatrix4 * src)
{
    memcpy(target, src, sizeof(aseMatrix4));
}

int aseMatrixInvert(aseMatrix4 * out, const aseMatrix4 * in)
{
    float * m = (float *)(&in->m[0][0]);
    float * om = (float *)(&out->m[0][0]);
    double inv[16], det;
    int i;
    
    inv[0] = m[5]  * m[10] * m[15] -
    m[5]  * m[11] * m[14] -
    m[9]  * m[6]  * m[15] +
    m[9]  * m[7]  * m[14] +
    m[13] * m[6]  * m[11] -
    m[13] * m[7]  * m[10];
    
    inv[4] = -m[4]  * m[10] * m[15] +
    m[4]  * m[11] * m[14] +
    m[8]  * m[6]  * m[15] -
    m[8]  * m[7]  * m[14] -
    m[12] * m[6]  * m[11] +
    m[12] * m[7]  * m[10];
    
    inv[8] = m[4]  * m[9] * m[15] -
    m[4]  * m[11] * m[13] -
    m[8]  * m[5] * m[15] +
    m[8]  * m[7] * m[13] +
    m[12] * m[5] * m[11] -
    m[12] * m[7] * m[9];
    
    inv[12] = -m[4]  * m[9] * m[14] +
    m[4]  * m[10] * m[13] +
    m[8]  * m[5] * m[14] -
    m[8]  * m[6] * m[13] -
    m[12] * m[5] * m[10] +
    m[12] * m[6] * m[9];
    
    inv[1] = -m[1]  * m[10] * m[15] +
    m[1]  * m[11] * m[14] +
    m[9]  * m[2] * m[15] -
    m[9]  * m[3] * m[14] -
    m[13] * m[2] * m[11] +
    m[13] * m[3] * m[10];
    
    inv[5] = m[0]  * m[10] * m[15] -
    m[0]  * m[11] * m[14] -
    m[8]  * m[2] * m[15] +
    m[8]  * m[3] * m[14] +
    m[12] * m[2] * m[11] -
    m[12] * m[3] * m[10];
    
    inv[9] = -m[0]  * m[9] * m[15] +
    m[0]  * m[11] * m[13] +
    m[8]  * m[1] * m[15] -
    m[8]  * m[3] * m[13] -
    m[12] * m[1] * m[11] +
    m[12] * m[3] * m[9];
    
    inv[13] = m[0]  * m[9] * m[14] -
    m[0]  * m[10] * m[13] -
    m[8]  * m[1] * m[14] +
    m[8]  * m[2] * m[13] +
    m[12] * m[1] * m[10] -
    m[12] * m[2] * m[9];
    
    inv[2] = m[1]  * m[6] * m[15] -
    m[1]  * m[7] * m[14] -
    m[5]  * m[2] * m[15] +
    m[5]  * m[3] * m[14] +
    m[13] * m[2] * m[7] -
    m[13] * m[3] * m[6];
    
    inv[6] = -m[0]  * m[6] * m[15] +
    m[0]  * m[7] * m[14] +
    m[4]  * m[2] * m[15] -
    m[4]  * m[3] * m[14] -
    m[12] * m[2] * m[7] +
    m[12] * m[3] * m[6];
    
    inv[10] = m[0]  * m[5] * m[15] -
    m[0]  * m[7] * m[13] -
    m[4]  * m[1] * m[15] +
    m[4]  * m[3] * m[13] +
    m[12] * m[1] * m[7] -
    m[12] * m[3] * m[5];
    
    inv[14] = -m[0]  * m[5] * m[14] +
    m[0]  * m[6] * m[13] +
    m[4]  * m[1] * m[14] -
    m[4]  * m[2] * m[13] -
    m[12] * m[1] * m[6] +
    m[12] * m[2] * m[5];
    
    inv[3] = -m[1] * m[6] * m[11] +
    m[1] * m[7] * m[10] +
    m[5] * m[2] * m[11] -
    m[5] * m[3] * m[10] -
    m[9] * m[2] * m[7] +
    m[9] * m[3] * m[6];
    
    inv[7] = m[0] * m[6] * m[11] -
    m[0] * m[7] * m[10] -
    m[4] * m[2] * m[11] +
    m[4] * m[3] * m[10] +
    m[8] * m[2] * m[7] -
    m[8] * m[3] * m[6];
    
    inv[11] = -m[0] * m[5] * m[11] +
    m[0] * m[7] * m[9] +
    m[4] * m[1] * m[11] -
    m[4] * m[3] * m[9] -
    m[8] * m[1] * m[7] +
    m[8] * m[3] * m[5];
    
    inv[15] = m[0] * m[5] * m[10] -
    m[0] * m[6] * m[9] -
    m[4] * m[1] * m[10] +
    m[4] * m[2] * m[9] +
    m[8] * m[1] * m[6] -
    m[8] * m[2] * m[5];
    
    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    
    if (det == 0)
        return 0;
    
    det = 1.0 / det;
    for (i = 0; i < 16; i++)
        *om++ = (float)(inv[i] * det);
    
    return 1;
}

void aseMatrixTranspose(aseMatrix4 * result, const aseMatrix4 * src)
{
    aseMatrix4 tmp;
    tmp.m[0][0] = src->m[0][0];
    tmp.m[0][1] = src->m[1][0];
    tmp.m[0][2] = src->m[2][0];
    tmp.m[0][3] = src->m[3][0];
    
    tmp.m[1][0] = src->m[0][1];
    tmp.m[1][1] = src->m[1][1];
    tmp.m[1][2] = src->m[2][1];
    tmp.m[1][3] = src->m[3][1];
    
    tmp.m[2][0] = src->m[0][2];
    tmp.m[2][1] = src->m[1][2];
    tmp.m[2][2] = src->m[2][2];
    tmp.m[2][3] = src->m[3][2];
    
    tmp.m[3][0] = src->m[0][3];
    tmp.m[3][1] = src->m[1][3];
    tmp.m[3][2] = src->m[2][3];
    tmp.m[3][3] = src->m[3][3];
    
    memcpy(result, &tmp, sizeof(aseMatrix4));
}

void aseMatrix4ToMatrix3(aseMatrix3 * result, const aseMatrix4 * src)
{
    result->m[0][0] = src->m[0][0];
    result->m[0][1] = src->m[0][1];
    result->m[0][2] = src->m[0][2];
    result->m[1][0] = src->m[1][0];
    result->m[1][1] = src->m[1][1];
    result->m[1][2] = src->m[1][2];
    result->m[2][0] = src->m[2][0];
    result->m[2][1] = src->m[2][1];
    result->m[2][2] = src->m[2][2];
}

void aseMatrixLoadIdentity(aseMatrix4 * result)
{
    memset(result, 0x0, sizeof(aseMatrix4));
    
    result->m[0][0] = 1.0f;
    result->m[1][1] = 1.0f;
    result->m[2][2] = 1.0f;
    result->m[3][3] = 1.0f;
}

void aseFrustum(aseMatrix4 * result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    aseMatrix4    frust;
    
    if ( (nearZ <= 0.0f) || (farZ <= 0.0f) ||
        (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f) )
        return;
    
    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;
    
    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;
    
    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;
    
    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;
    
    aseMatrixMultiply(result, &frust, result);
}

void asePerspective(aseMatrix4 * result, float fovy, float aspect, float nearZ, float farZ)
{
    float frustumW, frustumH;
    
    frustumH = tanf( fovy / 360.0f * M_PI ) * nearZ;
    frustumW = frustumH * aspect;
    
    aseFrustum(result, -frustumW, frustumW, -frustumH, frustumH, nearZ, farZ);
}

void aseOrtho(aseMatrix4 * result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    aseMatrix4    ortho;
    
    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f))
        return;
    
    aseMatrixLoadIdentity(&ortho);
    ortho.m[0][0] = 2.0f / deltaX;
    ortho.m[3][0] = -(right + left) / deltaX;
    ortho.m[1][1] = 2.0f / deltaY;
    ortho.m[3][1] = -(top + bottom) / deltaY;
    ortho.m[2][2] = -2.0f / deltaZ;
    ortho.m[3][2] = -(nearZ + farZ) / deltaZ;
    
    aseMatrixMultiply(result, &ortho, result);
}

void aseLookAt(aseMatrix4 * result, const aseVec3 * eye, const aseVec3 * target, const aseVec3 * up)
{
    aseVec3 side, up2, forward ;
    //aseVec4 eyePrime;
    aseMatrix4 transMat;
    
    aseVectorSubtract(&forward, target, eye);
    aseVectorNormalize(&forward);
    
    aseCrossProduct(&side, up, &forward);
    aseVectorNormalize(&side );
    
    aseCrossProduct(&up2, &side, &forward);
    aseVectorNormalize(&up2);
    
    aseMatrixLoadIdentity(result);
    result->m[0][0] = side.x;
    result->m[0][1] = side.y;
    result->m[0][2] = side.z;
    result->m[1][0] = up2.x;
    result->m[1][1] = up2.y;
    result->m[1][2] = up2.z;
    result->m[2][0] = -forward.x;
    result->m[2][1] = -forward.y;
    result->m[2][2] = -forward.z;
    
    aseMatrixLoadIdentity(&transMat);
    aseMatrixTranslate(&transMat, -eye->x, -eye->y, -eye->z);
    
    aseMatrixMultiply(result, result, &transMat);

}
