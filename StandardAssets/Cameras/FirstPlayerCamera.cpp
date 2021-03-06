//
// Created by 张程易 on 30/10/2017.
//

#include "FirstPlayerCamera.h"


void FirstPlayerCamera::update() {
    float cameraSpeed = (float)(2.5f * Utility::deltaTime);
    if (glfwGetKey(Utility::window, GLFW_KEY_W) == GLFW_PRESS)
        getGameObject()->transform.translate(cameraSpeed * getGameObject()->transform.getForward());
    if (glfwGetKey(Utility::window, GLFW_KEY_S) == GLFW_PRESS)
        getGameObject()->transform.translate(-cameraSpeed * getGameObject()->transform.getForward());
    if (glfwGetKey(Utility::window, GLFW_KEY_A) == GLFW_PRESS)
        getGameObject()->transform.translate(-cameraSpeed * getGameObject()->transform.getRight());
    if (glfwGetKey(Utility::window, GLFW_KEY_D) == GLFW_PRESS)
        getGameObject()->transform.translate(cameraSpeed * getGameObject()->transform.getRight());
}

void FirstPlayerCamera::onMouseMove(double xpos, double ypos) {

    Utility::MOUSE_X = xpos;
    Utility::MOUSE_Y = ypos;

    static double lastX = Utility::SCREEN_HEIGHT / 2, lastY = Utility::SCREEN_WIDTH / 2;

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    glm::vec3 rotation = getGameObject()->transform.getRotation();

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    rotation.y -= xoffset;
    rotation.z += yoffset;

    getGameObject()->transform.setRotation(rotation);
}

void FirstPlayerCamera::onScrollMove(double x) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= x;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

