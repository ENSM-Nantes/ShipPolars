#ifndef LIST_H
#define LIST_H

#include <gtk/gtk.h>

typedef struct
{
    char* fileName;
    size_t sizeFileName;
    pthread_mutex_t lock;
}sPolarData;


void SelectScenario(GtkDropDown *aListDropDown, GParamSpec *aPrmSpec, gpointer aUserData);

#endif
