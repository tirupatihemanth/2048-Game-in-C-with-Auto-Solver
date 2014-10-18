#include <stdio.h>
#include <stdlib.h>
#include "backend.h"
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

Grid *game_grid;

GtkWidget *gui_tile[4][4];

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
	int i,j;
	GtkWidget *window, *newgamebutton, *autoplaybutton, *hbox, *vbox;
//	image1 = gtk_image_new_from_file("/home/hemanth/Downloads/logo.jpg");
//	image2 = gtk_image_new_from_file("/home/hemanth/Downloads/logo.jpg");
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "2048");
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	newgamebutton = gtk_button_new_with_label("New Game");
	autoplaybutton = gtk_button_new_with_label("Auto Play");
	vbox = gtk_vbox_new(TRUE,10);
	hbox = gtk_hbox_new(TRUE,50);
	gtk_box_pack_start(GTK_BOX(hbox),newgamebutton, 0, 1, 5);
	gtk_box_pack_start(GTK_BOX(hbox),autoplaybutton,0, 1, 5);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, 1, 0, 10);

	//table = gtk_table_new(4,4,1);

	// tile[0] = gtk_image_new_from_file("./2048_tiles/tile_none.png");
	// tile[1] = gtk_image_new_from_file("./2048_tiles/tile_2.png");
	// tile[2] = gtk_image_new_from_file("./2048_tiles/tile_4.png");
	// tile[3] = gtk_image_new_from_file("./2048_tiles/tile_8.png");
	// tile[4] = gtk_image_new_from_file("./2048_tiles/tile_16.png");
	// tile[5] = gtk_image_new_from_file("./2048_tiles/tile_32.png");
	// tile[6] = gtk_image_new_from_file("./2048_tiles/tile_64.png");
	// tile[7] = gtk_image_new_from_file("./2048_tiles/tile_128.png");
	// tile[8] = gtk_image_new_from_file("./2048_tiles/tile_256.png");
	// tile[9] = gtk_image_new_from_file("./2048_tiles/tile_512.png");
	// tile[10] = gtk_image_new_from_file("./2048_tiles/tile_1024.png");
	// tile[11] = gtk_image_new_from_file("./2048_tiles/tile_2048.png");
	// tile[12] = gtk_image_new_from_file("./2048_tiles/tile_4096.png");
	// tile[13] = gtk_image_new_from_file("./2048_tiles/tile_8192.png");

	for(i=0;i<4;i++){
		hbox = gtk_hbox_new(TRUE,20);
		for(j=0;j<4;j++){
			gui_tile[i][j] = gtk_image_new();
//			g_signal_connect(gui_tile[i][j],"key_press_event",G_CALLBACK(onkeypress),NULL);
			gtk_box_pack_start(GTK_BOX(hbox),gui_tile[i][j],0,1,5);
		}
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,1,5);
	}
	grid_gui_set(game_grid);

	//gtk_table_attach(GTK_TABLE(table), image1, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	//gtk_table_attach(GTK_TABLE(table), image2, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	//gtk_table_attach(GTK_TABLE(table), image, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	//gtk_table_attach(GTK_TABLE(table), image, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	//gtk_box_pack_start(GTK_BOX(vbox),table,0,0,0);
	// for(i=0;i<4;i++){
	// 	hbox = gtk_hbox_new(0,0);
	// 	for(j=0;j<4;j++){
	// 		tile[i][j] = gtk_entry_new();
	// 		gtk_entry_set_max_length(GTK_ENTRY(tile[i][j]),5);
	// 		//gtk_entry_set_icon_from_gicon(GTK_ENTRY(tile[i][j]),GTK_ENTRY_ICON_PRIMARY,GTK_ICON(image));
	// 		gtk_widget_set_size_request(tile[i][j],75,75);
	// 		gtk_box_pack_start(GTK_BOX(hbox),tile[i][j],0,0,0);
	// 	}
	// 	gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
	// }

//	grid_gui_set(game_grid);

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

	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			switch(game_grid->array[i][j]){
				case 0:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_none.png");
					//gtk_table_attach(GTK_TABLE(table),tile[0],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] =  gtk_image_new_from_file("./2048_tiles/tile_none.png");
					break;
				case 2:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_2.png");
					//gtk_table_attach(GTK_TABLE(table),tile[1],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_2.png");
					break;
				case 4:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_4.png");
					//gtk_table_attach(GTK_TABLE(table),tile[2],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_4.png");
					break;
				case 8:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_8.png");
					//gtk_table_attach(GTK_TABLE(table),tile[3],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_8.png");
					break;
				case 16:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_16.png");
					//gtk_table_attach(GTK_TABLE(table),tile[4],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_16.png");
					break;
				case 32:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_32.png");
					//gtk_table_attach(GTK_TABLE(table),tile[5],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_32.png");
					break;
				case 64:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_64.png");
					//gtk_table_attach(GTK_TABLE(table),tile[6],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_64.png");
					break;
				case 128:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_128.png");
					//gtk_table_attach(GTK_TABLE(table),tile[7],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_128.png");
					break;
				case 256:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_256.png");
					//gtk_table_attach(GTK_TABLE(table),tile[8],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					//gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_256.png");
					break;
				case 512:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_512.png");
					//gtk_table_attach(GTK_TABLE(table),tile[9],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_512.png");
					break;
				case 1024:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_1024.png");
					//gtk_table_attach(GTK_TABLE(table),tile[10],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_1024.png");
					break;
				case 2048:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_2048.png");
					//gtk_table_attach(GTK_TABLE(table),tile[11],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_2048.png");
					break;
				case 4096:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_4096.png");
					//gtk_table_attach(GTK_TABLE(table),tile[12],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_4096.png");
					break;
				case 8192:
					gtk_image_set_from_file(GTK_IMAGE(gui_tile[i][j]),"./2048_tiles/tile_8192.png");
					//gtk_table_attach(GTK_TABLE(table),tile[13],i, i+1, j, j+1,GTK_FILL,GTK_FILL,0,0);
					gui_tile[i][j] = gtk_image_new_from_file("./2048_tiles/tile_8192.png");
					break;																																										
			}
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

gboolean onkeypress(GtkWidget *widget, GdkEventKey *event, gpointer data){
	decide_move(event->keyval);
	printf("%c\n",event->keyval);
	grid_print(game_grid);
	grid_gui_set(game_grid);
	return TRUE;
}