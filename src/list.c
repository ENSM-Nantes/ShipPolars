#include <iostream>
#include "list.h"


void SelectScenario(GtkDropDown *aListDropDown, GParamSpec *aPrmSpec, gpointer aUserData)
{
  int idx = gtk_drop_down_get_selected(aListDropDown);
  sPolarData *pPolarData = static_cast<sPolarData*>(aUserData);

  //Lock data, also use in app.c
  pthread_mutex_lock(&pPolarData->lock);
  
  if(idx >= 0)
    {
      g_print ("Élément sélectionné : %s\n", gtk_string_list_get_string(GTK_STRING_LIST(gtk_drop_down_get_model(aListDropDown)), idx));
      switch (idx)
	{
	case 0:	  
	  strcpy(pPolarData->fileName, " ");
	  break;

	case 1:	  
	  strcpy(pPolarData->fileName, "polar/polar_CopenhagenFerry_NorsePower_1rotor30x5.nc");
	  break;

	case 2:
	  strcpy(pPolarData->fileName, "polar/polar_FakeCargoMaersk_2rotor18x3.nc");
	  break;

	default:
	  break;

	}
    }

  //Unlock data
  pthread_mutex_unlock(&pPolarData->lock);
}


