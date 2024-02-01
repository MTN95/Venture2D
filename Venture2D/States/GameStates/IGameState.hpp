#pragma once
#include "../IState.hpp"
#include "../../Input/InputManager.hpp"

namespace venture
{
    class IGameState : public IState
    {
    public:
        virtual ~IGameState() override = default;

        void Init() override = 0;
        void ProcessInput( InputManager* input ) override = 0;
        void Update(float deltaTime) override = 0;
        void Render(SDL_Renderer* renderer) override = 0;
        void Clean() override = 0;
    };

	struct IGameStateDeleter
	{
		void operator()( IGameState* gstate ) const
		{
            gstate->Clean();
			delete  gstate;
		}
	};
}