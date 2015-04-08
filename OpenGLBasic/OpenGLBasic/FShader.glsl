/*
 片元管理器接受如下输入：
 
 Varyings：这个在前面已经讲过了，顶点着色器阶段输出的 varying 变量在光栅化阶段被线性插值计算之后输出到片元着色器中作为它的输入，即上图中的 gl_FragCoord，gl_FrontFacing 和 gl_PointCoord。OpenGL ES 2.0 也规定了所有实现应该支持的最大 varying 变量个数不能少于 8 个。
 
 Uniforms：前面也已经讲过，这里是用于片元着色器的常量，如雾化参数，纹理参数等；OpenGL ES 2.0 也规定了所有实现应该支持的最大的片元着色器 uniform 变量个数不能少于 16 个。
 
 Samples：一种特殊的 uniform，用于呈现纹理。
 
 Shader program：由 main 申明的一段程序源码，描述在片元上执行的操作。
 
 在顶点着色器阶段只有唯一的 varying 输出变量-即内建变量：gl_FragColor。
 
 */

precision mediump float;

void main()
{
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}