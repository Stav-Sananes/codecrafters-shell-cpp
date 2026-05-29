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
    } else if(command.substr(0, 4) == "echo"){
      std::cout << command.substr(5) << std::endl;
      continue;
    } else{
      std::cout << command << ": command not found" << std::endl;
    }
  }
}
