/*
 
 顶点着色器接收的输入：
 
 Attributes：由 vertext array 提供的顶点数据，如空间位置，法向量，纹理坐标以及顶点颜色，它是针对每一个顶点的数据。属性只在顶点着色器中才有，片元着色器中没有属性。属性可以理解为针对每一个顶点的输入数据。OpenGL ES 2.0 规定了所有实现应该支持的最大属性个数不能少于 8 个。
 Uniforms：uniforms保存由应用程序传递给着色器的只读常量数据。在顶点着色器中，这些数据通常是变换矩阵，光照参数，颜色等。由 uniform 修饰符修饰的变量属于全局变量，该全局性对顶点着色器与片元着色器均可见，也就是说，这两个着色器如果被连接到同一个应用程序中，它们共享同一份 uniform 全局变量集。因此如果在这两个着色器中都声明了同名的 uniform 变量，要保证这对同名变量完全相同：同名+同类型，因为它们实际是同一个变量。此外，uniform 变量存储在常量存储区，因此限制了 uniform 变量的个数，OpenGL ES 2.0 也规定了所有实现应该支持的最大顶点着色器 uniform 变量个数不能少于 128 个，最大的片元着色器 uniform 变量个数不能少于 16 个。
 Samplers：一种特殊的 uniform，用于呈现纹理。sampler 可用于顶点着色器和片元着色器。
 
 
 
 顶点着色器的输出：
 
 Varying：varying 变量用于存储顶点着色器的输出数据，当然也存储片元着色器的输入数据，varying 变量最终会在光栅化处理阶段被线性插值。顶点着色器如果声明了 varying 变量，它必须被传递到片元着色器中才能进一步传递到下一阶段，因此顶点着色器中声明的 varying 变量都应在片元着色器中重新声明同名同类型的 varying 变量。OpenGL ES 2.0 也规定了所有实现应该支持的最大 varying 变量个数不能少于 8 个。
 
 在顶点着色器阶段至少应输出位置信息-即内建变量：gl_Position，其它两个可选的变量为：gl_FrontFacing 和 gl_PointSize。
 */

//uniform mat4 projection;
//uniform mat4 modelView;
//
//attribute vec4 vPosition;
//
//void main()
//{
////    gl_Position = vPosition;
//    gl_Position = projection * modelView * vPosition;  //左乘，在这里，顶点先进行模型视图变换，然后再进行投影变换
//}


uniform mat4 projection;
uniform mat4 modelView;
attribute vec4 vPosition;

void main(void)
{
    gl_Position = projection * modelView * vPosition;
}