#include <iostream>
#include <stdio.h>
#include <random>
#include <string>

using LIFE = unsigned int;

using RUB = unsigned long int;

const int end_month = 7;
const int end_year = 2036;

int month = 1;
int year = 2026;

static std::random_device seed;
static std::mt19937 generator(seed());

class Person 
{
public:

    bool life = true;
// Животное
    bool animal = false;                // Подумать о создании нового класса...
    RUB animal_cost = 10'000;
// Деньги
    RUB money = 10'000;
    RUB safety_pillow = 50'000;
// Банкиры
    RUB bank_money = 0;
    float bank_percent = 0.3;
    RUB total_spent = 0;
// Доходы
    RUB salary = 10'000;
// Траты
    RUB spents_food = 8'000;
    RUB spents_internet = 1'500;

    RUB random_digital(const RUB x, const RUB y)
    {
        std::uniform_int_distribution<RUB> cost(x, y);
        return cost(generator);
    }

    void money_profit(const RUB profit)                                 // Изменение бюджета в плюс
    {
        money += profit;
    }
    void money_less(const RUB profit)                                   // Изменение бюджета в минус
    {
        money -= profit;
    }

    void money_count()                                                  // Выписка бюджета
    {
        if (life){
            printf("My money                   : %lu\n", money);
            printf("My money in bank           : %lu\n", bank_money);
            if (animal){
                printf("You have a animal\n");
            }
        }
        else{
            printf("U are bankrupt :( ");
        }
    }

    bool check_money(const RUB cost)                                    // Проверка на хватку денег (Выдает тру/фолс)
    {
        bool verified = false;
        if (cost < money){
            if (cost <= (money + bank_money)){
                verified = true;
            }
            if (cost > (money + bank_money)){
                life = false;
            }
        }
        return verified;
    }

    bool check_interest(const RUB cost)                                 // Проверка на заинтересованность в покупке (Выдает тру/фолс)
    {   
        bool verified = false;                                          // verified - проверено              
        if(bank_money > 0){
            float interest = static_cast<float>(cost) / static_cast<float>(bank_money);                           
            if ((0 < interest) && (interest <= 0.1)){       // Высокий интерес
                verified = true;
            }
            if ((0.1 < interest) && (interest <= 0.3)){     // Средний интерес
                if (random_digital(0, 100) < 50){
                    verified = true;              
                }
                else{
                    verified = false;
                }
            }
            if ((0.3 < interest) && (interest <= 0.5)){     // Низкий интерес
                if (random_digital(0, 100) < 10){
                    verified = true;              
                }
                else{
                    verified = false;
                }
            }
            if (interest > 0.5){            // Отсутствие интереса
                verified = false;
            }
        }    
        return verified;
    }

    void get_salary()                                                      // Зарплата
    {
        if (salary){
        money_profit(salary); 
        }
    }

    void buy_animal()
    {
        animal = true;
        money_less(animal_cost);    
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
            money_less(cost); 
        }

        if (!animal and check_money(animal_cost) && check_interest(animal_cost)){
            buy_animal();
            cost += animal_cost;
        }
        total_spent = cost;
    }

    void cost_save()                                                    // Сбережения
    {
        if (money > safety_pillow){
            RUB transfer = money - safety_pillow;
            bank_money += transfer;
            money -= transfer;
        }
    } 
    
    void bank_percent_profit()
    {
        bank_percent = 0.1;
        
        if (total_spent >= 5'000){
            bank_percent += 0.07;
        }
        money += static_cast<RUB>(static_cast<float>(bank_money) * (bank_percent / 12));
    }

};
/*
class Animal
{
    public:
    LIFE hunger = 5;

    void eating()
    {
        if (){
            hunger -= 1
        }
        if (hunger)
    }
}
*/

Person I{};

void simulation(Person& person)
{
    for(; year <= end_year; year++){                                    // Ежегодно

        for (; month <= 12 ; month++){                                  // Ежемесячно
                if(year == end_year && month == end_month){
                    person.money_count();
                    return;
                }
                
                person.get_salary(); 

                person.shopping();

                person.cost_save();
                person.bank_percent_profit();
        }
        month = 1;
    }
}

int main()
{
    simulation(I);
}
