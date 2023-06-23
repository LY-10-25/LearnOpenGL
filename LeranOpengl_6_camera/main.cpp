#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include <direct.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "camera.h"
std::string current_working_directory()
{
    char buff[250];
    _getcwd(buff, 250);
    std::string current_working_directory(buff);
    return current_working_directory;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;


//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


float offset = 0;
int screenWidth = 800;
int screenHeight = 600;
float x = 0;
float y = 0;
float z = -3;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间


Camera camera;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("./shader.vs", "./shader.fs");
    std::cout << "Current working directory: " << current_working_directory() << std::endl;
    unsigned int VAO, VBO,EBO;
    //创建
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //复制数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 0.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char* data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width1, height1, nrChannels1;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data1 = stbi_load("./awesomeface.png", &width1, &height1, &nrChannels1, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data1);

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);
    offset = 0.5;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    //// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
    //// 下面这行代码就需要改为:
    //glm::mat4 trans = glm::mat4(1.0f);
    //// 之后将不再进行提示
    ////glm::mat4 trans;
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    //vec = trans * vec;
    //std::cout << vec.x << vec.y << vec.z << std::endl;


    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    glm::mat4 trans = glm::mat4(1.0f);
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    //trans = glm::rotate(trans, glm::radians(450.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    int i=0;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));



    glm::mat4 view = glm::mat4(1.0f);
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // 使用 glm::to_string 将矩阵转换为字符串
    std::string matrixString = glm::to_string(view);

    // 输出矩阵的字符串表示
    std::cout << matrixString << std::endl;
    //    glm::vec3(0.0f, 0.0f, 0.0f),
    //    glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective<float>(glm::radians(45.0f), (float)(screenWidth / screenHeight), 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int modelLoc1 = glGetUniformLocation(ourShader.ID, "view");
    glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(view));

    int modelLoc2 = glGetUniformLocation(ourShader.ID, "projection");
    glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 

        float time = (float)glfwGetTime();
        //std::cout << "time = " << time << std::endl;
        //if (i > 1000)
        //{

        //    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //    i = 0;
        //}
        //i++;

        //ourShader.use();
        ourShader.setFloat("mix", offset);
        glBindVertexArray(VAO);


        //trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //if (i > 500)
        //{
        //    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //    i = 0;
        //}
        //i++;
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        ////float move = static_cast<float>(sin(glfwGetTime()));
        ////float move1 = static_cast<float>(cos(glfwGetTime()));
        //trans = glm::mat4(1.0f);
        ////trans = glm::translate(trans, glm::vec3(move, move1/2/3, 0.0f));
        //trans = glm::translate(trans, glm::vec3(0.0f,0.0f, 0.0f));
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); // this time take the matrix value array's first element as its memory pointer value
        ////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);


        //view = glm::mat4(1.0f);
        //view = glm::translate(view, glm::vec3(x, y, z));
        //modelLoc1 = glGetUniformLocation(ourShader.ID, "view");
        //glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(view));


        //float radius = 20.0f;
        //float camX = sin(glfwGetTime()) * radius;
        //float camZ = cos(glfwGetTime()) * radius;
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ) + glm::vec3(1.5f, 0.2f, -1.5f), glm::vec3(1.5f, 0.2f, -1.5f), glm::vec3(0.0, 1.0, 0.0));
        //modelLoc1 = glGetUniformLocation(ourShader.ID, "view");
        //glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(view));
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
        int modelLoc2 = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(projection));


        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        modelLoc1 = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

        //// 使用 glm::to_string 将矩阵转换为字符串
        //std::string matrixString = glm::to_string(view);

        //// 输出矩阵的字符串表示
        //std::cout << matrixString << std::endl;
        for (unsigned int i = 0; i < 10; i++)
        {
            if (((i %3) == 0) || (i == 0))
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, (float)glfwGetTime() , glm::vec3(1.0f, 0.3f, 0.5f));
                ourShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
                continue;
            }
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 10.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    //static bool flag = 1;
    //static bool flagZ = 1;
    //if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)&& flag)
    //{
    //    flag = 0;
    //    offset += 0.1f;
    //    if (offset >= 1.0)
    //        offset = 1.0;
    //    std::cout << "GLFW_KEY_ENTER is press" << std::endl;
    //    //glfwSetWindowShouldClose(window, true);
    //}
    //if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) && (flag ==0))
    //{
    //    flag = 1;
    //    //glfwSetWindowShouldClose(window, true);
    //}

    //static bool flag1 = 1;
    //if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) && flag1)
    //{
    //    flag1 = 0;
    //    offset -= 0.1f;
    //    if (offset <= 0)
    //        offset = 0;
    //    std::cout << "GLFW_KEY_ENTER is press" << std::endl;
    //    //glfwSetWindowShouldClose(window, true);
    //}
    //if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) && (flag1 == 0))
    //{
    //    flag1 = 1;
    //    //glfwSetWindowShouldClose(window, true);
    //}
    //


    //static bool flagX = 1;
    //if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) && flagX)
    //{
    //    flagX = 0;
    //    x += 0.5f;
    //    if (x >= 10)
    //        x = 0;
    //    std::cout << "GLFW_KEY_ENTER is press" << std::endl;
    //    //glfwSetWindowShouldClose(window, true);
    //}
    //if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) && (flagX == 0))
    //{
    //    flagX = 1;
    //    //glfwSetWindowShouldClose(window, true);
    //}


    //if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) && flagZ)
    //{
    //    flagZ = 0;
    //    z -= 0.1f;
    //    if (z <= (-10))
    //        z = 1;
    //    std::cout << "GLFW_KEY_ENTER is press" << std::endl;
    //    //glfwSetWindowShouldClose(window, true);
    //}
    //if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE) && (flagZ == 0))
    //{
    //    flagZ = 1;
    //    //glfwSetWindowShouldClose(window, true);
    //}
    float cameraSpeed = 10.0f * deltaTime;
    //float cameraSpeed = 0.05f; // adjust accordingly
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //    cameraPos += cameraSpeed * cameraFront;
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    cameraPos -= cameraSpeed * cameraFront;
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);


}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    //if (firstMouse)
    //{
    //    lastX = xpos;
    //    lastY = ypos;
    //    firstMouse = false;
    //}
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    std::cout << "xpos = " << xpos<<std::endl;
    std::cout << "ypos = " << ypos << std::endl;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset*2;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}