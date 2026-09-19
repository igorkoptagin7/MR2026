#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() 
{
#ifdef _WIN32
    // Настройка кодировки консоли для Windows
    SetConsoleCP(65001);       // кодировка ввода — UTF-8
    SetConsoleOutputCP(65001); // кодировка вывода — UTF-8
#endif

    setlocale(LC_ALL, "");     // подхватываем локаль системы (нужно для Linux/Mac)

    double salary;
    double extraIncome;
    cout << "Введите вашу зарплату на руки: ";
    cin >> salary;
    cout << "Введите доп. доход (подработки, если нет — 0): ";
    cin >> extraIncome;
    // --- Проверка на партнёра ---
    bool hasPartner;
    double partnerIncome = 0;
    double partnerSpending = 0;
    char answer;
    cout << "У вас есть вторая половинка, с которой вы ведёте общий бюджет? (y/n): ";
    cin >> answer;
    if (answer == 'y') 
    {
        hasPartner = true;
    }
    else 
    {
        hasPartner = false;
    }
    if (hasPartner)
    {
        cout << "Доход второй половинки в общий бюджет: ";
        cin >> partnerIncome;

        cout << "Траты на партнёра (свидания, подарки, сюрпризы) в месяц, в среднем: ";
        cin >> partnerSpending;
    }
    double totalIncome = salary + extraIncome + partnerIncome;
    cout << "\nОбщий доход домохозяйства: " << totalIncome << endl;
    // --- Остальные расходы ---
    double rent;
    double utilities;
    double transport;
    double food;
    cout << "\nТеперь введите расходы:" << endl;
    cout << "Аренда / ипотека в месяц: ";
    cin >> rent;
    cout << "Коммуналка + интернет + связь в месяц: ";
    cin >> utilities;
    cout << "Транспорт (проезд/бензин) в месяц: ";
    cin >> transport;
    cout << "Еда в месяц: ";
    cin >> food;
    double totalExpenses = rent + utilities + transport + food + partnerSpending;
    cout << "\nОбщие расходы: " << totalExpenses << endl;
    // --- Остаток ---
    double remaining = totalIncome - totalExpenses;
    cout << "Остаток после всех расходов: " << remaining << endl;
    // --- Рекомендация по тратам на партнёра ---
    if (hasPartner) 
    {
        double recommendedPartnerSpending = totalIncome * 0.05; // 5% от дохода — ориентир
        cout << "\n--- Совет по тратам на партнёра ---" << endl;
        cout << "Ориентировочная комфортная сумма (5% от дохода): "
            << recommendedPartnerSpending << endl;
        if (remaining < 0)
        {
            // Денег не хватает вообще — расходы больше дохода
            double deficit = -remaining; // переводим в положительное число
            double suggestedSpending = partnerSpending - deficit;
            if (suggestedSpending < 0) 
            {
                suggestedSpending = 0;
            }
            cout << "Внимание: расходы превышают доход на " << deficit << "." << endl;
            cout << "Предлагаем временно снизить траты на партнёра до "
                << suggestedSpending << " в месяц." << endl;
        }
        else if (partnerSpending < recommendedPartnerSpending) 
        {
            // Остаток положительный, и на партнёра тратится меньше нормы
            double roomToGrow = recommendedPartnerSpending - partnerSpending;
            cout << "У вас есть запас в бюджете. Можно увеличить траты на партнёра "
                << "примерно на " << roomToGrow << " (до " << recommendedPartnerSpending
                << " в месяц), не создавая рисков для бюджета." << endl;
        }
        else 
        {
            cout << "Текущие траты на партнёра выглядят сбалансированными — "
                << "менять ничего не нужно." << endl;
        }
    }
    return 0;
}
