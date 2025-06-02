#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Animal {
public:
	virtual void makeSound() = 0;
	virtual ~Animal() {};
};

class Dog : public Animal {
	void makeSound() {
		cout << "강아지는 멍멍" << endl;
	}
};

class Cat : public Animal {
	void makeSound() {
		cout << "고양이는 야옹" << endl;
	}
};

class Cow : public Animal {
	void makeSound() {
		cout << "소는 음머" << endl;
	}
};

class Zoo {
private:
	Animal* animals[10]; // 동물 객체를 저장하는 포인터 배열
	int count = 0; //현재 동물원에 있는 동물 수
public:

	// 동물을 동물원에 추가하는 함수
	// - Animal 객체의 포인터를 받아 포인터 배열에 저장합니다.
	// - 같은 동물이라도 여러 번 추가될 수 있습니다.
	// - 입력 매개변수: Animal* (추가할 동물 객체)
	// - 반환값: 없음
	void addAnimal(Animal* animal) {
		
		if (count < getAnimalsSize()) {
			animals[count] = animal;
			count++;
			cout << "동물원에 랜덤으로 동물을 추가합니다. (" << count << "/" << getAnimalsSize() << ")" << endl;
		}
		else {
			cout << "더 이상 동물원에 동물을 추가할 수 없습니다." << endl;
		}
	};


	// 동물원에 있는 모든 동물의 행동을 수행하는 함수
	// - 모든 동물 객체에 대해 순차적으로 소리를 내고 움직이는 동작을 실행합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	void performActions() {
		cout << "===========================" << endl;

		if (count > 0) {
			cout << "동물 울음 소리~~~" << endl;
			for (int i = 0; i < count; i++) {
				animals[i]->makeSound();
			}
		}
		else {
			cout << "울음을 낼 동물들이 없습니다." << endl;
		}

		
	};
	
	//배열 사이즈 가져오기
	int getAnimalsSize() {
		return sizeof(animals)/sizeof(animals[0]);
	}


	// Zoo 소멸자
	// - Zoo 객체가 소멸될 때, 동물 벡터에 저장된 모든 동물 객체의 메모리를 해제합니다.
	// - 메모리 누수를 방지하기 위해 동적 할당된 Animal 객체를 `delete` 합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음

	~Zoo() {
		cout << "===========================" << endl;
		cout << "Zoo 객체 소멸 시작" << endl;
		
		for (int i = 0; i < count; i++) {
			delete animals[i];
			cout << i+1 << "번째 동물 소멸" << endl;
		}

		delete[] animals;
		cout << "동물원 폐쇄 완료" << endl;
	};
};

Animal* createRandomAnimal() {
	int random = rand() % 3;
	cout << "랜덤 동물 : ";
	if (random == 0) {
		cout << "강아지 추가 시도" << endl;
		return new Dog;
	}
	else if (random == 1) {
		cout << "고양이 추가 시도" << endl;
		return new Cat;
	}
	else if (random == 2) {
		cout << "소 추가 시도" << endl;
		return new Cow;
	}

	return NULL;
};

int main()
{
	int num = 0;
	Zoo *zoo = new Zoo;
	cout << zoo->getAnimalsSize() << endl;
	/*
	for (int i = 0; i < zoo->getAnimalsSize(); i++) {
		zoo->addAnimal(createRandomAnimal());
	}
	*/
	bool loop = true;
	while (loop) {
		int num;
		cout << "============================================================" << endl;
		cout << "1. 랜덤 동물 추가,   2. 동물 울음소리,   그 외 동물원 폐쇄" << endl;
		cout << "선택해 주세요 : ";
		cin >> num;

		switch (num) {
		case 1:
			zoo->addAnimal(createRandomAnimal());
			break;
		case 2:
			zoo->performActions();
			break;
		case 3:
		default:
			zoo->~Zoo();
			loop = false;
			break;
		}
	
	}

	return 0;
}