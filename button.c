#include "button.h"

void OpenShiplify(void)
{
  system("xdg-open 'https://www.shiplify.io'");
}

static void CbkBrowsePolar(GtkNativeDialog *aDialog, int aRes, gpointer aData)
{
  GtkFileChooser *chooser = GTK_FILE_CHOOSER(aDialog);
 
  if(aRes == GTK_RESPONSE_ACCEPT)
    {
      char dest[SIZE_PATH_MAX+strlen(PREFIX_SEL_FILE)];
      GListModel *files = gtk_file_chooser_get_files(chooser);
      sBrowseData *pData = (sBrowseData*)aData;

      GFile *file = (GFile*)g_list_model_get_item(files, 0);
      char *path = g_file_get_path(file);
      
      strcpy(dest, PREFIX_SEL_FILE);
      strcat(dest, path);
      strncpy(pData->path, path, SIZE_PATH_MAX);

      if(path[strlen(path)-3] == '.' &&
	 path[strlen(path)-2] == 'n' &&
	 path[strlen(path)-1] == 'c')
	{
	  gtk_label_set_text(pData->labelOut, dest);
	  gtk_picture_set_filename(GTK_PICTURE( pData->logo ), "res/check.png");
	}
      else
	{
	  gtk_label_set_text(pData->labelOut, "\tWrong polar file format");
	  gtk_picture_set_filename(GTK_PICTURE( pData->logo ), "res/cross.png");
	}
      
      gtk_widget_set_margin_start(pData->logo, 30);
      g_free(path);
      g_object_unref(file);
      
    }
}

void BrowsePolar(GtkButton *aBtn, sBrowseData *aData)
{
  GtkFileChooserNative *dialog = gtk_file_chooser_native_new("Choose polar file", GTK_WINDOW(aData->win), GTK_FILE_CHOOSER_ACTION_OPEN, "_Select", "_Cancel");
  memset(aData, SIZE_PATH_MAX, 0);
  
  g_signal_connect(dialog, "response", G_CALLBACK(CbkBrowsePolar), aData);
  gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));  
}

void RemovePolar(void)
{
  char cmd[SIZE_CMD_MAX] = {0};
  char buffer[4] = {0};
  
  strcpy(cmd, "rm polar.nc");

  FILE *fp = NULL;
  fp = popen(cmd, "r");

  if(fp != NULL) pclose(fp);
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
