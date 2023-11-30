#pragma once

#include <iostream>

#include "enum.h"
#include "define.h"

#include "Character.h"
#include "Item.h"

using std::cout;
using std::cin;
using std::endl;

class ItemManager;
void Character::GetJobState(jobType job)
{
	switch (job)
	{
	case WARRIOR:
		AddSkill("�������");
		attack_ = 7;
		defense_ = 9;
		HP_ = 50;
		MP_ = 20;
		speed_ = 5;
		money_ = 10;
		break;
	case WIZARD:
		AddSkill("����ź");
		attack_ = 9;
		defense_ = 5;
		HP_ = 20;
		MP_ = 50;
		speed_ = 6;
		money_ = 20;
		break;
	case ARCHER:
		AddSkill("����ȭ��");
		attack_ = 8;
		defense_ = 6;
		HP_ = 25;
		MP_ = 25;
		speed_ = 8;
		money_ = 10;
		break;
	case FIHGHTER:
		AddSkill("��Ÿ");
		attack_ = 8;
		defense_ = 6;
		HP_ = 40;
		MP_ = 20;
		speed_ = 7;
		money_ = 10;
		break;
	case THIEF:
		AddSkill("���");
		attack_ = 7;
		defense_ = 4;
		HP_ = 30;
		MP_ = 30;
		speed_ = 9;
		money_ = 40;
		break;
	default:
		break;
	}
	level_ = 1;
	exp_ = 0;
}

void Character::SetName(const char* pName)
{
	strcpy_s(name_, pName);
}

void Character::SetPlayerJob(int type)
{
	job_ = static_cast<jobType>(type-1);
	GetJobState(job_);
}


jobType Character::GetPlayerJob()
{
	return job_;
}
const char* Character::GetJobName()
{
	switch (job_)
	{
	case WARRIOR:
		return "����";
		break;
	case WIZARD:
		return "������";
		break;
	case ARCHER:
		return "�ü�";
		break;
	case FIHGHTER:
		return "������";
		break;
	case THIEF:
		return "����";
		break;
	default:
		break;
	}
}


int Character::AddSkill(const char* name)
{
	Skill* skill = SkillManager::GetInst()->SearchSkillByName(name);
	skill->SetSkillOwner(this);

	for (size_t i = 0; i < SKILL_MAX; i++)
	{
		if (thisSkillList_[i] != nullptr)
		{
			if (!strcmp(thisSkillList_[i]->GetName(), name))	//������ ��ų�� �̹� ������ ���
			{
				cout << "�̹� �����ϰ� �ִ� ��ų�Դϴ�." << endl;
				return CANCEL;
			}
		}
	}
	for (size_t i = 0; i < SKILL_MAX; i++)
	{
		if (thisSkillList_[i] == nullptr)	//����ִ� ��� ��ų �߰�
		{
			thisSkillList_[i] = skill;
			return SUCCESS;
		}
	}
	cout << "�� �̻� ��ų�� �߰��� �� �����ϴ�." << endl;
	return FAIL;
}
void Character::UseSkill(int answer, Object* enermy)
{
	Skill* skill = thisSkillList_[answer - 1];
	skill->UseSkillEffect(enermy);
}


/*�κ��丮 �Լ�*/
void Character::InputItemToInven(int itemCode, int stack)
{
	Item* item = ItemManager::GetInst()->ItemList[itemCode];

	for (size_t i = 0; i < INVENTORY_SIZE; i++)
	{
		if (thisInventory_[i] == nullptr)
		{
			thisInventory_[i] = new ItemObject;
			thisInventory_[i]->pItemObj = item;
			thisInventory_[i]->stack = stack;
			return;
		}
		else
		{
			if (item->GetMaxStack() > 1 && !strcmp(thisInventory_[i]->pItemObj->GetName(), item->GetName()))
			{
				thisInventory_[i]->stack += stack;
				if (thisInventory_[i]->stack >= item->GetMaxStack())
				{
					stack = thisInventory_[i]->stack - item->GetMaxStack();
					thisInventory_[i]->stack = item->GetMaxStack();
				}
				else
					return;
			}
		}
	}
	cout << "���濡 ���� ������ �����ϴ�." << endl;
}

bool Character::IsInvemEmpty()
{
	for (size_t i = 0; i < INVENTORY_SIZE; i++)
	{
		if (thisInventory_[i] != nullptr)
		{
			return false;
		}
	}
	return true;
}

