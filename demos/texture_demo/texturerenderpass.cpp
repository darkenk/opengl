#include "texturerenderpass.hpp"

TextureRenderPass::TextureRenderPass(std::shared_ptr<Shader> shader,
                                     std::shared_ptr<Texture> texture) :
    RenderPass(shader, RenderPass::USER), mTexture{texture}
{
}

void TextureRenderPass::render()
{
    mTexture->bind(GL_TEXTURE0);
    RenderPass::render();
}
