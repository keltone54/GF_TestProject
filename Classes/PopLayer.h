#ifndef __POP_LAYER__
#define __POP_LAYER__

#include "cocos2d.h"

USING_NS_CC;

class PopLayer : public cocos2d::LayerColor
{
private:
	Sprite * box;

public:
	virtual bool init();

	void setBoxSize(float _width, float _height);
	void setBoxSize(Size _size);
	void setBoxSize(Vec2 _vec2);
	void setBoxPosition(Vec2 _pos);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void doClose(Object* obj);

	CREATE_FUNC(PopLayer);
};

#endif //__POP_LAYER__