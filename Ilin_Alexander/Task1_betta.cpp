#include <iostream>
#include <stdio.h>
#include <random>
#include <string>

using RUB = unsigned long int;

const int end_month = 7;
const int end_year = 2036;

class Person 
{
public:

    bool life = true;
// Животное
    bool animal = false;                // Подумать о создании нового класса...
    RUB animal_cost = 2'000;

// Деньги
    RUB money = 10'000;
    RUB safety_pillow = 50'000;
// Банкиры
    RUB bank_money = 0;
// Доходы
    RUB salary = 30'000;
// Траты
    RUB spents_food = 20'000;
    RUB spents_internet = 1'000;

    void money_profit(const RUB profit)                                 // Изменение бюджета
    {
        money += profit;
    }

    void money_count()                                                  // Выписка бюджета
    {
        if (life){
            printf("My money                   : %lu\n", money);
            printf("My money in bank           : %lu\n", bank_money);            
        }
        else{
            printf("U are bankrupt :( ");
        }
    }

    bool check_money(const RUB cost)                                    // Проверка на хватку денег (Выдает тру/фолс)
    {
        bool verified = false;
        if (cost > money){
            if (cost <= money + bank_money){
                verified = true;
            }
            if (cost > money + bank_money){
                life = false;
            }
        }
        return verified;
    }

    bool check_interest(const RUB cost)                                 // Проверка на заинтересованность в покупке (Выдает тру/фолс)
    {                                                                   // Добавить рандомную оценку на относительной цене покупки к бюджету общему
        bool verified = false;
        if (true){
            verified = true;
        }
        return verified;
    }

    void salary()                                                      // Зарплата
    {
        if (this -> salary){
        money_profit(salary); 
        }
    }

    void buy_animal()
    {
        animal = true;
        money_profit(-animal_cost);
    }

    void shopping()                                                     // Траты на еду
    {
        RUB cost = 0;
        if (spents_food){
            cost += spents_food;
        }
        if (spents_internet){
            cost += spents_internet;
        }
        if(check_money(cost)){
            money_profit(-cost); 
        }

        if (!animal and check_money(animal_cost) and check_interest(animal_cost)){
            buy_animal();
        }
    }

    void cost_save()                                                    // Сбережения
    {
        if (money > safety_pillow){
            RUB transfer = money - safety_pillow;
            bank_money += transfer;
            money -= transfer;
        }
    }   
};

Person I{};

void simulation(Person& person)
{
    int month = 1;
    int year = 2026;

    for(; year <= end_year; year++){                                    // Ежегодно

        for (; month <= 12 ; month++){                                  // Ежемесячно
                if(year == end_year && month == end_month){
                    person.money_count(); 
                    break;
                }
                
                person.salary(); 

                person.shopping();

                person.cost_save();
        }
        month = 1;
    }
}

int main()
{
    simulation(I);
}