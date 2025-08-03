## Project Overview
The game replicates the classic QBert mechanics where players control QBert, a character navigating a pyramid of tiles to change their colors while avoiding enemies like Coily, Slick, Sam, Ugg, and Wrongway. The engine supports:
- **Dynamic Level Management**: Procedurally generated levels with varying tile color rules (OneHit, TwoHit, Toggle).
- **Enemy AI**: Sophisticated enemy behaviors with state machines for Coily (Spawning, Egg, Snake, Dying states) and simpler movement patterns for other enemies.
- **High Score System**: Persistent storage of top 10 scores with player name entry.
- **Scene Management**: Multiple scenes for menu, name entry, gameplay, and high score display.
- **Audio Integration**: Sound effects for jumps, hits, and level completion.

### Engine
- **Component-Based Architecture**: Entities are represented as `GameObject`s with attached components (e.g., `TranslationComponent`, `TextureComponent`, `AnimationComponent`) for modularity.
- **Scene Management**: A `SceneManager` handles multiple scenes, enabling seamless transitions between menu, gameplay, and other scenes.
- **Input System**: An `InputManager` supports keyboard and controller inputs with command pattern bindings for flexible control schemes.
- **Resource Management**: A `ResourceManager` loads textures, fonts, and other assets, ensuring efficient resource handling.
- **Sound System**: A `SoundServiceLocator` provides a service-based audio system for playing sound effects.

### Design Choices
2. **Event-Driven Programming**: Components communicate via events (e.g., `OnTileColored`, `OnHealthChanged`) to reduce coupling and improve maintainability.
3. **Finite State Machines**: Complex behaviors (e.g., QBert, Coily) are implemented using state machines, allowing for clear transitions between states like Idle, Moving, or Dying. Simpler enemies dont implement FSM, but pattern can be easily added in the future.
4. **Data-Driven Design**: Level configurations are loaded from external files (via `LevelDataLoader`), enabling easy tweaking of enemy spawns and stage parameters.
5. **Extensibility**: The architecture supports adding new enemy types, tile rules, or game modes (e.g., Co-op, Versus) with minimal changes to core systems.
6. **Minimal trivial getters and setters** Code is design to use minimal amount of trivial getters ans setters. 

## Game Programming Patterns 
1. **Component Pattern**:
   - Used extensively in Minigin’s `GameObject`-`Component` system. Components like `LevelComponent`, `PlayerDataComponent`, and `QBertPlayer` encapsulate specific functionalities, allowing entities to be composed dynamically.
   - Example: `PlayerDataComponent` manages score and health, decoupling player state from gameplay logic.

2. **Command Pattern**:
   - Implemented in the input system via `Command` classes (e.g., `MoveCommand`, `NameEntryUpCommand`). This decouples input handling from game logic, enabling flexible rebinding and support for multiple input devices.
   - Example: `MoveCommand` translates keyboard/controller inputs into QBert movements.

3. **State Pattern**:
   - Used for QBert and Coily behaviors. QBert has states like `IdleState` and `DeadState`, while Coily transitions between `SpawningState`, `EggState`, `SnakeState`, and `DyingCoilyState`.
   - Example: `SnakeState` calculates Coily’s chase direction towards QBert, updating animations and movement.

4. **Observer Pattern**:
   - Employed for event-driven communication. Components subscribe to events (e.g., `OnTileColored`, `OnLevelCompleted`) to react to game state changes.
   - Example: `ScoreDisplayObserver` updates the UI when the player’s score changes.

5. **Factory Pattern**:
   - Used in `EnemyPrefabs` to create different enemy types (Coily, Slick, Sam, Ugg, Wrongway) based on string identifiers.
   - Example: `CreateCoily` constructs a Coily game object with appropriate components and settings.

6. **Singleton Pattern**:
   - Applied in `SceneManager`, `InputManager`, for global access to core systems.
   - Example: `SceneManager::GetInstance()` manages scene transitions.

7. **Service Locator**:
   - Used for `SoundServiceLocator`. Provides a global point of access to a service without coupling users to the concrete class that implements it.

8. **Proxy Pattern**:
   - Implemented in `QbertPositionProxy` to provide a controlled interface to QBert’s position, used by enemies like Coily for tracking.
   - Example: `QbertPositionProxy` updates enemy AI without direct access to the QBert component.

## C++20 Features Utilized

The project leverages modern C++20 features to enhance code clarity, performance, and safety:

1. **Concepts**:
   - Used implicitly in template constraints (e.g., `std::ranges`) to ensure type safety in generic code.
   - Example: `std::ranges::filter` in `Level::CheckForComplition` ensures compile-time correctness when filtering tiles.

2. **Ranges Library**:
   - Employed for clean and expressive data processing. The `std::ranges` library simplifies operations like filtering and iteration over collections.
   - Example: `Level::CheckForComplition` uses `std::views::filter` to check if all normal tiles are completed.

3. **Lambda Expressions**:
   - Extensively used for event subscriptions and menu item callbacks, providing concise inline functionality.
   - Example: `menuComp->AddMenuItem("Solo", []() { CreateNameEntryScene(); })` defines menu behavior inline.

4. **std::unique_ptr**:
   - Used for resource ownership and automatic memory management, ensuring no memory leaks in game objects and components.
   - Example: `auto bg = GameObjectBuilder().WithTexture("background.png", -2.f, 1.f).Build()` returns a `std::unique_ptr<dae::GameObject>`.

5. **Structured Bindings**:
   - Used in range-based for loops and tuple unpacking for cleaner code.
   - Example: Implicit in `for (auto& tilePtr : m_tiles)` loops.

6. **constexpr**:
   - Applied to constants like `MAX_STAGES` and `MAX_LEVELS` in `LevelManagerComponent` for compile-time evaluation, improving performance or even arrays.
   - Example: `constexpr int MAX_STAGES = 4;` ensures static allocation.
   - `static constexpr std::array<glm::ivec2, 4> SPRITE_DIRECTIONS = { RIGHT, UP_RIGHT, LEFT, UP_LEFT };` in `UggWrongway`

8. **std::unordered_map with Custom Hash**:
   - Used for mapping directions to animation frames with a custom `IVec2Hash` for `glm::ivec2` keys.
   - Example: `SnakeState::DirectionToFrame` maps directions to sprite frames.
   
