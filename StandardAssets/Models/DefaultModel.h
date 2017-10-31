//
// Created by 张程易 on 29/10/2017.
//

#ifndef ELFGE_DEFAULTMODEL_H
#define ELFGE_DEFAULTMODEL_H

#include "../../GameEngine/Common.h"
#include "../../GameEngine/Components/Model.h"
#include "../Meshs/DefaultMesh.h"

class DefaultModel: public Model {

    std::string directory;

public:

    std::vector<DefaultMesh *> meshes;

    DefaultModel(DefaultMesh * mesh){
        meshes.emplace_back(mesh);
    }

    DefaultModel(const std::string & path){
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

    void render(Shader *shader) override {
        for(auto & x: meshes){
            x->render(shader);
        }
    }

    void start() override;

    void update() override;

    void destroy() override;

    virtual ~DefaultModel();

private:
    void processNode(aiNode *node, const aiScene *scene){
        for(unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.emplace_back(new DefaultMesh(mesh, scene, directory));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

};


#endif //ELFGE_DEFAULTMODEL_H