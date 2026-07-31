#ifndef APP_H
#define APP_H

#include <iostream>
#include <gtk/gtk.h>
#include <pthread.h>
#include "nc.h"
#include "list.h"
#include "com.h"
#include "pr.h"
#include "pi.h"

#define SIZE_MAX_SCENARIO_NAME (256)

typedef struct
{
  Nc sails;
  Com hCom;
  Message osMsg;
  sPrData *prData;
  pthread_mutex_t sailsLock;
}sAppData;


void AppActivate(GApplication *app, gpointer aUserData);
void AppScenarioList(GtkStringList **aScenarioItems, GtkWidget **aScenarioDropDown, sPolarData *aPolarData);




#endif
