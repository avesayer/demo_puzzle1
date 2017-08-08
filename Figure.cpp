#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "Figure.h"
// #include "Game_Data.h"

#define PI 3.14159265
#define round(x) ((x)>=0?(float)((x)+0.5):(float)((x)-0.5))

Figure::Figure(Figure_Form form, Figure_Type type){
     int size = default_block_size;
     printf("Figure()\n");
     int index         = 0;
     int row_block     = 0;
     int column_block  = 0;
     float delta_x     = 0;
     float delta_y     = 0;
     fig_type = type;
     float center_offset = 0.5f;
     std::vector<std::vector<int>> matrix(2);
     for (int i = 0; i < 2; i++) { matrix[i].resize(4); }

     switch(form){
	  case I_figure:{
	       matrix = { {1, 1, 1, 1}, {0, 0, 0, 0} };
	       row_block = 4;
	       column_block = 1;
	  } break;
	  case O_figure:{
	       matrix = { { 1, 1 }, { 1, 1 } };
	       row_block = 2;
	       column_block = 2;
	  }break;
	  case Z_figure:{
	       matrix = { {1, 1, 0}, {0, 1, 1} };
	       row_block = 3;
	       column_block = 2;
	  }break;
	  case S_figure:{
	       matrix = { {0, 1, 1}, {1, 1, 0} };
	       row_block = 3;
	       column_block = 2;
	  }break;
	  case T_figure:{
	       matrix = { {0, 1, 0}, {1, 1, 1} };
	       center_offset = 0.75f;
	       row_block = 3;
	       column_block = 2;
	  }break;
	  case L_figure:{
	       matrix = { {0, 0, 1},{1, 1, 1} };
	       center_offset = 0.75f;
	       row_block = 3;
	       column_block = 2;
	  }break;
	  case J_figure:{
	       matrix = { {1, 0, 0}, {1, 1, 1} };
	       center_offset = 0.75f;
	       row_block = 3;
	       column_block = 2;
	  }break;
     }

     load_figure(form, type);
	  
     sprite_area.x = 0;
     sprite_area.y = 0;
     sprite_area.w = row_block*size;
     sprite_area.h = column_block*size;

     center.x = sprite_area.x + (sprite_area.w >> 1);
     center.y = sprite_area.y + (((float)sprite_area.h) * center_offset);
     rel_center.x = center.x;
     rel_center.y = center.y;
     
     for (int i = 0; i < 2; i++) {
	  for (int j = 0; j < 4; j++) {
	       if(matrix[i][j] == 1){
		    // determining the point location
		    point[index].x = sprite_area.x + (j * size) + (size >> 1);
		    point[index].y = sprite_area.y + (i * size) + (size >> 1);
		    // def_point[index].x = point[index].x;
		    // def_point[index].y = point[index].y;
		    
		    //calculating angle offset
		    delta_x = center.x - point[index].x;
		    delta_y = center.y - point[index].y; 
		    angle_offset[index] = atan2(delta_y,delta_x)*180.0/PI;
		    
		    index++;
	       }
	  }
     }
}

void Figure::set_default(int x, int y){

     SDL_Rect area = get_area();

     int shift_x = x - area.x;
     int shift_y = y - area.y;
     move_figure(shift_x, shift_y);
     for (int i(0); i < 4; i++) {
	  def_point[i].x = point[i].x;
	  def_point[i].y = point[i].y;
	  def_center = center;
     }
     def_angle = angle;
}

Figure::~Figure(){
     printf("~Figure()\n");
     SDL_DestroyTexture(sprite);
}

void Figure::transparent_on(){
     SDL_SetTextureAlphaMod(sprite, 200);
}

void Figure::transparent_off(){
     SDL_SetTextureAlphaMod(sprite, 255);
}

