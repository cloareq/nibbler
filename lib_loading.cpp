/*
** main.cpp for  in /home/maigna_j/rendu/nibbler
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  mar. mars  18 19:03:18 2014 Jeremy Maignan
** Last update mar. mars  18 19:03:18 2014 Jeremy Maignan
*/

#include <iostream>
#include <string>
#include <dlfcn.h>

#include "IDisplay.hh"

int                             loop(const int &x, const int &y, IDisplay *Window);

int  check_lib_loading(const void *lib)
{
  if (!lib)
    {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
      return (1);
    }
  return (0);
}

int     check_symbol_loading(const char *dlsym_error)
{
  if (dlsym_error)
    {
      std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
      return (1);
    }
  return(0);
}

int load_library(const int &x, const int &y, const std::string lib_name)
{
  void* lib;

  std::string *tmp  = new std::string("./");
  *tmp = *tmp + lib_name;
  std::cout << *tmp << std::endl;
  lib = dlopen(tmp->c_str(), RTLD_LAZY);
  if ((check_lib_loading(lib)) == 1)
    return (1);
  dlerror();
  create_t* create_display = (create_t*) dlsym(lib, "create");
  const char* dlsym_error = dlerror();
  if ((check_symbol_loading(dlsym_error)) == 1)
    return (1);
  IDisplay* Win = create_display(x, y);
  loop(x, y, Win);
  delete Win;
  dlclose(lib);
  return (0);
}
