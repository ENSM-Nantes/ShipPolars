#include "pi.h"
#include <string>

void PICreateBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiStatusBox)
{
  /*Box*/
  *aPiMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPiTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 100);
  *aPiBodyBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
  *aPiStatusBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);

  //Everything hugs the left edge; labelStatus/labelDetails/labelInfo are all direct
  //children of aPiBodyBox with xalign 0, so their text shares the same x position
  gtk_widget_set_halign(*aPiBodyBox, GTK_ALIGN_START);
  gtk_widget_set_halign(*aPiStatusBox, GTK_ALIGN_START);
  gtk_widget_set_valign(*aPiStatusBox, GTK_ALIGN_CENTER);

  //Space between the window's left border and the whole block
  gtk_widget_set_margin_start(*aPiBodyBox, 40);
}

void PISetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("Polar Status");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 80);
}

void PISetLogo(GtkWidget **aLogoStatus)
{
  *aLogoStatus = gtk_image_new();
  gtk_image_set_pixel_size(GTK_IMAGE(*aLogoStatus), 48);
}

void PISetLabels(GtkWidget **aLabelStatus, GtkWidget **aLabelDetails, GtkWidget **aLabelInfo)
{
  *aLabelStatus = gtk_label_new("Waiting connexion ...");
  gtk_label_set_xalign(GTK_LABEL(*aLabelStatus), 0);

  *aLabelDetails = gtk_label_new(" ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelDetails), 0);

  *aLabelInfo = gtk_label_new("The polar file is sent automatically by Bridge Command when it is launched,\nand stored as polar/polar.nc.");
  gtk_label_set_xalign(GTK_LABEL(*aLabelInfo), 0);
  gtk_widget_set_margin_top(*aLabelInfo, 50);
}

void PISetBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiStatusBox,
		 GtkWidget **aLogoStatus, GtkWidget **aTitle, GtkWidget **aLabelStatus, GtkWidget **aLabelDetails, GtkWidget **aLabelInfo)
{
  gtk_box_append(GTK_BOX (*aPiTitleBox), *aTitle);

  //Icon goes right after the status text, not before it
  gtk_box_append(GTK_BOX (*aPiStatusBox), *aLabelStatus);
  gtk_box_append(GTK_BOX (*aPiStatusBox), *aLogoStatus);

  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiStatusBox);
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aLabelDetails);
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aLabelInfo);

  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiTitleBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiBodyBox);
}

sPolarStatusData* PISetStatusData(GtkWidget **aLabelStatus, GtkWidget **aLabelDetails, GtkWidget **aLogoStatus)
{
  static sPolarStatusData statusData = {0};

  statusData.labelStatus = GTK_LABEL(*aLabelStatus);
  statusData.labelDetails = GTK_LABEL(*aLabelDetails);
  statusData.logoStatus = *aLogoStatus;

  return &statusData;
}

void PIUpdateStatus(sPolarStatusData *aData, bool aLoaded, const char *aPath, const char *aTimestamp, const char *aPolarInfo)
{
  if(NULL == aData) return;

  if(aLoaded)
    {
      std::string status = "Received";
      std::string details = std::string(aPath)+"\nReceived : "+std::string(aTimestamp)+"\n"+std::string(aPolarInfo);

      gtk_label_set_text(aData->labelStatus, status.c_str());
      gtk_label_set_text(aData->labelDetails, details.c_str());
      gtk_image_set_from_file(GTK_IMAGE(aData->logoStatus), "res/check.png");
    }
  else
    {
      gtk_label_set_text(aData->labelStatus, "Waiting connexion ...");
      gtk_label_set_text(aData->labelDetails, " ");
      gtk_image_set_from_file(GTK_IMAGE(aData->logoStatus), "res/cross.png");
    }
}