void Figure::load_figure(Figure_Form form, Figure_Type type){
     switch(form){
	  case I_figure:{
	       switch(type){
		    case classic:
			 load_figure_image("..\\data\\sprites\\i_d.png");
			 break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\i_m.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\i_s.png");
			 break;
	       }
	  } break;
	  case O_figure:{
	       switch(type){
		    case classic:
			 load_figure_image("..\\data\\sprites\\o_d.png");
			 break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\o_m.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\o_s.png");
			 break;
	       }
	  }break;
	  case Z_figure:{
	       switch(type){
		    case classic:
			 load_figure_image("..\\data\\sprites\\z_d.png");
			 break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\z_m.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\z_s.png");
			 break;
	       }
	  }break;
	  case S_figure:{
	       switch(type){
		    case classic:
			 load_figure_image("..\\data\\sprites\\s_d.png");
			 break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\s_m.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\s_s.png");
			 break;
	       }

	  }break;
	  case T_figure:{
	       switch(type){
		    case classic:
			 load_figure_image("..\\data\\sprites\\t_d.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\t_s.png");
			 break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\t_m.png");
			 break;
	       }
	  }break;
	  case L_figure:{
	       switch(type){
		    case classic:
			 load_figure_image("..\\data\\sprites\\l_d.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\l_s.png");
			 break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\l_m.png");
			 break;
	       }
	  }break;
	  case J_figure:{
	       switch(type){
		    case classic:{
			 load_figure_image("..\\data\\sprites\\j_d.png");
		    } break;
		    case mirror:
			 load_figure_image("..\\data\\sprites\\j_m.png");
			 break;
		    case stone:
			 load_figure_image("..\\data\\sprites\\j_s.png");
			 break;
	       }
	  }break;
     }
}

void Figure::load_figure_image(const char *path){
     SDL_Renderer *RenderScreen = Window_Info::get_renderer();
     SDL_Surface* tmp_surface;
     SDL_Texture* tmp_texture;
     
     if(sprite)
	  SDL_DestroyTexture(sprite);

     tmp_surface = IMG_Load(path);
     if(tmp_surface){
	  tmp_texture = SDL_CreateTextureFromSurface(RenderScreen, tmp_surface);
	  if(tmp_texture){
	       sprite = tmp_texture;
	       SDL_FreeSurface(tmp_surface);
	  }
	  else{
	       SDL_FreeSurface(tmp_surface);
	       printf("failed to load a texture from the surface! %s\n", SDL_GetError());
	       return;
	  }
     }
     else{
	  printf("failed to load a picture with a given path! - %s\n", IMG_GetError());
	  return;
     }
}

void Figure::set_to(int x, int y){

     int shift_x = x - center.x;
     int shift_y = y - center.y;

     move_figure(shift_x, shift_y);
}

void Figure::move_figure(float shift_x, float shift_y){
     int offset_x = sprite_area.x - center.x;
     int offset_y = sprite_area.y - center.y;
     
     center.x = center.x + shift_x;
     center.y = center.y + shift_y;
     
     sprite_area.x = center.x + offset_x;
     sprite_area.y = center.y + offset_y;
     
     for (int i = 0; i < 4; i++) {
	  point[i].x += shift_x;
	  point[i].y += shift_y;
     }
}

void Figure::set_default_state(){
     if(!idle){
	  if(angle != def_angle){
	       int angle_dt = def_angle - angle;
	       rotate_shell(angle_dt);
	       angle   = def_angle;

	  }
	  int size = default_block_size - active_block_size;

	  SDL_Point old_cntr = {center.x, center.y};
	  scale_image(size);
	  int shift_x = old_cntr.x - center.x;
	  int shift_y = old_cntr.y - center.y;
	  move_figure(shift_x, shift_y);
     }
}

void Figure::set_idle(){
     idle = true;
     stick = false;
}

void Figure::mouse_attach(bool attach){
     // check if it was grabbed already
     if(attach){
	  SDL_ShowCursor(SDL_DISABLE);
	  if(idle){
	       int size = active_block_size - default_block_size;
	       scale_image(size);
	       int shift_x = def_center.x - center.x;
	       int shift_y = def_center.y - center.y;

	       move_figure(shift_x, shift_y);
	       idle = false;
	  }
     }// else if it wasn't 
     else{
	  SDL_ShowCursor(SDL_ENABLE);
     }
}

void Figure::scale_image(int scale_dx){
     int size = get_size();
     float old_width = sprite_area.w;
     float old_height = sprite_area.h;
     int row_block = sprite_area.w/(size);
     int column_block = sprite_area.h/(size);
     
     size += scale_dx;
     sprite_area.w = row_block*(size);
     sprite_area.h = column_block*(size);

     float w_ratio = (center.x - sprite_area.x) / old_width;
     float h_ratio = (center.y - sprite_area.y) / old_height;

     float new_point_x = round((w_ratio * sprite_area.w) + sprite_area.x);
     float new_point_y = round((h_ratio * sprite_area.h) + sprite_area.y);
     
     center.x = new_point_x;
     center.y = new_point_y;

     // calculating new point
     for (int i = 0; i < 4; i++) {
	  w_ratio = (point[i].x - sprite_area.x) / old_width;
	  h_ratio = (point[i].y - sprite_area.y) / old_height;
	  
	  new_point_x = round((w_ratio * sprite_area.w) + sprite_area.x);
	  new_point_y = round((h_ratio * sprite_area.h) + sprite_area.y);
	  
	  point[i].x = new_point_x;
	  point[i].y = new_point_y;
     }
}

