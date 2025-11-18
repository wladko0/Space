#pragma once
#include "SDL/SDL.h"

#define DBLCLICK_TIMEWINDOW 800 // ms

namespace dblclick
{
  SDL_Event trigger_event;
  Uint8 numclicks=0;
  SDL_TimerID timerid;
  enum Event { react, reset };

  Uint32 dblclicktimer(Uint32 interval, void *param)
  {
    SDL_Event event2;

    event2.type = SDL_USEREVENT;
    event2.user.code = reset;
    event2.user.data1 = 0;
    event2.user.data2 = 0;
    SDL_PushEvent(&event2);
    return 0;
  }

  void init()
  {
    SDL_InitSubSystem(SDL_INIT_TIMER);
  }

  void check_event(SDL_Event *ev)
  {
    if (ev->type == SDL_MOUSEBUTTONDOWN)
    {
      if (ev->button.button == SDL_BUTTON_LEFT)
      {
        dblclick::numclicks++;
        if (dblclick::numclicks == 2)
        {
          SDL_RemoveTimer(dblclick::timerid);
          dblclick::numclicks = 0;

          trigger_event = *ev;
          SDL_Event event;
          event.type = SDL_USEREVENT;
          event.user.code = dblclick::react;
          event.user.data1 = &trigger_event;
          event.user.data2 = 0;
          SDL_PushEvent(&event);
        }
        else
        {
          dblclick::timerid = SDL_AddTimer(DBLCLICK_TIMEWINDOW, &dblclick::dblclicktimer, NULL);
        }
      }
    }
    else if (ev->type == SDL_USEREVENT)
    {
      if (ev->user.code == dblclick::react)
      {
          //darkcon doesn't care about it...
      }
      else if (ev->user.code == dblclick::reset)
      {
        dblclick::numclicks = 0;
      }
    }
  }

}
