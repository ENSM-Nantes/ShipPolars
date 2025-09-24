#include "about.h"

void AbCreateBoxes(GtkWidget **aAbBodyBox, GtkWidget **aAbMainBox, GtkWidget **aAbTitleBox)
{
  /*Box*/
  *aAbMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aAbTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aAbBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
}

void AbSetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("About Polar Manager");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 100);
}


void AbSetBoxes(GtkWidget **aAbBodyBox,GtkWidget **aAbMainBox,GtkWidget **aAbTitleBox,//Boxes
	        GtkWidget **aTitle, GtkWidget **aInfos//Labels
		) 
{
  gtk_box_append(GTK_BOX (*aAbTitleBox), *aTitle);
  
  gtk_box_append(GTK_BOX (*aAbBodyBox), *aInfos);
  
  gtk_box_append(GTK_BOX (*aAbMainBox), *aAbTitleBox);
  gtk_box_append(GTK_BOX (*aAbMainBox), *aAbBodyBox);
}
