#include "app.h"

/*
  **Polar Management 
  **ENSM Nantes
  **Florent Richard


  **opendata logo : https://www.flaticon.com/authors/hqrloveq
                    https://www.flaticon.com/authors/juicy-fish

*/

int main (int argc, char **argv)
{
  GtkApplication *app = NULL;
  int retRun = -1;
  
  gtk_init();
  
  app=gtk_application_new("fr.somos-project.polar-management", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK (AppActivate), NULL);

  retRun=g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return retRun;
}
