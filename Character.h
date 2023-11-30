#pragma once

#include <iostream>

#include "enum.h"
#include "define.h"

#include "Object.h"
#include "Item.h"

struct CharacterEquipStatus	//�淮���� : �� ������ ��ü�� ���� �����Ǵ� ��ġ�� ���� ����
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
	/*GET �Լ�*/
	void GetJobState(jobType job);
	const char* GetJobName();
	jobType GetPlayerJob();
	int Getattack() const { return attack_+ equipState.ATK; }
	int GetDefense() const { return defense_+ equipState.DEF; }
	ItemObject GetEquipItemByIndex(int index) { return equipList_[index]; }

	/*��ų �Լ�*/
	int AddSkill(const char* name);	//��ų �߰�, ����� �����ڵ�� ��� (0 : ���(�̹� ���� ��ų ����), 1 : �߰� ����, -1 : ����(�ڸ�����))
	void UseSkill(int num, Object* enermy);

	/*������ ���� �Լ�*/
	void InputItemToInven(int itemCode, int stack);	//������ �ڵ带 �޾� �κ��丮�� input
	bool IsInvemEmpty();								//�κ��丮�� ������� �� true
	void EquipItem(int invenNum);						//������ ����
	void UseItem(int ItemCode);							//������ ���
	//void equipPessiveOnOff();

	/*�÷��̾� �ൿ�̳� ���� �Լ�*/
	bool BuySometing(int price);			//���� ����

	/*SET �Լ�*/
	void SetName(const char* pName);
	void SetPlayerJob(int type);

	virtual void Kill(const Object* obj);
	virtual void Dead();

	//GET_INTERFACE �Լ� (�� ��ȯ ���� ������ ���Ĵ�� ���� ���)
	void GetInterFace_PlayerStatus();
	void GetInterFace_BattleMenu();
	void GetInterFace_Inventory();
	void GetInterFace_SkillList();
	void GetInterFace_EquipList();
};


