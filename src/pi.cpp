#include "pi.h"

void PICreateBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiButtonBox, GtkWidget **aPiTextInBox, GtkWidget **aPiTextOutBox, GtkWidget **aPiLogoFileBox, GtkWidget **aPiLogoSendBox)
{
  /*Box*/
  *aPiMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPiTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 100);
  *aPiBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  *aPiTextInBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 45);
  *aPiTextOutBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
  *aPiButtonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 44);
  *aPiLogoFileBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  *aPiLogoSendBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

  gtk_box_set_homogeneous (GTK_BOX(*aPiTextInBox), TRUE);
  gtk_widget_set_halign(*aPiTextInBox, GTK_ALIGN_START);
  gtk_widget_set_valign(*aPiTextInBox, GTK_ALIGN_START);
  gtk_box_set_homogeneous (GTK_BOX(*aPiTextOutBox), TRUE);
  gtk_widget_set_halign(*aPiTextOutBox, GTK_ALIGN_START);
  gtk_widget_set_valign(*aPiTextOutBox, GTK_ALIGN_START);
  gtk_widget_set_margin_top(*aPiTextOutBox, 20);
}

void PISetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("Polar Selection for SOMOS Project");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 80);
}

void PISetLogo(GtkWidget **aLogo, GtkWidget **aLogoShiplify, GtkWidget **aLogoBrowseCheck, GtkWidget **aLogoSendCheck) 
{ 
  //*aLogo = gtk_picture_new_for_filename("res/logo_ensm.png");
  *aLogoShiplify = gtk_picture_new_for_filename("res/d-v2.png");
  *aLogoBrowseCheck = gtk_picture_new();
  *aLogoSendCheck = gtk_picture_new();
}

void PISetButtons(GtkWidget **aShiplifyBtn, GtkWidget **aSendBtn, GtkWidget **aBrowseBtn, GtkWidget **aRemoveBtn) 
{ 
  *aShiplifyBtn = gtk_button_new_with_label ("Shiplify");
  *aSendBtn = gtk_button_new_with_label ("Send");  
  *aBrowseBtn = gtk_button_new_with_label ("Browse...");
  *aRemoveBtn = gtk_button_new_with_label ("Remove Polar");
}

void PISetLabels(GtkWidget **aLabelFileSent, GtkWidget **aLabelFileSelected, GtkWidget **aLabelShiplify, GtkWidget **aLabelPolar, GtkWidget **aLabelSend, GtkWidget **aEmpty2, GtkWidget **aEmpty3,GtkWidget **aEmpty4,GtkWidget **aEmpty5,GtkWidget **aLabelScenario,GtkWidget **aLabelOr, GtkWidget **aLabelRemove) 
{
  *aLabelFileSent = gtk_label_new("  ");
  *aLabelFileSelected = gtk_label_new("  ");

  *aLabelScenario = gtk_label_new("\t1 - Select a preload polar from BridgeCommand scenario :  ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelScenario), 0);
  *aLabelOr = gtk_label_new("\tOr :");
  gtk_label_set_xalign(GTK_LABEL(*aLabelOr), 0);
  *aLabelShiplify = gtk_label_new("\t1 - Download your polar file from Shiplify.io      ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelShiplify), 0);
  *aLabelPolar = gtk_label_new("\t2 - Select polar file to use ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelPolar), 0);
  *aLabelSend = gtk_label_new("\t3 - Send polar file to Bridge Command ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelSend), 0);  
  *aLabelRemove = gtk_label_new("\t4 - Remove downloaded polar ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelRemove), 0);  
  *aEmpty2 = gtk_label_new("                ");
  *aEmpty3 = gtk_label_new("                ");
  *aEmpty4 = gtk_label_new("                ");
  *aEmpty5 = gtk_label_new("                ");
}

void PISetBoxes(GtkWidget **aPiBodyBox,GtkWidget **aPiMainBox,GtkWidget **aPiTitleBox,GtkWidget **aPiButtonBox,GtkWidget **aPiTextInBox,GtkWidget **aPiTextOutBox,GtkWidget **aPiLogoFileBox,GtkWidget **aPiLogoSendBox,//Boxes
		GtkWidget **aShiplifyBtn,GtkWidget **aBrowseBtn,GtkWidget **aSendBtn,GtkWidget **aScenarioList, GtkWidget **aRemoveBtn,//Buttons/Lists
	        GtkWidget **aLogoBrowseCheck,GtkWidget **aLogoSendCheck,//Logos
		GtkWidget **aEmpty2,GtkWidget **aEmpty3,GtkWidget **aEmpty4,GtkWidget **aEmpty5,GtkWidget **aTitle,GtkWidget **aLabelShiplify,GtkWidget **aLabelPolar,GtkWidget **aLabelSend,GtkWidget **aLabelFileSelected,GtkWidget **aLabelFileSent,GtkWidget **aLabelScenario,GtkWidget **aLabelOr,GtkWidget **aLabelRemove//Labels
		) 
{
  gtk_box_append(GTK_BOX (*aPiTitleBox), *aTitle);

  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelScenario);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelOr);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelShiplify);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelPolar);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelSend);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelRemove);
  
  gtk_box_append(GTK_BOX (*aPiLogoFileBox), *aLogoBrowseCheck);
  gtk_box_append(GTK_BOX (*aPiLogoFileBox), *aLabelFileSelected);

  gtk_box_append(GTK_BOX (*aPiLogoSendBox), *aLogoSendCheck);
  gtk_box_append(GTK_BOX (*aPiLogoSendBox), *aLabelFileSent);
  
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aEmpty2);
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aEmpty3);
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aEmpty4);
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aPiLogoFileBox);
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aPiLogoSendBox);

  gtk_box_append(GTK_BOX (*aPiButtonBox), *aScenarioList);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aEmpty5);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aShiplifyBtn);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aBrowseBtn);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aSendBtn);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aRemoveBtn);
  
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiTextInBox);
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiButtonBox);
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiTextOutBox);

  //gtk_box_append(GTK_BOX (*aPiMainBox), *aPiHeaderBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiTitleBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiBodyBox);
}

sBrowseData* PISetBrowsePolarData(GtkWidget **aWin, GtkWidget **aLabelFileSelected, GtkWidget **aLogoBrowseCheck, char *aFilePath)
{
  static sBrowseData brData = {0};
  
  /*Browse polar data*/
  brData.win = GTK_WINDOW (*aWin);
  brData.path = aFilePath;
  brData.labelOut = GTK_LABEL(*aLabelFileSelected);
  brData.logo = *aLogoBrowseCheck;
  /********/

  return &brData;
}

sSendData* PISetSendPolarData(GtkWidget **aLabelFileSent, GtkWidget **aLogoSendCheck,char *aFilePath)
{
  static sSendData sdData = {0};
  
  /*Send polar data*/
  sdData.path = aFilePath;
  sdData.labelOut = GTK_LABEL(*aLabelFileSent);
  sdData.logo = *aLogoSendCheck;
  /********/

  return &sdData;
}
