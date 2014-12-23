/*
** sdl.c for  in /home/maigna_j/rendu/nibbler
**
** Made by Jeremy Maignan
** Login   <maigna_j@epitech.net>
**
** Started on  mar. mars  18 20:25:39 2014 Jeremy Maignan
** Last update mar. mars  18 20:25:39 2014 Jeremy Maignan
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

t_move        Display::move()
{
  SDL_EnableKeyRepeat(10, 10);
  SDL_PollEvent(&event);
  static t_move last = C_RIGHT;
  static int mode = 0;

  if (event.type == SDL_QUIT)
    exit(0);
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_m)
      (mode == 0) ? (mode = 1) : (mode = 0);
    if (event.key.keysym.sym == SDLK_KP_MINUS || event.key.keysym.sym == SDLK_KP_PLUS)
      speed(event, this->_diff);
    (mode == 0) ? (last = a_mode(last, event)) : (last = b_mode(last, event)); 
    event.type = 0;
  }
 return (last);
}

void        Display::display_snake(std::list<s_snake> snake, const t_apple &apple)
{
   std::list<s_snake>::iterator it;
   std::list<s_snake>::iterator it2;
   SDL_Rect pos;
   SDL_Rect pos_apple;

   usleep(20000 * this->_diff);
   SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 255, 255, 255));
   pos_apple.x = apple.pos_x * 25;
   pos_apple.y = apple.pos_y * 25;
   SDL_BlitSurface(this->apple_pic, NULL, this->screen, &pos_apple);
   for (it = snake.begin(); it != snake.end(); it++)
   {
    pos.x = it->pos_x * 25;
    pos.y = it->pos_y * 25;
    if (it == snake.begin())
    {
      if (it->move == C_DOWN)
        SDL_BlitSurface(this->head_down_pic, NULL, this->screen, &pos);
      else if (it->move == C_UP)
        SDL_BlitSurface(this->head_up_pic, NULL, this->screen, &pos);
      else if (it->move == C_LEFT)
        SDL_BlitSurface(this->head_left_pic, NULL, this->screen, &pos);
      else if (it->move == C_RIGHT)
        SDL_BlitSurface(this->head_right_pic, NULL, this->screen, &pos);
    }
    else
      SDL_BlitSurface(this->snake_pic, NULL, this->screen, &pos);
  }
  SDL_Flip(this->screen);
}

Display::Display(const int &x, const int &y)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("icon.jpg"), NULL);
 
    this->screen = SDL_SetVideoMode(x * 25, y * 25, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("SNAKE", NULL);
    this->snake_pic = IMG_Load("sdl/rsrc/body.bmp");
    this->apple_pic = IMG_Load("sdl/rsrc/apple.bmp");
    this->head_down_pic = IMG_Load("sdl/rsrc/head_down.bmp");
    this->head_up_pic = IMG_Load("sdl/rsrc/head_up.bmp");
    this->head_left_pic = IMG_Load("sdl/rsrc/head_left.bmp");
    this->head_right_pic = IMG_Load("sdl/rsrc/head_right.bmp");
    SDL_SetEventFilter(FilterEvents);
    this->_diff = 5;
    std::cout << "Press [M] to change the game mode" << std::endl;
    std::cout << "Press [-] or [+] to change the speed of the snake" << std::endl;
}

extern "C" Display* create(const int &x, const int &y)
  {
    return new Display(x, y);
  }
