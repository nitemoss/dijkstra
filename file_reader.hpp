#include <iostream>
#include <fstream>
#include <string>

void readFile(const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Process each line as needed
            std::cout << line << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main(){
    readFile("vertices.dat");
}