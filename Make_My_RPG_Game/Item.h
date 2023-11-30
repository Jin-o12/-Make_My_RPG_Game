#pragma once
#include <iostream>

#include "enum.h"
#include "define.h"

#include "Object.h"

class Object;
class ActivateItem;
class PassiveItem;

struct ItemObject;

class Item
{
protected:
	char name_[50];				//아이템 이름
	char desc_[200];			//아이템 설명
	void (Item::*itemEffact_)(Object*);
	int price_;
	int itemStack;
	int maxStack_;
	ItemType type_;
public:
	Item() {}
	Item(const char* name, const char* desc, int price)
	{
		strcpy_s(name_, name);
		strcpy_s(desc_, desc);
		price_ = price;
	}
	~Item() {}

	const char* GetName();
	const char* GetDescribe();
	int GetPrice();
	ItemType GetType();
	virtual int GetStack() = 0;
	virtual int GetMaxStack() = 0;
	virtual void SetStack(int add) = 0;

	virtual void ItemUse(Object* player) = 0;
	virtual void ItemPutInInven(Object* target) = 0;
	virtual void UseItemEffect(Object* target) = 0;

	void smallHPpotion(Object* target);
	void smallMPpotion(Object* target);
	void WigglerHelmet(Object* target);
	void leatherHelmet(Object* target);
	void leatherArmor(Object* target);
	void SteelHelmet(Object* target);
	void SteelArmor(Object* target);
	void WellMadeStick(Object* target);
};


class ActivateItem : public Item
{
private:
public:
	ActivateItem(const char* name, const char* desc, int price, ItemType type, void (Item::*effect)(Object*))
		: Item(name, desc, price)
	{
		type_ = type;
		itemEffact_ = effect;
	}

	void SetItemStack(int stack) { itemStack = stack; }
	void ItemUse(Object* player);
	void ItemPutInInven(Object* target);
	void UseItemEffect(Object* target);
	int GetStack();
	int GetMaxStack();
	void SetStack(int add);
};


class PassiveItem : public Item
{
private:
	bool isEquip = false;
	int equipPos_ = 0x0000;
public:
	PassiveItem(const char* name, const char* desc, int price, ItemType type, void (Item::*effect)(Object*))
		: Item(name, desc, price) 
	{
		maxStack_ = 1;
		type_ = type;
		itemEffact_ = effect;
	}

	void ItemUse(Object* player);
	void ItemPutInInven(Object* target);
	void UseItemEffect(Object* target);
	int GetStack();
	int GetMaxStack();
	void SetStack(int add);
};


class ItemManager
{
public:
	static ItemManager* GetInst()
	{
		static ItemManager ItemInst;
		return &ItemInst;
	}
	static Item* ItemList[ITEM_SUM];
	void initItemList();
	int SearchItemCodeByName(const char* name);
	//void initInventoryObject(ItemObject* inven);
};

struct ItemObject
{
	Item* pItemObj;
	int stack;
};
