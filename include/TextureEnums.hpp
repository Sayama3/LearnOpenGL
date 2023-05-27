//
// Created by ianpo on 27/05/2023.
//

#ifndef LEARNOPENGL_TEXTUREENUMS_HPP
#define LEARNOPENGL_TEXTUREENUMS_HPP

#include <glad/glad.h>

enum TextureType {
    TEXTURE_1D = GL_TEXTURE_1D,
    TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
    TEXTURE_2D = GL_TEXTURE_2D,
    TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
    TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
    TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    TEXTURE_3D = GL_TEXTURE_3D,
    TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
    TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
    TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE
};

enum TextureParameterName {
    DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
    TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
    TEXTURE_COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
    TEXTURE_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
    TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS,
    TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
    TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
    TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD,
    TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD,
    TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
    TEXTURE_SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
    TEXTURE_SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
    TEXTURE_SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
    TEXTURE_SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
    TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
    TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
    TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R
};

enum TextureWrapping {
    /**
     * The default behavior for textures. Repeats the texture image.
     */
    REPEAT = GL_REPEAT,
    /**
     * Same as REPEAT but mirrors the image with each repeat.
     */
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    /**
     * Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
     */
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    /**
     * Coordinates outside the range are now given a user-specified border color.
     */
    CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
};

enum TextureFormat {
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    RED_INTEGER = GL_RED_INTEGER,
    RG_INTEGER = GL_RG_INTEGER,
    RGB_INTEGER = GL_RGB_INTEGER,
    BGR_INTEGER = GL_BGR_INTEGER,
    RGBA_INTEGER = GL_RGBA_INTEGER,
    BGRA_INTEGER = GL_BGRA_INTEGER,
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL = GL_DEPTH_STENCIL
};

// TODO: Add documentation
enum TextureSlot : unsigned int {
    Texture0 = GL_TEXTURE0,
    Texture1 = GL_TEXTURE1,
    Texture2 = GL_TEXTURE2,
    Texture3 = GL_TEXTURE3,
    Texture4 = GL_TEXTURE4,
    Texture5 = GL_TEXTURE5,
    Texture6 = GL_TEXTURE6,
    Texture7 = GL_TEXTURE7,
    Texture8 = GL_TEXTURE8,
    Texture9 = GL_TEXTURE9,
    Texture10 = GL_TEXTURE10,
    Texture11 = GL_TEXTURE11,
    Texture12 = GL_TEXTURE12,
    Texture13 = GL_TEXTURE13,
    Texture14 = GL_TEXTURE14,
    Texture15 = GL_TEXTURE15,
    Texture16 = GL_TEXTURE16,
    Texture17 = GL_TEXTURE17,
    Texture18 = GL_TEXTURE18,
    Texture19 = GL_TEXTURE19,
    Texture20 = GL_TEXTURE20,
    Texture21 = GL_TEXTURE21,
    Texture22 = GL_TEXTURE22,
    Texture23 = GL_TEXTURE23,
    Texture24 = GL_TEXTURE24,
    Texture25 = GL_TEXTURE25,
    Texture26 = GL_TEXTURE26,
    Texture27 = GL_TEXTURE27,
    Texture28 = GL_TEXTURE28,
    Texture29 = GL_TEXTURE29,
    Texture30 = GL_TEXTURE30,
    Texture31 = GL_TEXTURE31,
    Count = 32,
};

#endif //LEARNOPENGL_TEXTUREENUMS_HPP
