#include "Sprite.hpp"
#include "../Game.hpp"
#include "../Util/Log.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace venture
{
	Sprite::Sprite()
		: mSpriteCount(0), mSpriteWidth(0), mSpriteHeight(0), mAnimSpeed(1.0f)
	{ }

	Sprite::Sprite( const Sprite & other )
		: mSpriteCount(other.mSpriteCount)
		, mSpriteWidth(other.mSpriteWidth)
		, mSpriteHeight(other.mSpriteHeight)
		, mAnimSpeed(1.0f)
		, mCurrentClip(other.mCurrentClip)
	{
		for ( int i = 0; i < MAX_SPRITES; ++i )
		{
			mSpriteClips[ i ] = other.mSpriteClips[ i ];
		}

		mSpriteTexture.reset(other.mSpriteTexture.get());
	}

	Sprite::~Sprite()
	{

	}

	Sprite& Sprite::operator=( const Sprite& other )
	{
		mSpriteCount = other.mSpriteCount;
		mSpriteWidth = other.mSpriteWidth;
		mSpriteHeight =  other.mSpriteHeight;
		mAnimSpeed = other.mAnimSpeed;
		mCurrentClip =  other.mCurrentClip;

		if ( this != &other )
		{
			for ( int i = 0; i < MAX_SPRITES; ++i )
			{
				mSpriteClips[ i ] = other.mSpriteClips[ i ];
			}
		}
		return *this;

		mSpriteTexture.reset(other.mSpriteTexture.get());
	}

	void Sprite::Render(SDL_Renderer* renderer, float xPos, float yPos)
	{
		mSpriteTexture->Render(renderer, static_cast<int>(xPos), static_cast<int>(yPos));
	}

	void Sprite::RenderFrame(SDL_Renderer* renderer, float xPos, float yPos, SDL_RendererFlip flip)
	{
		SDL_Rect* currentClip = &mSpriteClips[static_cast<int>(mCurrentClip) / mSpriteCount];  
		mSpriteTexture->RenderFrame(renderer, static_cast<int>(xPos), static_cast<int>(yPos), currentClip, flip);
	}

	void Sprite::Update(float deltaTime)
	{
		//Go to next frame
		mCurrentClip += mAnimSpeed;

		//Cycle animation
		if (mCurrentClip / mSpriteCount >= mSpriteCount)
		{
			mCurrentClip = 0;
		}
	}

	void Sprite::LoadSprite(const char* path, int spriteClipsCount)
	{
		mSpriteCount = spriteClipsCount;
		mSpriteTexture = std::make_unique<Texture>();
		std::string fullPath = std::string(SOLUTION_DIR) + path;
		if (!mSpriteTexture->CreateTexture(Game::get()->GetRenderer(), fullPath))
		{
			LOG_DEBUG("Failed to create a texture for the Sprite!");
		}

		// only takes in account 1 row of sprites.
		const int SPRITE_WIDTH = mSpriteTexture->GetTextureSize().x / mSpriteCount;
		const int SPRITE_HEIGHT = mSpriteTexture->GetTextureSize().y;
		
		mSpriteWidth = SPRITE_WIDTH;
		mSpriteHeight = SPRITE_HEIGHT;

		for (int i = 0; i <= mSpriteCount; i++)
		{
			mSpriteClips[i].x = i * SPRITE_WIDTH;
			mSpriteClips[i].y = 0;
			mSpriteClips[i].w = SPRITE_WIDTH;
			mSpriteClips[i].h = SPRITE_HEIGHT;
		}
	}

	std::unique_ptr<Sprite, SpriteDeleter> Sprite::Clone()
	{
		return std::unique_ptr<Sprite, SpriteDeleter>( this );
	}
			
}