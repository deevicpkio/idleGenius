#include "App.hpp"
#include "igcommon.h"
#include "guiStyles.h"
#include <raylib.h>
#include <spdlog/spdlog.h>

App::App() {
    lapTime = 0.0;
    controlFlags.quit = false;
    backgroundColor = WHITE;
    mainScene = new Scene;

}

App::~App() {
    delete mainScene;
}

int App::run() {
    if (!initialize()) {
        return FAILED_INIT;
    }
    
    if (!mainLoop()) {
        return FAILED_LOOP; 
    }
    
    CloseWindow();

    return SUCCESS;
}

bool App::initialize() {
    controlFlags.quit = false;
    InitWindow(SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT, "Idle Genius");
    ToggleFullscreen();
    SetTargetFPS(60);
    
    GuiLoadStyleDark();
    
    regularFont = LoadFont("assets/fonts/AnonymiceProNerdFontMono-Regular.ttf");
    spdlog::info("font base size: {}", regularFont.baseSize);
    GuiSetFont(regularFont);
    
    backgroundColor = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
    
    mainScene->init();
    
    return true; 
}

bool App::mainLoop() {
    while(!controlFlags.quit) {

        if (WindowShouldClose()) {
            controlFlags.quit = WindowShouldClose();
            continue;
        }
        
        handleInput();

        update(GetFrameTime());

        draw();

    }


    return true;
}

void App::handleInput() {
    int keyPressed = GetKeyPressed();

    switch(keyPressed)
    {
        case KEY_A:
            break;
        case KEY_D:
            break;
        case KEY_W:
            break;
        case KEY_S:
            break;
        case KEY_SPACE:
            break;
        case KEY_F1:
            GuiLoadStyleJungle();
            break;
        case KEY_F2:
            GuiLoadStyleCyber();
            break;
        case KEY_F3:
            GuiLoadStyleAshes();
            break;
        case KEY_F4:
            GuiLoadStyleBluish();
            break;
        case KEY_F5:
            GuiLoadStyleCandy();
            break;
        case KEY_F6:
            GuiLoadStyleCherry();
            break;
        case KEY_F7:
            GuiLoadStyleDark();
            break;
        case KEY_F8:
            GuiLoadStyleEnefete();
            break;
        case KEY_F9:
            GuiLoadStyleLavanda();
            break;
        case KEY_F10:
            GuiLoadStyleSunny();
            break;
        case KEY_F11:
            GuiLoadStyleTerminal();
            break;
        case KEY_F12:
            GuiLoadStyleDefault();
            break;
        case DEFAULT:
            break;
    }
}

void App::update(float deltaTime) {
    mainScene->update(deltaTime, &controlFlags);
}

void App::draw() {
    
    BeginDrawing();
    
    ClearBackground(backgroundColor);
    
    mainScene->draw(&controlFlags);

    EndDrawing();
}

