#pragma once
#include "Common_Function.h"
class ImpTime
{
public:
  ImpTime(void);
  ~ImpTime(void);

  void start();
  void stop();
  void paused();
  void unpause();
  int get_ticks();
  bool is_paused() const {return is_paused_;};
  bool is_started() const {return is_started_;}

private:
  int start_tick_;
  int paused_ticks_;

  bool is_paused_;
  bool is_started_;
};

