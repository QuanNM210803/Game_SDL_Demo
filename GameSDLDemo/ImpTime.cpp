#include "ImpTime.h"


ImpTime::ImpTime(void)
{
  start_tick_ = 0;
  paused_ticks_ = 0;
  is_paused_ = false;
  is_started_ = false;
}


ImpTime::~ImpTime(void)
{

}


void ImpTime::start()
{
  is_started_ = true;
  is_paused_ = false;

  start_tick_ = SDL_GetTicks();
}

void ImpTime::stop()
{
  is_started_ = false;
  is_paused_ = false;
}

void ImpTime::paused()
{
  if (is_started_ == true && is_paused_ == false)
  {
    is_paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_tick_;
  }
}

void ImpTime::unpause()
{
  if (is_paused_ == true)
  {
    is_paused_ = false;
    start_tick_ = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

int ImpTime::get_ticks()
{
  if (is_started_)
  {
    if (is_paused_)
    {
      return paused_ticks_;
    }
    else
    {
      return SDL_GetTicks() - start_tick_;
    }
  }

  return 0;
}
