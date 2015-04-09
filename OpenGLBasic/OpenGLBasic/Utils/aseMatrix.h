//
//  ASEMatrix.h
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/9.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#ifndef __OpenGLBasic__ASEMatrix__
#define __OpenGLBasic__ASEMatrix__

#include <stdio.h>
#include "aseVector.h"

//#ifndef M_PI
//#define M_PI 3.1415926535897932384626433832795f
//#endif


#define DEG2RAD( a ) (((a) * M_PI) / 180.0f)
#define RAD2DEG( a ) (((a) * 180.f) / M_PI)

// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

typedef struct aseMatrix3
{
    float   m[3][3];
} aseMatrix3;

typedef struct aseMatrix4
{
    float   m[4][4];
} aseMatrix4;

#ifdef __cplusplus
extern "C" {
#endif
    
    unsigned int aseNextPot(unsigned int n);
    
    void aseMatrixCopy(aseMatrix4 * target, const aseMatrix4 * src);
    
    int aseMatrixInvert(aseMatrix4 * out, const aseMatrix4 * in);
    
    void aseMatrixTranspose(aseMatrix4 * result, const aseMatrix4 * src);
    
    void aseMatrix4ToMatrix3(aseMatrix3 * target, const aseMatrix4 * src);
    
    void aseMatrixDotVector(aseVec4 * out, const aseMatrix4 * m, const aseVec4 * v);
    
    //
    /// multiply matrix specified by result with a scaling matrix and return new matrix in result
    /// result Specifies the input matrix.  Scaled matrix is returned in result.
    /// sx, sy, sz Scale factors along the x, y and z axes respectively
    //
    void aseMatrixScale(aseMatrix4 * result, float sx, float sy, float sz);
    
    //
    /// multiply matrix specified by result with a translation matrix and return new matrix in result
    /// result Specifies the input matrix.  Translated matrix is returned in result.
    /// tx, ty, tz Scale factors along the x, y and z axes respectively
    //
    void aseMatrixTranslate(aseMatrix4 * result, float tx, float ty, float tz);
    
    //
    /// multiply matrix specified by result with a rotation matrix and return new matrix in result
    /// result Specifies the input matrix.  Rotated matrix is returned in result.
    /// angle Specifies the angle of rotation, in degrees.
    /// x, y, z Specify the x, y and z coordinates of a vector, respectively
    //
    void aseMatrixRotate(aseMatrix4 * result, float angle, float x, float y, float z);
    
    //
    /// perform the following operation - result matrix = srcA matrix * srcB matrix
    /// result Returns multiplied matrix
    /// srcA, srcB Input matrices to be multiplied
    //
    void aseMatrixMultiply(aseMatrix4 * result, const aseMatrix4 *srcA, const aseMatrix4 *srcB);
    
    //
    //// return an identity matrix
    //// result returns identity matrix
    //
    void aseMatrixLoadIdentity(aseMatrix4 * result);
    
    //
    /// multiply matrix specified by result with a perspective matrix and return new matrix in result
    /// result Specifies the input matrix.  new matrix is returned in result.
    /// fovy Field of view y angle in degrees
    /// aspect Aspect ratio of screen
    /// nearZ Near plane distance
    /// farZ Far plane distance
    //
    void asePerspective(aseMatrix4 * result, float fovy, float aspect, float nearZ, float farZ);
    
    //
    /// multiply matrix specified by result with a perspective matrix and return new matrix in result
    /// result Specifies the input matrix.  new matrix is returned in result.
    /// left, right Coordinates for the left and right vertical clipping planes
    /// bottom, top Coordinates for the bottom and top horizontal clipping planes
    /// nearZ, farZ Distances to the near and far depth clipping planes.  These values are negative if plane is behind the viewer
    //
    void aseOrtho(aseMatrix4 * result, float left, float right, float bottom, float top, float nearZ, float farZ);
    
    //
    // multiply matrix specified by result with a perspective matrix and return new matrix in result
    /// result Specifies the input matrix.  new matrix is returned in result.
    /// left, right Coordinates for the left and right vertical clipping planes
    /// bottom, top Coordinates for the bottom and top horizontal clipping planes
    /// nearZ, farZ Distances to the near and far depth clipping planes.  Both distances must be positive.
    //
    void aseFrustum(aseMatrix4 * result, float left, float right, float bottom, float top, float nearZ, float farZ);
    
    void aseLookAt(aseMatrix4 * result, const aseVec3 * eye, const aseVec3 * target, const aseVec3 * up);
    
#ifdef __cplusplus
}
#endif


#endif /* defined(__OpenGLBasic__ASEMatrix__) */
