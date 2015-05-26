#ifndef TEXTURERENDERPASS_HPP
#define TEXTURERENDERPASS_HPP

#include "renderpass.hpp"
#include "texture.hpp"

class TextureRenderPass : public RenderPass
{
public:
    TextureRenderPass(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

    virtual void render();

private:
    std::shared_ptr<Texture> mTexture;
};

#endif // TEXTURERENDERPASS_HPP
