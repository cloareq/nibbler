/*
** event.cpp for  in /home/maigna_j/rendu/cpp_nibbler/sdl
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  jeu. avril  03 10:33:52 2014 Jeremy Maignan
** Last update jeu. avril  03 10:33:52 2014 Jeremy Maignan
*/

# include <stdlib.h>
# include <stdio.h>
# include <iostream>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <list>
 #include <unistd.h>

# include "snake.hh"
# include "display.hh"

extern int DIFF;

int           FilterEvents(const SDL_Event *event)
{
  if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
    return (1);
  return (0);
}

t_move  a_mode(t_move &last, const SDL_Event event)
  {
    if (event.key.keysym.sym == SDLK_RIGHT)
    {
     if (last == C_UP)
       last = C_RIGHT;
     else if (last == C_RIGHT)
       last = C_DOWN;
     else if (last == C_DOWN)
       last = C_LEFT;
     else if (last == C_LEFT)
      last = C_UP;
    }
  else if (event.key.keysym.sym == SDLK_LEFT)
    {
     if (last == C_RIGHT)
       last = C_UP;
     else if (last == C_DOWN)
       last = C_RIGHT;
     else if (last == C_LEFT)
       last = C_DOWN;
     else if (last == C_UP)
       last = C_LEFT;
    }
    return (last);
  }       

t_move  b_mode(t_move &last, const SDL_Event event)
  {
    if (event.key.keysym.sym == SDLK_UP && last != C_DOWN)
      last = C_UP;
    else if (event.key.keysym.sym == SDLK_DOWN && last != C_UP)
      last = C_DOWN;
    else if (event.key.keysym.sym == SDLK_LEFT && last != C_RIGHT)
      last = C_LEFT;
    else if (event.key.keysym.sym == SDLK_RIGHT && last != C_LEFT)
      last = C_RIGHT;
    return (last);
  }

void  speed(SDL_Event event, int &diff)
  {
  if (event.key.keysym.sym == SDLK_KP_MINUS)
   diff++;
  else if (event.key.keysym.sym == SDLK_KP_PLUS)
   diff--;
  if (diff > 10)
    diff = 10;
  if (diff == 0)
    diff = 1;
  std::cout << "Diff : " << (10 - diff) << "/10" << std::endl;
  }