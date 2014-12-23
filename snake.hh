/*
** snake.hh for  in /home/maigna_j/rendu/nibbler
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  mar. mars  18 21:03:55 2014 Jeremy Maignan
** Last update mar. mars  18 21:03:55 2014 Jeremy Maignan
*/

#ifndef SNAKE_HH_
#define SNAKE_HH_

#include <iostream>
#include <list>

typedef enum e_move
  {
    C_UP,
    C_RIGHT,
    C_DOWN,
    C_LEFT,
  } t_move;

typedef struct 	s_snake
{
  int 		pos_x;
  int	       	pos_y;
  t_move	move;
} t_snake;

typedef struct	s_apple
{
  int		pos_x;
  int		pos_y;
} t_apple;

class Snake
{
private:
  std::list<s_snake> 	_metha;
  s_apple 		_apple;
public:
  Snake(const int &x, const int &y);
  const std::list<s_snake>  	&get_metha() const;
  const t_apple			&get_apple() const;
  void				set_metha(const s_snake &tmp, const int &flag);
  void				init_apple(const int &x, const int &y);
  int				colision(const int &x, const int &y);
  void				check_apple(const int &x, const int &y, const s_snake &tmp);
};

//lib_loading.c
int  check_lib_loading(const void *lib);
int  check_symbol_loading(const char *dlsym_error);
int  load_library(const int &x, const int &y, const std::string lib_name);

//main.c
//int                             loop(int x, int y, IDisplay *Window);

#endif
