#include "Scene.hpp"
#include <raygui.h>
#include "common.h"
#include <spdlog/spdlog.h>

Scene::Scene() 
{
    spdlog::debug("Before instantiating generators");
    dbManager = new DBManager();
    profile = new IG::Profile(dbManager);
    idleGenerators = new IG::Generator(dbManager);
    toggleActive = 0;

    entryHeight = (float)GuiGetStyle(DEFAULT, TEXT_SIZE)*10.0f;
    entryGap = 5;
    panelScrArea = {SCREEN_WIDTH_DEFAULT*.3+5, 5, SCREEN_WIDTH_DEFAULT*.7-5, SCREEN_HEIGHT_DEFAULT-5};
    panelContent = {5+SCREEN_WIDTH_DEFAULT*.3+10, 5+10, SCREEN_WIDTH_DEFAULT*.7-5-10, (float)((entryHeight+entryGap) * idleGenerators->count()) *1.05f};
    panelView = { 0 };
    panelScroll = { 0, 0 };
}

Scene::~Scene() 
{
    delete profile;
    delete idleGenerators;
    delete dbManager;
}

void Scene::Update(float deltaTime, UIControlFlags* rControlFlags) 
{

}

void Scene::Draw(UIControlFlags* rControlFlags) 
{
    DrawProfile();

    // NOTE: General Actions Panel
    int dump = GuiPanel((Rectangle){5, 5+SCREEN_HEIGHT_DEFAULT*.6f, SCREEN_WIDTH_DEFAULT*.3f, SCREEN_HEIGHT_DEFAULT*.4-5}, NULL);
    // Exit game
    if (GuiButton((Rectangle){ 25, 1050, 125, 30 }, GuiIconText(ICON_EXIT, "Exit Game"))) rControlFlags->quit = true;
    

    DrawIdleGenerators();

}

void Scene::DrawProfile()
{
    // NOTE: Player Info Panel
    int dump = GuiPanel((Rectangle){5, 5, SCREEN_WIDTH_DEFAULT*.3f, SCREEN_HEIGHT_DEFAULT*.6f}, NULL);
    GuiLabel((Rectangle){10, 10, SCREEN_WIDTH_DEFAULT*.3f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}, std::to_string(profile->getData().id).c_str());
}

void Scene::DrawIdleGenerators() 
{
    int dump;

    GuiScrollPanel(panelScrArea, nullptr, panelContent, &panelScroll, &panelView);
    
    BeginScissorMode(panelView.x, panelView.y, panelView.width, panelView.height);
    int i = 0;
    for(auto gen : idleGenerators->getData()) {
        Rectangle contentPos = {15+panelScrArea.x + panelScroll.x, panelScrArea.y + ((entryHeight + entryGap) * i) + panelScroll.y + 15, SCREEN_WIDTH_DEFAULT*.7f*.7, (float)entryHeight};
        dump = GuiPanel(contentPos, NULL);
        GuiLabel((Rectangle){contentPos.x + 10, contentPos.y + 5, SCREEN_WIDTH_DEFAULT*.7f-20, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}, gen.name.c_str());
        // NOTE: Buy/Upgrade
        if (GuiButton((Rectangle){contentPos.x + 10 + contentPos.width, contentPos.y, 100, (float)entryHeight}, "BUY")) auto buy = gen.id;

        GuiToggleGroup((Rectangle){contentPos.x + 10 + contentPos.width + 110, contentPos.y, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)*5, (float)entryHeight}, "x1;x10;Max", &toggleActive);

        i++;
    }
    EndScissorMode();

}
