/*
** display.hh for  in /home/maigna_j/rendu/cpp_nibbler/sdl
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  lun. mars  31 15:41:29 2014 Jeremy Maignan
** Last update lun. mars  31 15:41:29 2014 Jeremy Maignan
*/

#ifndef DISPLAY_HH_
#define DISPLAY_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <iostream>
# include <list>

# include "snake.hh"
# include "IDisplay.hh"

class Display : public IDisplay
{
private:
  SDL_Surface *screen;
  SDL_Surface	*snake_pic;
  SDL_Surface	*apple_pic;
  SDL_Surface	*head_down_pic;
  SDL_Surface	*head_up_pic;
  SDL_Surface	*head_left_pic;
  SDL_Surface	*head_right_pic;
  SDL_Event event;
  int _diff;
public:
  Display(const int &x, const int &y);
  ~Display() {}
  void 		 display_snake(std::list<s_snake> snake, const t_apple &apple);
  e_move       move();
};

//event.cpp
int           FilterEvents(const SDL_Event *event);
t_move  a_mode(t_move &last, const SDL_Event event);
t_move  b_mode(t_move &last, const SDL_Event event);
void  speed(SDL_Event event, int &diff);



#endif
