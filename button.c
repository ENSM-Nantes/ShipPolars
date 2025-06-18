#include "button.h"

void OpenShiplify(void)
{
  system("xdg-open 'https://www.shiplify.io'");
}

static void CbkBrowsePolar(GObject *aSource, GAsyncResult *aRes, gpointer aData)
{
  GtkFileDialog *dialog = GTK_FILE_DIALOG(aSource);

  GError *error = NULL;
  GFile *file = gtk_file_dialog_open_finish(dialog, aRes, &error);
  
  if(file)
    {
      char dest[SIZE_PATH_MAX+strlen(PREFIX_SEL_FILE)];
      char *path = g_file_get_path(file);
      sBrowseData *pData = aData;
      strcpy(dest, PREFIX_SEL_FILE);
      strcat(dest, path);
      strncpy(pData->path, path, SIZE_PATH_MAX);
      //printf("Path : %s\n", pData->path);
      gtk_label_set_text(pData->labelOut, dest);
      gtk_picture_set_filename(GTK_PICTURE( pData->logo ), "res/check.png");
      gtk_widget_set_margin_start(pData->logo, 30);
      g_free(path);
      g_object_unref(file);
      
    }
}

void BrowsePolar(GtkButton *aBtn, sBrowseData *aData)
{
  GtkFileDialog *dialog = gtk_file_dialog_new();

  memset(aData, SIZE_PATH_MAX, 0);
  
  gtk_file_dialog_open(dialog,
		       aData->win,
		       NULL,
		       CbkBrowsePolar,
		       aData);

}

void SendPolar(GtkButton *aBtn, sSendData *aData)
{
  char cmd[SIZE_CMD_MAX] = {0};
  char buffer[4] = {0};
  
  strcpy(cmd, "res/sendpolar.sh ");
  strcat(cmd, aData->path);
  
  FILE *fp = NULL;
  fp = popen(cmd, "r");

  if(fp != NULL)
    {   
      if(fgets(buffer, sizeof(buffer), fp) != NULL)
	{
	  if('0' == buffer[0])
	    {
	      gtk_label_set_text(aData->labelOut, "\tPolar file sent successfully !");
	      gtk_picture_set_filename(GTK_PICTURE( aData->logo ), "res/check.png");
	      gtk_widget_set_margin_start(aData->logo, 30);
	    }
	  else
	    {
	      gtk_label_set_text(aData->labelOut, "\tFailure to send polar file");
	      gtk_picture_set_filename(GTK_PICTURE( aData->logo ), "res/cross.png");
	      gtk_widget_set_margin_start(aData->logo, 30);
	    }
	}

      pclose(fp);
    }
}
