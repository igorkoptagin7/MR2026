#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using RUB = unsigned long long int;
//using RUB = long long int;

struct Pet {
    bool presence;
    bool had_dog;
    int death_year;
    int death_month;
};

struct Bank {
    RUB mortgage;               // ипотека
    RUB deposit;                // вклад
    RUB currency;               // деньги на счету в банке
    RUB year_income;            // количество денег заработанных за последний год
    RUB last_year_income;       // количество денег заработанных за предыдущий год
    RUB last_last_year_income;  // количество денег заработанных за пред предыдущий год
    RUB tax_paid;               // НДФЛ заплачено

};

struct car {
    bool presence;  // наличие
    int power;      // мощность двигателя
    int hp;         // текущее здоровье
    int max_hp;     // максимум здоровья
    bool broken;    // сломана ли в данный момент

};

struct flat {
    bool presence;  // наличие




};

struct Person {
    RUB cash;
    RUB salary;
    Pet dog;    
    Bank account;
    car car_1;
    flat flat_1;

};

struct Person bob;

void bob_salary(const int year, const int month) 
{
    if (year == 2027 && month == 1) { // Переход со стажировки на полноправную должность
        bob.salary = 100'000; 
    }

    if (year == 2029 && month == 5) {  // Смена места работы, та же должность
        bob.salary = 140'000; 
    }

    if (year == 2030 && month == 1) {  // Повышение
        bob.salary = 180'000; 
    }

    if (year == 2030 && month == 12) {  //  Смена места работы, понижение
        bob.salary = 150'000; 
    }

    if (year == 2032 && month == 11) {  // Повышение
        bob.salary = 200'000;  
    }

    bob.account.currency += bob.salary;
    bob.account.year_income += bob.salary;
}

void bob_car(const int year, const int month) 
{
    if (!bob.flat_1.presence) {
        return;
    }
    
    if (year >= 2030 || (year == 2030 && month >= 6)) {                                                 // появление желания купить авто
        if (bob.account.currency >= 500'000 && bob.salary >= 100'000 && !(bob.car_1.presence)) {        // появление возможности купить авто
            bob.car_1.presence = true;
            bob.car_1.power = 90;
            bob.car_1.hp = 255;
            bob.car_1.max_hp = 255;
            bob.car_1.broken = false;
            bob.account.currency -= 300'000;
            }
        }

    bob.account.currency -= 50'000;  //затраты на авто: страховка, топливо, штраф и ТО    

    if (bob.account.currency <= 50'000 && bob.salary <= 100'000 && bob.car_1.presence) {        // продажа авто в случае нехватки средств
        bob.car_1.presence = false;
        bob.car_1.power = 0;
        bob.account.currency += 200'000;
        bob.account.year_income += 200'000; 
    }
}

void bob_car_use(const int year, const int month) 
{
    if (!bob.car_1.presence) {
        return;
    }
    if (bob.car_1.broken) {
        return;
    }
    //Постепенный износ
    bob.car_1.hp -= 1 + rand() % 3;
    if (bob.car_1.hp < 0) {
        bob.car_1.hp = 0;
    }

    //вероятность поломки квадрат износа
    double wear = 1.0 - (double)bob.car_1.hp / bob.car_1.max_hp;
    double break_chance = wear * wear;

    double roll = (double)rand() / RAND_MAX;
    if (roll < break_chance) {
        bob.car_1.broken = true;
    }
}

