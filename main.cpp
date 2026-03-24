#include <iostream>
#include <ctime>
#include <cstdlib>

#include <windows.h>

using namespace std;

struct Stats {
    int hp;
    int atk;
    int def;
    int speed;

    float critRate = 0.05f;
    float critDMG = 1.5f;
};

struct BonusStats {
    float hpPercent = 0;
    int hp = 0;
    float atkPercent = 0;
    int atk = 0;
    float defPercent = 0;
    int def = 0;

    float critRate = 0;
    float critDMG = 0;
};

class Character {
    public:
        Stats baseStats;
        BonusStats BonusStats;

        int currentHp;
        int gauge;

        Character(Stats s) {
            baseStats = s;
            currentHp = getFinalStats().hp;
            gauge = 0;
        }

        Stats getFinalStats() {
            Stats final = baseStats;

            final.hp = baseStats.hp * (1 + BonusStats.hpPercent) + BonusStats.hp;
            final.atk = baseStats.atk * (1 + BonusStats.atkPercent) + BonusStats.atk;
            final.def = baseStats.def * (1 + BonusStats.defPercent) + BonusStats.def;

            final.critRate = baseStats.critRate + BonusStats.critRate;
            final.critDMG = baseStats.critDMG + BonusStats.critDMG;

            return final;
        }

        // int attack() {
        //     Stats final = getFinalStats();

        //     int damage = final.atk;

        //     if(rand() % 100 < final.critRate*100) {
        //         cout << "CRIT!\n" ;
        //         damage = (int)(damage * final.critDMG);
        //     }

        //     return damage;
        // }

        void takeDamage(int damage) {
            currentHp -= damage;
            cout << "피해: " << damage << endl ;
            gauge += 5;
        }

        void gainGauge() {
            gauge += 20;
            if (gauge > 100) gauge = 100;
        }

        int ultimate() {
            Stats final = getFinalStats();

            gauge = 0;
            cout << "🔥\n";
            return final.atk * 2; // 200% 데미지
        }
};

class DamageSystem {
    public:
        static int calculateDamage(Character& attacker, Character& target) {
            Stats atkStats = attacker.getFinalStats();
            Stats defStats = target.getFinalStats();

            int damage = atkStats.atk;

            // 치명타 대미지 구현부
            if(rand() % 100 < atkStats.critRate * 100) {
                cout << "Crit!\n" ;
                damage = (int)(damage * atkStats.critDMG);
            }

            int finalDamage = damage - defStats.def;
            if(finalDamage < 0) finalDamage = 0;

            return finalDamage;
        }
};

int main() {
    SetConsoleOutputCP(65001);

    srand(time(0));

    Character player({20000, 2000, 1000, 100, 0.5f, 2.0f});
    Character enemy({360000, 2000, 500, 90, 0.0f, 1.0f});

    bool playerTurn = player.baseStats.speed >= enemy.baseStats.speed;

    while (player.currentHp > 0 && enemy.currentHp > 0) {
        if (playerTurn) {
            cout << "\n[플레이어 턴]\n";
            cout << "1. 공격\n2. 기 모으기\n";
            if (player.gauge >= 100) {
                cout << "3. 필살기\n";
            }
            int input;
            cin >> input;

            if (input == 1) {
                int damage = DamageSystem::calculateDamage(player, enemy);
                enemy.takeDamage(damage);
                player.gainGauge();
            }
            else if (input == 2) {
                player.gainGauge();
                player.gainGauge();
            }
            else if (input == 3 && player.gauge == 100) {
                int damage = player.ultimate();
                enemy.takeDamage(damage);
                player.gauge = 0;
            }

            if (enemy.currentHp <= 0) break;
        } else {
            cout << "\n[적 턴]\n";

            int action = rand() % 1;

            if (enemy.gauge == 100) {
                action = 2; // 필살기 강제 사용 (혹은 확률 조정 가능)
            }

            if (action == 0) {
                cout << "적이 공격!\n";
                int damage = DamageSystem::calculateDamage(enemy, player);
                player.takeDamage(damage);
                enemy.gainGauge();
            }
            // else if (action == 1) {
            //     cout << "적이 방어!\n";
            //     enemy.defend();
            //     enemy.gainGauge();
            // }
            else {
                cout << "적이 필살기 사용!!!\n";
                int damage = enemy.ultimate();
                player.takeDamage(damage);
            }
        }

        cout << "\n플레이어 HP: " << player.currentHp << endl;
        cout << "적 HP: " << enemy.currentHp << endl;

        playerTurn = !playerTurn;
    }

    if (player.currentHp <= 0) cout << "\n패배...\n";
    else cout << "\n승리!\n";

    return 0;
}

//g++ main.cpp -o game
//./game

/* 
 * feat: describe what you added or changed
 * refactor: describe what you improved
 * fix: describe the bug
 * 
 * chore: minor updates
 * 
 * docs: update LOG.md
 */
