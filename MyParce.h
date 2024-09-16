#pragma once
#include <string>
#include <iostream>
#include <fstream>


enum   State{
    SEARCHVAR,
    SEARCHSECTION,
    ERROR,
    FOUND
};

class MyParce
{
public:

    State st = SEARCHSECTION;

	std::ifstream stream;

	MyParce(const std::string &str);

    template<typename T>
    T GetValue(const std::string& find_str) {

        bool SearchSection = false;
        bool SearchVar = false;
        std::string varName = find_str.substr(find_str.find(".") + 1);
        std::string sectionName = find_str.substr(0, find_str.find("."));
        std::string result;

        while (!stream.eof()) {
           
            if (st == State::FOUND) {
                break;
            }
            std::string line;
            std::getline(stream, line);

            if (line.empty())
                continue;

            size_t pos = 0;
            if (st == State::SEARCHSECTION) {
                while (pos < line.size()) {
                    
                    if ((line[pos] == ' ')) {
                        pos++;
                        continue;
                    }

                    if (line[pos] == ';') {
                        break;
                    }

                    if (line[pos] == '[') {
                        pos++;
                        if (sectionName == getSection(line, pos)) {
                            SearchSection = true;
                            st = State::SEARCHVAR;
                            pos++;
                            break;
                        }
                    }
                    pos++;
                }
               
            }
           

            if (st == State::SEARCHVAR) {
                while (pos < line.size()) {
                    if (line[pos] == ' ') {
                        pos++;
                        continue;
                    }

                    if (line[pos] == ';') {
                        break;
                    }

                    if (line[pos] == '[') {
                        st = State::SEARCHSECTION;
                        break;
                    }
                    result = getVariable(line, pos, varName);
                    if (!result.empty()) {
                        break;
                    }
                    
                }
              
            }

        }
         
        return CheckType<T>(result);
    }

    template<typename T>
   T CheckType(std::string & result) {
       if constexpr (std::is_same < T, int>::value) {

           int int_variable = 0;
           size_t index = 0;
           while (index < result.size()) {

               int_variable = int_variable * 10;

               int_variable += result[index] - '0';

               index++;
           }
           return int_variable;
       }
       else if constexpr (std::is_same<T, double>::value) {

           double double_variable = 0;

           bool flag = false;

           int level = 1;

           size_t index = 0;

           while (index < result.size()) {

               if (result[index] == '.') {
                   flag = true;
                   continue;
               }

               if (!flag) {
                   double_variable += result[index] - '0' + double_variable * 10;
               }
               else {
                   double double_temp = result[index] - '0';
                   double_variable += double_temp / (level * 10);
               }

               index++;
           }
           return double_variable;
       }
       else if constexpr (std::is_same<T, std::string>::value) {
           return result;
       }
    }

    std::string getSection(const std::string & str,size_t& pos);

    std::string getVariable(const std::string & str,size_t& pos, const std::string& varName );

    std::string getValue(const std::string & str,size_t& pos);
};

