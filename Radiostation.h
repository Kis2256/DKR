#ifndef RADIOSTATION_H
#define RADIOSTATION_H
#include <vector>
#include <string>
#include <fstream>

class RadioStation { //основний клас для ініціалізації параметрів радіостанції
private:
    std::string m_RadioName; //назва радіостанції
    double m_MinRange; // мінімальне значення діапазону
    double m_MaxRange; // максимальне значення діапазону
    int m_Radius; //радіус дії станцій
    public:
    RadioStation();
    RadioStation(std::string RadioName, double MinRange,  double MaxRange,  int Radius);
//---------------сеттери-----------------------
    void setRadioName(const std::string& name);    //для додаткової можливості задання параметрів вручну
    void setMinRange(double min);
    void setMaxRange(double max);
    void setRadius(int radius);
//---------------геттери-----------------------
    std::string getRadioName() const  { return m_RadioName; }
    double getMinRange() const  { return m_MinRange; }
    double getMaxRange() const  { return m_MaxRange; }
    int getRadius() const  { return m_Radius; }

    std::string toString() const; //метод, який повертає рядок із описом радіостанції

    friend std::ostream& operator<<(std::ostream& os, const RadioStation& station); //зовнішня функція, яка використовується для +
};                                                                                  //+виводу об’єкта класу у потік і має доступ до значень private

class Logger{ //клас для логування подій у текстовий файл (із можливим шифруванням)
private:
    std::ofstream m_LogFile;
    std::string m_Mode;
public:
    Logger(const std::string& mode = "non", const std::string& filename = "RADIOSTATION_DATA.txt"); // Конструктор щоб відкрити файл для запису логів і встановити режим.
    ~Logger();
    void log(const std::string& message); //основний метод для запису повідомлень у лог
};

class RadioList {  //клас, де задається список вже реальних радіостанцій та всі їхні реальні параметри
public:
    std::vector<RadioStation> Radiostations = {   // контейнер, який зберігає список об'єктів типу RadioStation
        RadioStation("HitFm", 96.3, 96.5, 1800),
        RadioStation("NRJ", 98.3, 98.5, 800),
        RadioStation("Radio Bayraktar", 98.4, 98.6, 40),
        RadioStation("LuxFM", 103, 103.2, 500),
        RadioStation("Roks", 103.5, 103.7, 2000),
        RadioStation("PowerFM", 103.9, 104.1, 150),
        RadioStation("PeretsFM", 105.4, 105.6, 10),
        RadioStation("KissFM", 106.4, 106.6, 1000),
        RadioStation("Avtoradio", 107.3, 107.5, 300),
};
    void RadioSearch(Logger& logger);  //метод для знаходження підходящої станції та її відстані
};

#endif //RADIOSTATION_H
