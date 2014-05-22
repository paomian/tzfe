#include "HelloWorldScene.h"
#include "CardSprite.h"

USING_NS_CC;

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
    
    score = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
    this->addChild(layerColorBG);
    
    auto labelTTFSdut = LabelTTF::create("SDUT", "HirakakuProN-06", 80);
    labelTTFSdut -> setPosition(visibleSize.width/2,visibleSize.height - 250);
    addChild(labelTTFSdut);
    
    auto labelTTFCardScoreName = LabelTTF::create("分数", "HirakakuProN-06", 80);
    labelTTFCardScoreName -> setPosition(Point(visibleSize.width/5,visibleSize.height - 150));
    addChild(labelTTFCardScoreName);
    
    labelTTFCardScore = LabelTTF::create("0", "HirakakuProN-06", 80);
    labelTTFCardScore -> setPosition(visibleSize.width/2 + 150, visibleSize.height-150);
    addChild(labelTTFCardScore);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    createCardSprite(visibleSize);
    
    autoCreateCardNumber();
    autoCreateCardNumber();
    //cardArr[2][2]->setNumber(8192);
    //cardArr[1][1]->setNumber(16384);

        return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Point touchPo = touch->getLocation();
    
    firstX = touchPo.x;
    firstY = touchPo.y;
    
    return true;
}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Point touchPo = touch->getLocation();
    endX = firstX-touchPo.x;
    endY = firstY-touchPo.y;
    
    if (abs(endX) > abs(endY)) {
        //lf
        if (endX+5>0) {
            //l
            if(doDown())
            {autoCreateCardNumber();
                doCheckGameOver();
            }
           
        }else{
            if(doUp())
            {autoCreateCardNumber();
                doCheckGameOver();
            }
        }
    }else{
        if (endY + 5 > 0) {
            //down

            if(doLeft())
            {autoCreateCardNumber();
                doCheckGameOver();
            }
        }else{

            if(doRight())
            {autoCreateCardNumber();
                doCheckGameOver();
            }
        }
    }
}

void HelloWorld::doCheckGameOver() {
    bool isGameOver = true;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            auto a = cardArr[x][y]->getNumber();
            if (
                cardArr[x][y]->getNumber() == 0 ||
                (x > 0 && (a == cardArr[x-1][y]->getNumber())) ||
                (x < 3 && (a == cardArr[x+1][y]->getNumber())) ||
                (x > 0 && (a == cardArr[x][y-1]->getNumber())) ||
                (x < 3 && (a == cardArr[x][y+1]->getNumber())))
            {
                isGameOver = false;
            }
        }
    }
        if (isGameOver) {
            log("gameover");
             Director::getInstance()->replaceScene(TransitionCrossFade::create(1, HelloWorld::createScene()));

        }
}

void HelloWorld::autoCreateCardNumber() {
    int i = CCRANDOM_0_1() * 4;
    int j = CCRANDOM_0_1() * 4;
    if (cardArr[i][j] -> getNumber() > 0) {
        autoCreateCardNumber();
    }else{
        cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1?4:2);
        cardArr[i][j] -> setScale(0.5f);
        cardArr[i][j] -> runAction(ScaleTo::create(0.1f, 1.0f));
    }
}

void HelloWorld::createCardSprite(cocos2d::Size size) {
    int lon = (size.width-28)/4;
    for (int i = 0; i < 4; i++) {
        for (int j =0; j < 4; j++) {
            CardSprite *card = CardSprite::createCardSprite(0, lon, lon, lon * j + 90, lon * i + 90+size.height/6);
            addChild(card);
            cardArr[i][j] = card;
        }
    }
}

