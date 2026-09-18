#include <stdio.h>
#include <random>
#include <cmath>

using RUB = unsigned long long int;
using YEARS = unsigned int;

struct Person{
    RUB cash;
    RUB salary;
    YEARS age;
    unsigned int number_of_promotions;
    unsigned int health;
    int childs;
    bool car;
    bool wife;
    bool lizard;
    bool mortage;
    bool dismission;
};

struct Mortage{
    RUB debt;
    RUB payment;
    RUB down_payment;
    RUB principal_amount;
    unsigned int month;
    double interest_rate;
};

struct Time{
    unsigned int month;
    unsigned int year;
};

struct Person peter;
struct Mortage mortage;
struct Time time;


void peter_init()
{
    peter.age=21;
    peter.cash=0;
    peter.salary=40000;
    peter.health=60;
    peter.number_of_promotions=0;
    peter.dismission=false;

}


void mortage_init()
{
    mortage.debt=6500000;
    mortage.down_payment=2500000;
    mortage.principal_amount=mortage.debt-mortage.down_payment;

    mortage.interest_rate=0.155/12;
    mortage.month=12*10;

    RUB K = mortage.principal_amount;
    double& r = mortage.interest_rate;
    double t=std::pow(mortage.interest_rate/12.0+1, mortage.month);
    mortage.payment=(K)*(r*t)/(t-1);
}


void time_init()
{
    time.year=2027;
    time.month=1;
}


void peter_mortage()
{
    if (((time.year>=2029 and time.month>=1) or peter.cash>=mortage.down_payment)
     and peter.salary>mortage.payment+30000 and mortage.principal_amount>0){
        if (mortage.principal_amount<peter.cash*0.8){
            peter.cash-=mortage.principal_amount;
            mortage.principal_amount=0;
        }
        else{
            mortage.principal_amount-=mortage.payment;
            peter.cash-=mortage.payment;
        }
     }
}





void peter_salary()
{
    if (peter.dismission){
        peter.salary = 0;
        return;
    }

    double salary_thousands = 40.0;

    if (peter.number_of_promotions <= 5){
        salary_thousands =
            (-1.0/3.0) * std::pow(peter.number_of_promotions, 5)
          + (25.0/12.0) * std::pow(peter.number_of_promotions, 4)
          + (25.0/6.0)  * std::pow(peter.number_of_promotions, 3)
          - (385.0/12.0)* std::pow(peter.number_of_promotions, 2)
          + (397.0/6.0) * peter.number_of_promotions
          + 40.0;
    }
    else {
        salary_thousands = 350.0;
    }

    if (salary_thousands < 0) salary_thousands = 0;
    peter.salary = static_cast<RUB>(salary_thousands * 1000);
}


void world_tick()
{
    if (time.month==12){
        ++(time.year);
        time.month=1;
        peter.health-=1;
    }
    else{
        ++(time.month);
    }
}


void peter_promotion_at_work() 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 12*60);
    for (int i = 1; i<=6; i++){
        if (dist(gen) == 1){
            peter.number_of_promotions++;
            peter_salary();
            break;
        };
    }
}


void peter_dismissial_from_work()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 12*60);
    if (dist(gen) == 1){
        peter.dismission = true;
    }
}


void peter_disease()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(12, 54*12);
}



void simulation()
{
    while(peter.health){

        peter_salary();
        peter.cash+=peter.salary;
        peter_dismissial_from_work();
        peter_promotion_at_work();
        peter.dismission = false;
        peter_mortage();

        //peter_rent(year, month);              // аренда квартиры (растёт каждый год)
        //peter_mortage()
        //peter_food(year, month);              // еда (зависит от инфляции)
        //peter_transport(year, month);         // метро/бензин
        //peter_utilities(year, month);         // свет, вода, интернет
        //peter_phone(year, month);             // мобильная связь
        //peter_clothes(year, month);           // одежда (сезонно)

        //peter_taxes(year, month);             // НДФЛ, налог на имущество
        //peter_deposit(year, month);           // банковский вклад (капает %)
        //peter_stocks(year, month);            // акции (случайные колебания)
        //peter_credit(year, month);            // кредитка, проценты

        //peter_car(year, month);               // покупка машины в рассрочку
        //peter_car_repair(year, month);        // случайные поломки
        //peter_mortgage(year, month);          // ипотека на 20 лет

        //peter_vacation(year, month);          // отпуск раз в год
        //peter_entertainment(year, month);     // спортзал
        //peter_doctor(year, month);            // случайные болезни
        //peter_health_check(year);             // ухудшение здоровья с возрастом

        //peter_inheritance(year, month);       // наследство от бабушки
        //peter_friend_loan(year, month);       // дал в долг другу
        //peter_accident(year, month);          // ДТП

        //peter_economy(year, month);           // кризис/рост
        //peter_pandemic(year, month);          // ковид-подобное событие

        //peter_save_for_goal(year, month);     // цель: квартира/машина
        //peter_pension_fund(year, month);      // пенсионные накопления
        //peter_emergency_fund(year, month);    // подушка безопасности

        world_tick();
        if (peter.health==0){
            break;
        };
    }
}

int main(){
    peter_init();
    mortage_init();
    time_init();
    simulation();
}
