#include "MiniPoketmonGo.h"
#include "FileManager.h"
#include "Player.h"
#include <fstream>

MiniPoketmonGo::MiniPoketmonGo()
{
	fm = new FileManager();
	loadData();
}


MiniPoketmonGo::~MiniPoketmonGo()
{
	
}
void MiniPoketmonGo::loadData(){
	monsters = fm->readMonsterFromFile();
	balls = fm->readMonsterBallFromFile();
	player = fm->readPlayerFromFile(monsters, balls);
}


void MiniPoketmonGo::debug(){
	for (int i = 0; i < monsters.size(); i++){
		cout << monsters.at(i).getName() << endl;
	}
}

void MiniPoketmonGo::run(){
	bool out = false;
	while (!out){
		switch (menu_main()){
		case 1:
			menuPlayer();
			break;
		case 2:
			//menuMonster();
			break;
		case 3:
			menuBuy();
			break;
		case 4:
			//menuGetPoketmon();
			break;
		case 5:
			//menuExit();
			out = true;
			break;
		}
	}
}
int MiniPoketmonGo::menu_main(){
	int selectedNum;
	bool isError = false;
	while (1){
		system("cls");
		cout << "미니 포켓몬 고" << endl << endl;
		cout << "1. 플레이어 정보 보기 & 정보 변경" << endl;
		cout << "2. 내 몬스터 보기 & 정보 변경" << endl;
		cout << "3. 몬스터볼 구입하기" << endl;
		cout << "4. 몬스터 잡기" << endl;
		cout << "5. 저장 & 종료" << endl;
		if (isError)
			cout << "입력범위가 벗어 났습니다. 다시 입력해주세요" << endl;
		cin >> selectedNum;
		if (!(1 <= selectedNum && selectedNum <= 5))
			isError = true;
		
		else
			break;
		
	}
	return selectedNum;
}

void MiniPoketmonGo::menuPlayer(){
	bool isError = false;
	bool out = false;
	int selectedNum;
	while (!out){
		while (1){
			system("cls");
			cout << "플레이어 정보" << endl << endl;
			cout << "이름 : " << player->getName() << endl;
			cout << "성별 : " << ((player->getSex() == 1) ? "남" : "여") << endl;
			cout << "소지금 : " << player->getMoney() << endl;
			cout << "최대 보유 가능 몬스터 수 : " << player->getMaxMonster() << endl;
			cout << "최대 보유 가능 몬스터 볼 수 : " << player->getMaxBall() << endl<<endl;

			cout << "1. 플레이어 이름 변경" << endl;
			cout << "2. 소지금 추가하기" << endl;
			cout << "3. 최대 보유 가능 몬스터 수 추가하기" << endl;
			cout << "4. 최대 보유 가능 몬스터 볼 수 추가하기" << endl;
			cout << "5. 메인 메뉴로 돌아가기" << endl;

			if (isError)
				cout << "입력범위가 벗어 났습니다. 다시 입력해주세요" << endl;
			cin >> selectedNum;
			if (!(1 <= selectedNum && selectedNum <= 5)){
				isError = true;
			}
			else
				break;
		}

		switch (selectedNum){
		case 1:{
				   string newName;
				   cin.ignore();
				   cout << "변경할 이름을 입력하세요 : ";
				   getline(cin, newName);
				   player->setName(newName);
		}
			break;
		case 2:{
				   int addMoney;
				   cout << "추가할 액수를 입력하세요 : ";
				   cin >> addMoney;
				   player->setMoney(player->getMoney()+addMoney);
		}
			break;
		case 3:{
				   int addMaxMonster;
				   cout << "추가할 수를 입력하세요 : ";
				   cin >> addMaxMonster;
				   player->setMaxMonster(player->getMaxMonster() + addMaxMonster);
		}
			break;
		case 4:{
				   int addMaxBall;
				   cout << "추가할 수를 입력하세요 : ";
				   cin >> addMaxBall;
				   player->setMaxBall(player->getMaxBall() + addMaxBall);
		}
			break;
		case 5:
			out = true;
			break;
		}
	}

}

void MiniPoketmonGo::menuBuy(){
	system("cls");
	cout << "몬스터볼 구입 (소지금 : " << player->getMoney() << "원)" << endl << endl;
	vector<BallPocket>& ballPocket = player->getBallPocket();

	int playerTotalBallNum = 0;
	for (int i = 0; i < ballPocket.size(); i++) playerTotalBallNum += ballPocket.at(i).getNum();

	for (int i = 0; i < ballPocket.size()+1; i++){
		
		if (i == ballPocket.size()){
			cout << (i + 1) << ". 메인메뉴로 돌아가기" << endl;
		}
		else{
			BallPocket nowPocket = ballPocket.at(i);
			cout << (i + 1) << ". " << nowPocket.getBall().getName()
			<< "(" << nowPocket.getNum() << "개 보유 중) 개당 " << nowPocket.getBall().getPrice() << "원" << endl;
		}
	}
	
	while (1){
		int selectedNum; cin >> selectedNum;
		if (1 <= selectedNum && selectedNum <= ballPocket.size()+1){
			if (selectedNum == (ballPocket.size()+1) ){
				return;
			}
			while (1){
				cout << "원하는 구매 수량을 입력하세요 : ";
				int num; cin >> num;
				if (player->getMaxBall() < playerTotalBallNum + num){
					cout << "총 보유 수량을 넘어서게 됩니다." << endl;
					continue;
				}
				else{
					int price = num * (ballPocket.at(selectedNum - 1).getBall().getPrice());
					if (player->getMoney() < price){
						cout << "보유한 금액보다 많은 금액이 필요합니다." << endl;
					}
					else{
						player->setMoney(player->getMoney() - price);
						ballPocket.at(selectedNum - 1).addNum(num);
						return;
					}
				}
			}
		}
		else{
			cout << "입력 범위를 벗어났습니다." << endl;
		}
	}
}