void bob_car_repair(const int year, const int month)
{
    if (!bob.car_1.presence) {
        return;
    }
    if (!bob.car_1.broken) {
        return;
    }

    RUB cost = 5'000 + rand() % 95'001;

    if (bob.account.currency < cost) {
        return;
    }

    // макс хп падает и тем сильнее чем больше стоимость
    int hp_loss = 1 + (int)((double)cost / 100'000.0 * 9);
    if (bob.car_1.max_hp < 1) {
        bob.car_1.max_hp = 1;
    }

    bob.car_1.hp = bob.car_1.max_hp;
    bob.car_1.broken = false;
}

void bob_car_bill(const int year, const int month) 
{
    if (!bob.car_1.presence) {
        return;
    }
    if (month != 1) {
        return;
    }

    int power = bob.car_1.power;

    RUB rate;   // ставка за 1 л.с.
    if (power <= 100) {
        rate = 12;
    }
    else if (power <= 125) {
        rate = 25;
    }
    else if (power <= 150) {
        rate = 35;
    }
    else if (power <= 175) {
        rate = 45;
    }
    else if (power <= 200) {
        rate = 50;
    }
    else if (power <= 225) {
        rate = 65;
    }
    else if (power <= 250) {
        rate = 75;
    }
    else {
        rate = 150;
    }
    RUB tax = (RUB)power * rate;
    bob.account.currency -= tax;
}

void bob_food(const int year) 
{
    bob.account.currency -= (RUB)7000;
}

void bob_rent(const int year, const int month) 
{   
    long int rent = 0;

    if (bob.flat_1.presence) {
        return;
    }

    if ((year < 2027 || (year == 2027 && month <= 8))) {
        rent = 0;
    }
    else if (year < 2028 || (year == 2028 && month <= 6)) {
        rent = 20'000;
    }
    else {
        rent = 40'000;
    }
    
    bob.account.currency -= rent;
}

void bob_home_bills(const int year, const int month)  
{
    long int bills = 0;
    
    if (year > 2033 || (year == 2033 && month >= 3) ) {
        bills = 25'000;
    }
    else if (year > 2030 || (year == 2030 && month >= 4) ) {
        bills = 20'000;
    }
    else if (year > 2028 || (year == 2028 && month >= 6) ) {
        bills = 10'000;
    }
    else {
        bills = 5'000;
    }

    bob.account.currency -= bills;
}

void bob_mortgage(const int year, const int month) 
{
    long int mortgage = 0;

    if ((year > 2033 || (year == 2033 && month >= 3)) && bob.flat_1.presence == false) {
        
        bob.flat_1.presence = true;
        bob.account.mortgage = 15'000'000;

    }

    if (bob.account.mortgage > 0 && year < 2052) {

        mortgage = 70'000;

        if (month == 1) {
        mortgage *= 2;
        }

        if (bob.account.mortgage < mortgage) {
            mortgage = bob.account.mortgage;
        }

    }

    bob.account.currency -= mortgage;
    bob.account.mortgage -= mortgage;
          
}

void bob_dog(const int year, const int month) 
{
    if (bob.salary > 100'000 && bob.flat_1.presence == true && !bob.dog.presence && !bob.dog.had_dog) { // проверка возможности и желания зависти собаку
        bob.dog.presence = true;
        bob.dog.death_year = year + 12;
        bob.dog.death_month = month;
        bob.account.currency -= 20'000;
    }

    if (bob.dog.presence) {

        if ( !(year < bob.dog.death_year ||(year == bob.dog.death_year && month < bob.dog.death_month)) )  
        {
        bob.dog.presence = false;
        bob.account.currency -= 15'000;
        }
        else {
            bob.account.currency -= 7000;
        }
    }
}

void bob_food_bank_income(const int year, const int month)
{
    if (bob.account.currency > 200'000) {
        RUB put = (bob.account.currency - 200'000) / 10;
        bob.account.currency -= put;
        bob.account.deposit += put;
    }
    bob.account.deposit += (RUB)(bob.account.deposit * 0.005);
    bob.account.year_income += (RUB)(bob.account.deposit * 0.005);

    if (bob.account.currency <= 50'000 && bob.account.deposit > 0) {
        RUB need = (10'000 - bob.account.currency);
        if (need > bob.account.deposit) {
            need = bob.account.deposit;
        }
        bob.account.deposit -= need;
        bob.account.currency += need;
        bob.account.year_income += need;

    }
}

RUB sum_tax(RUB income)
{
    if (income <= 2'400'000) {
        return (RUB)(income * 0.13);
    }
    if (income <= 5'000'000) {
        return 312'000 + (RUB)((income - 2'400'000) * 0.15);
    }
    if (income <= 20'000'000) {
        return 702'000 + (RUB)((income - 5'000'000) * 0.18);
    }
     if (income <= 50'000'000) {
        return 3'402'000 + (RUB)((income - 20'000'000) * 0.20);
     }
    return 9'402'000 + (RUB)((income - 50'000'000) * 0.22);
}

void bob_NDFL(const int month) {

   RUB owed = sum_tax(bob.account.year_income);
   RUB delta = owed - bob.account.tax_paid;
   bob.account.currency -= delta;
   bob.account.tax_paid = owed;

    if (month == 1) {
        bob.account.last_last_year_income = bob.account.last_year_income;
        bob.account.last_year_income = bob.account.year_income;
        bob.account.year_income = 0;
        bob.account.tax_paid = 0;
    }

}

void simulation() 
{
    srand((unsigned)time(0));

    int year = 2026;
    int month = 9;

    while ( !(year == 2027 && month == 9) ) { 

        bob_salary(year, month);
        
        
        bob_mortgage(year, month);
        bob_rent(year, month);
        bob_home_bills(year, month);
        bob_food(year);
        bob_dog(year, month);
        bob_food_bank_income(year, month);
        bob_NDFL(month);

        bob_car(year, month);
        bob_car_use(year, month);
        bob_car_repair(year, month);
        bob_car_bill(year, month);
        //несколько кредитов или сдача в аренду

        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }

    }

}


void bob_init() 
{
    bob.account.currency = 20'000;
    bob.salary = 80'000;

    bob.account.deposit = 0;
    bob.account.tax_paid = 0;
    bob.account.mortgage = 0;
    
    bob.flat_1.presence = false;      // наличие квартиры
    
    bob.dog.presence = false;       // наличие собаки
    bob.dog.had_dog = false;

    bob.car_1.presence = false;         //наличие машины
    bob.car_1.power = 0;                //мощность двигателя
    bob.car_1.hp = 0;                   //прочность машины
    bob.car_1.max_hp = 255;             //максимальная прочность машины
    bob.car_1.broken = false;           // индикатор поломки

}

void bob_print() 
{
    printf("Bob cash = %llu\n", bob.account.currency);
}


int main () 
{
    bob_init();

    simulation();

    bob_print();

    return 0;
}