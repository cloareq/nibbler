/*
** ncurses.cpp for  in /home/maigna_j/rendu/cpp_nibbler/ncurses
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  lun. mars  31 15:42:57 2014 Jeremy Maignan
** Last update lun. mars  31 15:42:57 2014 Jeremy Maignan
*/

#include <unistd.h>

#include "display.hh"

Display::Display(const int &x, const int &y)
{
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  cbreak();
  curs_set(0);
  _x = x + 1;
  _y = y + 1;
  _diff = 6;
  _last_move = C_RIGHT;
}

Display::~Display()
{
  endwin();
}

void    Display::display_snake(std::list<s_snake> snake, const t_apple &apple)
{
  std::list<s_snake>::iterator it;
  int i = 0;
  
  usleep(20000 * this->_diff);
  _win = newwin(_x, _y, 0, 0);
  mvwaddch(_win, apple.pos_y, apple.pos_x, 'a');
  while (i < _x)
    {
      mvwaddch(_win, _y - 1, i, '|');
      mvwaddch(_win, i, _x - 1, '|');
      i++;
    }
  for (it = snake.begin(); it != snake.end(); it++)
    mvwaddch(_win, it->pos_y , it->pos_x, 's');
  wrefresh(_win);
}

e_move			Display::move()
{
  int			ch = getch();

  nodelay(stdscr, TRUE);
  if (ch == KEY_DOWN && this->_last_move != C_UP)
    this->_last_move = C_DOWN;
  else if (ch == KEY_UP && this->_last_move != C_DOWN)
    this->_last_move = C_UP;
  else if (ch == KEY_RIGHT && this->_last_move != C_LEFT)
    this->_last_move = C_RIGHT;
  else if (ch == KEY_LEFT && this->_last_move != C_RIGHT)
    this->_last_move = C_LEFT;
  return (this->_last_move);
}

WINDOW	*Display::getWin()
{
  return (_win);
}

extern "C" Display* create(const int &x, const int &y)
  {
    return (new Display(x, y));
  }
