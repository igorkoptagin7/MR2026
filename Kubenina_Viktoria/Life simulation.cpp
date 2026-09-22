#include <stdio.h>
#include <iostream>

using RUB = unsigned long long int;


struct Person {
	RUB cash;
	RUB salary;

};

//введение нового типа данных

struct Person vika;

void vika_init()
{
	vika.cash = 20'000;
	vika.salary = 80'000;
}



void vika_print()
{
	std::cout << "Vika cash = " << vika.cash << '\n';
}

void vika_salary(const int year, int month)
{
	if (year == 2026 and month == 12) { //promotion
		vika.salary = 120'000;

	}

	vika.cash += vika.salary;
}


void simulation()
{
	int year = 2026;
	int month = 9;
	while (not(year == 2036 and month == 12)) {

		vika_salary(year, month);
		//alice_car();
		//alice_mortgage();
		//alice_cat();
		//alice_rent();
		//alice_tax();
		//alice_bamk_inkome();
		//nalog_vb1chet

		++month;
		if (month == 13) {
			++year;
			month = 1;
		}

	}
}

int main()
{
	vika_init();
	
	simulation();

	vika_print();

}

