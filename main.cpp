#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "src/shader.h"
#include "src/stb_image.h"
#include "src/camera.h"
#include "src/model.h"
#include "src/screenshot.h"
#include "class/type.h"
#include "class/block.h"
#include "class/light.h"
#include "class/map.h"
#include "class/skybox.h"
#include "class/box.h"
#include "class/plane.h"
#include <iostream>
#include <vector>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void DrawMap(Shader& blockShader, Block& wall, Block& base, Block& end);
void DrawBox(Shader& blockShader);
void DrawLight(Shader& lightShader, Light& light);
void DrawSkybox(Shader& skyboxShader, SkyBox& skybox);
void DrawPlane(Shader& planeShader, Plane& plane);
void DrawModel(Shader& modelShader, Model& moon, Model& rock);
void DrawBuilding(Shader& blockShader, Block& wall);
unsigned int LoadTexture(char const* path);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(3.0f, 3.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(0.0f, 5.0f, 0.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
// map
LEVEL level = LEVEL1;
Map gameMap(level); // default level


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // mouse callback
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // use glad to load all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);


    Shader blockShader("../shaders/block_shader.vs", "../shaders/block_shader.fs");
    Shader lightShader("../shaders/light_shader.vs", "../shaders/light_shader.fs");
    Shader skyboxShader("../shaders/skybox.vs", "../shaders/skybox.fs");
    Shader planeShader("../shaders/plane.vs", "../shaders/plane.fs");
    Shader modelShader("../shaders/model.vs", "../shaders/model.fs");
    Block wall(WALL);
    Block base(BASE);
    Block end(END);
    Light light;
    SkyBox skybox;
    Plane plane;

    Model rock("../resources/objects/rock/rock.obj");
    Model moon("../resources/objects/planet/planet.obj");
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // frame timing
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glDepthFunc(GL_LESS);

        // input
        processInput(window);

        // render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawLight(lightShader, light);
        DrawMap(blockShader, wall, base, end);
        DrawBuilding(blockShader, wall);
        //DrawBox(blockShader);
        DrawSkybox(skyboxShader, skybox);
        DrawPlane(planeShader, plane);
        DrawModel(modelShader, moon, rock);

        // frame buffer swap
        glfwSwapBuffers(window);

        // events handling
        glfwPollEvents();
    }

    // terminate
    glfwTerminate();

    return 0;
}

// keyboard callback
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera.ProcessKeyboard(ORBIT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        saveScreenshot(window, "a.png");
    }
}

// viewport size callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // viewport size matches the window
    glViewport(0, 0, width, height);
}

// mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// scroll callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void DrawMap(Shader& blockShader, Block& wall, Block& base, Block& end)
{
    glm::mat4 model      = glm::mat4(1.0f);
    glm::mat4 view       = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
    blockShader.use();
    blockShader.setMat4("view", view);
    blockShader.setMat4("projection", projection);
    blockShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    blockShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    blockShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    blockShader.setVec3("light.position", lightPos);
    blockShader.setVec3("viewPos", camera.Position);
    blockShader.setFloat("shininess", 32.0f);
    int map_limit = gameMap.GetLimit();
    for (int i = 0; i != map_limit; ++i)
    {
        for (int j = 0; j != map_limit; ++j)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(i, 0, j));
            blockShader.setMat4("model", model);
//            blockShader.setVec3("objPos", glm::vec3(i, 0, j));
            TYPE type = gameMap.GetType(i, j);
            switch (type)
            {
                case WALL:
                    wall.Draw(blockShader);
                    break;
                default:
                    break;
            }
        }
    }
}

void DrawLight(Shader& lightShader, Light& light)
{
    lightPos = camera.Position + camera.Front + camera.Front + camera.Front + camera.Right;
    lightPos.y = 1.5f;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    lightShader.use();
    lightShader.setVec3("lightColor", lightColor);
    lightShader.setMat4("model", model);
    lightShader.setMat4("view", view);
    lightShader.setMat4("projection", projection);
    light.Draw(lightShader);

}

void DrawSkybox(Shader& skyboxShader, SkyBox& skybox)
{
    glDepthFunc(GL_LEQUAL);
    skyboxShader.use();
    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    skyboxShader.setMat4("view", view);
    skyboxShader.setMat4("projection", projection);
    glBindVertexArray(skybox.VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

//void DrawBox(Shader& blockShader)
//{
//    glm::mat4 model = glm::mat4(1.0f);
//    glm::mat4 view = camera.GetViewMatrix();
//    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
//    blockShader.use();
//    blockShader.setMat4("view", view);
//    blockShader.setMat4("projection", projection);
//    blockShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
//    blockShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
//    blockShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//    blockShader.setVec3("light.position", lightPos);
//    blockShader.setVec3("viewPos", camera.Position);
//    blockShader.setFloat("shininess", 32.0f);
//    for (auto box : boxList)
//    {
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(box.x, box.y, box.z));
//        box.Draw(blockShader);
//    }
//}

void DrawPlane(Shader& planeShader, Plane& plane)
{
    planeShader.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    planeShader.setMat4("model", model);
    planeShader.setMat4("view", view);
    planeShader.setMat4("projection", projection);
    planeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    planeShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    planeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    planeShader.setVec3("light.position", lightPos);
    planeShader.setVec3("viewPos", camera.Position);
    planeShader.setFloat("shininess", 32.0f);
    plane.Draw(planeShader);
}

void DrawModel(Shader& modelShader, Model& moon, Model& rock)
{
    modelShader.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 moonPos = glm::vec3(1.0f);
    const float radius = 100.0f;
    moonPos.x = radius * cos(glfwGetTime() / 10);
    moonPos.y = 50.0f;
    moonPos.z = radius * sin(glfwGetTime() / 10);
    model = glm::translate(model, moonPos);
    glm::mat4 view       = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
    modelShader.setMat4("model", model);
    modelShader.setMat4("view", view);
    modelShader.setMat4("projection", projection);
    modelShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    modelShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    modelShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    modelShader.setVec3("light.position", lightPos);
    modelShader.setVec3("viewPos", camera.Position);
    modelShader.setFloat("shininess", 32.0f);
    moon.Draw(modelShader);
}

void DrawBuilding(Shader& blockShader, Block& wall)
{
    int middle = gameMap.GetLimit() / 2;
    blockShader.use();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    blockShader.use();
    blockShader.setMat4("view", view);
    blockShader.setMat4("projection", projection);
    blockShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    blockShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    blockShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    blockShader.setVec3("light.position", lightPos);
    blockShader.setVec3("viewPos", camera.Position);
    blockShader.setFloat("shininess", 32.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle - 1, -0.25, middle - 1));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle - 1, -0.25, middle + 1));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle + 1, -0.25, middle - 1));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle + 1, -0.25, middle + 1));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 1.0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle - 1, 1.75f, middle - 1));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);


    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle - 0.625, 1.0f, middle - 1.125));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(-5.0f, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle - 0.625, 1.0f, middle + 0.875));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(-5.0f, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0, 0));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle + 0.875, 1.0f, middle - 0.625));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(middle - 1.125, 1.0f, middle - 0.625));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0, 0, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    blockShader.setMat4("model", model);
    wall.Draw(blockShader);
}