#ifndef IG_SCENE
#define IG_SCENE
#include <raylib.h>
#include "dbModels/DBManager.hpp"

namespace IG 
{
typedef struct
{
    bool quit;
	
} UIControlFlags;

typedef struct
{
    Rectangle panelScrArea;
    Rectangle panelContent;
    Rectangle panelView;
    Vector2   panelScroll;
    int       entryHeight;
    int       entryGap;
} MainPanelConstrains;

typedef struct
{
    Rectangle panelView;
    Rectangle gridPanel[2][10];
    Rectangle dataGrid[2][10];

} ProfilePanelConstrains;


class Scene 
{
public:
    Scene();
    ~Scene();
    void update(float deltaTime, UIControlFlags* rControlFlags);
    void init();
    void draw(UIControlFlags* rControlFlags);

private:
    int toggleActive;

    ProfilePanelConstrains profilePanelConstrains;
    MainPanelConstrains mainPanelConstrains;
    
    DBManager* dbManager;
    
    void layoutBuild();
    void layoutBuildMainPanel();
    void layoutBuildProfilePanel();
    void layoutBuildActionPanel();
    void drawProfile(); 
    void drawIdleGenerators(); 
};
}
#endif
