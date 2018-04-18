#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// ���ڴ�С�仯�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// ѭ���м�ⰴ��Esc�������˳�
void processInput(GLFWwindow *window);
// ����һϵ�г�ʼ�������ķ�װ
GLFWwindow* WindowInit(const unsigned int width, const unsigned int height, const char *name);
// �������������תtheta�Ƕȵ���ת����ĺ�����thetaΪ����(�ǻ�����)��p1��p2����Ϊ��ת��
glm::mat4 GetRotateMatrix(glm::vec3 p1, glm::vec3 p2, float theta);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

int main()
{
    auto window = WindowInit(SCR_WIDTH, SCR_HEIGHT, "Cube");
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    // ��ɫ����ʼ��
    Shader myShader("vShader.txt", "fShader.txt");
    // �����嶥������
    float vertices[] = {
        //---λ��-----------|----��������--|---��ɫ----------
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // color attrib
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // ����ľ������
    unsigned int texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    // ���û��Ʒ�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // ���ز���������
    int height, width, nrChannels;// ͼ��Ŀ�ߺ���ɫͨ����
    stbi_set_flip_vertically_on_load(true);// ����stb�����ͼ��y�᷽��
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);// Ϊ��ǰ�󶨵���������Զ�����������Ҫ�Ķ༶��Զ����
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    myShader.use();
    myShader.setInt("texture0", 0);
    // �۲����Ͳü�ͶӰ���󲻱仯����������涨��
    glm::mat4 viewMatrix(1.0f), perspectiveMatrix(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
    perspectiveMatrix = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
    myShader.setMat4("view", viewMatrix);
    myShader.setMat4("perspective", perspectiveMatrix);
    // ������ȼ��
    glEnable(GL_DEPTH_TEST);
    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // ����������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        myShader.use();

        // ������ʵʱ����ת��������ڲ�����ģ�;��������ת��������ת��������(1.0,0,0)��(0,1.0,1.0)������
        glm::mat4 modelMatrix(1.0f);
        modelMatrix = GetRotateMatrix(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, -1.0), 50.0*float(glfwGetTime()));
        myShader.setMat4("model", modelMatrix);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* WindowInit(const unsigned int width, const unsigned int height, const char *name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    return window;
}

glm::mat4 GetRotateMatrix(glm::vec3 p1, glm::vec3 p2, float theta)
{
    glm::mat4 trans1(1.0f), trans2(1.0f), rot(1.0f), rev_trans1(1.0f), rev_trans2(1.0f);
    trans1 = glm::translate(trans1, -p1);// ��ת��ƽ��������ԭ��
    rev_trans1 = glm::translate(rev_trans1, p1);
    glm::vec3 cur_p2 = p2 - p1;
    if (abs(cur_p2.z - 0.0f) > 1e-5)
    {
        float ang = 0.0f;
        if (abs(cur_p2.y - 0.0f) < 1e-5) // cur_p2.y == 0
            ang = glm::radians(90.0f);
        else
            ang = atan(abs(cur_p2.z / cur_p2.y));
        if (cur_p2.y > 0 && cur_p2.z < 0 || cur_p2.y < 0 && cur_p2.z>0)
        {
            trans2 = glm::rotate(trans2, ang, glm::vec3(1.0f, 0.0f, 0.0f));// ��ת����x��ת��xyƽ��
            rev_trans2 = glm::rotate(rev_trans2, -ang, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else
        {
            trans2 = glm::rotate(trans2, -ang, glm::vec3(1.0f, 0.0f, 0.0f));
            rev_trans2 = glm::rotate(rev_trans2, ang, glm::vec3(1.0f, 0.0f, 0.0f));
        }
    }
    glm::vec4 tmp = trans2 * glm::vec4(cur_p2, 1.0f);
    cur_p2 = glm::vec3(tmp.x, tmp.y, tmp.z);
    rot = glm::rotate(rot, glm::radians(theta), cur_p2);
    return rev_trans2 * rev_trans1 * rot * trans2 * trans1;
}