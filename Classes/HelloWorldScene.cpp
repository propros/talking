#include "HelloWorldScene.h"

USING_NS_CC;

#define time 0.05f

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    copyFile("testRapid.xml");
    
    di=Sprite::create("di.png");
    di->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
    addChild(di,1);
    
    content="石家庄t苍，放大！镜和科技发达ui啊是否能卡的岚互娱科技有限公司德克萨斯大";
    
    labelcontent=Label::createWithSystemFont("", "", 12);
    labelcontent->setAnchorPoint(Vec2(0, 0.5));
    labelcontent->setPosition(Vec2(70,di->getContentSize().height/3 ));
    labelcontent->setTag(5);
    labelcontent->setWidth(330);
    labelcontent->setHeight(di->getContentSize().height/1.5);
    labelcontent->setLineBreakWithoutSpace(true);
    di->addChild(labelcontent,1);
    
    
    labelname=Label::createWithSystemFont("苍岚", "", 16);
    labelname->setPosition(Vec2(50, di->getContentSize().height-10 ));
    di->addChild(labelname,1);
    
    auto touchlistener=EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, di);
    
    role1=Sprite::create("icon1.png");
    
    role1->setAnchorPoint(Vec2(0, 0));
    role1->setPosition(Vec2(visibleSize.width-di->getContentSize().width,di->getContentSize().height));
    di->addChild(role1,1);
    
    role2=Sprite::create("icon2.png");
    role2->setScale(2);
    role2->setAnchorPoint(Vec2(1, 0));
    role2->setPosition(Vec2(di->getContentSize().width, di->getContentSize().height));
    di->addChild(role2,2);
    
    dizuo=Sprite::create("dizuo.png");
    dizuo->setScale(0.6);
    dizuo->setAnchorPoint(Vec2(1, 0.8));
    dizuo->setPosition(Vec2(di->getContentSize().width, dizuo->getContentSize().height));
    di->addChild(dizuo);
    
    jiantou=Sprite::create("jiantou.png");
    jiantou->setAnchorPoint(Vec2(0.15, 0.5));
    jiantou->setScale(0.6);
    jiantou->setPosition(Point(dizuo->getPositionX()-dizuo->getContentSize().width/2,dizuo->getPositionY()));
    di->addChild(jiantou,1);
    
    auto moveup=MoveTo::create(0.5, Point(dizuo->getPositionX()-dizuo->getContentSize().width/2,dizuo->getPositionY()+jiantou->getContentSize().height/3));
    auto movedown=MoveTo::create(0.5, Point(dizuo->getPositionX()-dizuo->getContentSize().width/2,dizuo->getPositionY()));
    auto seq=Sequence::create(moveup,movedown,NULL);
    jiantou->runAction(RepeatForever::create(seq));
    
    
    schedule(schedule_selector(HelloWorld::logic),time);
    n = 0 ;
    readxml();
    
    return true;
}

std::vector<std::string>talklist;

void HelloWorld::copyFile(std::string filename)
{
    FileUtils* fu=FileUtils::getInstance();
    std::string wrpath=fu->getWritablePath();
    wrpath+=filename;
    if (!fu->isFileExist(wrpath)) {
        std::string datapath=fu->fullPathForFilename(filename.c_str());
        std::string pfilecontent=fu->getStringFromFile(datapath);
        log("%s",pfilecontent.c_str());
        FILE* file=fopen(wrpath.c_str(), "wb");
        if (file) {
            fputs(pfilecontent.c_str(), file);
            fclose(file);
        }
    }
}

void HelloWorld::readxml()
{
    //获取可以写的路径
    std::string path=FileUtils::getInstance()->getWritablePath();
    path+="testRapid.xml";//拼接路径
    //加载文档
    myDoucument=new XMLDocument();
    XMLError errID= myDoucument->LoadFile(path.c_str());
//    log("%s",path.c_str());
    //判断是否解析错误
    if (errID!=0) {
        log("error...");
        return;
    }
    //解析

    
    root=myDoucument->RootElement();
    chd=root->FirstChildElement();
    attr=chd->FirstAttribute();

}



void HelloWorld::logic(float t)
{
    
    std::string str = content.substr(0, this->n);
    this->labelcontent->setString(str);
    long length = content.length();
    if (n<length) {
        char ch = getContent()[n];
        //中文在ASCII码中是-127~0
        if (ch > -127 && ch< 0)
        {
            //一个中文占3个字节
            n+=3;
        }
        else
        {
            n++;
        }
    }

    if (n > content.length()) {
        this->unschedule(schedule_selector(HelloWorld::logic));
    }
    
    
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    auto location=touch->getLocation();
    auto rect=Rect(di->getPositionX()-di->getContentSize().width/2, di->getPositionY()-di->getContentSize().height/2, di->getContentSize().width, di->getContentSize().height);
    if (rect.containsPoint(location)) {
        if (chd) {
            element=chd->FirstChildElement();
            
            element=element->NextSiblingElement();
            std::string a=element->GetText();
            labelname->setString(a);
            element= element->NextSiblingElement();

            content=element->GetText();
            
            chd=chd->NextSiblingElement();
            
            if (role) {
                role1->setColor(Color3B(255, 255, 255));
                role1->setScale(2);
                role2->setColor(Color3B(77, 77, 77));
                role2->setScale(1);
                role=false;
            }else{
                role=true;
                role2->setScale(2);
                role1->setScale(1);
                role1->setColor(Color3B(77, 77, 77));
                role2->setColor(Color3B(255, 255, 255));
            }
        }else{
            log("wanle");
            delete myDoucument;
            
        }
        n=0;
        schedule(schedule_selector(HelloWorld::logic),time);
        
    }

    return true;
    //
}


























