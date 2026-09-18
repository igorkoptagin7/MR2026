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

    // Для ипотеки
    RUB mortgage_debt;
    RUB mortgage_payment;
    unsigned int mortgage_months_left;
    int months_since_start;

};

struct Person peter;

void peter_init()
{
    peter.age=21;
    peter.cash=0;
    peter.salary=40000;
    peter.health=60;
    peter.number_of_promotions=0;
    peter.dismission=false;

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


void world_tick(int *year, int *month)
{
    if (*month==12){
        ++(*year);
        *month=1;
        peter.health-=1;
    }
    else{
        ++(*month);
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

void peter_mortage()
{
    if (peter.mortage){
        if (peter.mortgage_months_left > 0){
            if (peter.cash >= peter.mortgage_payment) {
                peter.cash -= peter.mortgage_payment;
            } else {
                peter.cash = 0;
            }

            if (peter.mortgage_debt >= peter.mortgage_payment) {
                peter.mortgage_debt -= peter.mortgage_payment;
            } else {
                peter.mortgage_debt = 0;
            }
            peter.mortgage_months_left--;
        }
        return;
    }

    const RUB FLAT_PRICE = 6500000ULL;
    const RUB DOWN_PAYMENT = 2500000ULL;
    const RUB LOAN_AMOUNT = FLAT_PRICE - DOWN_PAYMENT;
    const double RATE = 0.155;
    const unsigned int TERM_MONTHS = 10 * 12;

    bool can_afford = (peter.cash >= DOWN_PAYMENT);
    bool time_is_up = (peter.months_since_start >= 24);

    if (!can_afford && !time_is_up) {
        return;
    }

    if (!can_afford) {
        peter.cash = DOWN_PAYMENT;
    }

    peter.cash -= DOWN_PAYMENT;

    double r = RATE / 12.0;
    double monthly =
        LOAN_AMOUNT * r / (1.0 - std::pow(1.0 + r, -(double)TERM_MONTHS));

    peter.mortage = true;
    peter.mortgage_debt = LOAN_AMOUNT;
    peter.mortgage_payment = static_cast<RUB>(monthly);
    peter.mortgage_months_left = TERM_MONTHS;
}

void simulation()
{
    int year=2027;
    int month=1;
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
        printf("Год: %d, Месяц: %d | Зарплата: %llu руб. | Повышений: %u\n",
               year, month, peter.salary, peter.number_of_promotions);
        world_tick(&year, &month);
        if (peter.health==0){
            break;
        };
    }
}

int main(){
    peter_init();
    simulation();
}
