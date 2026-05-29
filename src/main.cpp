#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string command;
  
  while(true){
    std::cout << "$ ";
    std::cin >> command;
    if(command == "exit"){
      break;
    }
    if(command == "echo"){
      std::cout << "\n";
      std::string message;
      std::getline(std::cin, message);
      std::cout << message << std::endl;
      continue;
    } else{
      std::cout << command << ": command not found" << std::endl;
    }
  }
}
