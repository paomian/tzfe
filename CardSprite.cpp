//
//  CardSprite.cpp
//  tzfe
//
//  Created by ipaomian on 14-4-27.
//
//

#include "CardSprite.h"

USING_NS_CC;

CardSprite * CardSprite::createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY){
    CardSprite *enemy = new CardSprite();
    if (enemy && enemy->init()) {
        enemy->autorelease();
        enemy->enemyInit(numbers, wight, height, CardSpriteX, CardSpriteY);
        
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

bool CardSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

void CardSprite::setNumber(int num) {
    number = num;
    
    if (number >= 0) {
        labelTTFCardNumber->setFontSize(100);
    }
    if (number >= 16) {
        labelTTFCardNumber->setFontSize(90);
    }
    if (number >= 128) {
        labelTTFCardNumber->setFontSize(60);
    }
    if (number >= 1024) {
        labelTTFCardNumber->setFontSize(40);
    }
    
    if (number == 0) {
        layerColorBG->setColor(cocos2d::Color3B(200,190,180));
    }
    if (number == 2) {
        layerColorBG->setColor(cocos2d::Color3B(240,230,220));
    }
    if (number == 4) {
        layerColorBG->setColor(cocos2d::Color3B(240,220,200));
    }
    if (number == 8) {
        layerColorBG->setColor(cocos2d::Color3B(240,180,120));
    }
    if (number == 16) {
        layerColorBG->setColor(cocos2d::Color3B(240,140,90));
    }
    if (number == 32) {
        layerColorBG->setColor(cocos2d::Color3B(240,120,90));
    }
    if (number == 64) {
        layerColorBG->setColor(cocos2d::Color3B(240,90,60));
    }
    if (number == 128) {
        layerColorBG->setColor(cocos2d::Color3B(240,90,60));
    }
    if (number == 256) {
        layerColorBG->setColor(cocos2d::Color3B(240,200,70));
    }
    if (number == 512) {
        layerColorBG->setColor(cocos2d::Color3B(240,200,70));
    }
    if (number == 1024) {
        layerColorBG->setColor(cocos2d::Color3B(0,130,0));
    }
    if (number >= 2048) {
        labelTTFCardNumber->setColor(cocos2d::Color3B(255,0,0));
        layerColorBG->setColor(cocos2d::Color3B(0,130,0));
    }
    if (number < 2048) {
        labelTTFCardNumber->setColor(cocos2d::Color3B(255,255,255));
    }
    
    if (number > 0) {
        labelTTFCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
    }else{
        labelTTFCardNumber->setString("");
    }
}

int CardSprite::getNumber() {
    return number;
}

void CardSprite::enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY) {
    number = numbers;
    
    setTextureRect(Rect(0,0,wight-15,height-15));
    setPosition(Point(CardSpriteX,CardSpriteY));
    layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255), wight-15, height-15);
    //layerColorBG->setPosition(Point(CardSpriteX,CardSpriteY));
    
    if (number > 0) {
        labelTTFCardNumber = cocos2d::LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "HirakakuProN-06", 100);
        labelTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width/2,layerColorBG->getContentSize().height/2));
        layerColorBG->addChild(labelTTFCardNumber);
    }else{
        labelTTFCardNumber = cocos2d::LabelTTF::create("", "HirakakuProN-06", 100);
        labelTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width/2,layerColorBG->getContentSize().height/2));
        layerColorBG->addChild(labelTTFCardNumber);
    }
    //setAnchorPoint(Point(0.5f, 0.5f));
    //this->setAnchorPoint(Point(CardSpriteX,CardSpriteY));
    //this->setAnchorPoint( Point::ANCHOR_TOP_RIGHT);
    this->addChild(layerColorBG);
}