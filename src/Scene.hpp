#ifndef IG_SCENE
#define IG_SCENE
#include <raylib.h>
#include "dbModels/DBManager.hpp"
#include "dbModels/GeneratorModel.hpp"
#include "dbModels/ProfileModel.hpp"

typedef struct {
	bool quit;
	
} UIControlFlags;

typedef struct {
    Rectangle panelScrArea;
    Rectangle panelContent;
    Rectangle panelView;
    Vector2   panelScroll;
    int       entryHeight;
    int       entryGap;
} MainPanelConstraints;

class Scene 
{
public:
    Scene();
    ~Scene();
    void update(float deltaTime, UIControlFlags* rControlFlags);
    void init();
    void draw(UIControlFlags* rControlFlags);

private:
    DBManager* dbManager;
    IG::Profile* profile;
    IG::Generator* idleGenerators;
    int toggleActive;
    MainPanelConstraints mainPanelConstrains;
    
    void layoutBuild();
    void layoutBuildMainPanel();
    void drawProfile(); 
    void drawIdleGenerators(); 
};
#endif
