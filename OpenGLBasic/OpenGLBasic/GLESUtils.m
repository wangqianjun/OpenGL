//
//  GLESUtils.m
//  OpenGLBasic
//
//  Created by 王钱钧 on 15/4/7.
//  Copyright (c) 2015年 Arthur. All rights reserved.
//

#import "GLESUtils.h"


@implementation GLESUtils

+ (GLuint)loadShader:(GLenum)type withFilepath:(NSString *)shaderFilePath
{
    NSError *error;
    NSString *shaderString = [NSString stringWithContentsOfFile:shaderFilePath encoding:NSUTF8StringEncoding error:&error];
    if (!shaderString) {
        NSLog(@"Error: loading shader file: %@ %@", shaderFilePath, error.localizedDescription);
    }
    
    return [self loadShader:type withString:shaderString];
}

+ (GLuint)loadShader:(GLenum)type withString:(NSString *)shaderString
{
    /**
     *  创建 shader
     *
     *  @param type  表示我们要处理的 shader 类型 它可以是 GL_VERTEX_SHADER 或 GL_FRAGMENT_SHADER，分别表示顶点 shader 或 片元 shader
     *
     *  @return 它返回一个句柄指向创建好的 shader 对象
     */
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        NSLog(@"Error: failed to create shader.");
        return 0;
    }
    
    // Load the shader source
    const char *shaderStringUTF8 = [shaderString UTF8String];
    
    /**
     *  函数 glShaderSource 用来给指定 shader 提供 shader 源码。
     第一个参数是 shader 对象的句柄；
     第二个参数表示 shader 源码字符串的个数；
     第三个参数是 shader 源码字符串数组；
     第四个参数一个 int 数组，表示每个源码字符串应该取用的长度，如果该参数为 NULL，表示假定源码字符串是 \0 结尾的，读取该字符串的内容指定 \0 为止作为源码，如果该参数不是 NULL，则读取每个源码字符串中前 length（与每个字符串对应的 length）长度个字符作为源码。
     */
    glShaderSource(shader, 1, &shaderStringUTF8, NULL);
    
    // Compile the shader
    /**
     *  函数 glCompileShader 用来编译指定的 shader 对象，这将编译存储在 shader 对象中的源码
     */
    glCompileShader(shader);
    
    // Check the complier status
    GLint compiled = 0;
    
    //我们可以通过函数 glGetShaderiv 来查询 shader 对象的信息，如本例中查询编译情况，此外还可以查询 GL_DELETE_STATUS，GL_INFO_LOG_STATUS，GL_SHADER_SOURCE_LENGTH 和 GL_SHADER_TYPE。
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            NSLog(@"Error compiling shader:\n%s\n", infoLog);
            
            free(infoLog);
        }
        
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
    
}

@end
