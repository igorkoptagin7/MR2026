#include <stdio.h>
#include <random>
#include <cmath>

using RUB = unsigned long long int;
using YEARS = unsigned int;

FILE* log_file = NULL;

// ================== СТРУКТУРЫ ==================

struct Person{
    RUB cash;
    RUB salary;
    YEARS age;
    unsigned int number_of_promotions;
    double health;
    int childs;
    bool car;
    bool wife;
    bool mortage;
    bool dismission;

    unsigned int mental;              // ментальное состояние, 0..100
    RUB month_income;                 // сколько заработал за этот месяц
    RUB month_mortgage_payment;       // сколько ушло на ипотеку за этот месяц
    RUB month_expenses;               // прочие расходы за месяц
    bool month_promotion;             // было ли повышение в этом месяце
    bool month_dismissed;             // уволили ли в этом месяце
    bool month_disease;               // болел ли в этом месяце
    bool month_mortgage_paid_off;     // закрыл ли ипотеку в этом месяце

    // счётчики болезней
    int count_cold;            // простуда
    int count_angina;          // ангина
    int count_broken_bone;     // перелом
    int count_heart_attack;    // сердечный приступ

    // что случилось в этом месяце (для лога)
    const char* month_disease_name;   // название болезни
    double month_disease_damage;      // урон здоровью

    // причина последнего урона (для смерти)
    const char* last_damage_source;   // "старости", "простуды", ...
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

// ================== ПРОТОТИПЫ ФУНКЦИЙ ==================

void peter_init();
void peter_reset_month_stats();
void mortage_init();
void time_init();
void peter_mortage();
void peter_salary();
void world_tick();
void peter_promotion_at_work();
void peter_dismissial_from_work();
void peter_damage(double amount, const char* source);
void peter_disease_cold();
void peter_disease_angina();
void peter_disease_broken_bone();
void peter_disease_heart_attack();
void peter_disease();
const char* month_name(unsigned int m);
void log_finance();
void log_health();
void log_age();
void log_mental();
void log_month_header();
void log_month_report();
void simulation();

// ================== ИНИЦИАЛИЗАЦИЯ ==================

void peter_init()
{
    peter.age = 21;
    peter.cash = 0;
    peter.salary = 40000;
    peter.health = 60.0;
    peter.number_of_promotions = 0;
    peter.dismission = false;

    peter.mental = 100;
    peter.month_income = 0;
    peter.month_mortgage_payment = 0;
    peter.month_expenses = 0;
    peter.month_promotion = false;
    peter.month_dismissed = false;
    peter.month_disease = false;
    peter.month_mortgage_paid_off = false;

    peter.count_cold = 0;
    peter.count_angina = 0;
    peter.count_broken_bone = 0;
    peter.count_heart_attack = 0;

    peter.month_disease_name = "";
    peter.month_disease_damage = 0.0;

    peter.last_damage_source = "старость";
}


void peter_reset_month_stats()
{
    peter.month_income = 0;
    peter.month_mortgage_payment = 0;
    peter.month_expenses = 0;
    peter.month_promotion = false;
    peter.month_dismissed = false;
    peter.month_disease = false;
    peter.month_mortgage_paid_off = false;
    peter.month_disease_name = "";
    peter.month_disease_damage = 0.0;
    // last_damage_source НЕ сбрасываем — он хранит последнюю причину урона
}


void mortage_init()
{
    mortage.debt = 6500000;
    mortage.down_payment = 2500000;
    mortage.principal_amount = mortage.debt - mortage.down_payment;

    // месячная ставка
    mortage.interest_rate = 0.155 / 12;
    mortage.month = 12 * 10;

    RUB K = mortage.principal_amount;
    double r = mortage.interest_rate;
    double t = std::pow(1.0 + r, mortage.month);
    mortage.payment = static_cast<RUB>((K) * (r * t) / (t - 1));
}


void time_init()
{
    time.year = 2027;
    time.month = 1;
}


void world_tick()
{
    if (time.month == 12){
        ++(time.year);
        time.month = 1;
        peter.age += 1;
    }
    else{
        ++(time.month);
    }

    if (peter.health <= 0.0) return;   // уже мертвы — не трогаем здоровье и причину

    peter.health -= 1.0 / 12.0;
    if (peter.health < 0.0) peter.health = 0.0;

    if (peter.health <= 0.0){
        peter.last_damage_source = "старость";
    }
}

// Сделать флаг и плату даже когда нет зарплаты
void peter_mortage()
{
    if (((time.year >= 2029 and time.month >= 1) or peter.cash >= mortage.down_payment)
     and peter.month_income > mortage.payment + 30000 and mortage.principal_amount > 0){

        if (mortage.principal_amount < peter.cash * 0.8){
            peter.cash -= mortage.principal_amount;
            peter.month_mortgage_payment += mortage.principal_amount;
            mortage.principal_amount = 0;
            peter.month_mortgage_paid_off = true;
        }
        else{
            mortage.principal_amount -= mortage.payment;
            peter.cash -= mortage.payment;
            peter.month_mortgage_payment += mortage.payment;
        }
    }
}

// ================== РАБОТА ==================


void peter_salary()
{
    if (peter.dismission){
        peter.salary = 0;
    }
    else{
        unsigned int x=peter.number_of_promotions;
        double salary_thousands =
            (-1.0/3.0) * std::pow(x, 5)
          + (25.0/12.0) * std::pow(x, 4)
          + (25.0/6.0)  * std::pow(x, 3)
          - (385.0/12.0)* std::pow(x, 2)
          + (397.0/6.0) * x
          + 40.0;
        peter.salary = static_cast<RUB>(salary_thousands * 1000);
    }
}


void peter_promotion_at_work() 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 12*60);
    for (int i = 1; i <= 100; i++){
        if (dist(gen) == 1 and peter.number_of_promotions<5){
            peter.number_of_promotions++;
            peter.month_promotion = true;
            peter_salary();
            break;
        }
    }
}


