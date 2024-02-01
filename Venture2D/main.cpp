#include "Game.hpp"

using namespace venture;

int main( int argc, char** argv )
{
	auto game = Game::get();
	game->RunGame();

	return EXIT_SUCCESS;
}


// BOX 
/*

//-----------------------------------------------------------------------------//
///
/// A simple Demo of using Box2D with SDL2
///


#include <iomanip>
#include <Box2D/Box2D.h>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

b2World* world;

constexpr int PIXELS_PER_METER = 80; // 640 / 80 = 8

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

constexpr int SCALED_WIDTH = WIDTH / PIXELS_PER_METER;
constexpr int SCALED_HEIGHT = HEIGHT / PIXELS_PER_METER;

constexpr double RAD_TO_DEG = 180 / M_PI;


using namespace std;

int main( int argc, char** argv )
{
	// Initialize SDL ------------------------------------------------------------------------------------------------------------------------------------------- //
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow( "FirstGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
	if ( window == nullptr )
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( renderer == nullptr )
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow( window );
		SDL_Quit();
		return -1;
	}

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode( 0, &DM );
	auto Width = DM.w;
	auto Height = DM.h;

	cout << "Width of the Screen: " << Width << endl;
	cout << "Height of the Screen: " << Height << endl;

	// Initialize SDL ------------------------------------------------------------------------------------------------------------------------------------------- //

	// Create a Box2D world to manage all physics entities and simulation.
	// The b2Vec2 argument sets the gravity vector; here, it's earth-like gravity (0.0f, 9.81f).
	world = new b2World( b2Vec2( 0.0f, 9.81f ) );

	// Create Box Texture
	SDL_Surface* tmp_sprites;
	tmp_sprites = IMG_Load( "Assets/box.png" );
	if ( !tmp_sprites )
	{
		return -1;
	}

	SDL_Texture* texture_box = SDL_CreateTextureFromSurface( renderer, tmp_sprites );
	SDL_FreeSurface( tmp_sprites );

	// cartesian origin box
	float x_box = -2.5f;
	float y_box = -2.5f;

	// size of box
	float w_box = 0.3f;
	float h_box = 0.3f;

	// angle of the box
	float angle_box = 45.0f; //45.0f;

	// Box
	SDL_FRect box;
	b2Body* Body;

	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.angle = angle_box; // flips the whole thing -> 180 grad drehung
	//boxBodyDef.angle = 0;
	boxBodyDef.position.Set( x_box, y_box );
	b2Vec2 vel;
	vel.Set( 0, 0.2f );

	Body = world->CreateBody( &boxBodyDef );
	Body->SetLinearVelocity( vel );

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox( ( w_box / 2.0f ) - dynamicBox.m_radius, ( h_box / 2.0f ) - dynamicBox.m_radius ); // will be 0.5 x 0.5

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	Body->CreateFixture( &fixtureDef );

	// box: convert Metres back to Pixels for width and height
	box.w = w_box * PIXELS_PER_METER;
	box.h = h_box * PIXELS_PER_METER;

	bool close_game = false;
	SDL_Event event;

	// The game Loop
	while ( !close_game )
	{
		b2Vec2 pos = Body->GetPosition(); // Body = Body from box
		float angle = Body->GetAngle();

		// RAD2Degree
		angle *= static_cast< float >( RAD_TO_DEG );

		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
			{
				close_game = true;
			}

			else if ( event.key.keysym.sym == SDLK_r )
			{
				Body->SetTransform( b2Vec2( x_box, y_box ), angle_box );
				Body->SetLinearVelocity( vel );
			}
		}

		// question box, update x and y destination
		box.x = ( ( SCALED_WIDTH / 2.0f ) + pos.x ) * PIXELS_PER_METER - box.w / 2;
		box.y = ( ( SCALED_HEIGHT / 2.0f ) + pos.y ) * PIXELS_PER_METER - box.h / 2;

		SDL_RenderClear( renderer );
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );

		SDL_RenderCopyExF( renderer, texture_box, nullptr, &box, Body->GetAngle() * RAD_TO_DEG, nullptr, SDL_FLIP_NONE );

		SDL_SetRenderDrawColor( renderer, 32, 70, 49, 0 );
		SDL_RenderPresent( renderer );

		// update
		world->Step( 1.0f / 60.0f, 6, 2 );
	}

	// box2D delete whole world and free memory
	delete world;

	SDL_DestroyTexture( texture_box );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}
*/

