#include "list.h"


void SelectScenario(GtkDropDown *aListDropDown, gpointer aUserData)
{
  int idx = gtk_drop_down_get_selected(aListDropDown);

  if(idx >= 0)
    {
      g_print ("Élément sélectionné : %s\n", gtk_string_list_get_string(GTK_STRING_LIST(gtk_drop_down_get_model(aListDropDown)), idx));
    }
}



