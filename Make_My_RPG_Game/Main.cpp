#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include "function.h"

#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "Skill.h"


using std::cout;
using std::cin;
using std::endl;

Character player;

void CreatePlayer();
bool ShowStage();
void ShowDungeon(StageType stage);
void ShowLodge(StageType stage);
void ShowShop(StageType stage);
void ShowStatus(StageType stage);
void Bettle(DungeonLevel level);
bool Load(const char* pFileName);
void Save(const char* pFileName);

int userAnswerInt;
char userAnswerChar;


void CreatePlayer()
{
	cout << "�̸��� �����ΰ���?" << endl;
	char name[20];
	cin >> name;
	player.SetName(name);

	do
	{
		cout << "������ ������." << endl;
		cout << "1. ���� / 2. ������ / 3. �ü� / 4. ������ / 5. ����" << endl;
		userAnswerInt = -1;
		cin >> userAnswerInt;
		if (0 >= userAnswerInt || userAnswerInt >= JOB_END+1)
		{
			cout << "��Ͽ� ���� �������� ���̽��ϴ�. �ٽ� �Է����ּ���." << endl;
			userAnswerInt = -1;
		}
		else
		{
			while (true)
			{
				player.SetPlayerJob(userAnswerInt);
				cout << "����� ������ ������ �ɷ�ġ�Դϴ�." << endl;
				player.GetInterFace_PlayerStatus();
				cout << "�̰ɷ� �������ðڽ��ϱ�? typing Y or N" << endl;
				cin >> userAnswerChar;
				if (userAnswerChar == 'y' || userAnswerChar == 'Y')
				{
					cout << "���� ������ �������ϴ�!" << endl;
					break;
				}
				else if (userAnswerChar == 'n' || userAnswerChar == 'N')
				{
					cout << "�������� ������ �ٽ� �մϴ�" << endl;
					player.SetPlayerJob(0);
					break;
				}
				else
				{
					cout << "Y Ȥ�� N �� �Է����ּ���" << endl;
					break;
				}
			}
		}
	} while (!(0 <= player.GetPlayerJob() && player.GetPlayerJob() < JOB_END));
	cout << "������ ������ �غ� �������ϴ�!" << endl;
	system("pause");
	system("cls");
}

bool ShowStage()
{
	system("cls");
	cout << "������� ���� �������ּ���." << endl;
	for (size_t i = 0; i < STAGE_END; i++)
	{
		cout << i << ". " << GetStageName(static_cast<StageType>(i)) << endl;
	}
	cout << "���� �Է� : " << endl;
	userAnswerInt = -1;
	cin >> userAnswerInt;
	switch (userAnswerInt)
	{
	case EXIT_GAME:
		cout << "������ �����մϴ�." << endl;
		return false;
	case DUNGEON:
		ShowDungeon(static_cast<StageType>(userAnswerInt - 1));
		break;
	case LODGE:
		ShowLodge(static_cast<StageType>(userAnswerInt - 1));
		break;
	case SHOP:
		ShowShop(static_cast<StageType>(userAnswerInt - 1));
		break;
	case STATUS:
		ShowStatus(static_cast<StageType>(userAnswerInt - 1));
		break;
	case SAVE:
		Save("save.txt");
		break;
	default:
		break;
	}
	return true;
}

void ShowDungeon(StageType level)
{
	cout << "���� ���̵��� �������ּ���." << endl;
	cout << "1. ���� / 2. ���� / 3. ����� / 4. ���� / 5. �Ǹ�" << endl; 
	cout << "���� �Է� : ";
	cin >> userAnswerInt;
	Bettle(static_cast<DungeonLevel>(userAnswerInt - 1));
}

