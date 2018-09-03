#ifndef __Pause_PopUp__
#define __Pause_PopUp__

#include "cocos2d.h"

USING_NS_CC;

class PlayerCharacter;

class PausePopup : public cocos2d::LayerColor
{
private:

	Sprite* box;
	Sprite* sdNoel;

	void initMenuBox();
	void menuResume(Ref* pSender);
	void menuSceneMove(Ref* pSender);
	void menuVoid(Ref* pSender);

	PlayerCharacter* m_pCharacter;

public:
	PausePopup();
	virtual bool init();

	void callEveryFrame(float f);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void setPopupPause(PlayerCharacter* _Character);

	void moveToSecondScene(Ref* pSender);


	CREATE_FUNC(PausePopup);
};

#endif //__Pause_PopUp__