#include "EnemyCharacter.h"
#include "GlobalDef.h"

#include "EnemyAnimation.h"

bool EnemyCharacter::init(int _enemyType)
{
	if (!Node::init()) return false;
	//============================================================

	enemyType = _enemyType;

	initCharacter();
	initValue();
	debugLabel();

	//============================================================
	initListener();
	return true;
}

void EnemyCharacter::initCharacter()
{
	bodyBox = Sprite::create();
	this->addChild(bodyBox);

	eeAnim = EnemyAnimation::create(enemyType);

	eeAnim->setAnimation(0);
	bodyBox->addChild(eeAnim);

	bodyBox->setTextureRect(eeAnim->getHitBox());
	bodyBox->setColor(Color3B::GREEN);
	bodyBox->setOpacity(0); // 히트박스 켜기/끄기

	eeAnim->setPosition(Vec2(bodyBox->getContentSize().width / 2, 0));
	eeAnim->setScale(0.65f);

	setHealthBar();
}

void EnemyCharacter::initListener()
{
	this->schedule(schedule_selector(EnemyCharacter::callEveryFrame));
}

void EnemyCharacter::initValue()
{
	orderType = 0;
	m_isDead = false;
	m_deadAction = false;
	isCanMove = true;
	isPaused = false;
}

void EnemyCharacter::debugLabel()
{
}

void EnemyCharacter::setHealthBar()
{
	health = eeAnim->getHealth();
	healthSave = health;
	healthMax = health;

	healthBar = Sprite::create();
	healthBarBorder = Sprite::create();

	healthBar->setTextureRect(Rect(0, 0, bodyBox->getContentSize().width - 2, 6));
	healthBarBorder->setTextureRect(Rect(0, 0, bodyBox->getContentSize().width, 8));
	healthBar->setColor(Color3B::RED);
	healthBarBorder->setColor(Color3B::BLACK);

	healthBarBorder->setPosition(Vec2(0, bodyBox->getContentSize().height + 12));
	healthBar->setPosition(pPos4(healthBarBorder) + Vec2(1, 0));
	healthBar->setAnchorPoint(anc4);
	healthBarBorder->setAnchorPoint(anc4);

	bodyBox->addChild(healthBarBorder);
	healthBarBorder->addChild(healthBar);

	healthBarBorder->setVisible(false);
}

void EnemyCharacter::callEveryFrame(float f)
{
	if (health <= 0 && !m_isDead) { m_isDead = true; }

	if (!m_isDead)
	{
		if (isCanMove)
		{
			if (orderType == enemyOrder::Chase_)
			{
				if (targetPos.x < this->getPositionX() && !getFlipedX())
					setFlipedX(true);
				else if (targetPos.x > this->getPositionX() && getFlipedX())
					setFlipedX(false);
			}
		}
		if (orderType == enemyOrder::Chase_)
			chaseTarget();
		else if (orderType == enemyOrder::March_)
			marching();
	}
	else if (m_isDead && !m_deadAction)
		deadAction();

	if (health != healthSave) // 데미지 입었을 때
	{
		healthSave = health;

		if (!healthBarBorder->isVisible())
			healthBarBorder->setVisible(true);

		healthBar->setScaleX((float)health / healthMax);
	}
	
}


bool EnemyCharacter::getFlipedX()
{
	return eeAnim->isFlippedX();
}

void EnemyCharacter::setFlipedX(bool _flip)
{
	eeAnim->setFlippedX(_flip);
	int n = eeAnim->getSaveType();
	eeAnim->saveTypeReset();
	eeAnim->setAnimation(n);
}

void EnemyCharacter::order(int _order)
{
	orderType = _order;

	switch (_order)
	{
	case enemyOrder::Wait_:
		eeAnim->setAnimation(0);
		break;
	case enemyOrder::Chase_:
		eeAnim->setAnimation(1);
		break;
	case enemyOrder::Attack_:
		eeAnim->setAnimation(2);
		break;
	case enemyOrder::March_:
		eeAnim->setAnimation(1);
		break;
	}
}

void EnemyCharacter::chaseTarget()
{
	if (!eeAnim->getRanger())
	{
		if (targetPos.x - targetSize.width * 1.5 > this->getPositionX())
			this->setPositionX(this->getPositionX() + eeAnim->getMoveSpeed());
		else if (targetPos.x + targetSize.width * 1.5 < this->getPositionX())
			this->setPositionX(this->getPositionX() - eeAnim->getMoveSpeed());

		if (targetPos.y - eeAnim->getMoveSpeed() > this->getPositionY())
			this->setPositionY(this->getPositionY() + eeAnim->getMoveSpeed() / 2);
		else if (targetPos.y + eeAnim->getMoveSpeed() < this->getPositionY())
			this->setPositionY(this->getPositionY() - eeAnim->getMoveSpeed() / 2);
	}
}

void EnemyCharacter::marching()
{
	if (!eeAnim->isFlippedX())
		this->setPositionX(this->getPositionX() + eeAnim->getMoveSpeed());
	else if (eeAnim->isFlippedX())
		this->setPositionX(this->getPositionX() - eeAnim->getMoveSpeed());
	
	if (getDistance(this->getPosition(), targetPos, 1) < 150)
	{
		if((!eeAnim->isFlippedX() && this->getPositionX() < targetPos.x + targetSize.width * 2) ||
			(eeAnim->isFlippedX() && this->getPositionX() > targetPos.x - targetSize.width * 2))
			order(enemyOrder::Chase_);
	}
}

double EnemyCharacter::getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni)
{
	double c = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
	double t = c / _magni;

	return t;
}

void EnemyCharacter::deadAction()
{
	isCanMove = false;
	m_deadAction = true;

	auto seq = Sequence::create(
		CallFunc::create(CC_CALLBACK_0(EnemyCharacter::deathRandomAnimation, this)),
		DelayTime::create(5.0),
		RemoveSelf::create(),
		CallFunc::create(CC_CALLBACK_0(EnemyCharacter::RemoveFPAC, this)),
		nullptr);

	this->runAction(seq);
}

void EnemyCharacter::deathRandomAnimation()
{
	int rnd = random(3, 5);
	eeAnim->setAnimation(rnd);

	healthBarBorder->setVisible(false);
}

void EnemyCharacter::RemoveFPAC()
{
	this->removeFromParentAndCleanup(true);
}

void EnemyCharacter::pauseAnimation()
{
	eeAnim->pause(); isPaused = true;
}

void EnemyCharacter::resumeAnimation()
{
	eeAnim->resume(); isPaused = false;
}
