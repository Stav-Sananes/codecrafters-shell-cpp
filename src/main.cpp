#include <iostream>
#include <string>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string command;

  while (true)
  {
    std::cout << "$ ";
    std::getline(std::cin, command);
    if (command == "exit")
    {
      break;
    }
    else if (command.substr(0, 5) == "echo ")
    {
      std::cout << command.substr(5) << std::endl;
    } else if(command.substr(0, 4) == "type"){
      if(command.substr(5) == "echo" || command.substr(5) == "exit" || command.substr(5) == "type"){
        std::cout << command.substr(5) << ": shell builtin" << std::endl;
      } else {
         std::cout << command << ": not found" << std::endl;
      }
    }
    else
    {
      std::cout << command << ": command not found" << std::endl;
    }
    
  }
}
