#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    //initialize the starting velocity
    velocity = Vec2(120.0, 120.0);
    
    //initalize the DVD logo sprite
    sprite = Sprite::create("DVD_video_logo.png");
    if (sprite == nullptr)
    {
        problemLoading("'DVD_video_logo.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        sprite->setScale(0.15f, 0.15f);
        
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
        this->scheduleUpdate();
    }
    return true;
}

//update method
void HelloWorld::update(float delta){
    //get needed variables
    auto position = sprite->getPosition();
    auto spriteBox = sprite->getBoundingBox();
    
    //update position
    position += velocity * delta;
    sprite->setPosition(position);
    //account for visible origin offset
    position -= Director::getInstance()->getVisibleOrigin();
    
    //collision detection and handling
    if (position.x - (spriteBox.size.width/2)  < 0 || position.x + (spriteBox.size.width/2)  > Director::getInstance()->getVisibleSize().width){
        velocity.x *= -1;
        sprite->setColor(Color3B(cocos2d::RandomHelper::random_int(1, 255), cocos2d::RandomHelper::random_int(1, 255), cocos2d::RandomHelper::random_int(1, 255)));
    }
    if (position.y - (spriteBox.size.height/2)  < 0 || position.y + (spriteBox.size.height/2) > Director::getInstance()->getVisibleSize().height){
        velocity.y *= -1;
        sprite->setColor(Color3B(cocos2d::RandomHelper::random_int(1, 255), cocos2d::RandomHelper::random_int(1, 255), cocos2d::RandomHelper::random_int(1, 255)));
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif


}
