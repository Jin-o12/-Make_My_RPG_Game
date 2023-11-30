#pragma once

#include <iostream>
#include "enum.h"
#include "Monster.h"

using std::cout;
using std::cin;
using std::endl;

void Monster::Initialize(DungeonLevel type)
{
	switch (type)
	{
	case EASY:
		strcpy_s(name_, "slime");
		attack_ = 2;
		defense_ = 1;
		HP_ = 5;
		MP_ = 0;
		speed_ = 1;
		money_ = 1;
		level_ = 1;
		exp_ = 2;
		break;
	case NORMAL:
		strcpy_s(name_, "skeletorn");
		attack_ = 6;
		defense_ = 4;
		HP_ = 10;
		MP_ = 5;
		speed_ = 3;
		money_ = 3;
		level_ = 5;
		exp_ = 5;
		break;
	case HARD:
		strcpy_s(name_, "goblin");
		attack_ = 10;
		defense_ = 8;
		HP_ = 30;
		MP_ = 10;
		speed_ = 7;
		money_ = 10;
		level_ = 15;
		exp_ = 8;
		break;
	case HELL:
		strcpy_s(name_, "ogre");
		attack_ = 20;
		defense_ = 15;
		HP_ = 50;
		MP_ = 30;
		speed_ = 10;
		money_ = 20;
		level_ = 20;
		exp_ = 10;
		break;
	case NIGHTMARE:
		strcpy_s(name_, "dragon");
		attack_ = 30;
		defense_ = 30;
		HP_ = 150;
		MP_ = 50;
		speed_ = 30;
		money_ = 100;
		level_ = 30;
		exp_ = 50;
		break;
	case DUNGEON_END:
		break;
	default:
		break;
	}
}

void Monster::GetInterFace_MonsterStatus()
{
	cout << "┌─── 상태창 ────────┐" << endl;
	cout << "│이름 : " << GetName() << "	│" << endl;
	cout << "│공격력 : " << Getattack() << "		│" << endl;
	cout << "│방어력 : " << Getdefense() << "	    │" << endl;
	cout << "│체력 : " << GetHP() << "	    │" << endl;
	cout << "│마나 : " << GetMP() << "	    │" << endl;
	cout << "└───────────────────┘" << endl;
}

void Monster::Kill(const Object* obj)
{
	cout << name_ << "에게 사망했습니다." << endl;
	return;
}

void Monster::Dead()
{
	delete this;
	return;
}