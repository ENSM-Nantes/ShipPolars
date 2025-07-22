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
  
  gtk_widget_queue_draw(data->area);
    
  return true; 
}



gboolean UpdateFromBC(gpointer aUserData)
{
  sAppData *data = (sAppData*)aUserData;

  data->hCom.WaitMessage(90, data->osMsg);	  
      
  return true;
}
