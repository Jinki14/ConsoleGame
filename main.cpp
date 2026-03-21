#include <iostream>
#include <ctime>
#include <cstdlib>

#include <windows.h>

using namespace std;

class Character {
    public:
    int hp;
    int atk;
    int def;
    bool isDefending;
    int gauge;

    Character(int h, int a, int d) {
        hp = h;
        atk = a;
        def = d;
        isDefending = false;
        gauge = 0;
    }

    int attack() {
        return atk;
    }

    void defend() {
        isDefending = true;
    }

    void takeDamage(int damage) {
        if(isDefending) {
            damage = damage * 40 / 100; // 60% 감소
        }

        int finalDamage = damage - def;

        if (finalDamage < 0) finalDamage = 0;

        hp -= finalDamage;

        cout << "받은 피해: " << finalDamage << endl ;

        isDefending = false;
    }

    void gainGauge() {
        gauge += 20;
        if (gauge > 100) gauge = 100;
    }

    int ultimate() {
        gauge = 0;
        cout << "🔥 필살기 발동!\n";
        return atk * 200 / 100; // 200% 데미지
    }
};

int main() {
    SetConsoleOutputCP(65001);

    srand(time(0));

    Character player(10000, 2000, 300);
    Character enemy(10000, 2000, 300);

    while (player.hp > 0 && enemy.hp > 0) {
        cout << "\n[플레이어 턴]\n";
        if (enemy.isDefending) {
            cout << "적은 방어 중이다!\n";
        }
        cout << "1. 공격\n2. 방어\n";
        if (player.gauge == 100) {
            cout << "3. 필살기\n";
        }
        int input;
        cin >> input;

        if (input == 1) {
            int damage = player.attack();
            enemy.takeDamage(damage);
            player.gainGauge();
        }
        else if (input == 2) {
            player.defend();
            cout << "방어 자세!\n";
            player.gainGauge();
        }
        else if (input == 3 && player.gauge == 100) {
            int damage = player.ultimate();
            enemy.takeDamage(damage);
        }

        enemy.isDefending = false;

        if (enemy.hp <= 0) break;

        cout << "\n[적 턴]\n";

        int action = rand() % 2;

        if (enemy.gauge == 100) {
            action = 2; // 필살기 강제 사용 (혹은 확률 조정 가능)
        }

        if (action == 0) {
            cout << "적이 공격!\n";
            int damage = enemy.attack();
            player.takeDamage(damage);
            enemy.gainGauge();
        }
        else if (action == 1) {
            cout << "적이 방어!\n";
            enemy.defend();
            enemy.gainGauge();
        }
        else {
            cout << "적이 필살기 사용!!!\n";
            int damage = enemy.ultimate();
            player.takeDamage(damage);
        }

        player.isDefending = false;

        cout << "\n플레이어 HP: " << player.hp << endl;
        cout << "적 HP: " << enemy.hp << endl;
    }

    if (player.hp <= 0) cout << "\n패배...\n";
    else cout << "\n승리!\n";

    return 0;
}

//g++ main.cpp -o game
//./game