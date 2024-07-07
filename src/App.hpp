#ifndef IG_APP
#define IG_APP
#define RAYGUI_IMPLEMENTATION
#include "common.h"
#include "Scene.hpp"

class App {
public:
    App();
    ~App();
    int Run();

private:
    float lapTime;
    UIControlFlags controlFlags;
    Color backgroundColor;
    Scene* mainScene;

    bool Initialize();
    bool MainLoop();
    void HandleInput();
    void Update(float deltaTime);
    void Draw();
};
#endif
