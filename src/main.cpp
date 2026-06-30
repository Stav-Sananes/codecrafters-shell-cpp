#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <filesystem>
std::vector<std::string> tokenize(const std::string &command)
{
  std::vector<std::string> tokens;
  std::istringstream ss(command);
  std::string token;
  while (ss >> token)
  {
    tokens.push_back(token);
  }
  return tokens;
}
void typeCommand(std::string input,
                 const std::array<std::string, 10> &built_in_commands)
{
  bool found = false;
  for (int i = 0; i < built_in_commands.size(); i++)
  {
    if (built_in_commands[i] == input.substr(5))
    {
      found = true;
      std::cout << input.substr(5) << " is a shell builtin" << std::endl;
      break;
    }
  }
  if (found == false)
  {
    std::string path = getenv("PATH");
    std::istringstream ss(path);
    std::string directory;
    while (getline(ss, directory, ':'))
    {
      std::string full_path = directory + "/" + input.substr(5);
      if (!access(full_path.c_str(), X_OK))
      {
        std::cout << input.substr(5) << " is " << full_path << std::endl;
        return;
      }
    }
    std::cout << input.substr(5) << ": not found" << std::endl;
  }
  return;
}
void runExternal(const std::vector<std::string> &tokens)
{
  // execvp wants a null-terminated array of char*
  std::vector<char *> argv;
  for (const auto &t : tokens)
  {
    argv.push_back(const_cast<char *>(t.c_str()));
  }
  argv.push_back(nullptr);

  pid_t pid = fork();
  if (pid == 0)
  {
    execvp(argv[0], argv.data());
    std::cerr << tokens[0] << ": command not found" << std::endl;
    exit(1);
  }
  else if (pid > 0)
  {
    int status;
    waitpid(pid, &status, 0);
  }
  else
  {
    std::cerr << "fork failed" << std::endl;
  }
}
int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::array<std::string, 10> built_in_commands = {"exit", "echo", "type", "pwd", "cd"};
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
      typeCommand(command, built_in_commands);
    }
    else if (command.substr(0, 3) == "pwd")
    {
      std::filesystem::path cwd = std::filesystem::current_path();
      std::cout << cwd << std::endl;
    }
    else if (command.substr(0, 2) == "cd")
    {
      std::filesystem::path new_path = command.substr(3);
      if (!fs::exists(new_path))
      {
        std::cout << "cd: " << new_path << ": No such file or directory" << std::endl;
      } else {
        std::filesystem::current_path(new_path);
      }
    }
    else
    {
      std::vector<std::string> tokens = tokenize(command);
      if (!tokens.empty())
      {
        runExternal(tokens);
      }
    }
  }
}
