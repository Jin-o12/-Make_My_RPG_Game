#pragma once

#include <conio.h>

#include "Item.h"
#include "define.h"
#include "enum.h"

const char* Item::GetName() { return name_; }
const char* Item::GetDescribe() { return desc_; }
int Item::GetPrice() { return price_; }
ItemType Item::GetType() { return type_; };

void Item::smallHPpotion(Object* target)
{	target->HPchange(SMALL_POTION);	}
void Item::smallMPpotion(Object* target)
{	target->MPchange(SMALL_POTION);	}
void Item::WigglerHelmet(Object* target)
{	target->DEFchange(WIGGLER);	}
void Item::leatherHelmet(Object* target)
{	target->DEFchange(LEATHER_HELMET_);	}
void Item::leatherArmor(Object* target)
{	target->DEFchange(LEATHER_ARMOR); }
void Item::SteelHelmet(Object* target)
{	target->DEFchange(STEEL_HELMET); }
void Item::SteelArmor(Object* target)
{	target->DEFchange(STEEL_ARMOR); }
void Item::WellMadeStick(Object* target)
{	target->ATKchange(WELL_MADE_STICK); }


/*ActivateItem*/

void ActivateItem::ItemUse(Object* player)
{}

void ActivateItem::ItemPutInInven(Object* target)
{}

void ActivateItem::UseItemEffect(Object* target) { ((*this).*itemEffact_)(target); }

int ActivateItem::GetStack() { return itemStack; };
int ActivateItem::GetMaxStack() { return itemStack; };

void ActivateItem::SetStack(int add)
{
	if (itemStack + add >= 4)
	{
		cout << "error! : ���� �뷮 �ʰ���(#1)" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		itemStack += add;
	}
}



/*PassiveItem*/
void PassiveItem::ItemUse(Object* player)
{
	cout << "����� �� �ִ� �������� �ƴմϴ�." << endl;
}

void PassiveItem::ItemPutInInven(Object* target)
{}

void PassiveItem::UseItemEffect(Object* target) { ((*this).*itemEffact_)(target); }
int PassiveItem::GetStack() { return 1; };
int PassiveItem::GetMaxStack() { return 1; };
void PassiveItem::SetStack(int add)
{
	cout << "error! : �߸��� ����(#2)" << endl;
	exit(EXIT_FAILURE);
}


/*ItemManager*/
Item* ItemManager::ItemList[ITEM_SUM];

void ItemManager::initItemList()
{
	ItemList[0] = new ActivateItem("���� ü�� ����", "���� ũ���� ü�� ����. ��� �� ü���� 10 ȸ�������ݴϴ�.", 3, POTION, &Item::smallHPpotion);
	ItemList[1] = new ActivateItem("���� ���� ����", "���� ũ���� ���� ����. ��� �� ������ 10 ȸ�������ݴϴ�.", 3, POTION, &Item::smallMPpotion);
	ItemList[2] = new PassiveItem("���Ÿ��� ����", "������ ������ ���Ÿ��� ����. ���Ÿ��� ��п� ������ 1 �������� ������ ��ϴ�.", 2, HELMET, &Item::WigglerHelmet);
	ItemList[3] = new PassiveItem("���� ����", "���� �������� ����� ���� �ո��� ���� �� �����ϴ�. ������ 2 ��½�ŵ�ϴ�.", 10, HELMET, &Item::leatherHelmet);
	ItemList[4] = new PassiveItem("���� ����", "ưư�� ������ �ǿܷ� ������� ������ �մϴ�. ������ 5 ��½�ŵ�ϴ�.", 10, ARMOR, &Item::leatherArmor);
	ItemList[5] = new PassiveItem("��ö ����", "�ܴ��� ��ö�� �Ӹ��� ����ϰ� ��ȣ�մϴ�. ������ 4 ��½�ŵ�ϴ�.", 25, HELMET, &Item::SteelHelmet);
	ItemList[6] = new PassiveItem("��ö ����", "��ö�� ���ſ� �θ��ٴ� ��� ������ ������ �� �����ϴ�. ������ 7 ��½�ŵ�ϴ�.", 25, ARMOR, &Item::SteelArmor);
	ItemList[7] = new PassiveItem("������ ��������", "�ڿ��� ���� ȯ������ ������ �������� ���Դϴ�. �̰ɷ� ������ 1 ��ŭ ���õ� �մϴ�.", 2, WEAPON, &Item::WellMadeStick);
}

int ItemManager::SearchItemCodeByName(const char* name)
{
	for (size_t i = 0; i < ITEM_SUM; i++)
	{
		if (strcmp(ItemList[i]->GetName(), name) == 0)
		{
			return i;
		}
	}
}

/*
void ItemManager::initInventoryObject(ItemObject* inven)
{
	for (size_t i = 0; i < INVENTORY_SIZE; i++)
	{
		ItemObject inven[i] = new ItemObject;
	}

}
*/
