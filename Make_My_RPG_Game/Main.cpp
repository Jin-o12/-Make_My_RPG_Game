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

int userAnswerInt;
char userAnswerChar;


void CreatePlayer()
{
	cout << "이름이 무엇인가요?" << endl;
	char name[20];
	cin >> name;
	player.SetName(name);

	do
	{
		cout << "직업을 고르세요." << endl;
		cout << "1. 전사 / 2. 마법사 / 3. 궁수 / 4. 격투가 / 5. 도적" << endl;
		userAnswerInt = -1;
		cin >> userAnswerInt;
		if (0 >= userAnswerInt || userAnswerInt >= JOB_END+1)
		{
			cout << "목록에 없는 선택지를 고르셨습니다. 다시 입력해주세요." << endl;
			userAnswerInt = -1;
		}
		else
		{
			while (true)
			{
				player.SetPlayerJob(userAnswerInt);
				cout << "당신이 선택한 직업의 능력치입니다." << endl;
				player.GetInterFace_PlayerStatus();
				cout << "이걸로 괜찮으시겠습니까? typing Y or N" << endl;
				cin >> userAnswerChar;
				if (userAnswerChar == 'y' || userAnswerChar == 'Y')
				{
					cout << "직업 선택이 끝났습니다!" << endl;
					break;
				}
				else if (userAnswerChar == 'n' || userAnswerChar == 'N')
				{
					cout << "직업선택 과정을 다시 합니다" << endl;
					player.SetPlayerJob(0);
					break;
				}
				else
				{
					cout << "Y 혹은 N 만 입력해주세요" << endl;
					break;
				}
			}
		}
	} while (!(0 <= player.GetPlayerJob() && player.GetPlayerJob() < JOB_END));
	cout << "게임을 시작할 준비가 끝났습니다!" << endl;
	system("pause");
	system("cls");
}

bool ShowStage()
{
	system("cls");
	cout << "가고싶은 곳을 선택해주세요." << endl;
	for (size_t i = 0; i < STAGE_END; i++)
	{
		cout << i << ". " << GetStageName(static_cast<StageType>(i)) << endl;
	}
	cout << "숫자 입력 : " << endl;
	userAnswerInt = -1;
	cin >> userAnswerInt;
	switch (userAnswerInt)
	{
	case EXIT_GAME:
		cout << "게임을 종료합니다." << endl;
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
	default:
		break;
	}
	return true;
}

void ShowDungeon(StageType level)
{
	cout << "던전 난이도를 선택해주세요." << endl;
	cout << "1. 쉬움 / 2. 보통 / 3. 어려움 / 4. 지옥 / 5. 악몽" << endl; 
	cout << "숫자 입력 : ";
	cin >> userAnswerInt;
	Bettle(static_cast<DungeonLevel>(userAnswerInt - 1));
}

