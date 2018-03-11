#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
/*����Ƿ�����Esc�������º󴰿ڹرգ���������*/
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// ���汾��Ϊ3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// �ΰ汾��Ϊ3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// COREģʽ, OPENGL3.3

    GLFWwindow* window = glfwCreateWindow(800, 800, "Star", NULL, NULL);// ����Լ���������
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);// ����������Ϊ��ǰ�߳���������
    // ��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // ������Ⱦ���ڵ����½�λ���Լ����
    glViewport(0, 0, 800, 800);
    // ÿ�δ��ڴ�С�ı�ʱ�Ļص�����ע��
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // �����ͱ��붥���Ƭ����ɫ��
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // ������ɹ����
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Ƭ����ɫ��ͬ��
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
    // �ڶ���Ƭ����ɫ���������м�Ļ�ɫ�����
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
    // ����������ɫ��
    unsigned int shaderProgram, shaderProgram2;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // ������ӳɹ����
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
    // ���ӳɹ���ɾ��������ɫ��
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    // ͼ�ζ�������
    // �����r = 0.8
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
    // �м������ζ�������
    float middle[] = {
        x * sin(36.0 / 180 * pi), x * cos(36.0 / 180 * pi), 0.0f,
        x * cos(18.0 / 180 * pi), -x * sin(18.0 / 180 * pi), 0.0f,
        0.0f, -x, 0.0f,
        -x * cos(18.0 / 180 * pi), -x * sin(18.0 / 180 * pi), 0.0f,
        -x * sin(36.0 / 180 * pi), x * cos(36.0 / 180 * pi), 0.0f,
    };
    // ��������ε���������
    unsigned int indices[] = { 0,1,2,2,3,4,4,0,2 };
    // ������������ֱ��������Ǳ߿�ͻ�ɫ�������
    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // �м���������ʹ�����������������ι���
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(middle), middle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);// ������, ����Ƿ�Ҫ�رմ���
        // ��Ⱦָ��......

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// ���������Ļ������ɫ(״̬����)
        glClear(GL_COLOR_BUFFER_BIT);// �����ɫ����(״̬ʹ��)

        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_LINE_LOOP, 0, 5);

        glfwSwapBuffers(window);// ������ɫ����
        glfwPollEvents();// �¼��ص�
    }
    // �˳���Ⱦ���ͷ���Դ
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glfwTerminate();
    return 0;
}