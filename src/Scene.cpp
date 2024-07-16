#include "Scene.hpp"
#include <raygui.h>
#include <string>
#include "dbModels/DBManager.hpp"
#include "dbModels/ProfileModel.hpp"
#include "igcommon.h"

namespace IG
{
enum EmojiId 
{
    BANK = 1,
    CHART = 2,
    COFFEE = 3,
    WORK = 4,
    SHOP = 5,
    SEPARATOR = 6,
    UNICORN = 7,
    REFRESH = 8,
    LITHIUM_MINE = 9,
    DIAMOND_MINE = 10,
    HOURGLASS = 11,
    DOUBLE_ARROW_UP = 12,
    CHECK_MARK = 13,
    CRYPTO_MINE = 14,
    ADULT_FILM = 15,
    FOOD_TRUCK = 16,
    PRESTIGE = 17,
    WORKER = 18,
    UP = 19,
    DOWN = 20,
    NEXT_PAGE = 21,
    PREV_PAGE = 22,
    BUY_ONE = 23,
    BUY_MAX = 24,
    SELECTED = 25,
    UNSELECTED = 26,
    SICK = 27,
    WORLD = 28,
    OCCULT = 29,
    UPGRADES = 30,
    ON = 31,
    OFF = 32,
    GOLD_MINE = 33,
    CULT_WEAK = 34,
    NAV_BACK = 35,
    EXIT = 36,
};

std::map<EmojiId, std::string> ICONS = 
{
    {BANK, "🏦"},
    {CHART, "📈"},
    {COFFEE, "☕"},
    {WORK, "👨"},
    {SHOP, "🛍️"},
    {SEPARATOR, "┊"},
    {UNICORN, "🦄"},
    {REFRESH, "🔄"},
    {LITHIUM_MINE, "🔋"},
    {DIAMOND_MINE, "💎"},
    {HOURGLASS, "⏳"},
    {DOUBLE_ARROW_UP, "⏫"},
    {CHECK_MARK, "✅"},
    {CRYPTO_MINE, "📟"},
    {ADULT_FILM, "🫦"},
    {FOOD_TRUCK, "🍕"},
    {PRESTIGE, "💸"},
    {WORKER, "👷"},
    {UP, "🔼"},
    {DOWN, "🔽"},
    {NEXT_PAGE, "⏭️"},
    {PREV_PAGE, "⏮️"},
    {BUY_ONE, "💰"},
    {BUY_MAX, "💰"},
    {SELECTED, "◻️"},
    {UNSELECTED, "◼️"},
    {SICK, "😷"},
    {WORLD, "🌍"},
    {OCCULT, "🪬"},
    {UPGRADES, "‼️"},
    {ON, "🟢"},
    {OFF, "🔴"},
    {GOLD_MINE, "🌟"},
    {CULT_WEAK, "🕍"},
    {NAV_BACK, "↩️"},
    {EXIT, "📛"}
};

Scene::Scene() 
{ 
}

Scene::~Scene() 
{
    delete dbManager;
}

void Scene::init()
{
    dbManager = new DBManager();
    toggleActive = 0;

    layoutBuild();
}

void Scene::update(float deltaTime, UIControlFlags* rControlFlags) 
{

}

void Scene::layoutBuild()
{
    layoutBuildProfilePanel();
    layoutBuildMainPanel();
    layoutBuildActionPanel();
}

void Scene::layoutBuildProfilePanel()
{
    profilePanelConstrains.panelView = (Rectangle){5, 5, SCREEN_WIDTH_DEFAULT*.3f, SCREEN_HEIGHT_DEFAULT*.6f};
    // NOTE: Grid
    profilePanelConstrains.dataGrid[0][0] = (Rectangle){10, 10, SCREEN_WIDTH_DEFAULT*.3f*.5f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}; // Col 1 -Row 1
    profilePanelConstrains.dataGrid[0][1] = (Rectangle){10, 10+(float)GuiGetStyle(DEFAULT, TEXT_SIZE), SCREEN_WIDTH_DEFAULT*.3f*.5f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}; // Col 1 - Row 2
    profilePanelConstrains.dataGrid[0][2] = (Rectangle){10, 10+(float)GuiGetStyle(DEFAULT, TEXT_SIZE)*2, SCREEN_WIDTH_DEFAULT*.3f*.5f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}; // Col 1 - Row 3
    profilePanelConstrains.dataGrid[1][2] = (Rectangle){SCREEN_WIDTH_DEFAULT*.3f*.5f-5, 10+(float)GuiGetStyle(DEFAULT, TEXT_SIZE)*2, SCREEN_WIDTH_DEFAULT*.3f*.5f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}; // Col 2 - Row 3
    profilePanelConstrains.dataGrid[1][0] = (Rectangle){SCREEN_WIDTH_DEFAULT*.3f*.5f-5, 10, SCREEN_WIDTH_DEFAULT*.3f*.5f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}; // Col 2 - Row 3
    profilePanelConstrains.dataGrid[1][1] = (Rectangle){SCREEN_WIDTH_DEFAULT*.3f*.5f-5, 10+(float)GuiGetStyle(DEFAULT, TEXT_SIZE), SCREEN_WIDTH_DEFAULT*.3f*.5f-5, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}; // Col 2 - Row 3
}

void Scene::layoutBuildMainPanel()
{
    mainPanelConstrains.entryHeight = (float)GuiGetStyle(DEFAULT, TEXT_SIZE)*10.0f;
    mainPanelConstrains.entryGap = 5;
    mainPanelConstrains.panelScrArea = {SCREEN_WIDTH_DEFAULT*.3+5, 5, SCREEN_WIDTH_DEFAULT*.7-5, SCREEN_HEIGHT_DEFAULT-5};
    mainPanelConstrains.panelContent = {5+SCREEN_WIDTH_DEFAULT*.3+10, 5+10, SCREEN_WIDTH_DEFAULT*.7-5-10, 
        (float)((mainPanelConstrains.entryHeight+mainPanelConstrains.entryGap) * dbManager->generatorCount()) *1.05f};
    mainPanelConstrains.panelView = { 0 };
    mainPanelConstrains.panelScroll = { 0, 0 };
}
void Scene::layoutBuildActionPanel()
{
}

void Scene::draw(UIControlFlags* rControlFlags) 
{
    drawProfile();

    // NOTE: General Actions Panel
    int dump = GuiPanel((Rectangle){5, 5+SCREEN_HEIGHT_DEFAULT*.6f, SCREEN_WIDTH_DEFAULT*.3f, SCREEN_HEIGHT_DEFAULT*.4-5}, NULL);
    // Exit game
    if (GuiButton((Rectangle){ 25, 1050, 125, 30 }, GuiIconText(ICON_EXIT, "Exit Game"))) rControlFlags->quit = true;
    

    drawIdleGenerators();

}

void Scene::drawProfile()
{
    ProfileEntry profile = dbManager->getProfileData();
    // NOTE: Player Info Panel
    int dump = GuiPanel(profilePanelConstrains.panelView, NULL);
    // ID
    std::string id = "Id: " + std::to_string(profile.id);
    GuiLabel(profilePanelConstrains.dataGrid[0][0], id.c_str());
    // Name
    std::string user_id = "Name: " + profile.user_name;
    GuiLabel(profilePanelConstrains.dataGrid[0][1], user_id.c_str());
    // Rank
    std::string rank = "Rank: " + std::to_string(profile.rank_id);
    GuiLabel(profilePanelConstrains.dataGrid[0][2], rank.c_str());
    // Current Exp
    std::string curr_exp = "Current Exp: " + std::to_string(profile.current_exp);
    GuiLabel(profilePanelConstrains.dataGrid[1][2], curr_exp.c_str());
    // test
    GuiLabel(profilePanelConstrains.dataGrid[1][0], curr_exp.c_str());
    GuiLabel(profilePanelConstrains.dataGrid[1][1], curr_exp.c_str());
}

void Scene::drawIdleGenerators() 
{
    int dump;

    GuiScrollPanel(mainPanelConstrains.panelScrArea, nullptr, mainPanelConstrains.panelContent, &mainPanelConstrains.panelScroll, &mainPanelConstrains.panelView);
    
    BeginScissorMode(mainPanelConstrains.panelView.x, mainPanelConstrains.panelView.y, mainPanelConstrains.panelView.width, mainPanelConstrains.panelView.height);
    int i = 0;
    for(auto gen : dbManager->getGenerators()) {
        Rectangle contentPos = {15+mainPanelConstrains.panelScrArea.x + mainPanelConstrains.panelScroll.x, mainPanelConstrains.panelScrArea.y + ((mainPanelConstrains.entryHeight + mainPanelConstrains.entryGap) * i) + mainPanelConstrains.panelScroll.y + 15, SCREEN_WIDTH_DEFAULT*.7f*.7, (float)mainPanelConstrains.entryHeight};
        dump = GuiPanel(contentPos, NULL);
        GuiLabel((Rectangle){contentPos.x + 10, contentPos.y + 5, SCREEN_WIDTH_DEFAULT*.7f-20, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)}, gen.name.c_str());
        // NOTE: Buy/Upgrade
        if (GuiButton((Rectangle){contentPos.x + 10 + contentPos.width, contentPos.y, 100, (float)mainPanelConstrains.entryHeight}, "BUY")) auto buy = gen.id;

        GuiToggleGroup((Rectangle){contentPos.x + 10 + contentPos.width + 110, contentPos.y, (float)GuiGetStyle(DEFAULT, TEXT_SIZE)*5, (float)mainPanelConstrains.entryHeight}, "x1;x10;Max", &toggleActive);

        i++;
    }
    EndScissorMode();

}

}

