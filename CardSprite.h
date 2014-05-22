//
//  CardSprite.h
//  tzfe
//
//  Created by ipaomian on 14-4-27.
//
//

#ifndef __tzfe__CardSprite__
#define __tzfe__CardSprite__

#include "cocos2d.h"

class CardSprite:public cocos2d::Sprite{
    //出书好游戏卡片的方法
public:
    static CardSprite *createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    void setNumber(int num);
    int getNumber();
    
private:

    int number;
    void enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);
    //显示数字的控件
    cocos2d::LabelTTF * labelTTFCardNumber;
    
    //显示的背景
    cocos2d::LayerColor *layerColorBG;
};

#endif /* defined(__tzfe__CardSprite__) */