void peter_dismissial_from_work()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 12*60);
    if (dist(gen) == 1){
        peter.dismission = true;
        peter.month_dismissed = true;
    }
}


void peter_find_work()
{
    if (peter.dismission==true){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 3);
        if (dist(gen) == 1){
            peter.dismission = false;
            peter.month_dismissed = false;
        }
    }
}

// ================== БОЛЕЗНИ ==================

void peter_damage(double amount, const char* source)
{
    peter.health = peter.health - amount;

    if (peter.health < 0.0){
        peter.health = 0.0;
    }

    peter.last_damage_source = source;
}


void peter_disease_cold()
{
    // 20 раз за жизнь
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 36);

    if (dist(gen) == 1){
        peter.count_cold = peter.count_cold + 1;

        peter.month_disease = true;
        peter.month_disease_name = "простуда";
        peter.month_disease_damage = 0.1;

        peter_damage(peter.month_disease_damage, "простуда");
    }
}


void peter_disease_angina()
{
    // раз в жизнь
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 720);

    if (dist(gen) == 1){
        peter.count_angina = peter.count_angina + 1;

        peter.month_disease = true;
        peter.month_disease_name = "ангина";
        peter.month_disease_damage = 0.5;

        peter_damage(peter.month_disease_damage, "ангина");
    }
}


void peter_disease_broken_bone()
{
    // раз в 2 жизни
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1440);

    if (dist(gen) == 1){
        peter.count_broken_bone = peter.count_broken_bone + 1;

        peter.month_disease = true;
        peter.month_disease_name = "перелом кости";
        peter.month_disease_damage = 0.3;

        peter_damage(peter.month_disease_damage, "перелом кости");
    }
}


void peter_disease_heart_attack()
{
    // раз в 10 жизней
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 7200);

    if (dist(gen) == 1){
        peter.count_heart_attack = peter.count_heart_attack + 1;

        peter.month_disease = true;
        peter.month_disease_name = "сердечный приступ";
        peter.month_disease_damage = 999.9;

        peter_damage(peter.month_disease_damage, "сердечный приступ");
    }
}


void peter_disease()
{
    if (peter.health <= 0.0) return;
    peter_disease_cold();

    if (peter.health <= 0.0) return;
    peter_disease_angina();

    if (peter.health <= 0.0) return;
    peter_disease_broken_bone();

    if (peter.health <= 0.0) return;
    peter_disease_heart_attack();
}

// ================== ТЕКСТОВЫЙ ФАЙЛ ==================

