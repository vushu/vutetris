#pragma once
#include <bismuth/particle.hpp>
#include <bismuth/renderer.hpp>
#include <glm/glm.hpp>
#include <vector>
namespace bi {
class ParticleEmitter {
public:
    // constructors, asssignment, destructor
    ParticleEmitter(unsigned int nparticles)
        : nr_particles(nparticles)
    {
    }

    ~ParticleEmitter();

    ///@param dt -- delta time
    ///@param position  particleemitter position
    ///@param velocity  particleemitter velocity
    ///@param offset  particleemitter offset
    void emit(float dt, glm::vec2 position, glm::vec2 velocity, glm::vec2 offset, glm::vec4 color, int textureId, int tileNumber, glm::vec2 tilesize, glm::vec2 particleSize, bool useAddiveBlend = false);
    void init(float lifeTime = 1.0f);
    void setLife(float lifeTime);

private:
    glm::vec2 position, velocity, offset;
    float life = 1.0f;
    std::vector<Particle> particles;
    float accDt = 0;
    const float FPS = 1.0f / 60.0f;

    unsigned int nr_particles = 0;
    unsigned int lastUsedParticle = 0;
    unsigned int firstUnusedParticle();
    void respawnParticle(Particle& particle);
    void particleLifeCheck(float dt);
};
}
