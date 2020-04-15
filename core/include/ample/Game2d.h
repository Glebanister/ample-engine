#pragma once

#include <unordered_map>
#include <memory>

#include "LayeredWindowActivity.h"
#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "GameException.h"
#include "CameraPerspective.h"
#include "CameraOrtho.h"
#include "Debug.h"
#include "Level.h"
#include "GameController.h"

namespace ample::game
{
class GameController;
}

namespace ample::game::game2d
{
class Level;
}

namespace ample::game::game2d
{
class Game2d : public graphics::LayeredWindowActivity
{
public:
    Game2d(window::Window &window);
    GameController &controller() noexcept;
    std::shared_ptr<GameController> controllerPointer() const noexcept;
    std::shared_ptr<game2d::Level> createLevel(const std::string &name,
                                               const float sliceThickness,
                                               const float physicsLayerPosition,
                                               const graphics::Vector2d<float> &gravity);
    void setCurrentLevel(std::shared_ptr<Level>);
    std::shared_ptr<Level> currentLevel() const noexcept;

private:
    std::shared_ptr<GameController> _gameController;
};
} // namespace ample::game::game2d
