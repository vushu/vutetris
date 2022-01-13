#include <bismuth/iomanager.hpp>
#include <bismuth/particleemitter.hpp>
#include <bismuth/renderer.hpp>
using namespace bi;

ParticleEmitter::~ParticleEmitter()
{
    bi::log("ParticleEmitter destroyed");
}

void ParticleEmitter::init(float lifeTime)
{
    this->life = lifeTime;
    for (unsigned int i = 0; i < nr_particles; ++i) {
        Particle p(0.0f);
        particles.push_back(std::move(p));
    }
}

void ParticleEmitter::emit(float dt, glm::vec2 position, glm::vec2 velocity, glm::vec2 offset, glm::vec4 color, int textureId, int tileNumber, glm::vec2 tilesize, glm::vec2 particleSize, bool useAddiveBlend)
{
    accDt += dt;
    this->position = position;
    this->velocity = velocity;
    this->offset = offset;

    if (useAddiveBlend)
        ioManager().renderer->setAdditiveBlend();

    auto texCoord = bi::ioManager().assetmanager->getTexture(textureId).getTexCoords(tileNumber, tilesize);

    for (Particle& p : this->particles) {
        if (p.life > 0.0f) {
            ioManager().renderer->drawTexture(p.position, particleSize, color, textureId, 0, texCoord);
        }
    }

    if (useAddiveBlend) {
        ioManager().renderer->endFlushBegin();
        ioManager().renderer->setDefaultBlend();
    }

    // 60 fps
    if (accDt >= FPS) {
        particleLifeCheck(FPS);
        accDt -= FPS;
        if (accDt < 0) {
            accDt = 0;
        }
    }
}

unsigned int ParticleEmitter::firstUnusedParticle()
{
    // search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < nr_particles; ++i) {
        if (particles[i].life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (particles[i].life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // override first particle if all others are alive
    lastUsedParticle = 0;
    return 0;
}

void ParticleEmitter::particleLifeCheck(float dt)
{
    unsigned int nr_new_particles = 1;
    // add new particles
    for (unsigned int i = 0; i < nr_new_particles; ++i) {
        int unusedParticle = firstUnusedParticle();
        Particle& particle = particles[unusedParticle];
        respawnParticle(particle);
    }
    // update all particles
    for (unsigned int i = 0; i < nr_particles; ++i) {
        Particle& p = particles[i];
        p.life -= dt;        // reduce life
        if (p.life > 0.0f) { // particle is alive, thus update
            p.position -= p.velocity * dt;
            p.color.a -= dt * 2.5f;
        }
    }
}

void ParticleEmitter::respawnParticle(Particle& particle)
{
    float randomX = ((rand() % 100) - offset.x) / particle.spreadValue; // spread
    float randomY = ((rand() % 100) - offset.y) / particle.spreadValue; // spread
    float rColor = 0.5f + ((rand() % 100) / 1.0f);
    particle.position = { position.x + randomX, position.y + randomY };
    particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.life = life;
    particle.velocity = velocity;
}

void ParticleEmitter::setLife(float lifeTime)
{
    this->life = lifeTime;
}
