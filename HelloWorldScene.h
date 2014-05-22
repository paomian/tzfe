#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    bool doLeft();
    bool doRight();
    bool doUp();
    bool doDown();
    
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    void autoCreateCardNumber();
    void doCheckGameOver();
    
private:
    int firstX,firstY,endX,endY;
    int score;
    cocos2d::LabelTTF *labelTTFCardScore;
    CardSprite *cardArr[4][4];
    void createCardSprite(cocos2d::Size size);
};

#endif // __HELLOWORLD_SCENE_H__
