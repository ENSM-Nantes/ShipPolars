#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>

#define SIZE_PATH_MAX (256)


void OnOffRotor(GtkButton *aBtn, gpointer aRotInfos);
void ChangeRot(GtkButton *aBtn, gpointer aRotInfos);

#endif
