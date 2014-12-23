/*
** IDisplay.hh for  in /home/maigna_j/rendu/nibbler
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  dim. mars  23 19:33:21 2014 Jeremy Maignan
** Last update dim. mars  23 19:33:21 2014 Jeremy Maignan
*/

#ifndef IDISPLAY_HH_
#define IDISPLAY_HH_
	
# include <iostream> 
# include "snake.hh"

class IDisplay
{
public:
	virtual void    display_snake(std::list<s_snake> snake, const t_apple &apple) = 0;
	virtual e_move  move() = 0;
	virtual		~IDisplay() {}
};

typedef IDisplay *create_t(const int &x, const int &y);

#endif
