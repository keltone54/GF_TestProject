#include "TestScene.h"
#include "GlobalDef.h"

#include "TestObject.h"

Scene* TestScene::createScene()
{
	return TestScene::create();
}

bool TestScene::init()
{
	if (!Scene::init()) return false;
	//============================================================
	// 레이어

	bgLayer = Layer::create();
	actLayer = Layer::create();
	this->addChild(bgLayer);
	this->addChild(actLayer);

	//============================================================
	// 초기화
	initValue();
	initBackground();
	debugLabel();
	//============================================================
	// 내용

	box = TestObject::create(1);
	box->setPosition(wPos5);
	this->addChild(box);

	winSize = Director::getInstance()->getWinSize();
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");

	if (this->createBox2dWorld(true))
		this->setBox2dWorld();

	//============================================================
	initListener();
	return true;
}

void TestScene::initListener()
{
	this->schedule(schedule_selector(TestScene::callEveryFrame));
	
	auto Keyboard_Listener = EventListenerKeyboard::create();
	Keyboard_Listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	
	auto Touch_Listener = EventListenerTouchOneByOne::create();
	Touch_Listener->setSwallowTouches(true);
	Touch_Listener->onTouchBegan = CC_CALLBACK_2(TestScene::onTouchBegan, this);
	Touch_Listener->onTouchMoved = CC_CALLBACK_2(TestScene::onTouchMoved, this);
	Touch_Listener->onTouchEnded = CC_CALLBACK_2(TestScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(Keyboard_Listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Touch_Listener, this);
}

void TestScene::initValue()
{
	
}

void TestScene::initBackground()
{
	/*auto bg = Sprite::create("bgstart.jpg");
	bg->setScale(0.66f);
	bg->setPosition(wPos5);
	bgLayer->addChild(bg);*/
}

void TestScene::debugLabel()
{
	lblMemory = Label::create("", "", 24);
	lblMemory->setPosition(wPos1 + Vec2(0, 70));
	lblMemory->setAnchorPoint(anc1);
	lblMemory->setColor(Color3B::WHITE);
	this->addChild(lblMemory, 101);
}

void TestScene::displayMemory()
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	lblMemory->setString(StringUtils::format("Memory: %dkb", (int)pmc.WorkingSetSize / 1024));
}

//=========================================================================

void TestScene::callEveryFrame(float f)
{
	displayMemory();

	int velocityIterations = 8;
	int positionIterations = 1;

	// Step : 물리 세계를 시뮬레이션한다.
	_world->Step(f, velocityIterations, positionIterations);

	// 만들어진 객체 만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) {
			Sprite* spriteData = (Sprite *)b->GetUserData();

			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

}

//=========================================================================

bool TestScene::onTouchBegan(Touch* touch, Event* event)
{
	//auto tp = touch->getLocation();
	
	Vec2 touchPoint = touch->getLocation();
	Vec2 touchPoint2 = Node::convertToNodeSpace(touchPoint);
	//log("nodeSpace..%f", touchPoint2.x);

	b2Body* tBall = this->getBodyAtTab(touchPoint2);

	bBallTouch = false;

	if (tBall == myBall)
	{
		log("touch start..");
		bBallTouch = true;
		startPoint = b2Vec2(touchPoint2.x / PTM_RATIO, touchPoint2.y / PTM_RATIO);
	}

	return true;
}

void TestScene::onTouchMoved(Touch * touch, Event * event)
{

}

void TestScene::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocation();
	Vec2 touchPoint2 = Node::convertToNodeSpace(touchPoint);

	if (myBall && bBallTouch)
	{
		log("touch end..");
		endPoint = b2Vec2(touchPoint2.x / PTM_RATIO, touchPoint2.y / PTM_RATIO);

		b2Vec2 force = endPoint - startPoint;

		force.x *= 250.0f;
		force.y *= 250.0f;

		myBall->ApplyForceToCenter(force, true);

		bBallTouch = false;
	}
}

void TestScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case KEY::KEY_SPACE:
		break;
	case KEY::KEY_GRAVE:
		break;
	case KEY::KEY_ESCAPE:
		Director::sharedDirector()->end();
		break;
	}
}











bool TestScene::createBox2dWorld(bool debug)
{
	// 월드 생성 시작 ---------------------------------------------------------

	// 중력의 방향을 결정한다.
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	// 디버그 드로잉 설정
	if (debug) {
		// 적색 : 현재 물리 운동을 하는 것
		// 회색 : 현재 물리 운동량이 없는 것
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	
	// 아래쪽.
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width * 2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
	// 왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	// 위쪽
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width * 2 / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	// 오른쪽
	groundEdge.Set(b2Vec2(winSize.width * 2 / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width * 2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 월드 생성 끝   ---------------------------------------------------------

	return true;
}

void TestScene::setBox2dWorld()
{
	myBall = this->addNewSprite(Vec2(25, 50), Size(50, 50), b2_dynamicBody, "test", 0);
	Sprite* myBallSprite = (Sprite *)myBall->GetUserData();
	Rect myBoundary = Rect(0, 0, winSize.width * 2, winSize.height);

	// 손쉬운 화면 스크롤링 기법인 Follow 액션을 사용해 넓은 화면을 이동시킨다.
	// 바디를 던지면 해당 바디에 카메라가 붙어 있으므로 자동으로 화면이 스크롤된다.
	this->runAction(Follow::create(myBallSprite, myBoundary));

	// 오른쪽 구석에 쌓아 놓을 바디들의 벡터값을 구성하고 스프라이트를 추가한다.
	float start = winSize.width * 2 - 130;

	struct BLOCK {
		Vec2 point;
		Size  size;
	};

	int const numBlocks = 6;
	struct BLOCK blocks[numBlocks] =
	{
		{ Vec2(start, 50), Size(10, 100) },
	{ Vec2(start + 50, 50), Size(10, 100) },
	{ Vec2(start + 25, 100 + 5), Size(200, 10) },
	{ Vec2(start, 120 + 50), Size(10, 100) },
	{ Vec2(start + 50, 120 + 50), Size(10, 100) },
	{ Vec2(start + 25, 220 + 5), Size(200, 10) }
	};

	for (int i = 0; i<numBlocks; i++)
	{
		this->addNewSprite(blocks[i].point, blocks[i].size, b2_dynamicBody, "test", 0);
	}
}

TestScene::~TestScene()
{
	delete _world;
	_world = nullptr;
}

void TestScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Scene::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(TestScene::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void TestScene::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

b2Body* TestScene::addNewSprite(Vec2 point, Size size, b2BodyType bodytype,	const char* spriteName, int type)
{
	// 바디데프 만들고 속성들을 지정한다.
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName) {
		if (strcmp(spriteName, "test") == 0) {
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			Sprite* sprite = Sprite::createWithTexture(texture,
				Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else {
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}

	// 월드에 바디데프의 정보로 바디를 만든다.
	b2Body* body = _world->CreateBody(&bodyDef);
	
	// 바디에 적용할 물리 속성용 바디의 모양을 만든다.
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	// Define the dynamic body fixture.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);
	
	return body;
}

b2Body * TestScene::getBodyAtTab(Point p)
{
	b2Fixture* fix;
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) {
			if (b->GetType() == b2_staticBody) continue;
			fix = b->GetFixtureList();
			if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y / PTM_RATIO))) {
				return b;
			}
		}
	}
	return nullptr;
}
