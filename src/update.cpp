#include "update.h"
#include "app.h"

gboolean UpdatePolar(gpointer aUserData)
{
  sAppData *data = (sAppData*)aUserData;
  sPrData *pPrData = (sPrData*)data->prData; 
  
  //Get values from BC
  for(int i=0;i<ANGLE_STEP_COUNT;i++)
    {
      pPrData->forceX[i]=data->sails.GetForce('X', data->osMsg.GetSTW(), data->osMsg.GetAWS(), i*15);
      pPrData->forceY[i]=data->sails.GetForce('Y', data->osMsg.GetSTW(), data->osMsg.GetAWS(), i*15);
    }

  std::string alertRot = "";

  alertRot.clear();

  pPrData->fOsX = data->sails.GetForce('X', data->osMsg.GetSTW(), data->osMsg.GetAWS(), data->osMsg.GetAWA());
  pPrData->fOsY = data->sails.GetForce('Y', data->osMsg.GetSTW(), data->osMsg.GetAWS(), data->osMsg.GetAWA());

  
  if(data->osMsg.GetRotOnOff() == true)
    {
      //Starboard wind
      if((data->osMsg.GetAWA()) >= 0 && (data->osMsg.GetAWA()) <= 180)
	{
	  if(data->osMsg.GetRotDir() == -1)
	    {
	      pPrData->fOsX *= -1;
	      pPrData->fOsY *= -1;

	      alertRot = "You have to change\nrotor rotation direction !";
	    }
	}
      //Port wind
      else
	{
	  if(data->osMsg.GetRotDir() == 1)
	    {
	      pPrData->fOsX *= -1;
	      pPrData->fOsY *= -1;
	  
	      alertRot = "You have to change\nrotor rotation direction !";
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
  
  return true;
}
