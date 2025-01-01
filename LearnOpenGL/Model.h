#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "stb_image.h"
#include <string>

#include "Shader.h"
#include "Mesh.h"

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
    Model(string path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);
private:
    // model data
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;
    bool gammaCorrection;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
};

