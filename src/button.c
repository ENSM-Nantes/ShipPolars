#include "button.h"
#include "app.h"
#include "sail.h"

gboolean OnOffReactivateButton(gpointer aData)
{
  GtkWidget *button = GTK_WIDGET(aData);
  gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
  gtk_button_set_label(GTK_BUTTON(button), "Power On/off");
  return FALSE;
}

gboolean OnOffReactivateLabel(gpointer aData)
{
  GtkWidget *label = GTK_WIDGET(aData);
  gtk_label_set_text(GTK_LABEL(label), " ");

  return FALSE;
}

void OnOffRotor(GtkButton *aBtn, gpointer aRotInfos)
{
  static std::string msg;
  static bool isClicked = false;
  sRotInfos *pRotInfos = static_cast<sRotInfos*>(aRotInfos);
  sAppData *pAppData = static_cast<sAppData*>(pRotInfos->appData);

  msg.clear();
  msg = "SA";

  if(!isClicked)
    {
      isClicked = true;
      msg += "RT1";
      gtk_picture_set_filename(GTK_PICTURE( pRotInfos->logoCheck ), "../res/check.png");
      gtk_label_set_text(GTK_LABEL(pRotInfos->powerLabel), "Please wait until the rotor reaches its rated speed");
    }
  else
    {
      isClicked = false;
      msg += "RT0";
      gtk_picture_set_filename(GTK_PICTURE( pRotInfos->logoCheck ), "../res/cross.png");
      gtk_label_set_text(GTK_LABEL(pRotInfos->powerLabel), "Please wait until the rotor has finished turning");
    }


  if(pRotInfos != NULL)
    {
      //std::cout << "OnOff button clicked, msg : " << msg << std::endl;
      pAppData->hCom.SendMessage(msg, false);

      gtk_button_set_label(GTK_BUTTON(aBtn), "Waiting...");
      gtk_widget_set_sensitive(GTK_WIDGET(aBtn), FALSE);
      g_timeout_add(TIME_TO_START_STOP_ROTOR*1000, OnOffReactivateButton, aBtn);
      g_timeout_add(TIME_TO_START_STOP_ROTOR*1000, OnOffReactivateLabel, pRotInfos->powerLabel);

    }

}

void ChangeRot(GtkButton *aBtn, gpointer aRotInfos)
{
  static std::string msg;
  static bool isClicked = true;
  sRotInfos *pRotInfos = static_cast<sRotInfos*>(aRotInfos);
  sAppData *pAppData = static_cast<sAppData*>(pRotInfos->appData);

  msg.clear();
  msg = "SA";

  if(!isClicked)
    {
      isClicked = true;
      msg += "RTL";
      gtk_picture_set_filename(GTK_PICTURE( pRotInfos->logoRot ), "res/arrow_rot_left.png");

    }
  else
    {
      isClicked = false;
      msg += "RTR";
      gtk_picture_set_filename(GTK_PICTURE( pRotInfos->logoRot ), "res/arrow_rot_right.png");
    }


  if(pRotInfos != NULL)
    {
      //std::cout << "OnOff button clicked, msg : " << msg << std::endl;
      pAppData->hCom.SendMessage(msg, false);
    }


}
