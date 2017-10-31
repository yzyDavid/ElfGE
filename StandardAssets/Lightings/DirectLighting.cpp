//
// Created by 张程易 on 31/10/2017.
//

#include "DirectLighting.h"

std::string DirectLighting::getName() {
    return "dirLight";
}

void DirectLighting::update(const std::string &prefix, Shader *shader) {
    shader->setVec3("dirLight.direction", getGameObject()->transform.getForward());
    shader->setVec3("dirLight.ambient", ambient);
    shader->setVec3("dirLight.diffuse", diffuse);
    shader->setVec3("dirLight.specular", specular);
}

DirectLighting::DirectLighting(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular) : ambient(
        ambient), diffuse(diffuse), specular(specular) {}
