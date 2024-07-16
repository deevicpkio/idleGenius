#ifndef IG_APP
#define IG_APP
#define RAYGUI_IMPLEMENTATION
#include "Scene.hpp"

namespace IG
{
class App {
public:
    App();
    ~App();
    int run();

private:
    float lapTime;
    UIControlFlags controlFlags;
    Color backgroundColor;
    Font regularFont;
    Scene* mainScene;

    bool initialize();
    bool mainLoop();
    void handleInput();
    void update(float deltaTime);
    void draw();
};
}

#endif
