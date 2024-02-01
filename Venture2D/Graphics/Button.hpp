#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <glm/glm.hpp>
#include <string>
#include "TextRenderer.hpp"
#include "../Input/InputManager.hpp"

namespace venture
{
	enum class ButtonAction
	{
		BUTTON_OUT,
		BUTTON_HOVERED,
		BUTTON_DOWN,
		BUTTON_PRESSED,
		BUTTON_RELEASED,
		BUTTON_TOTAL
	};

	class Button
	{
	public:
		Button( const char* buttonText, uint8_t textSize, const glm::vec2& position );

		void ProcessInput( InputManager* input );
		void Render( SDL_Renderer* renderer );
		void Clean();

		bool isButtonPressed() const { return mIsButtonPressed; }

		void ResetButton() { mIsButtonPressed = false; }

		const glm::vec2& GetOriginalPosition() const { return mOriginalPosition; }
		const glm::vec2& GetPosition() const { return mPosition; }
		void             SetPosition( const glm::vec2& newPosition ) { mPosition = newPosition; }
		
		void ApplySineAnimation( float deltaTime , float frequency, float amplitude, float phaseOffset  );

	private:
		bool mIsButtonPressed;

		std::unique_ptr<TextRenderer, TextRendererDeleter> mTestText;
		std::unique_ptr<TextRenderer, TextRendererDeleter> mTestTextHovered;
		std::unique_ptr<TextRenderer, TextRendererDeleter> mTestTextDown;

		std::string mButtonText;
		glm::vec2   mPosition;
		glm::vec2   mOriginalPosition;

		ButtonAction mButtonAction;

		float mElapsedTime = 0.0f;

	};

	struct ButtonDeleter
	{
		void operator()( Button* b ) const
		{
			b->Clean();
			delete b;
		}
	};
}