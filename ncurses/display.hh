/*
** display.hh for  in /home/maigna_j/rendu/cpp_nibbler/ncurses
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  lun. mars  31 15:42:22 2014 Jeremy Maignan
** Last update lun. mars  31 15:42:22 2014 Jeremy Maignan
*/

#ifndef DISPLAY_HH_
#define DISPLAY_HH_

#include <ncurses.h>
#include "snake.hh"
#include "IDisplay.hh"

class Display : public IDisplay
{
private:
	WINDOW *_win;
	int _x;
	int _y;
	int _diff;
	t_move _last_move;
public:
	Display(const int &x, const int &y);
	~Display();
	void    display_snake(std::list<s_snake> snake, const t_apple &apple);
	e_move move();
	WINDOW	*getWin();
};

#endif
