#include "update.h"
#include "app.h"
#include <cstdio>

gboolean UpdatePolar(gpointer aUserData)
{
  sAppData *data = (sAppData*)aUserData;
  sPrData *pPrData = (sPrData*)data->prData; 
  
  pthread_mutex_lock(&data->sailsLock);

  for(int i=0;i<ANGLE_STEP_COUNT;i++)
    {
      pPrData->forceX[i]=data->sails.GetForce('X', data->osMsg.GetSTW(), data->osMsg.GetAWS(), i*15);
      pPrData->forceY[i]=data->sails.GetForce('Y', data->osMsg.GetSTW(), data->osMsg.GetAWS(), i*15);
    }

  pPrData->fOsX = data->sails.GetForce('X', data->osMsg.GetSTW(), data->osMsg.GetAWS(), data->osMsg.GetAWA());
  pPrData->fOsY = data->sails.GetForce('Y', data->osMsg.GetSTW(), data->osMsg.GetAWS(), data->osMsg.GetAWA());

  pthread_mutex_unlock(&data->sailsLock);

  std::string alertRot = "";

  alertRot.clear();
  
  if(data->osMsg.GetRotOnOff() == true)
    {
      //Starboard wind
      if(data->osMsg.GetWindSide() == "starboard")
	{
	  if(data->osMsg.GetRotDir() == 1)
	    {
	      alertRot = "You have to change\nrotor rotation direction !";
	    
	  
	      if(data->osMsg.GetAWA() > 30)
		{
		  pPrData->fOsX *= -1;
		  pPrData->fOsY *= -1;
		}
	    }
	}
      //Port wind
      else
	{
	  if(data->osMsg.GetRotDir() == -1)
	    {	 
	      alertRot = "You have to change\nrotor rotation direction !";
	    

	      if(data->osMsg.GetAWA()  < -30)
		{
		  pPrData->fOsX *= -1;
		  pPrData->fOsY *= -1;
		}
	    }
	}
  
      gtk_widget_queue_draw(pPrData->areaX);
      gtk_widget_queue_draw(pPrData->areaY);
      gtk_widget_queue_draw(pPrData->areaSum);

      float fOsX = pPrData->fOsX;
      float fOsY = pPrData->fOsY;
    
      float angle = (atan2(-fOsX, fOsY) * 180.0 / M_PI) + 90;

      if(angle > 180) 
	{
	  float delta = (270-angle);
	  angle=-90-delta;
	}
  
      float force = sqrt(fOsX*fOsX + fOsY*fOsY);
      std::string forceLabel = "\n\n\n\n Force : "+std::to_string(force)+" kN"+"\n\n Angle : "+std::to_string(angle)+" °\n\n"+alertRot;


      gtk_label_set_text(pPrData->fLabel, forceLabel.c_str());
    }
  else
    {
      alertRot = "You have to start rotor(s) !";
      gtk_label_set_text(pPrData->fLabel, alertRot.c_str());
    }
  
  return true; 
}


gboolean UpdateFromBC(gpointer aUserData)
{
  sAppData *data = (sAppData*)aUserData;

  data->hCom.WaitMessage(0, data->osMsg);

  if(data->osMsg.GetShutDown())
    {
      std::remove(POLAR_FILE_PATH);
      g_application_quit(g_application_get_default());
      return G_SOURCE_REMOVE;
    }

  return true;
}
