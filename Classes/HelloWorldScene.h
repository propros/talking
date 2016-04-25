#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <tinyxml2/tinyxml2.h>
USING_NS_CC;
using namespace tinyxml2;
//#include "TalkNode.hpp"


class HelloWorld : public cocos2d::Layer
{
public:
    Sprite* di;
    Label* labelcontent;
    Label* labelname;
    
    Sprite* role1;
    Sprite* role2;
    Sprite* jiantou;
    Sprite* dizuo;
    
    
    int n;
    std::string content;
    const char*  getContent(){return content.c_str();}
    bool role=true;
    
    XMLDocument* myDoucument;
    XMLElement* root;
    XMLElement* chd;
    XMLElement* element;
    const XMLAttribute* attr;
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void copyFile(std::string filename);
    void readxml();
    void logic(float t);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
};

// .. . .
#endif // __HELLOWORLD_SCENE_H__
