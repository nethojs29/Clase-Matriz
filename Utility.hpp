#include <iostream>
#include <limits>

namespace utility {

    void pause(){
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << std::endl << "Press any key to continue...";
	std::cin.get();
	std::cout << std::endl;
    }

};
