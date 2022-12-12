#pragma once

#include <iostream>
#include <vector>

namespace ArgumentParser {

    struct Parameters {               //тип данных, отвечает за хранение параметров
        std::string name;
        std::string value;
        char short_name;
        bool empty;
        std::string* store;
        bool is_int;
        std::vector<int>* store_int;
        std::vector<std::string> values;
        bool is_multi;
        int min_arg;
        bool is_pos;
        std::string inf;
        Parameters() {
            name = "";
            value = "";
            short_name = '\0';
            empty = true;
            store = nullptr;
            is_int = false;
            store_int = nullptr;
            values.resize(0);
            is_multi = false;
            min_arg = 0;
            is_pos = false;
        }
    };

    struct Flags {
        std::string name;
        bool value;
        char short_name;
        bool* store;
        std::string inf;
        Flags() {
            name = "";
            short_name = '\0';
            value = false;
            store = nullptr;
        }
    };

    struct Helper {           //отвечает за вызов хэлп-меню
        std::string name;
        std::string inf;
        char short_name;
        bool is_helper;
        Helper() {
            name = "help";
            inf = "";
            short_name = '\0';
            is_helper = false;
        }
    };

    class ArgParser {
    public:
        ArgParser(std::string name);
        bool Parse(std::vector<std::string> str);
        ArgumentParser::ArgParser& AddStringArgument(std::string param1);
        void Default(bool flag3);
        void Default(const char* value1);
        ArgumentParser::ArgParser& AddStringArgument(char p, std::string param1);
        ArgumentParser::ArgParser& AddStringArgument(char p, std::string param1, std::string inf);
        std::string GetStringValue(std::string param1);
        void StoreValue(std::string& value);
        ArgumentParser::ArgParser& AddIntArgument(std::string param1);
        ArgumentParser::ArgParser& AddIntArgument(char p, std::string param1);
        ArgumentParser::ArgParser& AddIntArgument(std::string inf,std::string param1);
        int GetIntValue(std::string param1);
        int GetIntValue(std::string param1, int x);
        ArgumentParser::ArgParser& MultiValue();
        ArgumentParser::ArgParser& MultiValue(size_t MinArgsCount);
        void StoreValues(std::vector<int>& int_values);
        ArgumentParser::ArgParser& AddFlag(char f, std::string flag1);
        ArgumentParser::ArgParser& AddFlag(char f, std::string flag1, std::string inf);
        bool GetFlag(std::string flag1);
        void StoreValue(bool& store);
        ArgumentParser::ArgParser& Positional();
        bool Help();
        void AddHelp(char h, std::string name, std::string inf);
        std::string HelpDescription();
    private:
        std::vector<Parameters> string;   //вектор параметров; содержит переменные типа параметрс, каждая из которых содержит в себе поля(нэйм, вэлью, шот нэйм)
        std::string parser_name;          //имя парсера
        std::vector<Flags> flag;          //вектор флагов
        Helper help;                      //хэлпер, отвечает за хэлп-меню
    };
}