#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
/*检测是否按下了Esc键，按下后窗口关闭，结束程序*/
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// 主版本号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 次版本号为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// CORE模式, OPENGL3.3

    GLFWwindow* window = glfwCreateWindow(800, 800, "Star", NULL, NULL);// 宽高以及窗口名称
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);// 上下文设置为当前线程主上下文
    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 设置渲染窗口的左下角位置以及宽高
    glViewport(0, 0, 800, 800);
    // 每次窗口大小改变时的回调函数注册
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 创建和编译顶点和片段着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 检测编译成功与否
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // 片段着色器同理
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // 第二个片段着色器来绘制中间的黄色五边形
    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // 链接两个着色器
    unsigned int shaderProgram, shaderProgram2;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // 检测链接成功与否
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // 链接成功后删除两个着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    // 图形顶点数据
    // 五角星r = 0.8
    float r = 0.8;
    float pi = 3.1415926;
    float x = 0.8*sin(18.0 / 180 * pi) / sin(126.0 / 180 * pi);
    float vertices[] = {
        float(-r * cos(18.0 / 180 * pi)), float(r * sin(18.0 / 180 * pi)), 0.0f,
        float(r * cos(18.0 / 180 * pi)), float(r * sin(18.0 / 180 * pi)), 0.0f,
        float(-r * cos(54.0 / 180 * pi)), float(-r * sin(54.0 / 180 * pi)), 0.0f,
        0.0f, r, 0.0f,
        float(r * cos(54.0 / 180 * pi)), float(-r * sin(54.0 / 180 * pi)), 0.0f,
    };
    // 中间的五边形顶点数据
    float middle[] = {
        x * sin(36.0 / 180 * pi), x * cos(36.0 / 180 * pi), 0.0f,
        x * cos(18.0 / 180 * pi), -x * sin(18.0 / 180 * pi), 0.0f,
        0.0f, -x, 0.0f,
        -x * cos(18.0 / 180 * pi), -x * sin(18.0 / 180 * pi), 0.0f,
        -x * sin(36.0 / 180 * pi), x * cos(36.0 / 180 * pi), 0.0f,
    };
    // 绘制五边形的索引对象
    unsigned int indices[] = { 0,1,2,2,3,4,4,0,2 };
    // 两个顶点数组分别绘制五角星边框和黄色的五边形
    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 中间绘制五边形使用索引，三个三角形构成
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(middle), middle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);// 输入检测, 检测是否要关闭窗口
        // 渲染指令......

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// 设置清空屏幕所用颜色(状态设置)
        glClear(GL_COLOR_BUFFER_BIT);// 清空颜色缓冲(状态使用)

        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_LINE_LOOP, 0, 5);

        glfwSwapBuffers(window);// 交换颜色缓冲
        glfwPollEvents();// 事件回调
    }
    // 退出渲染后，释放资源
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glfwTerminate();
    return 0;
}