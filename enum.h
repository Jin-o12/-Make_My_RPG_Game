#pragma once

enum jobType : int
{
	WARRIOR,
	WIZARD,
	ARCHER,
	FIHGHTER,
	THIEF,
	JOB_END
};

enum StageType : int
{
	EXIT_GAME,
	DUNGEON,
	LODGE,
	SHOP,
	STATUS,
	STAGE_END
};

enum DungeonLevel : int
{
	EASY,
	NORMAL,
	HARD,
	HELL,
	NIGHTMARE,
	DUNGEON_END
};

enum BettleActtion : int
{
	ATTACK,
	DEFENSE,
	SKILL,
	ITEM,
	ESCAPE,
	BETTLE_ACTTION_END
};


enum LodgeActtion : int
{
	FOOD,
	DINNER,
	BED,
	FLUFFYBED
};

enum GameSystemState : short
{
	FAIL = -1,
	CANCEL = 0,
	SUCCESS = 1
};


enum ItemType : int
{
	PASSIVE_TYPE,
	WEAPON,
	HELMET,
	ARMOR,
	GREAVES,
	ACTIVATE_TYPE,
	POTION,
	ITEM_TYPE_END
};