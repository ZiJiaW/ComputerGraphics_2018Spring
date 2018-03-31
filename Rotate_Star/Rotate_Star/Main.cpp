#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* WindowInit(const unsigned int width, const unsigned int height, const char *name);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    GLFWwindow* window = WindowInit(SCR_WIDTH, SCR_HEIGHT, "Texture");
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    Shader myShader("vShader.txt", "fShader.txt");
    // 准备五角星顶点数据和颜色数据
    float r = 0.33;
    float pi = 3.1415926;
    float x = r*sin(18.0 / 180 * pi) / sin(126.0 / 180 * pi);
    float vertices1[] = {
        //  -------五角星顶点坐标  --------------------------------  ----颜色(黑)-----   
        -r * cos(18.0 / 180 * pi), r * sin(18.0 / 180 * pi), 0.0f, 0.0f, 0.0f, 0.0f,
        r * cos(18.0 / 180 * pi), r * sin(18.0 / 180 * pi), 0.0f, 0.0f, 0.0f, 0.0f,
        -r * cos(54.0 / 180 * pi), -r * sin(54.0 / 180 * pi), 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, r, 0.0f, 0.0f, 0.0f, 0.0f,
        r * cos(54.0 / 180 * pi), -r * sin(54.0 / 180 * pi), 0.0f, 0.0f, 0.0f, 0.0f
    };
    float vertices2[] = {
        // ----------五边形顶点坐标------------------------------  ----颜色(黄)-----
        x * sin(36.0 / 180 * pi), x * cos(36.0 / 180 * pi), 0.0f, 1.0f, 1.0f, 0.0f,
        x * cos(18.0 / 180 * pi), -x * sin(18.0 / 180 * pi), 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, -x, 0.0f, 1.0f, 1.0f, 0.0f,
        -x * cos(18.0 / 180 * pi), -x * sin(18.0 / 180 * pi), 0.0f, 1.0f, 1.0f, 0.0f,
        -x * sin(36.0 / 180 * pi), x * cos(36.0 / 180 * pi), 0.0f, 1.0f, 1.0f, 0.0f
    };
    unsigned int indices[] = { 0,1,2,2,3,4,4,0,2 };// 用索引绘制五边形
    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        myShader.use();
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, r, 0.0f));
        trans = glm::rotate(trans, float(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.0f, -r, -0.0f));
        myShader.setMat4("transform", trans);

        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_LINE_LOOP, 0, 5);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, &EBO);
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