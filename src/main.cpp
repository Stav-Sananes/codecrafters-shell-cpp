#include <iostream>
#include <string>
#include <format>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string command;

  std::cout << "$ ";
  std::cin >> command;
  if (command == "xyz")
  {
    std::string result = std::format("command not found: {}", command);
    std::cout << result << std::endl;
  }
}
