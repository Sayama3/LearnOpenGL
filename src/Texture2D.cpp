//
// Created by ianpo on 27/05/2023.
//

#include "Texture2D.hpp"
#include "stb_image.h"
#include <iostream>

Texture2D::Texture2D(const std::string &path, enum TextureFormat textureFormat, enum GLType pixelDataType) : m_TextureId(), format(textureFormat), m_Width(-1), m_Height(-1), m_NbrChannels(-1) {
    glGenTextures(1, &m_TextureId);
    glBindTexture(TextureType::TEXTURE_2D, m_TextureId);    // set the texture wrapping/filtering options (on currently bound texture)

    // Set Some default params
    SetParam(TextureParameterName::TEXTURE_WRAP_S, TextureWrapping::REPEAT);
    SetParam(TextureParameterName::TEXTURE_WRAP_T, TextureWrapping::REPEAT);
    SetParam(TextureParameterName::TEXTURE_MIN_FILTER, GL_LINEAR);
    SetParam(TextureParameterName::TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    const char* cstr = path.c_str();
    unsigned char *data = stbi_load(cstr, &m_Width, &m_Height, &m_NbrChannels, 0);

    if (data)
    {
        if(format == TextureFormat::NONE)
        {
            switch (m_NbrChannels) {
                case 1: {
                    format = TextureFormat::RED;
                    break;
                }
                case 2: {
                    format = TextureFormat::RG;
                    break;
                }
                case 3: {
                    format = TextureFormat::RGB;
                    break;
                }
                case 4: {
                    format = TextureFormat::RGBA;
                    break;
                }
            }
        }

        glTexImage2D(TextureType::TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, pixelDataType, data);
        glGenerateMipmap(TextureType::TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture\"" << path << "\"." << std::endl;
    }

    stbi_image_free(data);
    Unbind();
}

Texture2D::Texture2D(glm::vec4 color): m_TextureId(), format(TextureFormat::RGBA), m_Width(1), m_Height(1), m_NbrChannels(4) {
    glGenTextures(1, &m_TextureId);
    glBindTexture(TextureType::TEXTURE_2D, m_TextureId);    // set the texture wrapping/filtering options (on currently bound texture)

    // Set Some default params
    SetParam(TextureParameterName::TEXTURE_WRAP_S, TextureWrapping::REPEAT);
    SetParam(TextureParameterName::TEXTURE_WRAP_T, TextureWrapping::REPEAT);
    SetParam(TextureParameterName::TEXTURE_MIN_FILTER, GL_LINEAR);
    SetParam(TextureParameterName::TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char data[4] = {
            static_cast<unsigned char>(glm::clamp(color.r, 0.0f, 1.0f) * 255),
            static_cast<unsigned char>(glm::clamp(color.g, 0.0f, 1.0f) * 255),
            static_cast<unsigned char>(glm::clamp(color.b, 0.0f, 1.0f) * 255),
            static_cast<unsigned char>(glm::clamp(color.a, 0.0f, 1.0f) * 255),
    };
    glTexImage2D(TextureType::TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GLType::UNSIGNED_BYTE, data);
    glGenerateMipmap(TextureType::TEXTURE_2D);

    Unbind();
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_TextureId);
}

void Texture2D::Bind(unsigned int slot) {
    if(slot >= TextureSlot::COUNT) {
        std::cout << "The maximum texture slot is " << TextureSlot::COUNT - 1 << ". You want the " << slot << " slot, the result will be unexpected." << std::endl;
    }
    glActiveTexture(TextureSlot::TEXTURE0 + slot);
    glBindTexture(TextureType::TEXTURE_2D, m_TextureId);
}

void Texture2D::Unbind() {
    glBindTexture(TextureType::TEXTURE_2D, 0);
}
/**
 * Must bind the texture before changing it's param.
 * @param name The name of the parameter.
 * @param value The value of the parameter.
 */
void Texture2D::SetParam(TextureParameterName name, int value) {
    glTexParameteri(TextureType::TEXTURE_2D, name, value);
}