const char* month_name(unsigned int m)
{
    switch (m){
        case 1:  return "январь";
        case 2:  return "февраль";
        case 3:  return "март";
        case 4:  return "апрель";
        case 5:  return "май";
        case 6:  return "июнь";
        case 7:  return "июль";
        case 8:  return "август";
        case 9:  return "сентябрь";
        case 10: return "октябрь";
        case 11: return "ноябрь";
        case 12: return "декабрь";
    }
    return "";
}


void log_finance()
{
    fprintf(log_file, "-Финансы\n");

    if (peter.month_income > 0){
        fprintf(log_file, "  зп: +%llu\n", peter.month_income);
    }
    else{
        fprintf(log_file, "  зп: 0 (безработный)\n");
    }

    if (peter.month_mortgage_payment > 0){
        fprintf(log_file, "  списание по ипотеке: -%llu\n",
                peter.month_mortgage_payment);
    }

    if (peter.month_mortgage_paid_off){
        fprintf(log_file, "  !!! ипотека полностью погашена !!!\n");
    }

    fprintf(log_file, "  наличные: %llu\n", peter.cash);

    if (mortage.principal_amount > 0){
        fprintf(log_file, "  остаток ипотеки: %llu\n", mortage.principal_amount);
    }
}


void log_health()
{
    fprintf(log_file, "-Здоровье\n");
    fprintf(log_file, "  показатель: %.2f\n", peter.health);

    if (peter.month_disease){
        fprintf(log_file, "  болезнь: %s (урон %.1f)\n",
                peter.month_disease_name,
                peter.month_disease_damage);
    }
    fprintf(log_file, "  простуд за жизнь:    %d\n", peter.count_cold);
    fprintf(log_file, "  ангин за жизнь:      %d\n", peter.count_angina);
    fprintf(log_file, "  переломов за жизнь:  %d\n", peter.count_broken_bone);
    fprintf(log_file, "  инфарктов за жизнь:  %d\n", peter.count_heart_attack);
}


void log_age()
{
    fprintf(log_file, "-Возраст\n");
    fprintf(log_file, "  %u лет\n", peter.age);

    if (peter.month_promotion){
        fprintf(log_file, "  повышение на работе (всего: %u)\n",
                peter.number_of_promotions);
    }

    if (peter.month_dismissed){
        fprintf(log_file, "  уволен с работы\n");
    }
}


void log_mental()
{
    fprintf(log_file, "-Ментальное состояние\n");
    fprintf(log_file, "  %u / 100\n", peter.mental);

    if (peter.mental >= 80){
        fprintf(log_file, "  состояние: отличное\n");
    }
    else if (peter.mental >= 60){
        fprintf(log_file, "  состояние: хорошее\n");
    }
    else if (peter.mental >= 40){
        fprintf(log_file, "  состояние: нормальное\n");
    }
    else if (peter.mental >= 20){
        fprintf(log_file, "  состояние: плохое\n");
    }
    else{
        fprintf(log_file, "  состояние: критическое\n");
    }
}


void log_month_header()
{
    fprintf(log_file, "\n");
    fprintf(log_file, "================= %s %u ===================\n",
            month_name(time.month), time.year);
}


void log_month_report()
{
    log_month_header();
    log_finance();
    log_health();
    log_age();
    log_mental();
}

// ================== СИМУЛЯЦИЯ ==================

void simulation()
{
    do {

        peter_reset_month_stats();

        peter_salary();
        peter.cash += peter.salary;
        peter.month_income += peter.salary;

        peter_dismissial_from_work();
        peter_promotion_at_work();
        peter_find_work();

        peter_disease();

        peter_mortage();

        log_month_report();

        world_tick();
    } while (peter.health > 0.0);


    fprintf(log_file, "\n");
    fprintf(log_file, "===========================================\n");
    fprintf(log_file, "                 СМЕРТЬ\n");
    fprintf(log_file, "===========================================\n");
    fprintf(log_file, "  причина:  %s\n", peter.last_damage_source);
    fprintf(log_file, "  возраст:  %u лет\n", peter.age);

}

int main()
{
    log_file = fopen("statistics.txt", "w");
    if (log_file == NULL){
        printf("Не удалось открыть файл для записи\n");
        return 1;
    }

    peter_init();
    mortage_init();
    time_init();
    simulation();

    fclose(log_file);
    log_file = NULL;

    return 0;
}