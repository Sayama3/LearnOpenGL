//
// Created by ianpo on 27/05/2023.
//

#ifndef LEARNOPENGL_TEXTURE2D_HPP
#define LEARNOPENGL_TEXTURE2D_HPP

#include <string>
#include "glad/glad.h"
#include "TextureEnums.hpp"
#include "OpenGLType.hpp"
#include "glm/glm.hpp"

class Texture2D {
private:
    unsigned int m_TextureId;
    enum TextureFormat format;
    int m_Width;
    int m_Height;
    int m_NbrChannels;
public:
    /**
     * Constructor for the type Texture2D
     * @param path The path of the texture.
     * @param textureFormat The format of the texture (i.e. RGB, RGBA..). NONE = auto
     * @param pixelDataType The type of pixel (i.e. Byte, Short...). default = UNSIGNED_BYTE
     */
    Texture2D(const std::string & path, enum TextureFormat textureFormat = TextureFormat::NONE, enum GLType pixelDataType = GLType::UNSIGNED_BYTE);

    /**
     * Constructor a 1x1 2D texture with just a color.
     * @param color The color of the sole pixel.
     */
    Texture2D(glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
    ~Texture2D();

    void Bind(unsigned int slot = 0);
    void Unbind();

    void SetParam(TextureParameterName name, int value);
};


#endif //LEARNOPENGL_TEXTURE2D_HPP
