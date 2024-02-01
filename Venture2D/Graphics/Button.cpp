#include "Button.hpp"
#include "../Input/InputManager.hpp"
#include "../Game.hpp"
#include "../Util/Log.hpp"
#include "../Util/ColorMacros.hpp"

namespace venture
{
	Button::Button( const char* buttonText, uint8_t textSize, const glm::vec2& position )
		: mIsButtonPressed( false )
	{
		// 	entityBox = std::unique_ptr<Entity, EntityDeleter>( new Entity( "entityBox" ), EntityDeleter() );

		mTestText = std::unique_ptr<TextRenderer, TextRendererDeleter>( new TextRenderer( buttonText, textSize, COLOR_BLACK ), TextRendererDeleter() );
		mTestText->CreateText();

		mTestTextHovered = std::unique_ptr<TextRenderer, TextRendererDeleter>( new TextRenderer( buttonText, textSize, COLOR_LIGHTORANGE ), TextRendererDeleter() );
		mTestTextHovered->CreateText();

		mTestTextDown = std::unique_ptr<TextRenderer, TextRendererDeleter>( new TextRenderer( buttonText, textSize, COLOR_RED ), TextRendererDeleter() );
		mTestTextDown->CreateText();

		mButtonAction = ButtonAction::BUTTON_OUT;

		const auto& buttonSize = mTestText->GetTextTexture()->GetTextureSize();

		mPosition.x = position.x - ( buttonSize.x / 2.f );
		mPosition.y = position.y - ( buttonSize.y / 2.f );

		mOriginalPosition = mPosition;
	}

	void Button::ProcessInput( InputManager* input )
	{
		auto        mousePosition = InputManager::get()->GetMousePosition();

		// Check if mTestText and its texture are valid before using them
		if ( !mTestText || !mTestText->GetTextTexture() )
		{
			LOG_ERROR("ERROR in Button class");
			return; // Optionally log an error here
		}

		const auto& buttonSize = mTestText->GetTextTexture()->GetTextureSize();

		auto buttonW = mPosition.x + buttonSize.x;
		auto buttonH = mPosition.y + buttonSize.y;

		// LOG_INFO("{0},{1}", mousePosition.x,mousePosition.y);

		bool isMouseHovering = ( mousePosition.x >= mPosition.x && mousePosition.x < buttonW
								 && mousePosition.y >= mPosition.y && mousePosition.y < buttonH );

		bool isLeftMousePressed = InputManager::get()->isMouseButtonPressed( MouseButton::LEFT );
		bool isLeftMouseReleased = InputManager::get()->isMouseButtonReleased( MouseButton::LEFT );

		// if mouse is hovering over the button
		if ( isMouseHovering )
		{
			mButtonAction = ButtonAction::BUTTON_HOVERED;
		}

		if ( isMouseHovering && isLeftMousePressed )
		{
			mButtonAction = ButtonAction::BUTTON_PRESSED;
			mIsButtonPressed = true;
		}

		// 		if ( isMouseHovering && isLeftMouseReleased )
		// 		{
		// 			mIsButtonPressed = true;
		// 		}

		if ( !isMouseHovering )
		{
			mButtonAction = ButtonAction::BUTTON_OUT;
		}
	}

	void Button::Render( SDL_Renderer* renderer )
	{

		// Ensure renderers are valid before attempting to use them
		if ( mButtonAction == ButtonAction::BUTTON_OUT && mTestText )
		{
			mTestText->RenderText( renderer, mPosition );
		}
		else if ( mButtonAction == ButtonAction::BUTTON_HOVERED && mTestTextHovered )
		{
			mTestTextHovered->RenderText( renderer, mPosition );
		}
		else if ( mButtonAction == ButtonAction::BUTTON_PRESSED && mTestTextDown )
		{
			mTestTextDown->RenderText( renderer, mPosition );
		}
		else if ( mTestText )
		{
		// Default rendering if other states aren't met
			mTestText->RenderText( renderer, mPosition );
		}

// 		switch ( mButtonAction )
// 		{
// 			case ButtonAction::BUTTON_OUT:
// 				mTestText->RenderText( renderer, mPosition );
// 				break;
// 			case ButtonAction::BUTTON_HOVERED:
// 				mTestTextHovered->RenderText( renderer, mPosition );
// 				break;
// 			case ButtonAction::BUTTON_PRESSED:
// 				mTestTextDown->RenderText( renderer, mPosition );
// 				break;
// 			default:
// 				mTestText->RenderText( renderer, mPosition );
// 				break;
// 		}
	}

	void Button::Clean() 
	{
		if ( mTestText )
		{
			mTestText->Clean();
		}
		if ( mTestTextHovered )
		{
			mTestTextHovered->Clean();
		}
		if ( mTestTextDown )
		{
			mTestTextDown->Clean();
		}
	}

	void Button::ApplySineAnimation( float deltaTime,
									 float frequency,
									 float amplitude,
									 float phaseOffset )
	{
		mElapsedTime += deltaTime;

		// Apply easing by modifying the sine wave
		float easedSineWave = ( 1 - cos( ( mElapsedTime * frequency ) + phaseOffset ) ) / 2 * amplitude;

		glm::vec2 buttonPos = GetOriginalPosition();
		buttonPos.y += easedSineWave;
		SetPosition( buttonPos );
	}
}
