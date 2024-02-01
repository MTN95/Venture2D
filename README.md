# <div align="center">A 2D Action Adventure Game</div>

### <div align="center">Project Description</div>
   
This project was initially created in between semesters as a personal project.
Developed over a couple of weeks (not finished) as side project while pursuing my Computer Science studies,
Mostly to continue learning SDL2 and its extentions, and to learn a bit of physics with box2D.

### <div align="center">State-Based Design Pattern for Game States</div>

The State-Based Design Pattern is utilized to manage the different stages or scenes within the game, such as the main menu, gameplay, pause, and game-over states. This pattern allows for a clean separation of concerns, where each state encapsulates its unique behavior and assets, facilitating easy transitions and updates. By structuring the game around states, development becomes more organized, and adding new states or modifying existing ones is streamlined, enhancing the game's scalability and maintainability.

### <div align="center">Custom Implementations</div>

The game is using an Entity-Component based architecture, centered around a minimalistic approach for managing game objects and their behaviors. 
This design is structured around several key components:

### <div align="center">Core Components of the ECS</div>

IComponent: This interface serves as the base for all component classes, ensuring a consistent structure that supports polymorphism and flexibility. Components like TransformComponent and InputMovementComponent derive from IComponent, encapsulating specific data and behaviors needed for various entities.

EntityManager: The EntityManager acts as the central hub for creating, managing, and deleting entities within the game. It maintains a registry of all active entities and their associated components, facilitating efficient entity lookup and manipulation based on gameplay requirements.

Entity: Each Entity is a lightweight, unique identifier that aggregates components. Entities themselves are devoid of direct functionality or data; instead, they serve as containers for components that define their characteristics and behaviors within the game world.

Component Classes: Specific component classes, such as TransformComponent for spatial information (position, rotation, scale) and InputMovementComponent for handling movement inputs, provide modular chunks of functionality. By attaching different components to entities, a wide variety of game objects with diverse behaviors can be constructed using a mix-and-match approach.

TextRenderer and Button: The game's menu system is using a custom implementation of a text renderer and interactive buttons, (with the input manager allowing lock and unlock mechanics to avoid hold + drag over a button to click it.) 
This approach allows for an easy basic UI, tailored specifically to the game's needs (visual will probably be changed later), providing a seamless and intuitive navigation experience for the player.

Input Manager: A centralized input manager is implemented to handle all game inputs. This system simplifies input management, allowing for easy modifications and ensuring that input handling is consistent and efficient across all game states.

Timer Class (Single Thread Use): Utilizing the std::chrono library, a custom timer class has been developed for time management. This implementation supports precise control over timing events and animations, essential for game mechanics and ensuring smooth gameplay. The single-threaded design prioritizes simplicity and reliability.
    
<div align="center">    
The Game Plan
</div>

    An Action Adventure 2D Side Scroller Game, Runner Shooter Like. 
    Player Mechanics: Run, Jump, Duck, Pickup Weapons, Shoot.


### <div align="center">Libraries Used</div>

The libraries comes with the project so no need to download them yourself.


    (included in the repo)
    SDL2 library
    SDL2 extensions: SDL2_image, SDL2_mixer, SDL2_ttf
    OpenGL Mathematics (GLM) library 
    Box2D library
    SpdLog Library

NOTE: Vec2D.h is my own implementation of a templated 2D vector class started this project with this,
But decided to use glm instead.

### <div align="center">Building from Source</div>


This project is primarily developed using Microsoft Visual Studio Community, and vcpkg to manage the libraries.

If you're working with a different IDE, you might need to adjust the setup to compile and build. 

This involves configuring the environment to match the dependencies and settings used in Visual Studio.


### <div align="center">Build Instructions</div>

    Clone the Repository: git clone [[repo-link]](https://github.com/MTN95/Venture2D)
    Navigate to Project Directory
    Build the Project

### <div align="center">Final Notes</div>

This project, while modest in size at approximately 3000 lines of code, is committed to the principles of open-source development.

There remains much work to bring this game to completion. Currently, it features just the fundamentals, yet it's on a promising path. i invite contributions!

If you're interested in contributing, please submit a pull request accompanied by a detailed description of your suggested modifications for consideration.
