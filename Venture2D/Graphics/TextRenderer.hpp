#pragma once
#include "Texture.hpp"
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace venture
{
	// NOTE: if you want to use the setters such as "SetFont"/"SetTextColor"/"SetTextSize" 
	// You MUST call them before you call "CreateText" as the text attributes cannot be changed at runtime.
	// I.E Setting the font to a custom one / changing the color, must happen before we create the text.

	struct SDLFontDeleter
	{
		void operator()( TTF_Font* font ) const
		{
			TTF_CloseFont( font );
		}
	};

	class TextRenderer
	{
	public:
		TextRenderer( const char* text, uint8_t textSize, SDL_Color textColor );
		~TextRenderer();

		void Clean();

		void CreateText();

		void RenderText( SDL_Renderer* renderer, const glm::vec2& position );

		void SetFont( std::unique_ptr<TTF_Font, SDLFontDeleter> newFont ) { mFont = std::move( newFont ); }
		void SetTextColor( SDL_Color newColor ) { mTextColor = newColor; }
		void SetTextSize( int newSize ) { mTextSize = newSize; }

		std::unique_ptr<TTF_Font, SDLFontDeleter>& GetFont() { return mFont; }
		std::unique_ptr<Texture, TextureDeleter>& GetTextTexture() { return mTexture; }
		const glm::ivec2 GetTextSize() const { return mTexture->GetTextureSize(); }
		glm::vec2& GetTextPosition() { return mPosition; }
		const SDL_Color& GetTextColor() { return mTextColor; }

	private:
		std::unique_ptr<TTF_Font, SDLFontDeleter> mFont;
		std::unique_ptr<Texture, TextureDeleter> mTexture;
		std::string mText;
		SDL_Color mTextColor;
		int mTextSize;
		glm::vec2 mPosition;

	};

	struct TextRendererDeleter
	{
		void operator()( TextRenderer* t ) const
		{
			t->Clean();
			delete t;
		}
	};
}