// LINE 
/*
//-----------------------------------------------------------------------------//
///
/// A simple Demo of using Box2D with SDL2
///


#include <iomanip>
#include <Box2D/Box2D.h>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

b2World* world;

constexpr int PIXELS_PER_METER = 80; // 640 / 80 = 8

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

constexpr int SCALED_WIDTH = WIDTH / PIXELS_PER_METER;
constexpr int SCALED_HEIGHT = HEIGHT / PIXELS_PER_METER;

constexpr double RAD_TO_DEG = 180 / M_PI;


using namespace std;

int main( int argc, char** argv )
{
	// Initialize SDL ------------------------------------------------------------------------------------------------------------------------------------------- // 
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow( "FirstGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
	if ( window == nullptr )
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( renderer == nullptr )
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow( window );
		SDL_Quit();
		return -1;
	}

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode( 0, &DM );
	auto Width = DM.w;
	auto Height = DM.h;

	cout << "Width of the Screen: " << Width << endl;
	cout << "Height of the Screen: " << Height << endl;

	// Initialize SDL ------------------------------------------------------------------------------------------------------------------------------------------- // 

	// Create a Box2D world to manage all physics entities and simulation.
	// The b2Vec2 argument sets the gravity vector; here, it's earth-like gravity (0.0f, 9.81f).
	world = new b2World( b2Vec2( 0.0f, 9.81f ) );

	// Define the Cartesian origin coordinates for the ground.
	float ground_x = 0.0f;
	float ground_y = 0.0f;

	// Define start and end points of the ground line segment.
	b2Vec2 groundStartPoint( -3.0f, 2.0f ); // Start point of the ground line.
	b2Vec2 groundEndPoint( 3.0f, 2.0f ); // End point of the ground line.

	// Define a body definition for the ground.
	b2BodyDef myGroundDef;
	myGroundDef.type = b2_staticBody; // Static, as the ground doesn't move.
	myGroundDef.position.Set( ground_x, ground_y ); // Position of the ground in the world.
	myGroundDef.angle = 0; // Horizontal ground, so angle is 0.

	// Create a physical body in the world using the defined body definition.
	b2Body* groundLineBody = world->CreateBody( &myGroundDef );

	// Define an edge shape representing a line segment.
	b2EdgeShape edgeShape;
	edgeShape.SetTwoSided( groundStartPoint, groundEndPoint ); // Define the line segment's two end points.

	// Define fixture properties for the edge shape.
	b2FixtureDef edgeFixtureDef;
	edgeFixtureDef.shape = &edgeShape; // Attach the edge shape to the fixture.
	groundLineBody->CreateFixture( &edgeFixtureDef ); // Add the fixture to the ground body.

	// cartesian origin of _0019_PLATF.png 89 x 22
	float x_plat = -3.6f; // to edge
	float y_plat = -0.14f;// to edge

	// size of the platform
	float w_plat = 89.0f / PIXELS_PER_METER;
	float h_plat = 22.0f / PIXELS_PER_METER;

	// define a Rect for this platform and its body def
	SDL_FRect platform;
	b2Body* Body_platform;

	b2BodyDef platformBoyDef;
	platformBoyDef.type = b2_staticBody;
	platformBoyDef.position.Set( x_plat, y_plat );

	Body_platform = world->CreateBody( &platformBoyDef );

	// subtracting radius fixes the incorrect little gap that can appear when working with really small resolutions
	b2PolygonShape platformTile;
	// subtracting the radius kills the gap issue:
	platformTile.SetAsBox( ( w_plat / 2.0f ) - platformTile.m_radius, ( h_plat / 2.0f ) - platformTile.m_radius );
	b2FixtureDef fixturePlat;
	fixturePlat.shape = &platformTile;
	fixturePlat.density = 1.0f;
	fixturePlat.friction = 0.3f;
	fixturePlat.restitution = 0.5f;
	Body_platform->CreateFixture( &fixturePlat );

	// set the SDL_RECT rendering values
	platform.w = w_plat * PIXELS_PER_METER;
	platform.h = h_plat * PIXELS_PER_METER;
	platform.x = ( ( SCALED_WIDTH / 2.0f ) + x_plat ) * PIXELS_PER_METER - platform.w / 2;
	platform.y = ( ( SCALED_HEIGHT / 2.0f ) + y_plat ) * PIXELS_PER_METER - platform.h / 2;

	bool close_game = false;
	SDL_Event event;

	// The game Loop
	while ( !close_game )
	{

		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
			{
				close_game = true;
			}
		}


		SDL_RenderClear( renderer );
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );

		// Draw ground platform
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );
		SDL_RenderDrawLineF( renderer
							 , ( ( SCALED_WIDTH / 2.0f ) + edgeShape.m_vertex1.x ) * PIXELS_PER_METER
							 , ( ( SCALED_HEIGHT / 2.0f ) + edgeShape.m_vertex1.y ) * PIXELS_PER_METER
							 , ( ( SCALED_WIDTH / 2.0f ) + edgeShape.m_vertex2.x ) * PIXELS_PER_METER
							 , ( ( SCALED_HEIGHT / 2.0f ) + edgeShape.m_vertex2.y ) * PIXELS_PER_METER );


		SDL_SetRenderDrawColor( renderer, 32, 70, 49, 0 );
		SDL_RenderPresent( renderer );

		// update
		world->Step( 1.0f / 60.0f, 6, 2 );
	}

	// box2D delete whole world and free memory
	delete world;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}
*/

