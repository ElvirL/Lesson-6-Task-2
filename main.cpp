/*
Задание 2. Реализация программы напоминания о днях рождения
Что нужно сделать
Реализуйте простую программу по вычислению ближайшего дня рождения.
В начале программы пользователь последовательно вводит данные о днях рождения своих друзей: вводит имя друга и саму дату рождения 
полностью, включая месяц и год, в формате год/месяц/день. Сигналом окончания ввода дней рождения является “end” введённое в качестве имени.
После этого программа вычисляет ближайший день рождения по отношению к текущему времени и выводит его на экран вместе с именем в 
удобном, локальном формате - месяц/день. Если день рождения уже был в этом году, данные о пользователе пропускаются. 
Если у кого-то из друзей день рождения сегодня, то в консоль выводится специальное сообщение об этом. Учтите, что таких сообщений 
может быть несколько, ведь сразу несколько людей могут иметь дни рождения в один день.

Советы и рекомендации
Для подсчёта ближайшего дня используйте данные из структуры даты std::tm.
*/

#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>

int main(){
    setlocale(LC_ALL, "Russian");
    std::map<std::string, std::tm> birthday;

    std::string name;
    std::time_t t = std::time(nullptr);
    std::tm date = *std::localtime(&t);

    std::cin >> name;
    if (name != "end")
        std::cin >> std::get_time(&date, "%Y/%m/%d");

    while (name != "end"){
        birthday[name] = date;
        std::cin >> name;
        if (name !="end")
            std::cin >> std::get_time(&date, "%Y/%m/%d");
    }

    std::map<std::string, std::tm> upcoming_birthdays;

    std::tm temp_date = *std::localtime(&t);
    int min_difference_month = 13;
    int min_difference_day = 32;

    for (std::map<std::string, std::tm>::iterator it = birthday.begin(); it!=birthday.end(); ++it){
        if (it->second.tm_mon >= temp_date.tm_mon){
            int difference_month = it->second.tm_mon - temp_date.tm_mon;
            int difference_day = it->second.tm_mday - temp_date.tm_mday;

            if (difference_month == min_difference_month && min_difference_day == difference_day){
                upcoming_birthdays[it->first] = it->second;

            }
            else if (difference_month == min_difference_month && difference_day>=0 && min_difference_day > difference_day){
                upcoming_birthdays.clear();
                upcoming_birthdays[it->first] = it->second;
                min_difference_day = difference_day;
            }
            else if (difference_month < min_difference_month){
                min_difference_month = difference_month;
                min_difference_day = difference_day;
                upcoming_birthdays.clear();
                upcoming_birthdays[it->first] = it->second;
            }
        }
    }

    if (upcoming_birthdays.begin()->second.tm_mon == temp_date.tm_mon && upcoming_birthdays.begin()->second.tm_mday == temp_date.tm_mday){
        std::cout << "Сегодня день рождения: " << std::endl;
    }
    else {
        std::cout << "Ближайший день рождения: " << std::endl; 
    }

    for (std::map<std::string, std::tm>::iterator it = upcoming_birthdays.begin(); it!=upcoming_birthdays.end(); ++it){
            std::cout << it->first << " - " << std::put_time(&it->second, "%m/%d") << std::endl;
    }

}