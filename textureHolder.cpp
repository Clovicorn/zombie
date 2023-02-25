#include "textureHolder.h"
#include <assert.h>

TextureHolder *TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    // Test to see if null
    // quit if not or
    // create singleton
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}
/**
 * @brief Find texture in a map by filename
 * if not there add it and return the texture
 *
 * @param filename
 * @return Texture&
 */
Texture &TextureHolder::getTexture(string const &filename)
{
    auto &m = m_s_Instance->m_Textures;

    auto keyValuePair = m.find(filename);

    if (keyValuePair != m.end())
    {
        return keyValuePair->second;
    }
    else
    {
        auto &texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}