void Character::EquipItem(int invenNum)
{
	int equipType = static_cast<int>(thisInventory_[invenNum-1]->pItemObj->GetType());

	if (equipType >= ACTIVATE_TYPE)
	{
		cout << "������ �� �����ϴ�." << endl;
		return;
	}
	else
	{
		ItemObject* nowEquip = this->GetEquipItemByIndex(equipType - 1);
		Item* nowInven = thisInventory_[invenNum-1]->pItemObj;
		Item* temp;

		temp = nowInven;
		nowInven = nowEquip;
		nowEquip = temp;

		cout << "�����Ǿ����ϴ�." << endl;
	}
}

bool Character::BuySometing(int price)
{
	if (money_ < price)
	{
		cout << "���� �ݾ��� �����մϴ�." << endl;
		return 0;
	}
	else
	{
		cout << price << "��ŭ �����Ǿ����ϴ�." << endl;
		money_ -= price;
		return 1;
	}

}

void Character::UseItem(int ItemCode)
{}


void Character::Kill(const Object* obj)
{
	cout << "�ο򿡼� �¸��Ͽ����ϴ�." << endl;
	int exp = obj->Getexp();
	cout << exp_ << "�� ����ġ�� ������ϴ�." << endl;
	exp_ += exp;
	if (exp_ >= levelUpExp_)
	{
		level_++;
		exp_ -= levelUpExp_;
		cout << "������! ���� ���� : " << level_ << endl;
	}
	int money = obj->Getmoney();
	cout << money << "�� ���� ȹ���߽��ϴ�." << endl;
	money_ = money;
}

void Character::Dead()
{
	cout << "�������� �й��߽��ϴ�. ������" << money_ * 0.1f << "�� ����ġ�� ��� �Ұ� ������ �����մϴ�.";
	exp_ = 0;
	money_ -= money_ * 0.1f;

	if (money_ < 0)
	{
		money_ = 0;
	}
}



void Character::GetInterFace_PlayerStatus()
{
	cout << "�������� ����â ��������������" << endl;
	cout << "���̸� : " << GetName() << "	  ��" << endl;
	cout << "������ : " << GetJobName() << "	  ��" << endl;
	cout << "�����ݷ� : " << Getattack();
	if (equipState.ATK > 0)
		cout << "(+" << equipState.ATK << ")	  ��" << endl;
	else
		cout << "	  ��" << endl;
	cout << "������ : " << Getdefense();
	if (equipState.DEF > 0)
		cout << "(+" << equipState.DEF << ")	  ��" << endl;
	else
		cout << "	  ��" << endl;
	cout << "��ü�� : " << GetHP() << "	  ��" << endl;
	cout << "������ : " << GetMP() << "	  ��" << endl;
	cout << "���ӵ� : " << Getspeed() << "	  ��" << endl;
	cout << "�������� : " << Getmoney() << "	  ��" << endl;
	cout << "������ : " << Getlevel() << "	  ��" << endl;
	cout << "������ġ : " << Getexp() << "  	  ��" << endl;
	cout << "��������������������������������������" << endl;
}

void Character::GetInterFace_BattleMenu()
{
	cout << "������������������������������������������������������������������" << endl;
	cout << "��1. ����     2. ���    3.��ų  ��" << endl;
	cout << "��4. ������   5. ����            ��" << endl;
	cout << "������������������������������������������������������������������" << endl;
}

void Character::GetInterFace_Inventory()
{
	cout << "[���� ������]" << endl;
	int count = 0;
	for (size_t i = 0; i < INVENTORY_SIZE; i++)
	{
		if (thisInventory_[i] != nullptr)
		{
			cout << i+1 << ". " << thisInventory_[i]->pItemObj->GetName() << " * " << thisInventory_[i]->pItemObj->GetStack() << " #" << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "(  �κ��丮�� ����ֽ��ϴ�. )" << endl;
	}
}

void Character::GetInterFace_SkillList()
{
	int index = 1;
	for (int i=0; i< SKILL_MAX ; i++)
	{
		if (thisSkillList_[i] != nullptr)
		{
			cout << index << ". " << thisSkillList_[i]->GetName() << endl;
			index++;
		}
	}
}

void Character::GetInterFace_EquipList()
{
	cout << "[���â]" << endl;
	int count = 0;
	for (int i = 0; i < EQUIP_MAX; i++)
	{
		if (equipList_[i].pItemObj != nullptr)
		{
			cout << i << ". " << equipList_[i].pItemObj->GetName() << endl;
		}
		count++;
	}
	if (count == 0)
	{
		cout << "(  ������ ��� �����ϴ�.  )" << endl;
	}
}
