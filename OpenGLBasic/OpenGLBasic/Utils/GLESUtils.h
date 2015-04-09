//
//  GLESUtils.h
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/7.
//  Copyright (c) 2015年 Arthur. All rights reserved.

/*
 辅助类 GLESUtils 中有两个类方法用来跟进 shader 脚本字符串或 shader 脚本文件创建 shader，然后装载它，编译它
 */



#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>

@interface GLESUtils : NSObject

+ (GLuint)loadShader:(GLenum)type withString:(NSString *)shaderString;

+ (GLuint)loadShader:(GLenum)type withFilepath:(NSString *)shaderFilePath;

+(GLuint)loadProgram:(NSString *)vertexShaderFilepath withFragmentShaderFilepath:(NSString *)fragmentShaderFilepath;
@end
