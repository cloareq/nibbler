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
#include <sstream>
#include <string>
#include <unistd.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <dlfcn.h>
#include <GL/glut.h>

#include "snake.hh"
#include "IDisplay.hh"

Snake::Snake(const int &x, const int &y)
{
  int 	       	i;
  s_snake	tmp;
  
  i = 0;
  while (i < 4)
    {
      tmp.pos_x = x / 2 + i;
      tmp.pos_y = y / 2;
      tmp.move = C_RIGHT;
      this->_metha.push_front(tmp);
      i++;
    }
}

void		Snake::init_apple(const int &x, const int &y)
{
  std::list<s_snake>::iterator it;
  
  this->_apple.pos_x = rand() % x;
  this->_apple.pos_y = rand() % y;
  for(it = this->_metha.begin(); it != this->_metha.end(); ++it)
    {
      if (it->pos_x == this->_apple.pos_x &&
	  it->pos_y == this->_apple.pos_y)
	this->init_apple(x, y);
    }
}

const std::list<s_snake>  	&Snake::get_metha() const
{
	return (this->_metha);
}

const t_apple  		&Snake::get_apple() const
{
  return (this->_apple);
}

void				Snake::set_metha(const s_snake &tmp, const int &flag)
{
  this->_metha.push_front(tmp);
  if (flag == 1)
    this->_metha.pop_back();
}

int	       		Snake::colision(const int &x, const int &y)
{
  std::list<s_snake>::iterator it;
  
  if (this->_metha.front().pos_x < 0 || this->_metha.front().pos_y < 0 ||
      this->_metha.front().pos_x >= x || this->_metha.front().pos_y >= y )
    return (-1);
  for(it = this->_metha.begin(); it != this->_metha.end(); ++it)
    {
      if (it != this->_metha.begin() &&
	  this->_metha.front().pos_x == it->pos_x &&
	  this->_metha.front().pos_y == it->pos_y)	
	return (-1);
    }
  return (0);
}

void		       	Snake::check_apple(const int &x, const int &y, const s_snake &tmp)
{
  if (this->get_metha().front().pos_x == this->get_apple().pos_x &&
      this->get_metha().front().pos_y == this->get_apple().pos_y)
    {
      this->init_apple(x, y);
      this->set_metha(tmp, 0);
    }
  else
    this->set_metha(tmp, 1);
}

int		       	loop(const int &x, const int &y, IDisplay *Window)
{
  Snake			Python(x, y);
  s_snake		tmp;
  
  Python.init_apple(x, y);
  while ("You don't loose")
    {
      tmp.move = Window->move();
      tmp.pos_x = Python.get_metha().front().pos_x;
      tmp.pos_y = Python.get_metha().front().pos_y;
      if (tmp.move == C_LEFT)
        tmp.pos_x--;
      else if (tmp.move == C_RIGHT)
        tmp.pos_x++;
      else if (tmp.move == C_UP)
        tmp.pos_y--;
      else if (tmp.move == C_DOWN)
        tmp.pos_y++;	
      if (Python.colision(x, y) == -1)
      {
        std::cout << "score : " << Python.get_metha().size() - 4 << std::endl;
        return (-1);
      }
      Python.check_apple(x, y, tmp);
      Window->display_snake(Python.get_metha(), Python.get_apple());
    }
}

int check_param(const int &x, const int &y, const std::string &lib)
{
  if (x < 10 || x > 70)
    {
      std::cerr << "Error size x must be between 10 and 40" << std::endl;
      return (1);
    }
  else if (y < 10 || y > 40)
    {
      std::cerr << "Error size y must be between 10 and 40" << std::endl;
      return (1);
    }
  else if (lib != "lib_nibbler_sdl.so" && lib != "lib_nibbler_opengl.so" && lib != "lib_nibbler_ncurses.so")
    {
      std::cerr << "Error param 3 must be:\nlib_nibbler_sdl.so\nlib_nibbler_opengl.so\nlib_nibbler_ncurses.so" << std::endl;
      return (1);
    }
  return (0);
}

int				main(int ac, char **av)
{
  int			size_x;
  int			size_y;
  
  if (ac != 4)
    {
      std::cerr << "Usage: nibbler size x, size y, graphic librairy" << std::endl;
      return (1);
    }
  std::istringstream buffer(av[1]);
  buffer >> size_x;
  std::istringstream buffer2(av[2]);
  buffer2 >> size_y;
  if ((check_param(size_x, size_y, av[3])) == 1)
    return (1);
  srand (time(NULL));
  load_library(size_x, size_y, av[3]);
  return (0);
}
