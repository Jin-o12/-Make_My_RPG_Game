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
		cout << "error! : 적재 용량 초과분(#1)" << endl;
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
	cout << "사용할 수 있는 아이템이 아닙니다." << endl;
}

void PassiveItem::ItemPutInInven(Object* target)
{}

void PassiveItem::UseItemEffect(Object* target) { ((*this).*itemEffact_)(target); }
int PassiveItem::GetStack() { return 1; };
int PassiveItem::GetMaxStack() { return 1; };
void PassiveItem::SetStack(int add)
{
	cout << "error! : 잘못된 접근(#2)" << endl;
	exit(EXIT_FAILURE);
}


/*ItemManager*/
Item* ItemManager::ItemList[ITEM_SUM];

void ItemManager::initItemList()
{
	ItemList[0] = new ActivateItem("소형 체력 포션", "작은 크기의 체력 포션. 사용 시 체력을 10 회복시켜줍니다.", 3, POTION, &Item::smallHPpotion);
	ItemList[1] = new ActivateItem("소형 마나 포션", "작은 크기의 마나 포션. 사용 시 마력을 10 회복시켜줍니다.", 3, POTION, &Item::smallMPpotion);
	ItemList[2] = new PassiveItem("흔들거리는 모자", "수상할 정도로 흔들거리는 모자. 흔들거리는 기분에 방어력이 1 오른듯한 착각이 듭니다.", 2, HELMET, &Item::WigglerHelmet);
	ItemList[3] = new PassiveItem("가죽 투구", "질긴 가죽으로 만들어 쉽게 뚫리지 않을 것 같습니다. 방어력을 2 상승시킵니다.", 10, HELMET, &Item::leatherHelmet);
	ItemList[4] = new PassiveItem("가죽 갑옷", "튼튼한 가죽이 의외로 든든함을 느끼게 합니다. 방어력을 5 상승시킵니다.", 10, ARMOR, &Item::leatherArmor);
	ItemList[5] = new PassiveItem("강철 투구", "단단한 강철이 머리를 편안하게 보호합니다. 방어력을 4 상승시킵니다.", 25, HELMET, &Item::SteelHelmet);
	ItemList[6] = new PassiveItem("강철 갑옷", "강철을 전신에 두른다는 사실 만으로 강해진 것 같습니다. 방어력을 7 상승시킵니다.", 25, ARMOR, &Item::SteelArmor);
	ItemList[7] = new PassiveItem("적당한 나뭇가지", "자연이 만들어낸 환상적인 비율을 나뭇가지 검입니다. 이걸로 떄리면 1 만큼 아플듯 합니다.", 2, WEAPON, &Item::WellMadeStick);
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
