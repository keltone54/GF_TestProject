#ifndef __POP_CONFIRM__
#define __POP_CONFIRM__

#include "cocos2d.h"

USING_NS_CC;

class PopConfirm : public cocos2d::Layer
{
private:

	Sprite * box;

	Texture2D* btnImage;

	Sprite* btn[2];
	Label* btntxt[2];

	int nSelected;
	bool bPressed;

public:
	virtual bool init();

	void initListener();
	void initValue();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void buttonSelect();

	void doClose(Object* obj);
	void doConfirm(Object* obj);

	CREATE_FUNC(PopConfirm);
};

#endif //__POP_CONFIRM__