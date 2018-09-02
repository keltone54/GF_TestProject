#include <Psapi.h>
#include "TestData.h"

USING_NS_CC;

#define KEY EventKeyboard::KeyCode


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