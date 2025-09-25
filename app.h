#ifndef APP_H
#define APP_H

#include <iostream>
#include <gtk/gtk.h>
#include "nc.h"
#include "com.h"
#include "pr.h"
#include "pi.h"

typedef struct
{
  Nc sails;
  Com hCom;
  Message osMsg;
  sPrData *prData;
  
}sAppData;


void AppActivate(GApplication *app, gpointer aUserData);
void AppScenarioList(GtkStringList **aScenarioItems, GtkWidget **aScenarioDropDown);




#endif
