#ifndef SAIL_H
#define SAIL_H

#include <gtk/gtk.h>
#include <string>

#define TIME_TO_START_STOP_ROTOR (30)

struct sRotInfos
{
  GtkWidget *logoCheck;
  GtkWidget *logoRot;
  GtkWidget *powerLabel;
  GtkWidget *rotSpeedLabel;
  GtkWidget *btnOnOff;
  GtkWidget *btnChangeDir;
  void *appData;
};

void SaCreateBoxes(GtkWidget **aSaBodyBox, GtkWidget **aSaMainBox, GtkWidget **aSaTitleBox);
void SaSetTitle(GtkWidget **aTitle);
void SaSetBoxes(GtkWidget **aSaBodyBox, GtkWidget **aSaMainBox, GtkWidget **aSaTitleBox, GtkWidget **aTitle, GtkWidget **aPowerLabel, GtkWidget **aRotSpeedLabel, GtkWidget **aLogoRotorCheck, GtkWidget **aLogoRotorDir, void *aAppData, sRotInfos *aRotInfos); 


#endif
