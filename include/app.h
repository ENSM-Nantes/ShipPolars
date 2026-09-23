#ifndef APP_H
#define APP_H

#include <iostream>
#include <gtk/gtk.h>
#include <pthread.h>
#include "nc.h"
#include "com.h"
#include "pr.h"
#include "pi.h"

#define POLAR_FILE_PATH ("polar/polar.nc")

typedef struct
{
  Nc sails;
  Com hCom;
  Message osMsg;
  sPrData *prData;
  pthread_mutex_t sailsLock;
}sAppData;


void AppActivate(GApplication *app, gpointer aUserData);




#endif
