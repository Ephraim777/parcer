
#include "MyParce.h"

int main()
{
   
    try {
        MyParce object("fols.txt");

        auto temp = object.GetValue<std::string>("Section1.var1");
        std::cout << temp;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}
