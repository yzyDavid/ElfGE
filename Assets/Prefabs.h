//
// Created by 张程易 on 30/10/2017.
//

#ifndef ELFGE_PREFABS_H
#define ELFGE_PREFABS_H

#include <UI/Image.h>
#include "GameEngine.h"
#include "StandardAssets.h"

namespace Prefabs{

    extern StandardMaterial material;

    class DirLight: public Prefab{
        glm::vec3 rotation;
    public:
        DirLight(const glm::vec3 &rotation) : rotation(rotation) {}

        GameObject * instantiate(Scene *scene) override {
            auto ret = scene->createGameObject()
            ->createComponent<CubeMesh>("brickwall.jpg", "brickwall.jpg", "brickwall_normal.jpg")
            ->createComponent<Renderer>(
                    &material, ShaderManager::getShader("light_with_directional_shadow"))
            ->createComponent<DirectLighting>();
            ret->transform.setRotation(rotation);
            return ret;
        }
    };

    class PointLight: public Prefab{

        glm::vec3 position;
    public:
        PointLight(const glm::vec3 &position) : position(position) {}
        GameObject * instantiate(Scene *scene) override {
            auto result = scene->createGameObject()
                    ->createComponent<PointLighting>();
            result->transform.setPosition(position);
            return result;
        }
    };

    class Cube: public Prefab{
        glm::vec3 position;
    public:
        Cube(const glm::vec3 &position) : position(position) {}
        GameObject * instantiate(Scene *scene) override {

            auto result = scene->createGameObject()
                    ->createComponent<DefaultModel>(new CubeMesh("brickwall.jpg", "brickwall.jpg", "brickwall_normal.jpg"))
                    ->createComponent<Renderer>(
                            &material, ShaderManager::getShader("light_with_directional_shadow"))
                    ->createComponent<AABBCollider>(false)
                    ->createComponent<RigidBody>(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1.0, false);

            result->transform.setPosition(position);
            return result;
        }
    };

    class Camera: public Prefab{
    public:
        GameObject * instantiate(Scene *scene) override {
            auto camera = scene->createGameObject()
                                   ->createComponent<FirstPlayerCamera>();

            scene->setCamera(camera->getComponent<FirstPlayerCamera>());
            return camera;
        }
    };
    class DemoTerrain: public Prefab{
    public:
        GameObject *instantiate(Scene *scene) override {
            auto terrain = scene->createGameObject()
                    ->createComponent<Terrain>("heightMap.png", "brickwall.jpg", "brickwall_normal.jpg")
                    ->createComponent<Renderer>(
                            &material,
                            ShaderManager::getShader("light_with_directional_shadow")
                    );
            return terrain;
        }
    };



    class ImageButton: public Prefab{

        class ImageButtonScript: public Component {
            double xl, xr, yl, yr;
            std::function<void()> * callback, onenter, onexit;
        public:
            ImageButtonScript(double xl, double xr, double yl, double yr, std::function<void()> *callback) : xl(xl),
                                                                                                             xr(xr),
                                                                                                             yl(yl),
                                                                                                             yr(yr),
                                                                                                             callback(
                                                                                                                     callback) {}
            void onEnter(){
                if(callback != nullptr) callback->operator()();
                getGameObject()->transform.setScale(glm::vec3(0.8));
            }

            void onExit(){
                getGameObject()->transform.setScale(glm::vec3(1.0));
            }

            void start() override {
                onenter = std::bind(&ImageButtonScript::onEnter, this);
                onexit = std::bind(&ImageButtonScript::onExit, this);

                Input::attachOnMouseClick(xl, xr, yl, yr, 10,&onenter, &onexit);

                Component::start();
            }

            void destroy() override {
                Input::detachOnMouseClick(callback);
                Component::destroy();
            }
        };
        GameObject * canvas;
        unsigned int image;
        glm::vec2 size;
        glm::vec3 position;
        std::function<void()> * callback;

    public:
        ImageButton(GameObject *canvas, unsigned int image, const glm::vec2 &size, const glm::vec3 &position,
                    std::function<void()> *callback) : canvas(canvas), image(image), size(size), position(position),
                                                       callback(callback) {}

        GameObject *instantiate(Scene *scene) override {
            auto result = scene->createGameObject();
            result->setParent(canvas);
            result->transform.setPosition(position);
            double px = result->transform.getPosition().x;
            double py = result->transform.getPosition().y;
            result->createComponent<Image>( image, size.x, size.y );
            result->createComponent<ImageButtonScript>(
                            px - size.x / 2, px + size.x / 2,
                            py - size.y / 2, py + size.y / 2,
                            callback
                    );
            return result;
        }
    };

};

#endif //ELFGE_PREFABS_H
