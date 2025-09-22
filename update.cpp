#include "update.h"
#include "app.h"
#include "com.h"


gboolean UpdatePolar(gpointer aUserData)
{
  sAppData *data = (sAppData*)aUserData;

  //Get values from BC
  for(int i=0;i<ANGLE_STEP_COUNT;i++)
    {
      data->forceX[i]=data->sails.GetForce('X', data->osMsg.GetSTW(), data->osMsg.GetAWS(), i*15);
      data->forceY[i]=data->sails.GetForce('Y', data->osMsg.GetSTW(), data->osMsg.GetAWS(), i*15);
    }

  data->fOsX = data->sails.GetForce('X', data->osMsg.GetSTW(), data->osMsg.GetAWS(), data->osMsg.GetAWA());
  data->fOsY = data->sails.GetForce('Y', data->osMsg.GetSTW(), data->osMsg.GetAWS(), data->osMsg.GetAWA());

  gtk_widget_queue_draw(data->areaX);
  gtk_widget_queue_draw(data->areaY);
  gtk_widget_queue_draw(data->areaSum);

  float fOsX = data->fOsX;
  float fOsY = data->fOsY;
  float angle = atan2(-fOsX, fOsY) * 180.0 / M_PI;
  float force = sqrt(fOsX*fOsX + fOsY*fOsY);
  std::string forceLabel = "\n\n\n\n Force : "+std::to_string(force)+" kN"+"\n\n Angle : "+std::to_string(angle)+" °";

  gtk_label_set_text(data->fLabel, forceLabel.c_str());

  return true; 
}


gboolean UpdateFromBC(gpointer aUserData)
{
  sAppData *data = (sAppData*)aUserData;

  data->hCom.WaitMessage(90, data->osMsg);	  
      
  return true;
}
