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
    float topMargin = 10;
    float leftMargin = 10;
    float colWidth = SCREEN_WIDTH_DEFAULT*.3f*.5f-15;
    float rowHeight = (float)GuiGetStyle(DEFAULT, TEXT_SIZE)*2.0+topMargin;
    float colSeparation = 20;
    float rowSeparation = 5;
    float textMargin = 5;

    profilePanelConstrains.panelView = (Rectangle){5, 5, SCREEN_WIDTH_DEFAULT*.3f, SCREEN_HEIGHT_DEFAULT*.6f};
    // NOTE: Grid Cell Panel
    profilePanelConstrains.gridPanel[0][0] = (Rectangle){leftMargin, topMargin+rowSeparation, colWidth, rowHeight}; // Col 1 -Row 1
    profilePanelConstrains.gridPanel[0][1] = (Rectangle){leftMargin, topMargin+rowSeparation*2+rowHeight, colWidth, rowHeight}; // Col 1 - Row 2
    profilePanelConstrains.gridPanel[0][2] = (Rectangle){leftMargin, topMargin+rowSeparation*3+rowHeight*2, colWidth, rowHeight}; // Col 1 - Row 3
    profilePanelConstrains.gridPanel[0][3] = (Rectangle){leftMargin, topMargin+rowSeparation*4+rowHeight*3, colWidth, rowHeight}; // Col 1 - Row 4
    profilePanelConstrains.gridPanel[0][4] = (Rectangle){leftMargin, topMargin+rowSeparation*5+rowHeight*4, colWidth, rowHeight}; // Col 1 - Row 5
    profilePanelConstrains.gridPanel[0][5] = (Rectangle){leftMargin, topMargin+rowSeparation*6+rowHeight*5, colWidth, rowHeight}; // Col 1 - Row 6
    profilePanelConstrains.gridPanel[0][6] = (Rectangle){leftMargin, topMargin+rowSeparation*7+rowHeight*6, colWidth, rowHeight}; // Col 1 - Row 7
    profilePanelConstrains.gridPanel[0][7] = (Rectangle){leftMargin, topMargin+rowSeparation*8+rowHeight*7, colWidth, rowHeight}; // Col 1 - Row 8
    profilePanelConstrains.gridPanel[0][8] = (Rectangle){leftMargin, topMargin+rowSeparation*9+rowHeight*8, colWidth, rowHeight}; // Col 1 - Row 9
    profilePanelConstrains.gridPanel[0][9] = (Rectangle){leftMargin, topMargin+rowSeparation*10+rowHeight*9, colWidth, rowHeight}; // Col 1 - Row 10
    profilePanelConstrains.gridPanel[1][0] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation, colWidth, rowHeight}; // Col 2 - Row 1
    profilePanelConstrains.gridPanel[1][1] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*2+rowHeight, colWidth, rowHeight}; // Col 2 - Row 2
    profilePanelConstrains.gridPanel[1][2] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*3+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 3
    profilePanelConstrains.gridPanel[1][3] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*4+rowHeight*3, colWidth, rowHeight}; // Col 2 - Row 4
    profilePanelConstrains.gridPanel[1][4] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*5+rowHeight*4, colWidth, rowHeight}; // Col 2 - Row 5
    profilePanelConstrains.gridPanel[1][5] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*6+rowHeight*5, colWidth, rowHeight}; // Col 2 - Row 6
    profilePanelConstrains.gridPanel[1][6] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*7+rowHeight*6, colWidth, rowHeight}; // Col 2 - Row 7
    profilePanelConstrains.gridPanel[1][7] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*8+rowHeight*7, colWidth, rowHeight}; // Col 2 - Row 8
    profilePanelConstrains.gridPanel[1][8] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*9+rowHeight*8, colWidth, rowHeight}; // Col 2 - Row 9
    profilePanelConstrains.gridPanel[1][9] = (Rectangle){leftMargin+colWidth+colSeparation, topMargin+rowSeparation*10+rowHeight*9, colWidth, rowHeight}; // Col 2 - Row 10
    // NOTE: Data Grid
    profilePanelConstrains.dataGrid[0][0] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation, colWidth, rowHeight}; // Col 1 -Row 1
    profilePanelConstrains.dataGrid[0][1] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*2+rowHeight, colWidth, rowHeight}; // Col 1 - Row 2
    profilePanelConstrains.dataGrid[0][2] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*3+rowHeight*2, colWidth, rowHeight}; // Col 1 - Row 3
    profilePanelConstrains.dataGrid[0][3] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*4+rowHeight*3, colWidth, rowHeight}; // Col 1 - Row 4
    profilePanelConstrains.dataGrid[0][4] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*5+rowHeight*4, colWidth, rowHeight}; // Col 1 - Row 5
    profilePanelConstrains.dataGrid[0][5] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*6+rowHeight*5, colWidth, rowHeight}; // Col 1 - Row 6
    profilePanelConstrains.dataGrid[0][6] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*7+rowHeight*6, colWidth, rowHeight}; // Col 1 - Row 7
    profilePanelConstrains.dataGrid[0][7] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*8+rowHeight*7, colWidth, rowHeight}; // Col 1 - Row 8
    profilePanelConstrains.dataGrid[0][8] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*9+rowHeight*8, colWidth, rowHeight}; // Col 1 - Row 9
    profilePanelConstrains.dataGrid[0][9] = (Rectangle){leftMargin+textMargin, topMargin+rowSeparation*10+rowHeight*9, colWidth, rowHeight}; // Col 1 - Row 10
    profilePanelConstrains.dataGrid[1][0] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation, colWidth, rowHeight}; // Col 2 - Row 1
    profilePanelConstrains.dataGrid[1][1] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*2+rowHeight, colWidth, rowHeight}; // Col 2 - Row 2
    profilePanelConstrains.dataGrid[1][2] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*3+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 3
    profilePanelConstrains.dataGrid[1][3] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*4+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 4
    profilePanelConstrains.dataGrid[1][4] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*5+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 5
    profilePanelConstrains.dataGrid[1][5] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*6+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 6
    profilePanelConstrains.dataGrid[1][6] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*7+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 7
    profilePanelConstrains.dataGrid[1][7] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*8+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 8
    profilePanelConstrains.dataGrid[1][8] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*9+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 9
    profilePanelConstrains.dataGrid[1][9] = (Rectangle){leftMargin+colWidth+colSeparation+textMargin, topMargin+rowSeparation*10+rowHeight*2, colWidth, rowHeight}; // Col 2 - Row 10
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
    // Name
    std::string user_id = "Name: " + profile.user_name;

    dump = GuiPanel(profilePanelConstrains.gridPanel[0][0], NULL);
    GuiLabel(profilePanelConstrains.dataGrid[0][0], user_id.c_str());
    
    // Rank
    std::string curr_exp = to_string_precision(profile.current_exp, 0);
    std::string rank = "Rank: " + std::to_string(profile.rank_id) + " (" + curr_exp + ")";
    
    dump = GuiPanel(profilePanelConstrains.gridPanel[1][0], NULL);
    GuiLabel(profilePanelConstrains.dataGrid[1][0], rank.c_str());
    
    // Wealth
    std::string wealth = "Total Wealth: " + to_string_precision(profile.lifetime_currency, 0);
    
    dump = GuiPanel(profilePanelConstrains.gridPanel[0][1], NULL);
    GuiLabel(profilePanelConstrains.dataGrid[0][1], wealth.c_str());
    
    // Current Gold
    std::string current_gold = "Current Gold: " + to_string_precision(profile.current_gold, 0);
    
    dump = GuiPanel(profilePanelConstrains.gridPanel[1][1], NULL);
    GuiLabel(profilePanelConstrains.dataGrid[1][1], current_gold.c_str());
    
    // Prestige Points
    std::string prestige = "Prestige: " + to_string_precision(profile.prestige, 1);
    
    dump = GuiPanel(profilePanelConstrains.gridPanel[0][2], NULL);
    GuiLabel(profilePanelConstrains.dataGrid[0][2], prestige.c_str());
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

