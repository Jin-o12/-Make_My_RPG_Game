#pragma once
#pragma warning(disable:4244)
#include <iostream>
#include "Skill.h"

using std::cout;
using std::endl;

const char* Skill::GetName() {  return name_;  }
const char* Skill::GetDescribe() {  return desc_;  }
void Skill::UseSkillEffect(Object* target)
{ 
	cout << target->GetName() << "에게 " << this->GetName() << "사용" << endl;
	((*this).*skillFunc)(target);
}
Skill* SkillManager::skillList[]{};	//static 변수 초기화



void Skill::Crush(Object* target) { AttackSkill(target, me_->Getattack() * CRUSH_DMG); }
void Skill::ManaBullet(Object* target) { AttackSkill(target, me_->Getattack() * CRUSH_DMG); }
void Skill::ManaArrow(Object* target) { AttackSkill(target, me_->Getattack() * MANA_ARROW_DMG); }
void Skill::Smite(Object* target) { AttackSkill(target, me_->Getattack() * SMITE_DMG); }
void Skill::Ambush(Object* target) { AttackSkill(target, me_->Getattack() * AMBUSH_DMG); }

void Skill::AttackSkill(Object* target, int damage)
{
	int realDamage = target->GetDemage(damage);
	cout << target->GetName() << "에게 " << realDamage << "(" << damage << "-" << target->Getdefense() << ")" << "의 스킬 피해!" << endl;
}