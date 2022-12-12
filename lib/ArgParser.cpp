#include "ArgParser.h"

#include <iostream>
#include <vector>
#include <string>

using namespace ArgumentParser;

ArgumentParser::ArgParser::ArgParser(std::string name) {      //конструктор аргпарсера, принимает имя - т.е задает имя нашему парсеру
    parser_name = name;
    flag.resize(0);
    string.resize(0);
}

bool ArgumentParser::ArgParser::Parse(std::vector<std::string> str) {
    for (int i = 0; i < string.size(); i++) {
        if (string[i].is_pos == true) {                //смотрим есть ли у нас позишионал-элементы
            for (int j = 1; j < str.size(); j++) {
                string[i].values.push_back(str[j]);
                string[i].empty = false;
                if (string[i].store_int != nullptr) {
                    string[i].store_int->push_back(std::stoi(str[j]));
                }
            }
            break;
        }
    }

    for (int i = 0; i < str.size(); i++) {              //рассматриваем случаи когда подается с большим именем,когда с коротким
        if (str[i][0] == '-' && str[i][1] == '-') {        //проходимся по вектору параметров и записываем нужное значение в нужный параметр
            str[i].erase(0, 2);
            std::string buffer = str[i].substr(0, str[i].find('='));
            str[i].erase(0, str[i].find('=') + 1);
            std::string buffer_1 = str[i];
            if (help.is_helper == true && buffer == help.name) {
                std::string buf = HelpDescription();
                std::cout << buf;
                return true;
            }
            for (int j = 0; j < string.size(); j++) {
                if (string[j].name == buffer) {
                    if (string[j].is_multi == false) {
                        string[j].value = buffer_1;
                        string[j].empty = false;
                        if (string[j].store != nullptr) {
                            *string[j].store = buffer_1;
                        }
                    } else {
                        string[j].values.push_back(buffer_1);
                        string[j].empty = false;
                        if (string[j].store_int != nullptr) {
                            string[j].store_int->push_back(std::stoi(buffer_1));
                        }
                    }
                }
            }
            for (int j = 0; j < flag.size(); j++) {
                if (flag[j].name == buffer) {
                    flag[j].value = true;
                    if (flag[j].store != nullptr) {
                        *flag[j].store = true;
                    }
                }
            }
        } else if (str[i][0] == '-' && str[i][1] != '-') {
            str[i].erase(0, 1);
            if (help.is_helper == true && str[i][0] == help.short_name) {
                std::string buf = HelpDescription();
                std::cout << buf;
                return true;
            }
            if (str[i].find('=') == std::string::npos) {
                for (int j = 0; j <= str[i].size(); j++) {
                    for (int k = 0; k < flag.size(); k++) {
                        if (flag[k].short_name == str[i][j]) {
                            flag[k].value = true;
                            if (flag[k].store != nullptr) {
                                *flag[k].store = true;
                            }
                        }
                    }
                }
            } else {
                char buffer = str[i][0];
                str[i].erase(0, str[i].find('=') + 1);
                std::string buffer_1 = str[i];
                for (int j = 0; j < string.size(); j++) {
                    if (string[j].short_name == buffer) {
                        if (string[j].is_multi == false) {
                            string[j].value = buffer_1;
                            string[j].empty = false;
                            if (string[j].store != nullptr) {
                                *string[j].store = buffer_1;
                            }
                        } else {
                            string[j].values.push_back(buffer_1);
                            string[j].empty = false;
                            if (string[j].store_int != nullptr) {
                                string[j].store_int->push_back(std::stoi(buffer_1));
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < string.size(); i++) {      //проверка все ли заполнили
        if (string[i].empty == true) {
            return false;
        }
    }

    for (int i = 0; i < string.size(); i++) {
        if (string[i].values.size() < string[i].min_arg) {
            return false;
        }
    }

    return true;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddStringArgument(std::string param1) {   //функция добавления стрингового аргумента
    Parameters k;
    k.name = param1;
    string.push_back(k);

    return *this;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddStringArgument(char p, std::string param1) {
    Parameters k;
    k.short_name = p;
    k.name = param1;
    string.push_back(k);

    return *this;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddStringArgument(char p, std::string param1, std::string inf) {
    Parameters k;
    k.short_name = p;
    k.inf = inf;
    k.name = param1;
    string.push_back(k);

    return *this;
}

void ArgumentParser::ArgParser::Default(bool flag3) {     //базовое значение при создании переменной  //функция для флагов
    flag[flag.size() - 1].value = flag3;
}

void ArgumentParser::ArgParser::Default(const char* value1) {    //функция для аргументов
    string[string.size() - 1].value = value1;
    string[string.size() - 1].empty = false;
}

std::string ArgumentParser::ArgParser::GetStringValue(std::string param1) {   //получение значения по имени введенного параметра
    for (int i = 0; i < string.size(); i++) {
        if (string[i].name == param1) {
            return string[i].value;
        }
    }
}

void ArgumentParser::ArgParser::StoreValue(std::string& value) {   //внешняя переменная, в которой надо хранить значение
    string[string.size() - 1].store = &value;
}

void ArgumentParser::ArgParser::StoreValue(bool& store) {
    flag[flag.size() - 1].store = &store;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddIntArgument(std::string param1) {
    Parameters k;
    k.name = param1;
    k.is_int = true;
    string.push_back(k);

    return *this;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddIntArgument(char p, std::string param1) {
    Parameters k;
    k.short_name = p;
    k.name = param1;
    k.is_int = true;
    string.push_back(k);

    return *this;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddIntArgument(std::string inf,std::string param1) {
    Parameters k;
    k.name = param1;
    k.inf = inf;
    k.is_int = true;
    string.push_back(k);

    return *this;
}

int ArgumentParser::ArgParser::GetIntValue(std::string param1) {
    for (int i = 0; i < string.size(); i++) {
        if (string[i].name == param1) {
            return std::stoi(string[i].value);
        }
    }
}

int ArgumentParser::ArgParser::GetIntValue(std::string param1, int x) {
    for (int i = 0; i < string.size(); i++) {
        if (string[i].name == param1) {
            return std::stoi(string[i].values[x]);
        }
    }
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::MultiValue() {    //задает мин количество значений которые должны быть в массиве
    string[string.size() - 1].is_multi = true;
    return *this;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::MultiValue(size_t MinArgsCount) {
    string[string.size() - 1].is_multi = true;
    string[string.size() - 1].min_arg = MinArgsCount;
    return *this;
}

void ArgumentParser::ArgParser::StoreValues(std::vector<int>& int_values) {   //хранение значения во внешнем векторе
    string[string.size() - 1].store_int = &int_values;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddFlag(char f, std::string flag1) {   //добавление флагов
    Flags k;
    k.short_name = f;
    k.name = flag1;
    flag.push_back(k);

    return *this;
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddFlag(char f, std::string flag1, std::string inf) {
    Flags k;
    k.short_name = f;
    k.name = flag1;
    k.inf = inf;
    flag.push_back(k);

    return *this;
}

bool ArgumentParser::ArgParser::GetFlag(std::string flag1) {     //получение значения флагов
    for (int i = 0; i < flag.size(); i++) {
        if (flag[i].name == flag1) {
            return flag[i].value;
        }
    }
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::Positional() {  //если введен позиционный аргумент, то поданы все значения которые нам надо туда записать
    string[string.size() - 1].is_pos = true;
    return *this;
}



bool ArgumentParser::ArgParser::Help() {
    return help.is_helper;
}

std::string ArgumentParser::ArgParser::HelpDescription() {      //выводит описание программы
    std::string str;
    str = str + parser_name + "\n";
    str = str + help.name + " " + help.short_name + " " + help.inf + "\n";
    for (int i = 0; i < string.size(); i++) {
        str = str + string[i].name + " " + string[i].short_name + " " + string[i].inf + "\0";
    }
    for (int i = 0; i < flag.size(); i++) {
        str = str + flag[i].name + " " + flag[i].short_name + " " + flag[i].inf + "\0";
    }
    return str;
}

void ArgParser::AddHelp(char h, std::string name, std::string inf) {    //добавляет описание для хэлп-меню
    help.is_helper = true;
    help.name = name;
    help.inf = inf;
    help.short_name = h;
}
