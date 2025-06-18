#ifndef BUTTON_H
#define BUTTON_H

#include <gtk/gtk.h>

#define SIZE_PATH_MAX (256)
#define SIZE_CMD_MAX (SIZE_PATH_MAX)
#define PREFIX_SEL_FILE ("\tSelected file : \t")

typedef struct{
  GtkWindow  *win;
  char *path;
  GtkLabel *labelOut;
  GtkWidget *logo;
  
}sBrowseData;

typedef struct{
  char *path;
  GtkLabel *labelOut;
  GtkWidget *logo;
  
}sSendData;

void OpenShiplify(void);
void BrowsePolar(GtkButton *aBtn, sBrowseData *aData);
void SendPolar(GtkButton *aBtn, sSendData *aData);


#endif
