#ifndef POLAR_INJECTION_HPP
#define POLAR_INJECTION_HPP

#include <gtk/gtk.h>

/****************** Structure definitions **************/
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

/****************** Polar Injection prototype definitions **************/
void PICreateBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiButtonBox, GtkWidget **aPiTextInBox, GtkWidget **aPiTextOutBox, GtkWidget **aPiLogoFileBox, GtkWidget **aPiLogoSendBox);
void PISetTitle(GtkWidget **aTitle);
void PISetLogo(GtkWidget **aLogo, GtkWidget **aLogoShiplify, GtkWidget **aLogoBrowseCheck, GtkWidget **aLogoSendCheck);
void PISetButtons(GtkWidget **aShiplifyBtn, GtkWidget **aSendBtn, GtkWidget **aBrowseBtn);
void PISetLabels(GtkWidget **aLabelFileSent, GtkWidget **aLabelFileSelected, GtkWidget **aLabelShiplify, GtkWidget **aLabelPolar, GtkWidget **aLabelSend, GtkWidget **aEmpty2, GtkWidget **aEmpty3,GtkWidget **aLabelScenario);
void PISetBoxes(GtkWidget **aPiBodyBox,GtkWidget **aPiMainBox,GtkWidget **aPiTitleBox,GtkWidget **aPiButtonBox,GtkWidget **aPiTextInBox,GtkWidget **aPiTextOutBox,GtkWidget **aPiLogoFileBox,GtkWidget **aPiLogoSendBox,GtkWidget **aShiplifyBtn,GtkWidget **aBrowseBtn,GtkWidget **aSendBtn, GtkWidget **aScenarioList, GtkWidget **aLogoBrowseCheck,GtkWidget **aLogoSendCheck, GtkWidget **aEmpty2,GtkWidget **aTitle,GtkWidget **aLabelShiplify,GtkWidget **aLabelPolar,GtkWidget **aLabelSend,GtkWidget **aLabelFileSelected,GtkWidget **aLabelFileSentGtkWidget,GtkWidget **aLabelScenario);
sBrowseData* PISetBrowsePolarData(GtkWidget **aWin, GtkWidget **aLabelFileSelected, GtkWidget **aLogoBrowseCheck, char *aFilePath);
sSendData* PISetSendPolarData(GtkWidget **aLabelFileSent, GtkWidget **aLogoSendCheck,char *aFilePath);
/*************************/

#endif
