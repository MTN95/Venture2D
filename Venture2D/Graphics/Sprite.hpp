#pragma once
#include <SDL2/SDL_image.h>
#include <memory>
#include "Texture.hpp"

namespace venture
{
	struct SpriteDeleter;
	
	class Sprite
	{
	public:
		Sprite();
		Sprite(const Sprite& other);
		~Sprite();

		Sprite& operator=(const Sprite& other);

		void Render(SDL_Renderer* renderer, float xPos, float yPos);
		void RenderFrame(SDL_Renderer* renderer, float xPos, float yPos, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void Update(float deltaTime);

		void LoadSprite(const char* path, int spriteClipsCount = 1);

		const int GetSpriteWidth() const { return mSpriteWidth; }
		const int GetSpriteHeight() const { return mSpriteHeight; }
		const float& GetAnimationSpeed() const { return mAnimSpeed; }

		void SetAnimationSpeed(float newSpeed) { mAnimSpeed = newSpeed; }

		std::unique_ptr<Sprite,SpriteDeleter> Clone();

	private:
		static constexpr int MAX_SPRITES = 50;
		
		std::unique_ptr<Texture> mSpriteTexture;
		SDL_Rect mSpriteClips[MAX_SPRITES]{};
		int mSpriteCount;
		float mCurrentClip = 0.f;

		int mSpriteWidth;
		int mSpriteHeight;

		/**
		 * Spritesheet animation speed
		 * 1.0f is normal speed
		 * 0.5f is half speed
		 * and so on .. 
		 */ 
		float mAnimSpeed;

	};


	struct SpriteDeleter
	{
		void operator()( Sprite* s ) const
		{
			delete s;
		}
	};
}