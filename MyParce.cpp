#include "MyParce.h"
#include <iterator>
#include <type_traits>
MyParce::MyParce(const std::string &str): stream(str) {

	if (!stream.is_open()) {
        stream.close();
		throw std::logic_error("File is not open, perhaps path is wrong\n");
	}
	else {

		stream.seekg(0, std::ios::end);
		std::streamsize fileSize = stream.tellg();
		stream.seekg(0, std::ios::beg);

		if (fileSize == 0) {
            stream.close();
            throw std::logic_error("File is empty, check please path\n");
		}

		
	}
}

std::string MyParce::getSection(const std::string & str,size_t& pos)
{
    std::string section;
    while(pos < str.size() && str[pos] != ']'){
        section += str[pos];
        pos++;
    }
    
    return section;
}

std::string MyParce::getVariable(const std::string & str,size_t& pos, const std::string& varName ){

    std::string result;
    std::string name;
    while(pos < str.size() && str[pos] != ';'){
        if(str[pos] == ' ')
        {
            pos++;
            continue;
        }
        if(str[pos] == '=')
        {
            if(name == varName){
                st = State::FOUND;
                pos++;
                return getValue(str,pos);
            }else
            {
                pos++;
                break;
            }
        }
        name+= str[pos];
        pos++;
    }
    return result;
}

std::string MyParce::getValue(const std::string & str,size_t& pos){
    std::string result;

    while(pos < str.size() && str[pos] != ';'){
        if(str[pos] == ' ' && result.empty())
        {
            pos++;
            continue;
        }

        result += str[pos];
        pos++;
    }
    if (result.empty()) {
       stream.close();
       throw std::logic_error("Value is empty in file\n");
    }
    return result;
}

