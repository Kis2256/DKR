#include "Radiostation.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <ostream>

RadioStation::RadioStation() : m_RadioName(""), m_MinRange(0), m_MaxRange(0), m_Radius(0) {} // додатковий конструктор за замовчуванням

RadioStation::RadioStation(std::string RadioName, double MinRange, double MaxRange, int Radius) //основний конструктор з параметрами
: m_RadioName(RadioName), m_MinRange(MinRange), m_MaxRange(MaxRange), m_Radius(Radius) {}

void RadioStation::setRadioName(const std::string& name) { m_RadioName = name; }  //можливість редагувати параметри напряму
void RadioStation::setMinRange(double min) { m_MinRange = min; }
void RadioStation::setMaxRange(double max) { m_MaxRange = max; }
void RadioStation::setRadius(int radius) { m_Radius = radius; }

std::string RadioStation::toString() const {         //метод, який повертає рядок з текстовим описом об'єкта радіостанції
    std::ostringstream oss; //output string stream ( потік, який дозволяє записувати дані у рядок )
    oss << m_RadioName
        << " | Frequency: " << m_MinRange << " - " << m_MaxRange << "(MHz)"
        << " | Radius: " << m_Radius << "m";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const RadioStation& station) {  // дозволяє виводити об'єкти класу RadioStation так,
    os << station.toString();                                              // ніби вони звичайні змінні, напряму через std::cout або запис у файл.
    return os;
}

std::string cipher (const std::string& text, char key = 0xFF) { // функція XOR шифрування
    std::string result = text;  // копія оригінального тексту
    for (size_t i = 0; i < result.size(); ++i) { //перебирає кожен елемент тексту
        result[i] = result[i] ^ key; //кожен символ зашифровується XOR операцією з ключем
    }
    return result; //повертає зашифрований рядок
}

Logger::Logger(const std::string& mode, const std::string& filename) : m_Mode(mode) { //конструктор для ініціалізації об’єкта
    m_LogFile.open(filename, std::ios::out | std::ios::trunc); // відкриває файл і задопомогою std::ios::out відкриває файл для виведення тексту та після завершення+
    if (m_LogFile.is_open()) {     //перевіряє чи файл відкрився  | //+ std::ios::trunc стирає запис минулого файла
        std::string startMessage = "-----Log started-----";
        if (m_Mode == "ciphers") {    //перевірка чи увімкнене шифрування
            m_LogFile << cipher(startMessage) << std::endl;
        } else {
            m_LogFile << startMessage << std::endl;
        }
    }
}

Logger::~Logger() {  //деструктор для завершення логу
    if (m_LogFile.is_open()) {
        std::string endMessage = "-----Log ended-----";
        if (m_Mode == "ciphers") {
            m_LogFile << cipher(endMessage) << std::endl;
        } else {
            m_LogFile << endMessage << std::endl;
        }
        m_LogFile.close(); //закриває файл
    }
}

void Logger::log(const std::string& message) {   //виконує логування повідомлень у файл, з урахуванням чи увімкнене шифрування
    if (m_LogFile.is_open()) {
        if (m_Mode == "ciphers") {
            m_LogFile << cipher(message) << std::endl;
        } else {
            m_LogFile << message << std::endl;
        }
    }
}

void RadioList::RadioSearch(Logger& logger){   //метод для знаходження підходящої станції та її відстані
    double UserValueMin;
    double UserValueMax;
    std::cout << "Write the min range of your radio station:" << std::endl;
    std::cin >> UserValueMin;
    std::cout << "Write the max range of your radio station:" << std::endl;
    std::cin >> UserValueMax;
        logger.log("Search started: User range [" + std::to_string(UserValueMin) + " - " + std::to_string(UserValueMax) + "]"); // У файл записується повідомлення,+
    std::sort(Radiostations.begin(), Radiostations.end(),      //відсортовує станції по дистанції                               //+ яке повідомляє, що почався пошук,+
             [](const RadioStation& near, const RadioStation& far){                                                             //+ із зазначеним діапазоном частот
                 return near.getRadius() < far.getRadius() ;  //від найблищої до найдальшої
             });
    int found = 0; //прапорець дял перевірки чи знайдено станції за вказаним діапазоном
    for (const RadioStation& station : Radiostations) {    //ітерації по контейнеру Radiostations
        if (station.getMaxRange() >= UserValueMin && station.getMinRange() <= UserValueMax){
            std::cout <<station<< std::endl;
            found = 1;
            logger.log("Found station: " + station.toString());
        }
        }
    if (found == 0) {
        std::cout << "No radio stations found on this frequency"<<std::endl;
        logger.log("No stations found for the selected range");
    }
};
