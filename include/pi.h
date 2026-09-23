#ifndef POLAR_INJECTION_HPP
#define POLAR_INJECTION_HPP

#include <gtk/gtk.h>

/****************** Structure definitions **************/
typedef struct{
  GtkLabel *labelStatus;
  GtkLabel *labelDetails;
  GtkWidget *logoStatus;
}sPolarStatusData;

/****************** Polar Status prototype definitions **************/
void PICreateBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiStatusBox);
void PISetTitle(GtkWidget **aTitle);
void PISetLogo(GtkWidget **aLogoStatus);
void PISetLabels(GtkWidget **aLabelStatus, GtkWidget **aLabelDetails, GtkWidget **aLabelInfo);
void PISetBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiStatusBox,
		 GtkWidget **aLogoStatus, GtkWidget **aTitle, GtkWidget **aLabelStatus, GtkWidget **aLabelDetails, GtkWidget **aLabelInfo);
sPolarStatusData* PISetStatusData(GtkWidget **aLabelStatus, GtkWidget **aLabelDetails, GtkWidget **aLogoStatus);
void PIUpdateStatus(sPolarStatusData *aData, bool aLoaded, const char *aPath, const char *aTimestamp, const char *aPolarInfo);
/*************************/

#endif