void ShowLodge(StageType level)
{
	while (true)
	{
		cout << "��======================== " << GetStageName(level) << " ========================��" << endl;
		cout << "��0. ���ư���									   ��" << endl;
		cout << "��1. �ѳ� �Ļ�		>  2G    [+ 5  HP] [+ 0  MP]   ��" << endl;
		cout << "��2. Ǫ���� �Ļ�		>  5G    [+ 10 HP] [+ 0  MP]   ��" << endl;
		cout << "��3. �Ϲ� ħ��		>  10G   [+ 20 HP] [+ 5  MP]   ��" << endl;
		cout << "��4. ǫ�� ħ��		>  20G   [+ 40 HP] [+ 10 MP]   ��" << endl;
		cout << "��======================================================��" << endl;
		cin >> userAnswerInt;

		int hp = 0;
		int mp = 0;
		bool playerBuy = 0;
		switch (userAnswerInt - 1)
		{
		case -1:
			return;
		case FOOD:
			playerBuy= player.BuySometing(2);
			if (!playerBuy)
				break;
			player.HPchange(5);
			hp = 5;
			break;
		case DINNER:
			playerBuy = player.BuySometing(5);
			if (!playerBuy)
				break;
			player.HPchange(10);
			hp = 10;
			break;
		case BED:
			playerBuy = player.BuySometing(10);
			if (!playerBuy)
				break;
			player.HPchange(20);
			player.MPchange(5);
			hp = 20;
			mp = 5;
			break;
		case FLUFFYBED:
			playerBuy = player.BuySometing(20);
			if (!playerBuy)
				break;
			player.HPchange(40);
			player.MPchange(10);
			hp = 40;
			mp = 10;
			break;
		default:
			break;
		}

		if ((hp >= 0 || mp >=0) && playerBuy)
		{
			cout << "ü���� " << hp << "��ŭ, ������ " << mp << "ȸ���Ǿ����ϴ�" << endl;
			player.GetInterFace_PlayerStatus();
			system("pause");
			system("cls");
			return;
		}
	}
}


void ShowShop(StageType level)
{
	Item* shopItemList[6] = { ItemManager::GetInst()->ItemList[P_SMALL_HP],
							  ItemManager::GetInst()->ItemList[P_SMALL_MP],
							  ItemManager::GetInst()->ItemList[H_WIGGLER],
							  ItemManager::GetInst()->ItemList[W_WELL_MADE_STICK],
							  ItemManager::GetInst()->ItemList[H_LEATHER],
							  ItemManager::GetInst()->ItemList[A_LEATHER] };
	while (true)
	{
		cout << "��==================== " << GetStageName(level) << " ====================��" << endl;
		cout << "| 0 . ������ (��������ȭ��)" << "			|" << endl;
		for (size_t i = 0; i < 6; i++)
		{
			cout << "| " << i+1 << ". " << shopItemList[i]->GetName() << "			|" << endl;
		}
		cout << "��==============================================��" << endl;
		cout << "���ϴ� �׸��� ��ȣ�� �Է����ּ���." << endl;
		cin >> userAnswerInt;

		if(userAnswerInt == 0)
		{ 
			cout << "�������� �����ϴ�." << endl;
			return;
		}
		else if (userAnswerInt <= 6)
		{
			Item* choiceItem = shopItemList[userAnswerInt - 1];
			cout << choiceItem->GetName() << choiceItem->GetDescribe() << endl;
			cout << "�����Ͻðڽ��ϱ�? Y or N" << endl;
			cin >> userAnswerChar;

			if (userAnswerChar == 'y' || userAnswerChar == 'Y')
			{
				if (player.BuySometing(choiceItem->GetPrice()))
				{
					player.InputItemToInven(ItemManager::GetInst()->SearchItemCodeByName(choiceItem->GetName()), 1);
					cout << choiceItem->GetName() << "�� ���ŵǾ����ϴ�." << endl;
					system("pause");
					continue;
				}
				else
				{
					continue;
				}
			}
			else if (!(userAnswerChar == 'n' || userAnswerChar == 'N'))
			{
				cout << "Y Ȥ�� N �� �Է����ּ���" << endl;
				system("pause");
			}
		}
		system("cls");
	}
}


void ShowStatus(StageType level)
{
	player.GetInterFace_PlayerStatus();
	player.GetInterFace_Inventory();
	player.GetInterFace_EquipList();

	cout << "1. ��� ���� / 2. ������" << endl;
	cin >> userAnswerInt;

	switch (userAnswerInt)
	{
	case 1:
		cout << "�������� �������ּ���." << endl;
		player.GetInterFace_Inventory();
		cin >> userAnswerInt;
		player.EquipItem(userAnswerInt);
		break;
	case 2:
		cout << "����ȭ������ ���ư��ϴ�." << endl;
		system("pause");
		return;
	}
	
	cout << "(���� �Է½� ���� ȭ������ ���ư��ϴ�.)" << endl;
	system("pause");
}

