#include <Psapi.h>
#include "TestData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

USING_NS_CC;

#define KEY EventKeyboard::KeyCode

//=======================================

const short wSizeX = 1280;
const short wSizeY = 720;
const short wCenterX = wSizeX / 2;
const short wCenterY = wSizeY / 2;

#define wPos1 Vec2(0.0f, 0.0f)
#define wPos2 Vec2(wCenterX, 0.0f)
#define wPos3 Vec2(wSizeX, 0.0f)
#define wPos4 Vec2(0.0f, wCenterY)
#define wPos5 Vec2(wCenterX, wCenterY)
#define wPos6 Vec2(wSizeX, wCenterY)
#define wPos7 Vec2(0.0f, wSizeY)
#define wPos8 Vec2(wCenterX, wSizeY)
#define wPos9 Vec2(wSizeX, wSizeY)

#define anc1 Vec2(0.0f, 0.0f)
#define anc2 Vec2(0.5f, 0.0f)
#define anc3 Vec2(1.0f, 0.0f)
#define anc4 Vec2(0.0f, 0.5f)
#define anc5 Vec2(0.5f, 0.5f)
#define anc6 Vec2(1.0f, 0.5f)
#define anc7 Vec2(0.0f, 1.0f)
#define anc8 Vec2(0.5f, 1.0f)
#define anc9 Vec2(1.0f, 1.0f)

#define pPos1(_parent_) Vec2(0, 0)
#define pPos2(_parent_) Vec2(_parent_->getContentSize().width / 2, 0)
#define pPos3(_parent_) Vec2(_parent_->getContentSize().width, 0)
#define pPos4(_parent_) Vec2(0, _parent_->getContentSize().height / 2)
#define pPos5(_parent_) Vec2(_parent_->getContentSize().width / 2, _parent_->getContentSize().height / 2)
#define pPos6(_parent_) Vec2(_parent_->getContentSize().width, _parent_->getContentSize().height / 2)
#define pPos7(_parent_) Vec2(0, _parent_->getContentSize().height)
#define pPos8(_parent_) Vec2(_parent_->getContentSize().width / 2, _parent_->getContentSize().height)
#define pPos9(_parent_) Vec2(_parent_->getContentSize().width, _parent_->getContentSize().height)

enum actList
{
	Wait,
	Move,
	Attack,
	Die,
	Victory,
	VictoryLoop,
	shotA,
	mgA,
	mgB,
	mgC
};

#define createNoti(_class, _name, _func, _target) NotificationCenter::sharedNotificationCenter()->addObserver(_target, callfuncO_selector(_class::_func), _name, NULL)

#define sendNoti(_message, _name) auto notiParam = String::create(_message);\
NotificationCenter::sharedNotificationCenter()->postNotification(_name, notiParam)

#define deleteAllNoti(_target) NotificationCenter::sharedNotificationCenter()->removeAllObservers(this)