
#include "MainObject.h"

MainObject::MainObject()
{
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = WIDTH_MAIN_OBJECT;
  rect_.h = HEIGHT_MAIN_OBJECT;
  x_val_ = 0;
  y_val_ = 0;
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
  if (events.type == SDL_KEYDOWN)
  {
    switch (events.key.keysym.sym)
    {
    case SDLK_UP:
      y_val_ -= SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_DOWN:
      y_val_ += SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_RIGHT:
      x_val_ += SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_LEFT:
      x_val_ -= SPEED_MAIN_OBJECT;
      break;;
    default:
      break;
    }
  }
  else if (events.type == SDL_KEYUP)
  {
    switch(events.key.keysym.sym )
    {
      case SDLK_UP: y_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_DOWN: y_val_ -= SPEED_MAIN_OBJECT; break;
      case SDLK_LEFT: x_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_RIGHT: x_val_ -= SPEED_MAIN_OBJECT; break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN)
  {
    BulletObject* p_bullet = new BulletObject();
    if (events.button.button == SDL_BUTTON_LEFT)
    {
      p_bullet->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
      p_bullet->LoadImg(g_name_bullet_main_laser);
      p_bullet->set_type(BulletObject::LASER);
      Mix_PlayChannel(-1, bullet_sound[0], 0);
    }
    else if (events.button.button == SDL_BUTTON_RIGHT)
    {
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
      p_bullet->LoadImg(g_name_bullet_main_fire);
      p_bullet->set_type(BulletObject::SPHERE);
      Mix_PlayChannel(-1, bullet_sound[1], 0);
    }

    p_bullet->SetRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this->rect_.h*0.8);
    p_bullet->set_is_move(true);
    p_bullet->set_x_val(SPEED_BULLET_MAIN);
    p_bullet_list_.push_back(p_bullet);
  }
  else if (events.type == SDL_MOUSEBUTTONUP)
  {

  }
  else
  {
    ;//
  }
}

void MainObject::MakeBullet(SDL_Surface* des)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet_ = p_bullet_list_.at(i);
    if (p_bullet_ != NULL)
    {
      if (p_bullet_->get_is_move())
      {
        p_bullet_->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_bullet_->Show(des);
      }
      else 
      {
        if (p_bullet_ != NULL)
        {
          p_bullet_list_.erase(p_bullet_list_.begin() + i);
          delete p_bullet_;
          p_bullet_ = NULL;
        }
      }
    }
  }
}



//************************************
// Method:    HandleMove
// FullName:  MainObject::HandleMove
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void MainObject::HandleMove()
{
  rect_.x += x_val_;

  if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
  {
    rect_.x -= x_val_;
  }


  rect_.y += y_val_;
  if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200)
  {
    rect_.y -= y_val_;
  }
}

void MainObject::RemoveBullet(const int& idx)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    if (idx < p_bullet_list_.size())
   {
      BulletObject* p_bullet = p_bullet_list_.at(idx);
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);

      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
  }
}