void Bettle(DungeonLevel level)
{
	system("cls");
	Monster* pMonster = new Monster;
	pMonster->Initialize(level);
	userAnswerInt = BETTLE_ACTTION_END + 1;

	while (true)
	{
		system("cls");
		cout << "��================" << GetDungeonName(level) << " ���� ================��" << endl;
		pMonster->GetInterFace_MonsterStatus();
		player.GetInterFace_PlayerStatus();

		cout << endl << "+++++++++++++++++++++++++++++++++++" << endl;
		player.GetInterFace_BattleMenu();
		cout << "�ൿ�� �������ּ��� : " << endl;
		cin >> userAnswerInt;

		bool isPlayerFirst = true;
		if (player.Getspeed() >= pMonster->Getspeed())
			isPlayerFirst = true;
		else
			isPlayerFirst = false;

		switch (userAnswerInt -1)
		{
		case ATTACK:
			if (isPlayerFirst)
				BettleTimeLine(&player, pMonster);
			else
				BettleTimeLine(pMonster, &player);
			break;
		case DEFENSE:
			player.GetDefendedDamage(pMonster->Getattack());
			cout << (pMonster->GetName()) << "�� ������ ���," << player.GetDemage(pMonster->Getattack()) << "�� �������� �Ծ���!" << endl;
			break;
		case SKILL:
			cout << "����Ͻ� ��ų�� �������ּ���." << endl;
			player.GetInterFace_SkillList();
			cin >> userAnswerInt;
			player.UseSkill(userAnswerInt, pMonster);
			cout << (pMonster->GetName()) << "�� ������ ���," << player.GetDemage(pMonster->Getattack()) << "�� �������� �Ծ���!" << endl;
			break;
		case ITEM:
			if (!player.IsInvemEmpty())
			{
				cout << "����Ͻ� �������� �������ּ���" << endl;
				player.GetInterFace_Inventory();
				cin >> userAnswerInt;
				player.UseItem(userAnswerInt - 1);
			}
			else
			{
				cout << "����� �� �ִ� �������� �����ϴ�." << endl;
				system("pause");
				continue;
			}
			break;
		case ESCAPE:
			cout << "������ �����ƽ��ϴ�." << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			break;
		}

		if (pMonster->GetHP() <= 0 || player.GetHP() <= 0)
		{
			system("pause");
			return;
		}
		system("pause");
	}
}

int main()
{
	IntalizeGameOption();
	SkillManager::GetInst()->initSkillList();
	ItemManager::GetInst()->initItemList();

	bool isLoad = false;
	while (!isLoad)
	{
		system("cls");
		cout << "1. �� ĳ���� ����" << endl;
		cout << "2. �ҷ�����" << endl;
		int select = -1;
		cin >> select;
		switch (select - 1)
		{
		case CREATE:
			CreatePlayer();
			isLoad = true;
			break;
		case LOAD:
			isLoad = Load("save.txt");
			break;
		}
	}

	while (ShowStage());
	return 0;
}

bool Load(const char* pFileName)
{
	bool result = false;
	FILE* pFile;
	fopen_s(&pFile, pFileName, "rt");
	if (pFile == nullptr)
	{
		cout << "�ҷ��� ������ �������� �ʽ��ϴ�." << endl;
		result = false;
		system("pause");
	}
	else
	{
		char name[20] = "";
		fread(name, sizeof(char), 20, pFile);
		fclose(pFile);

		cout << name << "�� ������ �ҷ��Խ��ϴ�" << endl;
		result = true;
		system("pause");
	}
	fclose(pFile);
	return result;
}

void Save(const char* pFileName)
{
	FILE* pFile;
	fopen_s(&pFile, pFileName, "wt");
	fwrite(player.GetName(), sizeof(char), strlen(player.GetName()), pFile);
	fclose(pFile);
	cout << "������ ����Ǿ����ϴ�." << endl;
	system("pause");
}













/*
11.19
 - ����(����Ŀ��) ����
 - ���� ����Ŀ�� : ��ĭ�� �κ��丮�� �Ѱ� �̻��� ������ �������� ������ �� �ְ� ��
 - STACK_MSX = 3
*/

/*
11.25
> ����Ŀ�� ������ ���� �� ����
 - ����(�� ����), �κ��丮 ���

> ����
 - �Ǹ�, �����ϱ⿡�� ����Ŀ��

> ĳ���� ����
 - ��� ����Ʈ
 - ��� �ɷ�ġ ���� (���� �ɷ�ġ + �߰� �ɷ�ġ ���·� ǥ��)

+)




/*

memset(void*,  int,  size_t);

(�迭�� �ּ�, �ʱ�ȭ �� ��, ���� ����)
 -> �ش� �迭�� 0���� ������ ���̱��� �ʱ�ȭ �� ������ �ʱ�ȭ

 #include <Window.h>
 ZeroMemory(����ü, ����);	//����ü�� 0���� �ʱ�ȭ

*/