void ShowLodge(StageType level)
{
	while (true)
	{
		cout << "┌======================== " << GetStageName(level) << " ========================┐" << endl;
		cout << "│1. 한끼 식사		>  2G    [+ 5  HP] [+ 0  MP]   │" << endl;
		cout << "│2. 푸짐한 식사		>  5G    [+ 10 HP] [+ 0  MP]   │" << endl;
		cout << "│3. 일반 침대		>  10G   [+ 20 HP] [+ 5  MP]   │" << endl;
		cout << "│4. 푹신 침대		>  20G   [+ 40 HP] [+ 10 MP]   │" << endl;
		cout << "└======================================================┘" << endl;
		cin >> userAnswerInt;

		int hp = 0;
		int mp = 0;
		switch (userAnswerInt - 1)
		{
		case FOOD:
			player.BuySometing(2);
			player.HPchange(5);
			hp = 5;
			break;
		case DINNER:
			player.BuySometing(5);
			player.HPchange(10);
			hp = 10;
			break;
		case BED:
			player.BuySometing(10);
			player.HPchange(20);
			player.MPchange(5);
			hp = 20;
			mp = 5;
			break;
		case FLUFFYBED:
			player.BuySometing(20);
			player.HPchange(40);
			player.MPchange(10);
			hp = 40;
			mp = 10;
			break;
		default:
			break;
		}

		if (hp >= 0 || mp >=0)
		{
			cout << "체력이 " << hp << "만큼, 마나가 " << mp << "회복되었습니다" << endl;
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
		cout << "┌==================== " << GetStageName(level) << " ====================┐" << endl;
		cout << "| 0 . 나가기 (지역선택화면)" << "			|" << endl;
		for (size_t i = 0; i < 6; i++)
		{
			cout << "| " << i+1 << ". " << shopItemList[i]->GetName() << "			|" << endl;
		}
		cout << "└==============================================┘" << endl;
		cout << "원하는 항목의 번호를 입력해주세요." << endl;
		cin >> userAnswerInt;

		if(userAnswerInt == 0)
		{ 
			cout << "상점에서 나갑니다." << endl;
			return;
		}
		else if (userAnswerInt <= 6)
		{
			Item* choiceItem = shopItemList[userAnswerInt - 1];
			cout << choiceItem->GetName() << choiceItem->GetDescribe() << endl;
			cout << "구매하시겠습니까? Y or N" << endl;
			cin >> userAnswerChar;

			if (userAnswerChar == 'y' || userAnswerChar == 'Y')
			{
				if (player.BuySometing(choiceItem->GetPrice()))
				{
					player.InputItemToInven(ItemManager::GetInst()->SearchItemCodeByName(choiceItem->GetName()), 1);
					cout << choiceItem->GetName() << "가 구매되었습니다." << endl;
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
				cout << "Y 혹은 N 만 입력해주세요" << endl;
			}
			system("cls");
		}
	}
}


void ShowStatus(StageType level)
{
	player.GetInterFace_PlayerStatus();
	player.GetInterFace_Inventory();
	player.GetInterFace_EquipList();

	cout << "1. 장비 장착 / 2. 나가기" << endl;
	cin >> userAnswerInt;

	switch (userAnswerInt)
	{
	case 1:
		cout << "아이템을 선택해주세요." << endl;
		player.GetInterFace_Inventory();
		cin >> userAnswerInt;
		player.EquipItem(userAnswerInt);
		break;
	case 2:
		cout << "메인화면으로 돌아갑니다." << endl;
		system("pause");
		return;
	}
	
	cout << "(엔터 입력시 이전 화면으로 돌아갑니다.)" << endl;
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
		cout << "┌================" << GetDungeonName(level) << " 던전 ================┐" << endl;
		pMonster->GetInterFace_MonsterStatus();
		player.GetInterFace_PlayerStatus();

		cout << endl << "+++++++++++++++++++++++++++++++++++" << endl;
		player.GetInterFace_BattleMenu();
		cout << "행동을 선택해주세요 : " << endl;
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
			cout << (pMonster->GetName()) << "의 공격을 방어," << player.GetDemage(pMonster->Getattack()) << "의 데미지를 입었다!" << endl;
			break;
		case SKILL:
			cout << "사용하실 스킬을 선택해주세요." << endl;
			player.GetInterFace_SkillList();
			cin >> userAnswerInt;
			player.UseSkill(userAnswerInt, pMonster);
			cout << (pMonster->GetName()) << "의 공격을 방어," << player.GetDemage(pMonster->Getattack()) << "의 데미지를 입었다!" << endl;
			break;
		case ITEM:
			if (!player.IsInvemEmpty())
			{
				cout << "사용하실 아이템을 선택해주세요" << endl;
				player.GetInterFace_Inventory();
				cin >> userAnswerInt;
				player.UseItem(userAnswerInt - 1);
			}
			else
			{
				cout << "사용할 수 있는 아이템이 없습니다." << endl;
				system("pause");
				continue;
			}
			break;
		case ESCAPE:
			cout << "무사히 도망쳤습니다." << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			break;
		}

		if (pMonster->GetHP() <= 0)
		{
			player.Kill(pMonster);
			system("pause");
			system("cls");
			return;
		}	
		else if(player.GetHP() <= 0)
		{
			player.Dead();
			system("pause");
			system("cls");
			return;
		}
	}
}

int main()
{
	IntalizeGameOption();
	SkillManager::GetInst()->initSkillList();
	ItemManager::GetInst()->initItemList();
	CreatePlayer();	
	
	while (ShowStage());
	return 0;
}


/*
11.19
 - 포션(스텍커블) 구매
 - 포션 스텍커블 : 한칸의 인벤토리에 한개 이상의 갯수의 아이템이 적제될 수 있게 함
 - STACK_MSX = 3
*/

/*
11.25
> 스텍커블 아이템 구분 및 구현
 - 구매(돈 차감), 인벤토리 목록

> 상점
 - 판매, 구매하기에서 스텍커블

> 캐릭터 정보
 - 장비 리스트
 - 장비 능력치 적용 (기존 능력치 + 추가 능력치 형태로 표시)

+)
> 전투에서 아이템 사용
*/




/*

memset(void*,  int,  size_t);

(배열의 주소, 초기화 할 값, 지정 길이)
 -> 해당 배열을 0부터 지정된 길이까지 초기화 할 값으로 초기화

 #include <Window.h>
 ZeroMemory(구조체, 길이);	//구조체를 0으로 초기화

*/
