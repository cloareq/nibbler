#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include "display.hh"
#include <stdio.h>

t_move  a_mode(t_move &last, const SDL_Event &event)
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

t_move  b_mode(t_move &last, const SDL_Event &event)
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

void  speed(const SDL_Event &event, int &diff)
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

void        Display::drawApple(const t_apple &apple) const
{
  glColor3ub(255, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(apple.pos_x * 25 - 25 / 2, apple.pos_y * 25 - 25 / 2);
  glVertex2f(apple.pos_x * 25 - 25 / 2, apple.pos_y * 25 + 25 / 2);
  glVertex2f(apple.pos_x * 25 + 25 / 2, apple.pos_y * 25 + 25 / 2);
  glVertex2f(apple.pos_x * 25 + 25 / 2, apple.pos_y * 25 - 25 / 2);
  glEnd();
  glFlush();
}

void        Display::drawBody(const int &x, const int &y) const
{
  glBegin(GL_QUADS);
  glColor3ub(9, 242, 9);
  glVertex2f(x * 25 - 25 / 2, y * 25 - 25 / 2);
  glVertex2f(x * 25 - 25 / 2, y * 25 + 25 / 2);
  glColor3ub(0, 75, 0);
  glVertex2f(x * 25 + 25 / 2, y * 25 + 25 / 2);
  glVertex2f(x * 25 + 25 / 2, y * 25 - 25 / 2);
  glEnd();
  glFlush();
}

void        Display::drawHead(const int &x, const int &y) const
{
  glBegin(GL_QUADS);
  glColor3ub(122, 48, 2);
  glVertex2f(x * 25 - 25 / 2, y * 25 - 25 / 2);
  glVertex2f(x * 25 - 25 / 2, y * 25 + 25 / 2);
  glColor3ub(221, 89, 6);
  glVertex2f(x * 25 + 25 / 2, y * 25 + 25 / 2);
  glVertex2f(x * 25 + 25 / 2, y * 25 - 25 / 2);
  glEnd();
  glFlush();
}

void        Display::display_snake(std::list<s_snake> snake, const t_apple &apple)
{
    std::list<s_snake>::iterator it;

    glClearColor(1.0, 0.87 , 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    usleep(20000 * this->_diff);
    this->drawApple(apple);
    for (it = snake.begin(); it != snake.end(); it++)
    {
      if (it == snake.begin()) {
        this->drawHead(it->pos_x, it->pos_y);
      } else {
        this->drawBody(it->pos_x, it->pos_y);
      }
    }
    SDL_GL_SwapBuffers();
}

Display::Display(const int &x, const int &y)
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    exit(0);
  }
  SDL_WM_SetCaption("Snake Opengl", NULL);
  SDL_SetVideoMode(x * 25, y * 25, 32, SDL_OPENGL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-12.5, x * 25 - 12.5, y * 25 - 12.5, -12.5, 0, 1);
  glClearColor(1.0, 0.87, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  this->_diff = 5;
}

extern "C" Display* create(const int &x, const int &y)
  {
    return new Display(x, y);
  }
