#include <iostream>
#include <string>
#include <filesystem>
#ifdef _WIN32
constexpr char PATH_LIST_SEPARATOR = ';';
#else
constexpr char PATH_LIST_SEPARATOR = ':';
#endif
namespace fs = std::filesystem;
bool has_execute_permission(const fs::path &file_path)
{
  if (!fs::exists(file_path))
  {
    return false;
  }

  fs::perms p = fs::status(file_path).permissions();

  return (p & (fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec)) != fs::perms::none;
}
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
    }
    else if (command.substr(0, 4) == "type")
    {
      if (command.substr(5) == "echo" || command.substr(5) == "exit")
      {
        std::cout << command.substr(5) << " is a shell builtin" << std::endl;
      }
      else if ((command.substr(5) == "grep" || command.substr(5) == "ls" || command.substr(5) == "cat" || command.substr(5) == "cp") && has_execute_permission("/usr/bin/" + command.substr(5)))
      {
        std::cout << command.substr(5) << " is " << "/usr/bin/" << command.substr(5) << std::endl;
      }
      else
      {
        std::cout << command.substr(5) << ": not found" << std::endl;
      }
    }
    else
    {
      std::cout << command << ": command not found" << std::endl;
    }
  }
}
