#pragma once

#include "enum.h"
#include "define.h"

#include "Object.h"


void IntalizeGameOption()
{
	system("mode con:cols=150 lines=40");
	//std::wcout.imbue(std::locale("Kor"));
}

const char* GetStageName(StageType type)
{
	switch (type)
	{
	case EXIT_GAME:
		return "게임 종료";
		break;
	case DUNGEON:
		return "던전";
		break;
	case LODGE:
		return "여관";
		break;
	case SHOP:
		return "상점";
		break;
	case STATUS:
		return "캐릭터 정보";
		break;
	case SAVE:
		return "저장";
		break;
	default:
		break;
	}
};

const char* GetDungeonName(DungeonLevel level)
{
	switch (level)
	{
	case EASY:
		return "쉬움";
		break;
	case NORMAL:
		return "보통";
		break;
	case HARD:
		return "어려움";
		break;
	case HELL:
		return "지옥";
		break;
	case NIGHTMARE:
		return "악몽";
		break;
	default:
		break;
	}
}

void BettleTimeLine(Object* pFirst, Object* pSecond)
{
	cout << (pFirst->GetName()) << "의 공격! " << pSecond->GetDemage(pFirst->Getattack()) << "의 데미지!" << endl;
	if (pSecond->GetHP() <= 0)
	{
		pFirst->Kill(pSecond);
		return;
	}
	cout << (pSecond->GetName()) << "의 공격! " << pFirst->GetDemage(pSecond->Getattack()) << "의 데미지!" << endl;
	if (pFirst->GetHP() <= 0)
		pFirst->Dead();
}