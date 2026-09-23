#include <iostream>
#include <string>
#include <random>
#include <cstdio>
#include <windows.h>
#include <locale>


//typedef int RUB;
using RUB = unsigned long long int;

enum class LifeStatus {
    SCHOOL,
    COLLEGE,
    UNIVERSITY,
    WORKING
};

enum class EducationLevel {
    NONE,           
    SCHOOL,         
    COLLEGE,        
    UNIVERSITY      
};


struct Car {
    bool has_car = false;
    std::string model = "Отсутствует";
    int health = 100;              
    int age_months = 0;            

    // Финансовые параметры
    RUB purchase_price = 0;
    RUB monthly_cost = 0;          // Страховка + бензин + налоги

    // Стоимость разных типов ремонта
    RUB light_repair_cost = 15000;     
    RUB heavy_repair_cost = 50000;     
    RUB capital_repair_cost = 150000;  
};


struct Person {
    RUB cash = 0;
    RUB salary = 0;

    bool is_well_off_family = false;
    LifeStatus status = LifeStatus::SCHOOL;
    EducationLevel education = EducationLevel::NONE;
    std::string current_activity = "Учится в школе (1 класс)";

    int work_experience_months = 0;

    Car car; 
    Bank bank;

    double oge_average = 0.0;
    int ege_total = 0;
};


struct Mortgage {
    bool is_active = false;
    RUB total_amount = 0;          // Общая сумма ипотеки
    RUB remaining_balance = 0;     // Остаток долга
    double annual_rate = 0.0;      // Годовая ставка
    int term_months = 0;           // Срок в месяцах
    RUB monthly_payment = 0;       // Ежемесячный платеж
    int months_paid = 0;           // Сколько месяцев уже выплачено
};

struct Loan {
    bool is_active = false;
    RUB total_amount = 0;          // Общая сумма кредита
    RUB remaining_balance = 0;     // Остаток долга
    double annual_rate = 0.0;      // Годовая ставка
    int term_months = 0;           // Срок в месяцах
    RUB monthly_payment = 0;       // Ежемесячный платеж
    int months_paid = 0;           // Сколько месяцев уже выплачено
};

struct Bank {
    // Налог
    double tax_rate = 0.13;        // НДФЛ 13%
    RUB tax_paid_total = 0;        // Всего уплачено налогов

    // Стипендия
    RUB scholarship = 0;           // Размер стипендии (0 если не учится)

    // Ипотека
    Mortgage mortgage;

    // Кредит
    Loan loan;

    // Методы для расчётов
    void calculate_mortgage_payment() {
        if (!mortgage.is_active) return;

        // Формула аннуитетного платежа
        double monthly_rate = mortgage.annual_rate / 100.0 / 12.0;
        if (monthly_rate > 0) {
            mortgage.monthly_payment = static_cast<RUB>(
                mortgage.remaining_balance *
                (monthly_rate * pow(1 + monthly_rate, mortgage.term_months)) /
                (pow(1 + monthly_rate, mortgage.term_months) - 1)
                );
        }
        else {
            mortgage.monthly_payment = mortgage.remaining_balance / mortgage.term_months;
        }
    }

    void calculate_loan_payment() {
        if (!loan.is_active) return;

        double monthly_rate = loan.annual_rate / 100.0 / 12.0;
        if (monthly_rate > 0) {
            loan.monthly_payment = static_cast<RUB>(
                loan.remaining_balance *
                (monthly_rate * pow(1 + monthly_rate, loan.term_months)) /
                (pow(1 + monthly_rate, loan.term_months) - 1)
                );
        }
        else {
            loan.monthly_payment = loan.remaining_balance / loan.term_months;
        }
    }
};

struct Person alice;

std::random_device rd;
std::mt19937 gen(rd());

bool check_chance(int chance_percent) {
    std::uniform_int_distribution<> distrib(1, 100);
    return distrib(gen) <= chance_percent;
}

void alice_oge(const int year, const int month) {
    if (year != 2035 || month != 6 || alice.status != LifeStatus::SCHOOL) return;

    std::cout << "\n  [ЭКЗАМЕН] " << year << " год: Элис сдаёт ОГЭ!\n";

    int total_oge_score = 0;
    for (int i = 1; i <= 4; ++i) {
        int chance_good_grade = alice.is_well_off_family ? 70 : 40;
        int grade = 2;

        if (check_chance(chance_good_grade)) {
            grade = check_chance(50) ? 5 : 4;
        }
        else {
            grade = check_chance(60) ? 3 : 2;
        }
        total_oge_score += grade;
    }

    alice.oge_average = static_cast<double>(total_oge_score) / 4.0;
    std::cout << "  Средний балл ОГЭ: " << alice.oge_average << "\n";

    if (alice.oge_average > 3.1) {
        alice.current_activity = "Учится в 10 классе";
        std::cout << "  [РЕШЕНИЕ] Элис проходит в 10 класс!\n";
    }
    else if (alice.oge_average >= 2.5) {
        alice.status = LifeStatus::COLLEGE;
        alice.current_activity = "Учится в колледже";
        std::cout << "  [РЕШЕНИЕ] Элис поступает в колледж.\n";
    }
    else {
        alice.status = LifeStatus::WORKING;
        alice.education = EducationLevel::NONE;  
        alice.current_activity = "Работает (без образования)";
        std::cout << "  [РЕШЕНИЕ] Провал ОГЭ. Элис идет работать.\n";
    }
}