// BOX + LINE 
/*
//-----------------------------------------------------------------------------//
///
/// A simple Demo of using Box2D with SDL2
///


#include <iomanip>
#include <Box2D/Box2D.h>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

b2World* world;

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

constexpr int PIXELS_PER_METER = 80; // 640 / 80 = 8

constexpr int SCALED_WIDTH = WIDTH / PIXELS_PER_METER;
constexpr int SCALED_HEIGHT = HEIGHT / PIXELS_PER_METER;

constexpr double RAD_TO_DEG = 180 / M_PI;


using namespace std;

int main( int argc, char** argv )
{
	// Initialize SDL ------------------------------------------------------------------------------------------------------------------------------------------- //
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow( "FirstGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
	if ( window == nullptr )
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( renderer == nullptr )
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow( window );
		SDL_Quit();
		return -1;
	}

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode( 0, &DM );
	auto Width = DM.w;
	auto Height = DM.h;

	cout << "Width of the Screen: " << Width << endl;
	cout << "Height of the Screen: " << Height << endl;

	// Initialize SDL ------------------------------------------------------------------------------------------------------------------------------------------- //

	// Create a Box2D world to manage all physics entities and simulation.
	// The b2Vec2 argument sets the gravity vector; here, it's earth-like gravity (0.0f, 9.81f).
	world = new b2World( b2Vec2( 0.0f, 9.81f ) );

	// Define the Cartesian origin coordinates for the ground.
	float ground_x = 0.0f;
	float ground_y = 0.0f;

	// Define start and end points of the ground line segment.
	b2Vec2 groundStartPoint( -3.0f, 2.0f ); // Start point of the ground line.
	b2Vec2 groundEndPoint( 3.0f, 2.0f ); // End point of the ground line.

	// Define a body definition for the ground.
	b2BodyDef myGroundDef;
	myGroundDef.type = b2_staticBody; // Static, as the ground doesn't move.
	myGroundDef.position.Set( ground_x, ground_y ); // Position of the ground in the world.
	myGroundDef.angle = 0; // Horizontal ground, so angle is 0.

	// Create a physical body in the world using the defined body definition.
	b2Body* groundLineBody = world->CreateBody( &myGroundDef );

	// Define an edge shape representing a line segment.
	b2EdgeShape edgeShape;
	edgeShape.SetTwoSided( groundStartPoint, groundEndPoint ); // Define the line segment's two end points.

	// Define fixture properties for the edge shape.
	b2FixtureDef edgeFixtureDef;
	edgeFixtureDef.shape = &edgeShape; // Attach the edge shape to the fixture.
	groundLineBody->CreateFixture( &edgeFixtureDef ); // Add the fixture to the ground body.


	// Create Box Texture
	SDL_Surface* tmp_sprites;
	tmp_sprites = IMG_Load( "Assets/box.png" );
	if ( !tmp_sprites )
	{
		return -1;
	}

	SDL_Texture* texture_box = SDL_CreateTextureFromSurface( renderer, tmp_sprites );
	SDL_FreeSurface( tmp_sprites );

	// cartesian origin box
	float x_box = -2.5f;
	float y_box = -2.5f;

	// size of box
	float w_box = 0.3f;
	float h_box = 0.3f;

	// angle of the box
	float angle_box = 45.0f; //45.0f;

	// Box
	SDL_FRect box;
	b2Body* Body;

	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.angle = angle_box; // flips the whole thing
	//boxBodyDef.angle = 0;
	boxBodyDef.position.Set( x_box, y_box );

	Body = world->CreateBody( &boxBodyDef );
	
	b2Vec2 vel;
	vel.Set( 0, 0.2f );
	Body->SetLinearVelocity( vel );

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox( ( w_box / 2.0f ) - dynamicBox.m_radius, ( h_box / 2.0f ) - dynamicBox.m_radius ); // will be 0.5 x 0.5

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	Body->CreateFixture( &fixtureDef );

	// box: convert Meters back to Pixels for width and height
	box.w = w_box * PIXELS_PER_METER;
	box.h = h_box * PIXELS_PER_METER;

	// cartesian origin of _0019_PLATF.png 89 x 22
	float x_plat = -3.6f; // to edge
	float y_plat = -0.14f;// to edge

	// size of the platform
	float w_plat = 89.0f / PIXELS_PER_METER;
	float h_plat = 22.0f / PIXELS_PER_METER;

	bool close_game = false;
	SDL_Event event;

	// The game Loop
	while ( !close_game )
	{
		b2Vec2 pos = Body->GetPosition(); // Body = Body from box
		float angle = Body->GetAngle();

		// RAD2Degree
		angle *= static_cast< float >( RAD_TO_DEG );

		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
			{
				close_game = true;
			}

// 			else if ( event.key.keysym.sym == SDLK_r )
// 			{
// 				Body->SetTransform( b2Vec2( x_box, y_box ), angle_box );
// 				Body->SetLinearVelocity( vel );
// 			}
		}

		// question box, update x and y destination
		box.x = ( ( SCALED_WIDTH / 2.0f ) + pos.x ) * PIXELS_PER_METER - box.w / 2;
		box.y = ( ( SCALED_HEIGHT / 2.0f ) + pos.y ) * PIXELS_PER_METER - box.h / 2;

		SDL_RenderClear( renderer );
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );

		// Draw ground platform
		SDL_SetRenderDrawColor( renderer, 255, 255, 0, 0 );
		
		SDL_RenderDrawLineF( renderer
							 , ( ( SCALED_WIDTH / 2.0f ) + edgeShape.m_vertex1.x ) * PIXELS_PER_METER
							 , ( ( SCALED_HEIGHT / 2.0f ) + edgeShape.m_vertex1.y ) * PIXELS_PER_METER
							 , ( ( SCALED_WIDTH / 2.0f ) + edgeShape.m_vertex2.x ) * PIXELS_PER_METER
							 , ( ( SCALED_HEIGHT / 2.0f ) + edgeShape.m_vertex2.y ) * PIXELS_PER_METER );


		SDL_RenderCopyExF( renderer, texture_box, nullptr, &box, Body->GetAngle() * RAD_TO_DEG, nullptr, SDL_FLIP_NONE );

		SDL_SetRenderDrawColor( renderer, 32, 70, 49, 0 );
		SDL_RenderPresent( renderer );

		// update
		world->Step( 1.0f / 60.0f, 6, 2 );
	}

	// box2D delete whole world and free memory
	delete world;

	SDL_DestroyTexture( texture_box );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}


*/
