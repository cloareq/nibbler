#ifndef DISPLAY_HH_
#define DISPLAY_HH_

# include <iostream>
# include <list>

# include "snake.hh"
# include "IDisplay.hh"

class Display : public IDisplay
{
private:
  SDL_Event	event;
  int		_diff;
public:
  Display(const int &x, const int &y);
  ~Display() {}
  void 		 display_snake(std::list<s_snake> snake, const t_apple &apple);
  e_move	 move();
  void		 drawApple(const t_apple &apple) const;
  void		 drawBody(const int &x, const int &y) const;
  void           drawHead(const int &x, const int &y) const;
};

#endif
