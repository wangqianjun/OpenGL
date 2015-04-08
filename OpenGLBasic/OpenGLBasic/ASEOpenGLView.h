//
//  ASEOpenGLView.h
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/8.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>

@interface ASEOpenGLView : UIView {
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_context;
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
    
    GLuint _programHandle;
    GLuint _positionSlot;
}

@end
