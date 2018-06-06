
#include<allegro5\allegro.h>
#include<allegro5\allegro_native_dialog.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_primitives.h>

#include<iostream>
#include<random>
#include<math.h>
//#include<time.h>


struct  Line
{
	float x1 = 0, y1 = 0;
	float x2 = 0, y2 = 0;
} line[35];//36 is the of lines number 


#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 500
int main(int argc, char* argv[])
{


	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Allegro initial fail !!!", NULL, NULL);
		return -1;
	}


	ALLEGRO_DISPLAY *display;

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	al_set_window_position(display, 300, 150);
	al_set_window_title(display, "hello world");

	if (!display)
	{
		al_show_native_message_box(NULL, NULL, NULL, "Allegro display not found!!!", NULL, NULL);
		exit(-1);
	}

	//For drawing shaps
	al_init_primitives_addon();

	//----------------------For lines


	//initials
	float space = 10, height_diff = 10;
	float top_x1 = 40, top_y1 = 50, bottom_x2 = 40, bottom_y2 = 400;

	line[0].x1 = top_x1; line[0].y1 = top_y1;
	line[0].x2 = bottom_x2; line[0].y2 = bottom_y2;

	int color = 10;
	ALLEGRO_COLOR line_color;

	int size = (sizeof(line) / sizeof(float)) / 4;

	//---------initializing 36 lines 

	for (int i = 0; i < size; i++)
	{
		line[i + 1].x1 = line[i].x1 + space;  line[i + 1].y1 = line[i].y1 + height_diff;
		line[i + 1].x2 = line[i].x2 + space;				line[i + 1].y2 = line[i].y2;
	}

	//randomizeing lines
	srand(time(0));
	int r1, r2;

	Line temp;
	for (int i = 0; i < size; i++)
	{
		r1 = rand() % size;
		r2 = rand() % size;

		temp.y1 = line[r1].y1;
		line[r1].y1 = line[r2].y1;
		line[r2].y1 = temp.y1;

	}


	//printing randomized lines
	for (int i = 0; i < size; i++)
	{

		line_color = al_map_rgba(60, 40, line[i].y1, 50);

		al_draw_line(line[i].x1, line[i].y1, line[i].x2, line[i].y2, line_color, 5);

		al_flip_display();

		al_rest(0.1);
	}
	ALLEGRO_COLOR black = al_map_rgb(1, 1, 1);
	//bubble sorting
	int i, j;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	for (i = 0; i < size; i++)
	{
		// Last i elements are already in place   
		for (j = 0; j < size - i; j++)
		{
			if (line[j].y1 > line[j + 1].y1)
			{
				temp.y1 = line[j + 1].y1;
				line[j + 1].y1 = line[j].y1;
				line[j].y1 = temp.y1;
			}

			al_draw_line(line[j].x1, top_y1, line[j].x2, line[j].y2, black, 5);
			al_draw_line(line[j].x1, line[j].y1, line[j].x2, line[j].y2, line_color, 5);
			al_rest(0.01);
			al_draw_line(line[j+1].x1, top_y1, line[j + 1].x2, line[j + 1].y2, black, 5);
			al_draw_line(line[j + 1].x1, line[j + 1].y1, line[j + 1].x2, line[j + 1].y2, line_color, 5);

			al_flip_display();
		}
		line_color = al_map_rgba(60, 40, line[i].y1, 50);

		al_draw_line(line[i].x1, top_y1, line[i].x2, line[i].y2, black, 5);
		al_draw_line(line[i].x1, line[i].y1, line[i].x2, line[i].y2, line_color, 5);
		
		al_flip_display();
		al_rest(0.2);
	}


	for (i = 0; i < size - 1; i++)
	{
		line_color = al_map_rgba(60, 40, line[i].y1, 50);

		al_draw_line(line[i].x1, top_y1, line[i].x2, line[i].y2, black, 5);
		al_draw_line(line[i].x1, line[i].y1, line[i].x2, line[i].y2, line_color, 5);

		al_flip_display();
		
		al_rest(0.1);
	}

	std::cout<< " The end" <<std::endl;
	al_rest(500);
	//al_destroy_font(font);
	al_destroy_display(display);

	return 0;
}