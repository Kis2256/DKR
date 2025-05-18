#include <iostream>
#include "Radiostation.h"

int main() {
    char choice;
    std::cout << "Do you want to encrypt file with cipher? (y/n): ";
    std::cin >> choice;
    std::string mode;
    if (choice == 'y' || choice == 'Y') {   //перевіряємо чи обрано режим із шифруванням
     mode = "ciphers";
    } else {
     mode = "non";
    }
    Logger logger(mode); //створюємо об'єкт класу Logger, передаючи йому наш режим
    RadioList radioList;
    radioList.RadioSearch(logger); //викликаємо метод RadioSearch, передаючи йому logger, щоб у процесі пошуку він міг записувати лог у файл
    return 0;
}
