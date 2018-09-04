#ifndef __POP_LAYER__
#define __POP_LAYER__

#include "cocos2d.h"

USING_NS_CC;

class PopLayer : public cocos2d::LayerColor
{
private:

	Sprite * box;

	Texture2D* btnImage;

	Sprite* btn[4];
	Label* btntxt[4];

	int nSelected;
	bool bPressed;

public:
	virtual bool init();
	
	void initListener();
	void initValue();

	void callEveryFrame(float f);

	void setBoxSize(float _width, float _height);
	void setBoxSize(Size _size);
	void setBoxSize(Vec2 _vec2);
	void setBoxPosition(Vec2 _pos);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void buttonSelect();

	void doClose(Object* obj);
	void doReturnStartScene(Object* obj);

	CREATE_FUNC(PopLayer);
};

#endif //__POP_LAYER__