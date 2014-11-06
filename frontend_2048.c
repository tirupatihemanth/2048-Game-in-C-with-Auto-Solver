#include <stdio.h>
#include <stdlib.h>
#include "backend.h"
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <time.h>
#include "2048_AI.h"

Grid *game_grid;	
GtkWidget *gui_tile[4][4];
GtkWidget *window, *newgamebutton, *autoplaybutton, *hbox, *vbox, *scorelabel;
void terminated_dialogue(Grid *);
void grid_gui_set(Grid *);
void gui_init(int , char **);
void decide_move(char);
void game_play(Grid *);
void newgame_clicked(GtkWidget* , gpointer);
void autoplay_clicked(GtkWidget*, gpointer);

gboolean onkeypress(GtkWidget* , GdkEventKey*, gpointer);

int main(int argc, char *argv[]){

	game_grid = grid_initialise(4, 4);

	gui_init(argc, argv);

	return 0;

}

void close_dialogue(GtkWidget *window, gpointer data){
	GtkWidget *closedialogue = gtk_dialog_new_with_buttons("Exit?",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	GtkWidget *label;
	label = gtk_label_new("Are you sure want to exit the Application?");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(closedialogue)->vbox), label, 0,1,10);
	gtk_widget_show_all(closedialogue);
	gint response = gtk_dialog_run(GTK_DIALOG(closedialogue));
	if(response == GTK_RESPONSE_OK){
		gtk_widget_destroy(closedialogue);
		gtk_widget_destroy(window);
		exit(0);
	}
	else{
		gtk_widget_destroy(closedialogue);
	}
}

void terminated_dialogue(Grid *grid){

	GtkWidget *newgame, *exitbutton, *scorelabel;
	char str[50] = "No more moves. Your score is: ";
	char score[7];
	sprintf(score, "%d",grid->score);
	strcat(str,score);
	scorelabel = gtk_label_new(str);
	//newgame = gtk_button_new_with_label("New Game");
	//exitbutton = gtk_button_new_with_label("Exit");
	GtkWidget *term_dialogue = gtk_dialog_new_with_buttons("You Lose",GTK_WINDOW(window),GTK_DIALOG_MODAL,"New game",1,"Exit",2,NULL);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(term_dialogue)->vbox),scorelabel,0,1,10);
	gtk_widget_show_all(term_dialogue);
	gint response = gtk_dialog_run(GTK_DIALOG(term_dialogue));
	if(response == 1){
		grid_reset(grid);
		grid_gui_set(grid);
		gtk_widget_destroy(term_dialogue);
	}
	else{
		gtk_widget_destroy(term_dialogue);
		close_dialogue(window,NULL);
	}
}


void gui_init(int argc, char **argv){

	gtk_init(&argc,&argv);
	int i,j;
	GdkColor color;
	color.red = 240*65535/255;
	color.green = 128*65535/255;
	color.blue = 128*65535/255;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
	gtk_window_set_title(GTK_WINDOW(window), "2048");
	g_signal_connect(window,"delete-event",G_CALLBACK(close_dialogue),NULL);
	newgamebutton = gtk_button_new_with_label("New Game");
	autoplaybutton = gtk_button_new_with_label("Auto Play");
	scorelabel = gtk_label_new("Score: 0");
	vbox = gtk_vbox_new(TRUE,10);
	hbox = gtk_hbox_new(TRUE,50);
	gtk_box_pack_start(GTK_BOX(hbox),newgamebutton, 0, 1, 5);
	gtk_box_pack_start(GTK_BOX(hbox),autoplaybutton,0, 1, 5);
	gtk_box_pack_start(GTK_BOX(hbox),scorelabel,0,1,5);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, 1, 0, 10);

	for(i=0;i<4;i++){
		hbox = gtk_hbox_new(TRUE,20);
		for(j=0;j<4;j++){
			gui_tile[i][j] = gtk_image_new();
			gtk_box_pack_start(GTK_BOX(hbox),gui_tile[i][j],0,1,5);
		}
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,1,5);
	}
	grid_gui_set(game_grid);


	g_signal_connect(newgamebutton,"clicked",G_CALLBACK(newgame_clicked), NULL);
	g_signal_connect(autoplaybutton,"clicked",G_CALLBACK(autoplay_clicked), NULL);
	g_signal_connect(window,"key_press_event",G_CALLBACK(onkeypress),NULL);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show_all(window);
	gtk_main();

}

void newgame_clicked(GtkWidget *newgamebutton, gpointer data){

	grid_reset(game_grid);
	grid_gui_set(game_grid);
	return;
}

void grid_gui_set(Grid *game_grid){

	int i,j;
	char str[10], score[15] = "Score: ";
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			switch(game_grid->array[i][j]){

				case 0:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_none.png");
					break;

				case 2:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_2.png");
					break;

				case 4:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_4.png");
					break;

				case 8:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_8.png");
					break;

				case 16:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_16.png");
					break;

				case 32:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_32.png");
					break;

				case 64:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_64.png");
					break;

				case 128:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_128.png");
					break;

				case 256:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_256.png");
					break;

				case 512:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_512.png");
					break;

				case 1024:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_1024.png");
					break;

				case 2048:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_2048.png");
					break;

				case 4096:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_4096.png");
					break;

				case 8192:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_8192.png");
					break;																																										
			}
		}
	}
	sprintf(str,"%d",game_grid->score);
	gtk_label_set_text(GTK_LABEL(scorelabel), strcat(score, str));
	return;
	
}


void autoplay_clicked(GtkWidget *autoplaybutton, gpointer data){
	int i,j;
	Bestmove *bestmove;
	while(1){
		bestmove = best_move(game_grid, 5, INT_MIN, INT_MAX, USER);
		//bestmove = best_move(game_grid,5);
		//printf("direction: %d\n",bestmove->direction);
		if(bestmove->direction){
			move_tiles(game_grid, bestmove->direction,1);
			grid_print(game_grid);
			grid_gui_set(game_grid);

			while (gtk_events_pending()){
				gtk_main_iteration();
			}
		}
		else
			break;
	}
}

void decide_move(char var){

	switch(var){

		case 'w':
			move_tiles(game_grid, UP,1);
			break;

		case 's':
			move_tiles(game_grid, DOWN,1);
			break;

		case 'a':
			move_tiles(game_grid, LEFT,1);
			break;

		case 'd':
			move_tiles(game_grid, RIGHT,1);
			break;

	}	
}

gboolean onkeypress(GtkWidget *widget, GdkEventKey *event, gpointer data){
	if(is_terminated(game_grid)){
		terminated_dialogue(game_grid);
		return TRUE;
	}
	decide_move(event->keyval);
	printf("%c\n",event->keyval);
	grid_print(game_grid);
	printf("Score: %d\n",game_grid->score);
	printf("Heuristic Score: %d\n",game_grid->heuristicscore);
	grid_gui_set(game_grid);
	return TRUE;
}
