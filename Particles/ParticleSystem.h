#pragma once

#include <SFML/Graphics.hpp>

#include "Particles/ParticleUpdater.h"
#include "Particles/ParticleGenerator.h"

namespace particles {

class ParticleData;

/* Abstract base class for all particle system types */
class ParticleSystem : public sf::Transformable {
public:
	ParticleSystem(int maxCount);
	virtual ~ParticleSystem();

	ParticleSystem(const ParticleSystem &) = delete;
	ParticleSystem &operator=(const ParticleSystem &) = delete;

	virtual void update(const sf::Time &dt);
	virtual void render(sf::RenderTarget &renderTarget) = 0;

	virtual void reset();

	template<typename T>
	inline T *addGenerator() {
		T *g = new T();
		m_generators.push_back(g);
		return g;
	}

	template<typename T>
	inline T *addUpdater() {
		T *u = new T();
		m_updaters.push_back(u);
		return u;
	}

	void emitParticles(int count); 	// emit a fix number of particles

protected:
	void emitWithRate(float dt);	// emit a stream of particles defined by emitRate and dt

public:
	float	emitRate;	// Note: For a constant particle stream, it should hold that: emitRate <= (maximalParticleCount / averageParticleLifetime)

protected:
	float m_dt;

	ParticleData *m_particles;
	
	std::vector<ParticleGenerator *> m_generators;
	std::vector<ParticleUpdater *> m_updaters;

	sf::VertexArray m_vertices;
};


class PointParticleSystem : public ParticleSystem {
public:
	PointParticleSystem(int maxCount);
	virtual ~PointParticleSystem() {}

	PointParticleSystem(const PointParticleSystem &) = delete;
	PointParticleSystem &operator=(const PointParticleSystem &) = delete;

	virtual void render(sf::RenderTarget& renderTarget) override;

protected:
	void updateVertices();
};


class TextureParticleSystem : public ParticleSystem {
public:
	TextureParticleSystem(int maxCount, sf::Texture *texture);
	virtual ~TextureParticleSystem() {}

	TextureParticleSystem(const TextureParticleSystem &) = delete;
	TextureParticleSystem &operator=(const TextureParticleSystem &) = delete;

	virtual void render(sf::RenderTarget &renderTarget) override;

	void setTexture(sf::Texture *texture);

protected:
	void updateVertices();

public:
	bool additiveBlendMode;

protected:
	sf::Texture *m_texture;
};


class SpriteSheetParticleSystem : public TextureParticleSystem {
public:
	SpriteSheetParticleSystem(int maxCount, sf::Texture *texture) : TextureParticleSystem(maxCount, texture) {}
	virtual ~SpriteSheetParticleSystem() {}

	SpriteSheetParticleSystem(const SpriteSheetParticleSystem &) = delete;
	SpriteSheetParticleSystem &operator=(const SpriteSheetParticleSystem &) = delete;

	virtual void render(sf::RenderTarget &renderTarget) override;

protected:
	void updateVertices();
};


class MetaballParticleSystem : public TextureParticleSystem {
public:
	MetaballParticleSystem(int maxCount, sf::Texture *texture, int windowWidth, int windowHeight);
	virtual ~MetaballParticleSystem() {}

	MetaballParticleSystem(const MetaballParticleSystem &) = delete;
	MetaballParticleSystem &operator=(const MetaballParticleSystem &) = delete;

	virtual void render(sf::RenderTarget &renderTarget) override;

public:
	sf::Color color{ sf::Color::White };
	float threshold{ 0.5f };

protected:
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_sprite;
	sf::Shader m_shader;
};

}