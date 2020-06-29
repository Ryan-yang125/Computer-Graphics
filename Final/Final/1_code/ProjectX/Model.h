#pragma once
#include "Mesh.h"
#include "TextureManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>
class Model {
public:
    Model(char* path) {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    vector<Mesh> meshes;
    string directory;
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};
