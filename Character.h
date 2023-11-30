#pragma once

#include <iostream>

#include "enum.h"
#include "define.h"

#include "Object.h"
#include "Item.h"

struct CharacterEquipStatus	//경량패턴 : 각 아이템 객체에 대한 변동되는 수치를 따로 저장
{
	int ATK;
	int DEF;
};
struct ItemObject;

class Skill;
class Item;
class Character : public Object
{
private:
	jobType job_;
	int levelUpExp_ = 30;
	ItemObject equipList_[EQUIP_MAX] = { nullptr };
	CharacterEquipStatus equipState = {0, 0};

protected:
public:
	/*GET 함수*/
	void GetJobState(jobType job);
	const char* GetJobName();
	jobType GetPlayerJob();
	int Getattack() const { return attack_+ equipState.ATK; }
	int GetDefense() const { return defense_+ equipState.DEF; }
	ItemObject GetEquipItemByIndex(int index) { return equipList_[index]; }

	/*스킬 함수*/
	int AddSkill(const char* name);	//스킬 추가, 결과를 숫자코드로 출력 (0 : 취소(이미 동일 스킬 존재), 1 : 추가 성공, -1 : 실패(자리없음))
	void UseSkill(int num, Object* enermy);

	/*아이템 관련 함수*/
	void InputItemToInven(int itemCode, int stack);	//아이템 코드를 받아 인벤토리에 input
	bool IsInvemEmpty();								//인벤토리가 비어있을 시 true
	void EquipItem(int invenNum);						//아이템 장착
	void UseItem(int ItemCode);							//아이템 사용
	//void equipPessiveOnOff();

	/*플레이어 행동이나 상태 함수*/
	bool BuySometing(int price);			//돈을 지불

	/*SET 함수*/
	void SetName(const char* pName);
	void SetPlayerJob(int type);

	virtual void Kill(const Object* obj);
	virtual void Dead();

	//GET_INTERFACE 함수 (값 반환 없이 정해진 형식대로 정보 출력)
	void GetInterFace_PlayerStatus();
	void GetInterFace_BattleMenu();
	void GetInterFace_Inventory();
	void GetInterFace_SkillList();
	void GetInterFace_EquipList();
};


