#pragma once
#include <iostream>

#include "Skill.h"
#include "enum.h"
#include "define.h"
#include "Item.h"

using std::cout;
using std::endl;

struct ItemObject;
class Skill;
class Item;

class Object
{
private:
protected:
	char name_[20];
	int attack_;
	int defense_;
	int HP_;
	int MP_;
	int speed_;
	int money_;
	int level_;
	int exp_;
	Skill* thisSkillList_[SKILL_MAX] = { nullptr };
	ItemObject* thisInventory_[INVENTORY_SIZE] = { nullptr };
public:
	//GET 함수
	const char* GetName();
	int Getattack() const;
	int Getdefense() const;
	int GetHP() const;
	int GetMP() const;
	int Getspeed() const;
	int Getmoney() const;
	int Getlevel() const;
	int Getexp() const;

	/*상태변화& 액션 관련 함수*/
	int GetDemage(int atk);	//데미지를 입음
	void GetDefendedDamage(int atk);	//추가 방어도가 포함된 만큼만 데미지를 입음
	void HPchange(int getHP);	//체력변동 (음수 값을 적을 시 소모)
	void MPchange(int getMP);	//마나변동 (음수 값을 적을 시 소모)
	void ATKchange(int getATK);	//공격력 수치
	void DEFchange(int getDEF);	//방어력 수치
	void SPDchange(int getSPD);	//속도 수치

	virtual void Kill(const Object* obj) {};
	virtual void Dead() {};

	
};