#ifndef APP_H
#define APP_H

#include <iostream>
#include <gtk/gtk.h>
#include "nc.h"
#include "com.h"
#include "message.h"

#define FORCE_LINE_COUNT (9)
#define RADIUS_MAX (350)
#define ANGLE_STEP_COUNT (13)
#define FORCE_MAX (120)
#define ANGLE_STEP_DEGRES (15)
#define ENET_SERVER_HOST ("rpi5-somos-1.local")

typedef struct
{
  float forceLegend[FORCE_LINE_COUNT];
  float forceX[ANGLE_STEP_COUNT];
  float forceY[ANGLE_STEP_COUNT];
  float fOsX;
  float fOsY;
  GtkWidget *area;
  Nc sails;
  Com hCom;
  Message osMsg;
  
}sAppData;


void AppActivate(GApplication *app, gpointer aUserData);





#endif
