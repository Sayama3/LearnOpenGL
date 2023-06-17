//
// Created by ianpo on 17/06/2023.
//

#include "Texture.hpp"
#include "stb_image.h"
#include "Logger.hpp"

Texture::Texture(unsigned int id, TextureUsage textureUsage, std::string path) : m_TextureId(id), type(TextureUsageToName(textureUsage)), path(path), m_CurrentSlot(-1), init(false) {

}

void Texture::Setup(enum TextureFormat format, enum GLType pixelDataType) {
    glGenTextures(1, &m_TextureId);
    init = true;
    glBindTexture(TextureType::TEXTURE_2D, m_TextureId);    // set the texture wrapping/filtering options (on currently bound texture)

    // Set Some default params
    this->SetParam(TextureParameterName::TEXTURE_WRAP_S, TextureWrapping::REPEAT);
    this->SetParam(TextureParameterName::TEXTURE_WRAP_T, TextureWrapping::REPEAT);
    this->SetParam(TextureParameterName::TEXTURE_MIN_FILTER, GL_LINEAR);
    this->SetParam(TextureParameterName::TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    const char* cstr = path.c_str();
    int width;
    int height;
    int nbrChannels;
    unsigned char *data = stbi_load(cstr, &width, &height, &nbrChannels, 0);

    if (data)
    {
        if(format == TextureFormat::NONE)
        {
            switch (nbrChannels) {
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
                default: {
                    format = TextureFormat::RGBA;
                }
            }
        }

        glTexImage2D(TextureType::TEXTURE_2D, 0, format, width, height, 0, format, pixelDataType, data);
        glGenerateMipmap(TextureType::TEXTURE_2D);
    }
    else
    {
        LOG("Failed to load texture \"" + path + "\".\n" + stbi_failure_reason());
    }

    stbi_image_free(data);
    Unbind();

}

void Texture::Delete() {
    glDeleteTextures(1, &m_TextureId);
    init = false;
}

void Texture::SetParam(TextureParameterName name, int value) {
    glTexParameteri(TextureType::TEXTURE_2D, name, value);
}
void Texture::Bind(unsigned int slot) {
    if(slot >= TextureSlot::COUNT) {
        LOG("The maximum texture slot is " + std::to_string(TextureSlot::COUNT - 1) + ". You want the " + std::to_string(slot) + " slot, the result will be unexpected.");
    }
    m_CurrentSlot = static_cast<int>(slot);
    glActiveTexture(TextureSlot::TEXTURE0 + m_CurrentSlot);
    glBindTexture(TextureType::TEXTURE_2D, m_TextureId);
}

void Texture::Unbind() {
    glActiveTexture(TextureSlot::TEXTURE0 + m_CurrentSlot);
    glBindTexture(TextureType::TEXTURE_2D, 0);
    m_CurrentSlot = -1;
}

Texture::~Texture() {
    if(init) Delete();
}
