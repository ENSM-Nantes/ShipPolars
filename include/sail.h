#ifndef SAIL_H
#define SAIL_H

#include <gtk/gtk.h>

void SaCreateBoxes(GtkWidget **aSaBodyBox, GtkWidget **aSaMainBox, GtkWidget **aSaTitleBox);
void SaSetTitle(GtkWidget **aTitle);
void SaSetBoxes(GtkWidget **aSaBodyBox, GtkWidget **aSaMainBox, GtkWidget **aSaTitleBox, GtkWidget **aTitle, void *aAppData); 


#endif
