#include <stdio.h>
#include <stdlib.h>
#include "backend.h"
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

Grid *game_grid;

GtkWidget *tile[4][4];
void grid_gui_set(Grid *);
void gui_init(int , char **);
void decide_move(char);
void game_play(Grid *);
void newgame_clicked(GtkWidget* , gpointer);
void autoplay_clicked(GtkWidget*, gpointer);
gboolean onkeypress(GtkWidget* , GdkEventKey*, gpointer);

int main(int argc, char *argv[]){

	game_grid = grid_initialise(4, 4);

	// grid_delete(game_grid);
	gui_init(argc, argv);
	//game_play(game_grid);
	return 0;

}


void gui_init(int argc, char **argv){

	gtk_init(&argc,&argv);
	int i,j,k;
	GtkWidget *window, *newgamebutton, *autoplaybutton, *hbox, *vbox;
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	newgamebutton = gtk_button_new_with_label("New Game");
	autoplaybutton = gtk_button_new_with_label("Auto Play");
	vbox = gtk_vbox_new(0,0);
	hbox = gtk_hbox_new(0,0);
	gtk_box_pack_start(GTK_BOX(hbox),newgamebutton,0,0,0);
	gtk_box_pack_start(GTK_BOX(hbox),autoplaybutton,0,0,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
	for(i=0;i<4;i++){
		hbox = gtk_hbox_new(0,0);
		for(j=0;j<4;j++){
			tile[i][j] = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(tile[i][j]),5);
			gtk_widget_set_size_request(tile[i][j],75,75);
			gtk_box_pack_start(GTK_BOX(hbox),tile[i][j],0,0,0);
		}
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
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

void autoplay_clicked(GtkWidget *autoplaybutton, gpointer data){

	return;
}

void grid_gui_set(Grid *game_grid){

	int i,j,k;
	char entry[5];
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			k = get_tile(game_grid,i,j);
			sprintf(entry,"%d",k);
			gtk_entry_set_text(GTK_ENTRY(tile[i][j]),entry);
		}
	}
	return;

}

void decide_move(char var){

	switch(var){

		case 'w':
			move_tiles(game_grid, UP);
			break;

		case 's':
			move_tiles(game_grid, DOWN);
			break;

		case 'a':
			move_tiles(game_grid, LEFT);
			break;

		case 'd':
			move_tiles(game_grid, RIGHT);
			break;

	}	
}

void game_play(Grid *game_grid){

	char var;
	grid_print(game_grid);
	while(1){
		fflush(stdin);
		var = getchar();
		if(var == 'q')
			break;
		else if(var == 'r')
			grid_reset(game_grid);
		else
			decide_move(var);
		grid_print(game_grid);
		grid_gui_set(game_grid);
	}

}

gboolean onkeypress(GtkWidget *widget, GdkEventKey *event, gpointer data){
	decide_move(event->keyval);
	grid_gui_set(game_grid);
}