SDL_Rect Figure::get_area(){
     SDL_Rect rect = {point[0].x, point[0].y,
		      -500, -500};
     for (int i = 0; i < 4; i++) {
	  if(rect.x >= point[i].x){
	       rect.x = point[i].x;
	       if(idle) rect.x -= default_block_size >> 1;
	       else     rect.x -= active_block_size >> 1;
	  }
	  if(rect.y >= point[i].y){
	       rect.y = point[i].y;
	       if(idle) rect.y -= default_block_size >> 1;
	       else     rect.y -= active_block_size >> 1;
	  }
	  if(rect.w <= point[i].x){
	       rect.w = point[i].x;
	       if(idle) rect.w += (default_block_size >> 1);
	       else     rect.w += (active_block_size >> 1);
	  }
	  if(rect.h <= point[i].y){
	       rect.h = point[i].y;
	       if(idle) rect.h += (default_block_size >> 1);
	       else     rect.h += (active_block_size >> 1);
	  }
     }
     rect.w -= rect.x;
     rect.h -= rect.y;
     
     return rect;
}


bool Figure::is_idle()             { return idle; }
bool Figure::is_sticked()          { return stick; }
bool Figure::is_flip(){ return (flip == SDL_FLIP_VERTICAL) ? true : false; }

SDL_Point Figure::get_center()     {  return center; }
SDL_Point Figure::get_def_center() {  return def_center; }
void Figure::grid_stick()          {  stick = !stick ? 1 : 0; }

SDL_Point* Figure::get_shell(){ SDL_Point* points = point; return points; }
SDL_Point* Figure::get_def_shell() { SDL_Point* def_points = def_point; return def_points;}

int Figure::get_width()       { return sprite_area.w; }
int Figure::get_height()      { return sprite_area.h; }
int Figure::get_size()        { return idle ? default_block_size : active_block_size; }

Figure_Type Figure::get_type(){ return fig_type; }


void Figure::flip_figure(){
     if(flip == SDL_FLIP_NONE)
	  flip = SDL_FLIP_VERTICAL;
     else
	  flip = SDL_FLIP_NONE;

     SDL_Rect area = get_area();

     for (int i = 0; i < 4; i++) {
	  SDL_Point new_point = {0, point[i].y};
	  new_point.x = (area.x + area.w) - (point[i].x - area.x);
	  point[i].x = new_point.x;
     }

     rel_center.x = center.x;
     int old_x = center.x;
     SDL_Point new_cntr = {0, center.y};
     new_cntr.x = (area.x + area.w) - (center.x - area.x);
     center.x = new_cntr.x;
     move_figure(old_x - new_cntr.x, 0);

     rel_center.x = new_cntr.x - rel_center.x;
}
void Figure::rotate_shell(float angle_dx){
     int delta_x = 0;
     int delta_y = 0;
     
     // setting the rotation configure
     // if(angle_dx < 0) angle_dx = -angle_dx;
     
     // simply rounding procedure
     if((int)angle % 360 == 0) { angle = 0; }

     // rotating the skeleton
     for (int i = 0; i < 4; i++) {
	  // calculating radius
	  float delta_x = (center.x - point[i].x)*(center.x - point[i].x);
	  float delta_y = (center.y - point[i].y)*(center.y - point[i].y);
	  float new_radius = sqrt(delta_x + delta_y);

	  //calculating angle offset
	  delta_x = center.x - point[i].x;
	  delta_y = center.y - point[i].y; 
	  point[i].x = round((center.x + cos((angle+angle_dx+180.0+angle_offset[i])*PI/180.0) * new_radius));
	  point[i].y = round((center.y + sin((angle+angle_dx+180.0+angle_offset[i])*PI/180.0) * new_radius));
     }
}

void Figure::update_angle(float angle_dt){ angle += angle_dt; }

void Figure::draw(){
     SDL_Renderer *RenderScreen = Window_Info::get_renderer();

     SDL_Point ff_center;
     ff_center.y = center.y - sprite_area.y;
     if(flip == SDL_FLIP_NONE)
     	  ff_center.x = center.x - sprite_area.x;
     else
	  ff_center.x = (center.x - rel_center.x) - sprite_area.x;

     SDL_RenderCopyEx(RenderScreen, sprite, 0, &sprite_area, angle, &ff_center, flip);
}
