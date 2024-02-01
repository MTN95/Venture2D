#pragma once

#include <SDL2/SDL.h>
#include "../Input/InputManager.hpp"

namespace venture {

	class IState
	{
	public:
		virtual ~IState() = default;

		virtual void Init() = 0;
		virtual void ProcessInput( InputManager* input ) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(SDL_Renderer* renderer) = 0;
		virtual void Clean() = 0;
	
	};

}