#include "Logger.h"
#include "Exceptie_Fisier.h"
#include <sstream>

unsigned long int   get_log_count()
{
    std::ifstream file("logfile.txt");
    std::string penultim = "";
    std::string last_line = "";
    std::string line;
    while (std::getline(file, line)) {
        penultim = last_line;
        last_line = line;
    }
    file.close();
    std::istringstream iss(penultim);
    std::string word;
    std::string last_word = "";
    while (iss >> word) {
        last_word = word;
    }
    unsigned long int result{};
    if (!last_word.empty()) 
    {
        last_word.erase(last_word.size() - 1);
        result = std::stoul(last_word);
    }
    return result + 1;
}

Logger&             Logger::get_instance()
{
    if (Logger::instance == nullptr)
        Logger::instance = new Logger;
    return *Logger::instance;
}

void                Logger::destroy_instance()
{
    if (Logger::instance)
        delete Logger::instance;
    Logger::instance = nullptr;
}

void                Logger::log_data(const char* filename, std::string data)
{
    std::ofstream logare(filename, std::ios::app);
    if (!logare.is_open())
        throw Exceptie_Fisier(1);
    if (!log_count)
        logare << "***NOUA INSTANTA DE LOGARE***"; 
    logare << "\nLOGAREA NUMARUL " << log_count++ << ':' << "\n\t" << data << "\t";
    logare.close();
}