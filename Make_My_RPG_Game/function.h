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
		return "���� ����";
		break;
	case DUNGEON:
		return "����";
		break;
	case LODGE:
		return "����";
		break;
	case SHOP:
		return "����";
		break;
	case STATUS:
		return "ĳ���� ����";
		break;
	case SAVE:
		return "����";
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
		return "����";
		break;
	case NORMAL:
		return "����";
		break;
	case HARD:
		return "�����";
		break;
	case HELL:
		return "����";
		break;
	case NIGHTMARE:
		return "�Ǹ�";
		break;
	default:
		break;
	}
}

void BettleTimeLine(Object* pFirst, Object* pSecond)
{
	cout << (pFirst->GetName()) << "�� ����! " << pSecond->GetDemage(pFirst->Getattack()) << "�� ������!" << endl;
	if (pSecond->GetHP() <= 0)
	{
		pFirst->Kill(pSecond);
		return;
	}
	cout << (pSecond->GetName()) << "�� ����! " << pFirst->GetDemage(pSecond->Getattack()) << "�� ������!" << endl;
	if (pFirst->GetHP() <= 0)
		pFirst->Dead();
}