void alice_ege(const int year, const int month) {
    if (year != 2037 || month != 6 || alice.status != LifeStatus::SCHOOL) return;

    std::cout << "\n  [ЭКЗАМЕН] " << year << " год: Элис сдаёт ЕГЭ!\n";

    int total_ege_score = 0;
    for (int i = 1; i <= 3; ++i) {
        int score = alice.is_well_off_family ? (50 + (rand() % 46)) : (30 + (rand() % 56));
        total_ege_score += score;
    }

    alice.ege_total = total_ege_score;
    std::cout << "  Сумма баллов ЕГЭ: " << alice.ege_total << "\n";

    if (alice.ege_total > 170) {
        alice.status = LifeStatus::UNIVERSITY;
        alice.current_activity = "Учится в университете";
        std::cout << "  [РЕШЕНИЕ] Элис поступает в университет!\n";
    }
    else {
        alice.status = LifeStatus::WORKING;
        alice.education = EducationLevel::SCHOOL;  
        alice.current_activity = "Работает (школа)";
        std::cout << "  [РЕШЕНИЕ] Баллов не хватило. Элис идет работать.\n";
    }
}


void alice_college(const int year, const int month) {
    if (alice.status != LifeStatus::COLLEGE) return;

    int college_year = year - 2035;

    if (year == 2038 && month == 6) {
        alice.status = LifeStatus::WORKING;
        alice.education = EducationLevel::COLLEGE;  
        alice.current_activity = "Работает (колледж)";
        std::cout << "\n  [СОБЫТИЕ] " << year << " год: Элис окончила колледж!\n";
    }
}

void alice_university(const int year, const int month) {
    if (alice.status != LifeStatus::UNIVERSITY) return;

    int uni_year = year - 2037;

    if (year == 2041 && month == 6) {
        alice.status = LifeStatus::WORKING;
        alice.education = EducationLevel::UNIVERSITY;  
        alice.current_activity = "Работает (университет)";
        std::cout << "\n  [СОБЫТИЕ] " << year << " год: Элис получила диплом ВУЗа!\n";
    }
}

void alice_education(const int year, const int month) {
    alice_oge(year, month);
    alice_ege(year, month);

    alice_college(year, month);
    alice_university(year, month);
}


void alice_car(const int year, const int month) {

    if (!alice.car.has_car) {
        if (year >= 2038 && alice.cash >= 600000) {
            if (check_chance(15)) {
                // Инициализируем машину при покупке
                alice.car.has_car = true;
                alice.car.model = "Suzuki Swift";
                alice.car.health = 100;
                alice.car.age_months = 0;
                alice.car.purchase_price = 600000;
                alice.car.monthly_cost = 5000;

                alice.cash -= alice.car.purchase_price;

                std::cout << "  [СОБЫТИЕ] Элис купила " << alice.car.model
                    << " за " << alice.car.purchase_price << "\n";
            }
        }
    }
    
    else {
        alice.cash -= alice.car.monthly_cost;

        alice.car.age_months++;

        // Базовый шанс 3%, плюс 1% за каждые 10% износа, плюс 0.5% за каждый год владения
        int wear_factor = (100 - alice.car.health) / 10;
        int age_factor = alice.car.age_months / 12; // полных лет владения
        int breakdown_chance = 3 + wear_factor + age_factor;

        // Ограничим максимум, чтобы машина не ломалась каждый месяц
        breakdown_chance = (std::min)(breakdown_chance, 25);

        if (check_chance(breakdown_chance)) {
            //тип ремонта: лёгкий: 55%, сложный: 30%, капитальный: 15%
            int repair_roll = rand() % 100;

            if (repair_roll < 55) {
                alice.cash -= alice.car.light_repair_cost;
                alice.car.health -= 2;
                std::cout << "  [РЕМОНТ] Лёгкий ремонт " << alice.car.model
                    << " (-" << alice.car.light_repair_cost
                    << "). Состояние: " << alice.car.health << "%" << "\n";
            }
            
            else if (repair_roll < 85) {
                alice.cash -= alice.car.heavy_repair_cost;
                alice.car.health -= 10;
                std::cout << "  [РЕМОНТ] Сложный ремонт " << alice.car.model
                    << " (-" << alice.car.heavy_repair_cost
                    << "). Состояние: " << alice.car.health << "%" << "\n";
            }
            
            else {
                alice.cash -= alice.car.capital_repair_cost;
                alice.car.health -= 25;
                std::cout << "  [РЕМОНТ] КАПИТАЛЬНЫЙ ремонт " << alice.car.model
                    << " (-" << alice.car.capital_repair_cost
                    << "). Состояние: " << alice.car.health << "%" << "\n";
            }

            if (alice.car.health <= 0) {
                std::cout << "  [СОБЫТИЕ] Машина " << alice.car.model
                    << " окончательно сломалась и отправлена на свалку." << "\n";

                alice.car.has_car = false;
                alice.car.model = "Отсутствует";
                alice.car.health = 0;
            }
        }
    }
}

