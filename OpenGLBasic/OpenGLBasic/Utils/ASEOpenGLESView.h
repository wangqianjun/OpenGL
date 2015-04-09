//
//  ASEOpenGLESView.h
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/9.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>

@interface ASEOpenGLESView : UIView
{
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_context;
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
}

@property (strong, nonatomic) CAEAGLLayer *eaglLayer;


- (void)render;
- (void)cleanup;
@end
