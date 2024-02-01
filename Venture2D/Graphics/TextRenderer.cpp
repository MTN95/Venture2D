#include "TextRenderer.hpp"
#include "../Game.hpp"
#include "../Util/Log.hpp"

namespace venture 
{
	TextRenderer::TextRenderer(const char* text, uint8_t textSize, SDL_Color textColor)
		: mText(text), mTextSize(textSize), mTextColor(textColor)
	{
		mPosition = glm::vec2();
		std::string defaultFont = std::string(SOLUTION_DIR) + "Venture2D/Assets/fonts/public-pixel.ttf";

		mFont.reset(TTF_OpenFont(defaultFont.c_str(), mTextSize));
		if (mFont == nullptr)
		{
			LOG_ERROR("Failed to open font!");
		}

		mTexture.reset( new Texture() );
    }

	TextRenderer::~TextRenderer()
	{
		Clean();
	}

	void TextRenderer::Clean()
	{ }

	void TextRenderer::CreateText()
	{
		if (!mTexture->CreateTextureFromText(
			Game::get()->GetRenderer(),
			mFont.get(),
			mText,
			mTextColor))
		{
			LOG_ERROR("Failed to create a texture from text!\n");
		}
	}

	void venture::TextRenderer::RenderText(SDL_Renderer* renderer, const glm::vec2& position)
	{
		mTexture->Render(renderer,static_cast<int>(position.x), static_cast<int>(position.y));
	}
}