bool HelloWorld::doLeft(){
    log("doleft");
    bool isdo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int x1 = x + 1; x1 < 4; x1++) {
                if (cardArr[x1][y]->getNumber() > 0) {
                    if (cardArr[x][y] ->getNumber() <= 0) {
                        cardArr[x][y] -> setNumber(cardArr[x1][y] -> getNumber());
                        cardArr[x1][y] -> setNumber(0);
                        
                        x--;
                        isdo = true;
                    }else if(cardArr[x][y] -> getNumber() == cardArr[x1][y] -> getNumber()) {
                        cardArr[x][y] -> setNumber(cardArr[x][y] -> getNumber() * 2);
                        cardArr[x][y] -> setScale(0.5f);
                        cardArr[x][y] -> runAction(ScaleTo::create(0.1f, 1.0f));
                        cardArr[x1][y] -> setNumber(0);
                        score += cardArr[x][y] -> getNumber();
                        labelTTFCardScore->setString(__String::createWithFormat("%i",score) -> getCString());
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool HelloWorld::doRight(){
    log("doright");
    bool isdo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 3; x >= 0; x--) {
            for (int x1 = x - 1; x1 >= 0; x1--) {
                if (cardArr[x1][y]->getNumber() > 0) {
                    if (cardArr[x][y] ->getNumber() <= 0) {
                        cardArr[x][y] -> setNumber(cardArr[x1][y] -> getNumber());
                        cardArr[x1][y] -> setNumber(0);
                        
                        x++;
                        isdo = true;
                    }else if(cardArr[x][y] -> getNumber() == cardArr[x1][y] -> getNumber()) {
                        cardArr[x][y] -> setNumber(cardArr[x][y] -> getNumber() * 2);
                        cardArr[x][y] -> setScale(0.5f);
                        cardArr[x][y] -> runAction(ScaleTo::create(0.1f, 1.0f));
                        cardArr[x1][y] -> setNumber(0);
                        score += cardArr[x][y] -> getNumber();
                        labelTTFCardScore->setString(__String::createWithFormat("%i",score) -> getCString());
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool HelloWorld::doUp(){
    log("doup");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y >= 0; y--) {
            for (int y1 = y - 1; y1 >= 0; y1--) {
                if (cardArr[x][y1]->getNumber() > 0) {
                    if (cardArr[x][y] ->getNumber() <= 0) {
                        cardArr[x][y] -> setNumber(cardArr[x][y1] -> getNumber());
                        cardArr[x][y1] -> setNumber(0);
                        
                        y++;
                        isdo = true;
                    }else if(cardArr[x][y] -> getNumber() == cardArr[x][y1] -> getNumber()) {
                        cardArr[x][y] -> setNumber(cardArr[x][y] -> getNumber() * 2);
                        cardArr[x][y] -> setScale(0.5f);
                        cardArr[x][y] -> runAction(ScaleTo::create(0.1f, 1.0f));
                        cardArr[x][y1] -> setNumber(0);
                        score += cardArr[x][y] -> getNumber();
                        labelTTFCardScore->setString(__String::createWithFormat("%i",score) -> getCString());
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool HelloWorld::doDown(){
    log("dodown");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int y1 = y + 1; y1 < 4; y1++) {
                if (cardArr[x][y1]->getNumber() > 0) {
                    if (cardArr[x][y] ->getNumber() <= 0) {
                        cardArr[x][y] -> setNumber(cardArr[x][y1] -> getNumber());
                        cardArr[x][y1] -> setNumber(0);
                        
                        y--;
                        isdo = true;
                    }else if(cardArr[x][y] -> getNumber() == cardArr[x][y1] -> getNumber()) {
                        cardArr[x][y] -> setNumber(cardArr[x][y] -> getNumber() * 2);
                        cardArr[x][y] -> setScale(0.5f);
                        cardArr[x][y] -> runAction(ScaleTo::create(0.1f, 1.0f));
                        cardArr[x][y1] -> setNumber(0);
                        score += cardArr[x][y] -> getNumber();
                        labelTTFCardScore->setString(__String::createWithFormat("%i",score) -> getCString());
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}


