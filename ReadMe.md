# OpenGL练习

## 内容

1. BeatifulTriangle：绘制一个彩色三角形
2. HM1Star：绘制一个五角星，中间五边形用黄色填充
3. Rotate_Star：2的基础上，使得五角星绕某一点转动
4. TexturePractice：绘制带有木板纹理的长方体
5. Cube：绘制木板纹理的3D彩色立方体，并设置其绕空间中任意直线旋转
6. Light：实现基础冯氏光照的立方体，带一个光源
7. ModelWithLight：读取3D模型贴图进行显示，设置其绕y轴旋转，带两个静止点光源，可观察光照颜色变化

## 运行环境

Visual Studio 2017

## 依赖库

1. GLFW3：封装渲染和窗口等接口，处理用户输入等
2. GLAD：根据OPENGL驱动版本加载OPENGL函数
3. GLM：为OPENGL编写的矩阵运算库
4. assimp：流行的模型解析库
5. std_image：纹理解析库