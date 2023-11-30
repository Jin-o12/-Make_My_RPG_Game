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
		AddSkill("내려찍기");
		attack_ = 7;
		defense_ = 9;
		HP_ = 50;
		MP_ = 20;
		speed_ = 5;
		money_ = 10;
		break;
	case WIZARD:
		AddSkill("마나탄");
		attack_ = 9;
		defense_ = 5;
		HP_ = 20;
		MP_ = 50;
		speed_ = 6;
		money_ = 20;
		break;
	case ARCHER:
		AddSkill("마나화살");
		attack_ = 8;
		defense_ = 6;
		HP_ = 25;
		MP_ = 25;
		speed_ = 8;
		money_ = 10;
		break;
	case FIHGHTER:
		AddSkill("강타");
		attack_ = 8;
		defense_ = 6;
		HP_ = 40;
		MP_ = 20;
		speed_ = 7;
		money_ = 10;
		break;
	case THIEF:
		AddSkill("기습");
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
		return "전사";
		break;
	case WIZARD:
		return "마법사";
		break;
	case ARCHER:
		return "궁수";
		break;
	case FIHGHTER:
		return "격투가";
		break;
	case THIEF:
		return "도적";
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
			if (!strcmp(thisSkillList_[i]->GetName(), name))	//동일한 스킬이 이미 존재할 경우
			{
				cout << "이미 보유하고 있는 스킬입니다." << endl;
				return CANCEL;
			}
		}
	}
	for (size_t i = 0; i < SKILL_MAX; i++)
	{
		if (thisSkillList_[i] == nullptr)	//비어있는 경우 스킬 추가
		{
			thisSkillList_[i] = skill;
			return SUCCESS;
		}
	}
	cout << "더 이상 스킬을 추가할 수 없습니다." << endl;
	return FAIL;
}
void Character::UseSkill(int answer, Object* enermy)
{
	Skill* skill = thisSkillList_[answer - 1];
	skill->UseSkillEffect(enermy);
}


/*인벤토리 함수*/
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
	cout << "가방에 남는 공간이 없습니다." << endl;
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
		cout << "장착할 수 없습니다." << endl;
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

		cout << "장착되었습니다." << endl;
	}
}

bool Character::BuySometing(int price)
{
	if (money_ < price)
	{
		cout << "소지 금액이 부족합니다." << endl;
		return 0;
	}
	else
	{
		cout << price << "만큼 차감되었습니다." << endl;
		money_ -= price;
		return 1;
	}

}

void Character::UseItem(int ItemCode)
{}


void Character::Kill(const Object* obj)
{
	cout << "싸움에서 승리하였습니다." << endl;
	int exp = obj->Getexp();
	cout << exp_ << "의 경험치를 얻었습니다." << endl;
	exp_ += exp;
	if (exp_ >= levelUpExp_)
	{
		level_++;
		exp_ -= levelUpExp_;
		cout << "레벨업! 현재 레벨 : " << level_ << endl;
	}
	int money = obj->Getmoney();
	cout << money << "의 돈을 획득했습니다." << endl;
	money_ = money;
}

void Character::Dead()
{
	cout << "전투에서 패배했습니다. 소지금" << money_ * 0.1f << "와 경험치를 모두 잃고 마을로 복귀합니다.";
	exp_ = 0;
	money_ -= money_ * 0.1f;

	if (money_ < 0)
	{
		money_ = 0;
	}
}



void Character::GetInterFace_PlayerStatus()
{
	cout << "┌─── 상태창 ──────┐" << endl;
	cout << "│이름 : " << GetName() << "	  │" << endl;
	cout << "│직업 : " << GetJobName() << "	  │" << endl;
	cout << "│공격력 : " << Getattack();
	if (equipState.ATK > 0)
		cout << "(+" << equipState.ATK << ")	  │" << endl;
	else
		cout << "	  │" << endl;
	cout << "│방어력 : " << Getdefense();
	if (equipState.DEF > 0)
		cout << "(+" << equipState.DEF << ")	  │" << endl;
	else
		cout << "	  │" << endl;
	cout << "│체력 : " << GetHP() << "	  │" << endl;
	cout << "│마나 : " << GetMP() << "	  │" << endl;
	cout << "│속도 : " << Getspeed() << "	  │" << endl;
	cout << "│소지금 : " << Getmoney() << "	  │" << endl;
	cout << "│레벨 : " << Getlevel() << "	  │" << endl;
	cout << "│경험치 : " << Getexp() << "  	  │" << endl;
	cout << "└─────────────────┘" << endl;
}

void Character::GetInterFace_BattleMenu()
{
	cout << "┌───────────────────────────────┐" << endl;
	cout << "│1. 공격     2. 방어    3.스킬  │" << endl;
	cout << "│4. 아이템   5. 도망            │" << endl;
	cout << "└───────────────────────────────┘" << endl;
}

void Character::GetInterFace_Inventory()
{
	cout << "[보유 아이템]" << endl;
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
		cout << "(  인벤토리가 비어있습니다. )" << endl;
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
	cout << "[장비창]" << endl;
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
		cout << "(  장착된 장비가 없습니다.  )" << endl;
	}
}
