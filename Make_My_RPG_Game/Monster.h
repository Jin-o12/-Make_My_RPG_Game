#pragma once

#include <iostream>
#include "enum.h"
#include "Object.h"

using std::cout;
using std::cin;
using std::endl;

class Monster : public Object
{

public:
	void Initialize(DungeonLevel type);
	void GetInterFace_MonsterStatus();

	virtual void Kill(const Object* obj);
	virtual void Dead();
};