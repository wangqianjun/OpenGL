////
////  ASEOpenGLView.m
////  OpenGLBasic
////
////  Created by 王钱钧 on 15/4/8.
////  Copyright (c) 2015年 Arthur. All rights reserved.
//
///**
// *  创建 program，装配 shader，链接 program，使用 program
// */
//

//
//  OpenGLView.m
//  Tutorial01
//
//  Created by kesalin on 12-11-24.
//  Copyright (c) 2012年 Created by kesalin@gmail.com on. All rights reserved.
//

#import "ASEOpenGLView.h"
#import "GLESUtils.h"


// 使用匿名 category 来声明私有成员
@interface ASEOpenGLView()
{
    CADisplayLink * _displayLink;
}



- (void)setupProgram;
- (void)setupProjection;

- (void)updateTransform;
- (void)displayLinkCallback:(CADisplayLink*)displayLink;

@end

@implementation ASEOpenGLView
@synthesize posX = _posX;
@synthesize posY = _posY;
@synthesize posZ = _posZ;
@synthesize scaleZ = _scaleZ;
@synthesize rotateX = _rotateX;


- (void)cleanup
{
    [super cleanup];
    
    if (_programHandle != 0) {
        glDeleteProgram(_programHandle);
        _programHandle = 0;
    }
    
    if (_context && [EAGLContext currentContext] == _context)
        [EAGLContext setCurrentContext:nil];
    
    _context = nil;
}

- (void)setupProgram
{
    // Load shaders
    NSString *vertexShaserPath = [[NSBundle mainBundle]pathForResource:@"VShader" ofType:@"glsl"];
    NSString *fragmentShaderPath = [[NSBundle mainBundle]pathForResource:@"FShader" ofType:@"glsl"];
    GLuint vertexShader = [GLESUtils loadShader:GL_VERTEX_SHADER withFilepath:vertexShaserPath];
    GLuint fragmentShader = [GLESUtils loadShader:GL_FRAGMENT_SHADER withFilepath:fragmentShaderPath];
    
    // Create program, attach shaders
    _programHandle = glCreateProgram();
    
    if (!_programHandle) {
        NSLog(@"Failed to create program");
        return;
    }
    
    //将顶点 shader 和片元 shader 装配到 program 对象中
    glAttachShader(_programHandle, vertexShader);
    glAttachShader(_programHandle, fragmentShader);
    
    
    // Link program
    //再使用 glLinkProgram 将装配的 shader 链接起来，这样两个 shader 就可以合作干活了
    glLinkProgram(_programHandle);
    
    
    //链接过程会对 shader 进行可链接性检查,也就是前面说到同名变量必须同名同型以及变量个数不能超出范围等检查
    GLint linked;
    glGetProgramiv(_programHandle, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(_programHandle, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(_programHandle, infoLen, NULL, infoLog);
            NSLog(@"Error linking program:\n%s\n", infoLog);
            
            free(infoLog);
        }
        
        glDeleteProgram(_programHandle);
        _programHandle = 0;
        return;
    }
    
    
    //如果一切正确，那我们就可以调用 glUseProgram 激活 program 对象从而在 render 中使用它
    glUseProgram(_programHandle);
    
    // Get attribute slot from program
    //通过调用 glGetAttribLocation 我们获取到 shader 中定义的变量 vPosition 在 program 的槽位，通过该槽位我们就可以对 vPosition 进行操作
    _positionSlot = glGetAttribLocation(_programHandle, "vPosition");
    
    _modelViewSlot = glGetUniformLocation(_programHandle, "modelView");
    
    _projectionSlot = glGetUniformLocation(_programHandle, "projection");
}

- (void)setupProjection
{
    float aspect = self.frame.size.width / self.frame.size.height;
    aseMatrixLoadIdentity(&_projectionMatrix);
    
    /**
     *  gluPerspective(fovy, aspect, zNear, zFar);
     
     fovy 定义了 camera 在 y 方向上的视线角度（介于 0 ~ 180 之间），aspect 定义了近裁剪面的宽高比 aspect = w/h，而 zNear 和 zFar 定义了从 Camera/Viewer 到远近两个裁剪面的距离（注意这两个距离都是正值）。这四个参数同样也定义了一个视锥体。
     */
    asePerspective(&_projectionMatrix, 60.0, aspect, 1.0, 20.0);
    
    // Load projection matrix
    glUniformMatrix4fv(_projectionSlot, 1, GL_FALSE, (GLfloat *)&_projectionMatrix.m[0][0]);
    
}

