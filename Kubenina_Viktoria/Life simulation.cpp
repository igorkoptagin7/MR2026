#include <stdio.h>
#include <iostream>

using RUB = unsigned long long int;


struct Person {
	RUB cash;
	RUB salary;
	RUB from_mother;
	RUB food;

};


struct Person vika;


void vika_init()
{
	vika.cash = 0;
	vika.salary = 0;
	vika.from_mother = 25'000;
	vika.food = 15'000;
}



void vika_print()
{
	std::cout << "Vika cash = " << vika.cash << '\n';
}

void vika_salary(const int year, int month)
{
	if (year == 2026 and month == 10) { //find work
		vika.salary = 30'000;

	}

	vika.cash += vika.salary;
}

void vika_from_mother(const int year, int month)
{
	vika.cash += vika.from_mother;
}


void vika_food(const int year, int month)
{
	vika.cash -= vika.food;
}


void simulation()
{
	int year = 2026;
	int month = 9;
	while (not(year == 2026 and month == 11)) {

		vika_salary(year, month);
		vika_from_mother(year, month);
		vika_food(year, month);
		//alice_car();
		//alice_mortgage();
		//alice_cat();
		//alice_rent();
		//alice_tax();
		//alice_bank_inkome();
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

