#include "bismuth/glhelper.hpp"
#include <bismuth/framebuffer.hpp>
using namespace bi;

Framebuffer::Framebuffer() {}
Framebuffer::~Framebuffer() {}

void Framebuffer::init(int width, int height) {
    this->texture = std::make_unique<Texture>(width, height);
    this->texture->init();
    fboId = glhelper::createFrameBuffer(texture->textureId);
    this->textureId = texture->textureId;

    unsigned int rboId;
    glGenRenderbuffers(1, &rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        bi::log("Framebuffer Failed to be created");
    }
    else{
        bi::log("Framebuffer sucessfully to be created");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->fboId);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

