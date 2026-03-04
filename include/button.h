#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>
#include "pi.h"

#define SIZE_PATH_MAX (256)
#define SIZE_CMD_MAX (SIZE_PATH_MAX)
#define PREFIX_SEL_FILE ("\tSelected file : \t")


void OpenShiplify(void);
void BrowsePolar(GtkButton *aBtn, sBrowseData *aData);
void SendPolar(GtkButton *aBtn, sSendData *aData);
void RemovePolar(void);
void OnOffRotor(void *aAppData);
void ChangeRot(void *aAppData);

#endif