- (void)updateTransform
{
    aseMatrixLoadIdentity(&_modelViewMatrix);
    
    aseMatrixTranslate(&_modelViewMatrix, self.posX,self.posY, self.posZ);
    
    aseMatrixRotate(&_modelViewMatrix, self.rotateX, 1.0, 0.0, 0.0);
    
    aseMatrixScale(&_modelViewMatrix, 1.0, 1.0, self.scaleZ);
    
    glUniformMatrix4fv(_modelViewSlot, 1, GL_FALSE, (GLfloat*)&_modelViewMatrix.m[0][0]);
    
}

- (void)drawTriangle
{
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f,  -0.5f, 0.0f
    };
    
    // Load the vertex data
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, 0, GL_FALSE, vertices);
    glEnableVertexAttribArray(_positionSlot);
    
    // Dra triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
}

// 画四棱锥
- (void)drawTriCone
{
    // http://www.cnblogs.com/kesalin/archive/2012/12/07/3D_transform.html
    
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.0f, -0.707f,
    };
    
    GLubyte indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 0, 4, 1, 4, 2, 4, 3
    };
    
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(_positionSlot);
    
    
    /**
     *  这次我们使用顶点索引数组结合 glDrawElements 来渲染,相比 glDrawArrays 我们可以减少存储重复顶点的内存消耗。比如在本例的索引表中，我们重复利用了顶点 0，1，2，3，4，它们对应 vertices 数组中5个顶点（三个浮点数组成一个顶点）。
     *
     *  @param GL_LINES 为描绘图元的模式
     *  @param count  为顶点索引的个数
     *  @param type  指顶点索引的数据类型
     *  @param indices 存放顶点索引的数组
     */
    glDrawElements(GL_LINES, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
}

#pragma mark - 绘制

- (void)render
{
    [super render];
    [self drawTriCone];
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
    
    
}


#pragma mark - lifecycle
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupProgram];
        [self setupProjection];
        
        [self resetTransform];
    }
    
    return self;
}


- (void)layoutSubviews
{
    
    [super layoutSubviews];
    
    glUseProgram(_programHandle);

    [self updateTransform];

    [self render];
}

#pragma mark - Transform properties

- (void)toggleDisplayLink
{
    if (_displayLink == nil) {
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(displayLinkCallback:)];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    else {
        [_displayLink invalidate];
        [_displayLink removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        _displayLink = nil;
    }
}

- (void)displayLinkCallback:(CADisplayLink*)displayLink
{
    self.rotateX += displayLink.duration * 90;
}

- (void)resetTransform
{
    if (_displayLink != nil) {
        [_displayLink removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        _displayLink = nil;
    }
    
    _posX = 0.0;
    _posY = 0.0;
    _posZ = -5.5;
    
    _scaleZ = 1.0;
    _rotateX = 0.0;
    
    [self updateTransform];
}

- (void)setPosX:(float)x
{
    _posX = x;
    
    [self updateTransform];
    [self render];
}

- (float)posX
{
    return _posX;
}

- (void)setPosY:(float)y
{
    _posY = y;
    
    [self updateTransform];
    [self render];
}

- (float)posY
{
    return _posY;
}

- (void)setPosZ:(float)z
{
    _posZ = z;
    
    [self updateTransform];
    [self render];
}

- (float)posZ
{
    return _posZ;
}

- (void)setScaleZ:(float)scaleZ
{
    _scaleZ = scaleZ;
    
    [self updateTransform];
    [self render];
}

- (float)scaleZ
{
    return _scaleZ;
}

- (void)setRotateX:(float)rotateX
{
    _rotateX = rotateX;
    
    [self updateTransform];
    [self render];
}

- (float)rotateX
{
    return _rotateX;
}


@end