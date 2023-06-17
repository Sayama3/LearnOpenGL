//
// Created by ianpo on 17/06/2023.
//

#ifndef LEARNOPENGL_TEXTURE_HPP
#define LEARNOPENGL_TEXTURE_HPP

#include <string>
#include "TextureEnums.hpp"
#include "OpenGLType.hpp"

class Texture {
private:
    unsigned int m_TextureId;
    std::string type;
    std::string path; // store path of texture to compare with other textures
    int m_CurrentSlot;
    bool init;
public:
    Texture(unsigned int id, TextureUsage textureUsage, std::string path);
    ~Texture();
    void Setup(enum TextureFormat format = TextureFormat::NONE, enum GLType pixelDataType = GLType::UNSIGNED_BYTE);
    void Delete();
    void Bind(unsigned int slot = 0);
    void Unbind();

    void SetParam(TextureParameterName name, int value);
};


#endif //LEARNOPENGL_TEXTURE_HPP