RUB calculate_salary_by_education(EducationLevel edu, int experience_months) {
    RUB base_salary = 0;

    //базовая зарплата в зависимости от образования
    switch (edu) {
    case EducationLevel::NONE:
        base_salary = 25000; 
        break;
    case EducationLevel::SCHOOL:
        base_salary = 35000;  
        break;
    case EducationLevel::COLLEGE:
        base_salary = 55000; 
        break;
    case EducationLevel::UNIVERSITY:
        base_salary = 80000; 
        break;
    }

    //индексация зарплаты с опытом работы
    int years_worked = experience_months / 12;
    double experience_bonus = 1.0 + (years_worked * 0.02);

    return static_cast<RUB>(base_salary * experience_bonus);
}

void alice_salary(const int year, const int month) {
    RUB gross_salary = 0;
    RUB net_salary = 0;

    if (alice.status == LifeStatus::WORKING) {
        alice.salary = calculate_salary_by_education(alice.education, alice.work_experience_months);
        gross_salary = alice.salary;
        alice.work_experience_months++;
    }
    else if (alice.status == LifeStatus::UNIVERSITY) {
        alice.bank.scholarship = 5000;
        alice.cash += alice.bank.scholarship;
        return;
    }
    else if (alice.status == LifeStatus::SCHOOL || alice.status == LifeStatus::COLLEGE) {
        if (alice.is_well_off_family) {
            alice.cash += 3000;
        }
        return;
    }

    // начисление зарплаты с вычетом налога
    if (gross_salary > 0) {
        RUB tax = static_cast<RUB>(gross_salary * alice.bank.tax_rate);
        net_salary = gross_salary - tax;

        alice.cash += net_salary;
        alice.bank.tax_paid_total += tax;

        // Логируем раз в год
        if (month == 1) {
            std::cout << "  [ЗАРПЛАТА] " << year << " год: " << gross_salary
                << " руб. (налог: " << tax << ", на руки: " << net_salary
                << ", опыт: " << alice.work_experience_months / 12 << " лет)\n";
        }
    }
}

void simulation() {
    int year = 2026;
    int month = 9;
    while (not (year == 2060 and month == 1)) {
        alice_education(year, month);
        alice_salary(year, month);
        alice_car(year, month);
        //alice_mortgadge();
        //alice_rent();
        //alice_home_bills();
        //alice_food();
        //alice_dog();
        //alice_bank_income();
        ++month;
        if (month == 13) {
            ++year;
            month = 1;
        }
    }
}



void alice_init() {
    alice.cash = 20000;
    alice.salary = 0;

    alice.is_well_off_family = check_chance(50);

    if (alice.is_well_off_family) {
        std::cout << "[СТАРТ] Элис родилась в благополучной семье. Родители помогают с учебой.\n";
        alice.cash += 50000;
    }
    else {
        std::cout << "[СТАРТ] Элис родилась в обычной семье. Всего придется добиваться самой.\n";
    }
}

void alice_printf() {
    std::cout << "\n--- ИТОГОВОЕ СОСТОЯНИЕ ЭЛИС ---\n";
    std::cout << "Текущий статус:   " << alice.current_activity << "\n";
    std::cout << "Зарплата:         " << alice.salary << " руб./мес.\n";
    std::cout << "Накопления:       " << alice.cash << " руб.\n";

        if (alice.car.has_car) {
            std::cout << "Машина:           " << alice.car.model << "\n";
            std::cout << "  Состояние:      " << alice.car.health << "%\n";
            std::cout << "  Возраст:        " << alice.car.age_months / 12
                << " лет " << alice.car.age_months % 12 << " мес.\n";
        }
        else {
            std::cout << "Машина:           Отсутствует\n";
        }
}

int main()
{
    SetConsoleOutputCP(1251);

    alice_init();
    simulation();
    alice_printf();
}

//разбить образования на отдельные функции,прописать структуру для машины, чтобы там всё было, также сделать для банка, по зарплатам образования тожетуда же, в отдельные, 