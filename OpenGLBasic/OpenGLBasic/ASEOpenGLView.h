//
//  ASEOpenGLView.h
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/8.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>
#import "aseMatrix.h"

@interface ASEOpenGLView : UIView {
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_context;
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
    
    GLuint _programHandle;
    GLuint _positionSlot;
    GLuint _modelViewSlot;
    GLuint _projectionSlot;
    
    aseMatrix4 _modelViewMatrix; // 模型视图变换
    aseMatrix4 _projectionMatrix;// 投影变换
    
    float _posX;
    float _posY;
    float _posZ;
    
    float _rotateX;
    float _scaleZ;

}


@property (assign, nonatomic) float posX;
@property (nonatomic, assign) float posY;
@property (nonatomic, assign) float posZ;

@property (nonatomic, assign) float scaleZ;
@property (nonatomic, assign) float rotateX;

- (void)resetTransform;
- (void)render;
- (void)cleanup;
- (void)toggleDisplayLink;


@end
