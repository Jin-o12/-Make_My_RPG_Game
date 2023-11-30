#pragma once

#include "Object.h"

const char* Object::GetName()  { return name_; }
int Object::Getattack() const  { return attack_; }
int Object::Getdefense() const  { return defense_; }
int Object::GetHP() const  { return HP_; }
int Object::GetMP() const  { return MP_; }
int Object::Getspeed() const  { return speed_; }
int Object::Getmoney() const  { return money_; }
int Object::Getlevel() const  { return level_; }
int Object::Getexp() const  { return exp_; }


/*상태변화& 액션 관련 함수*/
int Object::GetDemage(int atk)
{
	int damage = atk - defense_;
	if (damage > 0)
	{
		HP_ -= damage;
		return damage;
	}
	else
		return 0;
}
void Object::GetDefendedDamage(int atk)
{
	/*
	> 방어도 계산 기준
		기존 방어도에 방어도 * DEFENSE_PERCENTAGE 수치만큼 합산하여 더 방어
	*/
	int damage = atk - (defense_ + (defense_ * DEFENSE_PERCENTAGE));
	GetDemage(atk);
}
void Object::HPchange(int getHP) { this->HP_ += getHP; }
void Object::MPchange(int getMP) { this->MP_ += getMP; }
void Object::ATKchange(int getATK) { this->attack_ += getATK; }
void Object::DEFchange(int getDEF) { this->defense_ += getDEF; }
void Object::SPDchange(int getSPD) { this->speed_ += getSPD; }


