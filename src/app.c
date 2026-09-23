#include "app.h"
#include "button.h"
#include "update.h"
#include "pthread.h"
#include "about.h"
#include "sail.h"
#include <sys/stat.h>
#include <ctime>

//Global app data
sPrData gPrData={{-200,-160,-120,-80,-40,0,40,80,120,160,200},FORCE_MAX,{0},{0},0,0,NULL,NULL,NULL,NULL};
sAppData gAppData;

typedef struct
{
  sPolarStatusData *statusData;
  bool loaded;
  char path[SIZE_PATH_MAX];
  char timestamp[64];
  char polarInfo[256];
}sStatusIdleData;

static gboolean PRApplyScaleIdle(gpointer aUserData)
{
  float *pMaxForce = (float*)aUserData;

  PRSetScale(&gPrData, *pMaxForce);
  if(gPrData.areaX) gtk_widget_queue_draw(gPrData.areaX);
  if(gPrData.areaY) gtk_widget_queue_draw(gPrData.areaY);

  free(pMaxForce);
  return G_SOURCE_REMOVE;
}

static gboolean PIUpdateStatusIdle(gpointer aUserData)
{
  sStatusIdleData *pStatus = (sStatusIdleData*)aUserData;

  PIUpdateStatus(pStatus->statusData, pStatus->loaded, pStatus->path, pStatus->timestamp, pStatus->polarInfo);

  free(pStatus);
  return G_SOURCE_REMOVE;
}

static void PostStatusUpdate(sPolarStatusData *aStatusData, bool aLoaded, const char *aPath, const char *aTimestamp, const char *aPolarInfo)
{
  sStatusIdleData *pStatus = (sStatusIdleData*)malloc(sizeof(sStatusIdleData));

  pStatus->statusData = aStatusData;
  pStatus->loaded = aLoaded;
  strncpy(pStatus->path, aPath, SIZE_PATH_MAX-1);
  pStatus->path[SIZE_PATH_MAX-1] = 0;
  strncpy(pStatus->timestamp, aTimestamp, sizeof(pStatus->timestamp)-1);
  pStatus->timestamp[sizeof(pStatus->timestamp)-1] = 0;
  strncpy(pStatus->polarInfo, aPolarInfo, sizeof(pStatus->polarInfo)-1);
  pStatus->polarInfo[sizeof(pStatus->polarInfo)-1] = 0;

  g_idle_add(PIUpdateStatusIdle, pStatus);
}

static void *AppThreadManagement(void *aData)
{
  bool isNetStarted = false, isNcLoaded = false;
  sPolarStatusData *pStatusData = static_cast<sPolarStatusData*>(aData);
  guint idUpdateBC = 0, idUpdatePolar = 0;
  time_t lastMtime = 0;

  /*Start Enet server*/
  while(!isNetStarted)
    {
      if(0 == gAppData.hCom.Connect(ENET_SERVER_HOST, 18304))
	{
	  isNetStarted = true;
	  idUpdateBC = g_timeout_add(100, UpdateFromBC, &gAppData);
	}

      //Pause the thread
      sleep(1);
    }

  /*Nc Management*/
  while(true)
    {
      struct stat fileStat;
      bool fileExists = (0 == stat(POLAR_FILE_PATH, &fileStat));

      //Polar file gone, or replaced by a new one sent from Bridge Command
      if(isNcLoaded && (!fileExists || fileStat.st_mtime != lastMtime))
	{
	  pthread_mutex_lock(&gAppData.sailsLock);
	  gAppData.sails.Close();
	  pthread_mutex_unlock(&gAppData.sailsLock);
	  std::cout << "Polar file closed : " << POLAR_FILE_PATH << std::endl;
	  isNcLoaded = false;

	  //Remove periodic callback
	  if(idUpdatePolar) g_source_remove(idUpdatePolar);

	  PostStatusUpdate(pStatusData, false, "", "", "");
	}

      //Get nc file
      if(!isNcLoaded && fileExists)
	{
	  pthread_mutex_lock(&gAppData.sailsLock);
	  bool opened = (0 == gAppData.sails.Open(POLAR_FILE_PATH, "TotalSails_X", "TotalSails_Y"));
	  bool inited = opened && (0 == gAppData.sails.Init("STW_kt", "TWS_kt", "TWA_deg"));
	  pthread_mutex_unlock(&gAppData.sailsLock);

	  if(inited)
	    {
	      std::cout << "Polar file loaded : " << POLAR_FILE_PATH << std::endl;

	      pthread_mutex_lock(&gAppData.sailsLock);
	      float maxForce = gAppData.sails.GetMaxForce();
	      pthread_mutex_unlock(&gAppData.sailsLock);
	      std::cout << "[DEBUG] GetMaxForce() returned " << maxForce << std::endl;

	      float *pMaxForce = (float*)malloc(sizeof(float));
	      *pMaxForce = maxForce;
	      g_idle_add(PRApplyScaleIdle, pMaxForce);

	      //Add peridic update callback
	      idUpdatePolar = g_timeout_add(100, UpdatePolar, &gAppData);

	      isNcLoaded = true;
	      lastMtime = fileStat.st_mtime;

	      char timestamp[64];
	      struct tm *tmInfo = localtime(&fileStat.st_mtime);
	      strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tmInfo);

	      pthread_mutex_lock(&gAppData.sailsLock);
	      std::string vesselType = gAppData.sails.GetGlobalAttrString("vessel_type");
	      std::string genDate = gAppData.sails.GetGlobalAttrString("date");
	      int sailCount = gAppData.sails.GetSailCount();
	      pthread_mutex_unlock(&gAppData.sailsLock);

	      std::string polarInfo = "Vessel type : "+(vesselType.empty() ? "unknown" : vesselType)
		+"\nSails/rotors : "+std::to_string(sailCount)
		+"\nMax force : "+std::to_string(maxForce)+" kN";
	      if(!genDate.empty()) polarInfo += "\nGenerated : "+genDate;

	      PostStatusUpdate(pStatusData, true, POLAR_FILE_PATH, timestamp, polarInfo.c_str());
	    }
	}

      //Pause the thread
      sleep(2);
    }

  return NULL;
}

void AppActivate(GApplication *app, gpointer aUserData)
{
  /*Generic App variables*/
  GtkWidget *overlay, *win, *tabBox, *headerBox, *logo, *empty1;
  /********/
  /*Polar Status variables*/
  static GtkWidget *piBodyBox, *piMainBox, *piTitleBox, *piStatusBox;
  static GtkWidget *piTitle, *labelStatus, *labelDetails, *labelInfo, *logoStatus;
  static pthread_t tPolarStatus;
  sPolarStatusData *pStatusData;
  /********/
  /*Polar Reader variables*/
  static GtkWidget *prBodyBox, *prMainBox, *prTitleBox, *prLeftBox, *prMidBox, *prRightBox;
  static GtkWidget *prTitle;
  static GtkWidget *labelPolarX, *labelPolarY, *labelVector, *labelAngleForce;
  static GtkWidget *prPolarXArea, *prPolarYArea, *prSumArea;
  static pthread_t tPrIdle;
  /********/
  /*About variables*/
  static GtkWidget *abBodyBox, *abMainBox,  *abTitleBox;
  static GtkWidget *abTitle, *abInfos;
  /********/
  /*Sail Management variables*/
  static sRotInfos rotInfos;
  static GtkWidget *logoRotorCheck, *logoRotorDir, *powerLabel, *rotSpeedLabel;
  static GtkWidget *saBodyBox, *saMainBox,  *saTitleBox;
  static GtkWidget *saTitle;
  /********/

  /*Window*/
  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "ShipPolars");
  gtk_window_set_default_size (GTK_WINDOW (win), 1920, 1080);
  gtk_window_set_resizable(GTK_WINDOW(win), TRUE);
  gtk_window_set_decorated(GTK_WINDOW(win), TRUE);
  /********/

  /*App Constants*/
  GtkWidget *emptyTop = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_size_request (emptyTop, 0, 10);
  GtkWidget *appBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  /********/

  /*Generic header*/
  headerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
  empty1 = gtk_label_new("                ");
  logo = gtk_picture_new_for_filename("res/logo_ensm.png");
  gtk_box_append(GTK_BOX (headerBox), logo);
  gtk_box_append(GTK_BOX (headerBox), empty1);
  /********/

  //Polar Status create boxes
  PICreateBoxes(&piBodyBox, &piMainBox, &piTitleBox, &piStatusBox);

  //Polar Status title
  PISetTitle(&piTitle);

  //Polar Status logo
  PISetLogo(&logoStatus);

  //Polar Status labels
  PISetLabels(&labelStatus, &labelDetails, &labelInfo);

  /*Polar Status boxes*/
  PISetBoxes(&piBodyBox, &piMainBox, &piTitleBox, &piStatusBox,
	     &logoStatus, &piTitle, &labelStatus, &labelDetails, &labelInfo);

  /*Polar Status data + thread*/
  pStatusData = PISetStatusData(&labelStatus, &labelDetails, &logoStatus);
  PIUpdateStatus(pStatusData, false, "", "", "");

  pthread_create(&tPolarStatus, nullptr, AppThreadManagement, pStatusData);
  pthread_detach(tPolarStatus);
  /********/

  pthread_mutex_init(&gAppData.sailsLock, nullptr);

  //Polar Reader create boxes
  PRCreateBoxes(&prBodyBox, &prMainBox, &prTitleBox, &prLeftBox, &prMidBox, &prRightBox);

  //Polar Reader title
  PRSetTitle(&prTitle);

  //Polar Reader labels
  PRSetLabels(&labelPolarX, &labelPolarY, &labelVector, &labelAngleForce);

  /*Polar Reader core*/

  /*Set app data*/
  gAppData.prData = &gPrData;
  gPrData.fLabel = GTK_LABEL(labelAngleForce);
  /****/

  /*Cairo area drawing*/
  prPolarXArea = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (prPolarXArea), 800);
  gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (prPolarXArea), 800);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(prPolarXArea), PRDrawPolarX, &gAppData, NULL);
  //gtk_widget_set_margin_start(prPolarXArea, 100);
  gPrData.areaX = prPolarXArea;

  prPolarYArea = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (prPolarYArea), 800);
  gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (prPolarYArea), 800);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(prPolarYArea), PRDrawPolarY, &gAppData, NULL);
  //gtk_widget_set_margin_start(prPolarYArea, 300);
  gPrData.areaY = prPolarYArea;

  prSumArea = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (prSumArea), 200);
  gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (prSumArea), 400);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(prSumArea), PRDrawSum, &gAppData, NULL);
  gtk_widget_set_margin_start(prSumArea, 50);
  gPrData.areaSum = prSumArea;
  /********************/

  /*Polar Reader boxes*/
  PRSetBoxes(&prBodyBox, &prMainBox, &prTitleBox, &prLeftBox, &prMidBox, &prRightBox,//Boxes
	     &prTitle,&labelPolarX, &labelPolarY, &labelVector, &labelAngleForce,//Labels
	     &prPolarXArea, &prPolarYArea, &prSumArea//Cairo
	     );

  //About create boxes
  AbCreateBoxes(&abBodyBox, &abMainBox, &abTitleBox);

  //About title
  AbSetTitle(&abTitle);
  abInfos = gtk_label_new("\tName : ShipPolars \n\r\tVersion : v1.3\n\r\tProject : SOMOS Project 2026\n\r\tOwner : ENSM-Nantes\n\r\tContact : florent.richard@supmaritime.fr\n\r\tWebsite : somos-project.fr");

  /*About boxes*/
  AbSetBoxes(&abBodyBox,&abMainBox,&abTitleBox,//Boxes
	     &abTitle,&abInfos//Labels
	     );

  //Sail management create boxes
  SaCreateBoxes(&saBodyBox, &saMainBox, &saTitleBox);

  //Sail management title
  SaSetTitle(&saTitle);

  rotInfos.appData = &gAppData;

  /*Sail management boxes*/
  SaSetBoxes(&saBodyBox,&saMainBox,&saTitleBox,//Boxes
	     &saTitle, &powerLabel, &rotSpeedLabel,//Labels
	     &logoRotorCheck, &logoRotorDir, //Logos
	     &gAppData, &rotInfos);


  /*Tab menu*/
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

  gtk_stack_add_titled(GTK_STACK(stack), piMainBox, "tab1", "Polar Status");
  gtk_stack_add_titled(GTK_STACK(stack), prMainBox, "tab2", "Polar Reader");
  gtk_stack_add_titled(GTK_STACK(stack), saMainBox, "tab3", "Sail Management");
  gtk_stack_add_titled(GTK_STACK(stack), abMainBox, "tab4", "About");

  GtkWidget *switcher = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

  gtk_widget_set_halign (GTK_WIDGET(switcher), GTK_ALIGN_START);
  gtk_widget_set_valign (GTK_WIDGET(switcher), GTK_ALIGN_START);

  tabBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_box_append(GTK_BOX(tabBox), switcher);
  gtk_box_append(GTK_BOX(tabBox), stack);
  /********/

  /*Add all boxes*/
  gtk_box_append(GTK_BOX(appBox), emptyTop);
  gtk_box_append(GTK_BOX(appBox), headerBox);
  gtk_box_append(GTK_BOX(appBox), tabBox);
  /**/

  /*Overlay*/
  overlay = gtk_overlay_new();
  //Footer overlay, display on all pages
  GtkWidget *labelFooter = gtk_label_new("ShipPolars v1.3 - SOMOS Project 2026 - ENSM Nantes");
  gtk_widget_set_halign(labelFooter, GTK_ALIGN_END);
  gtk_widget_set_valign(labelFooter, GTK_ALIGN_END);

  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), labelFooter);
  /*************/

  /*Set Child*/
  gtk_window_set_child(GTK_WINDOW(win), overlay);
  gtk_overlay_set_child (GTK_OVERLAY(overlay), appBox);
  /********/

  /*CSS*/
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "res/style.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_add_css_class(headerBox, "header-label");
  gtk_widget_add_css_class(labelFooter, "footer-label");
  gtk_widget_add_css_class(piTitle, "title-label");
  gtk_widget_add_css_class(prTitle, "title-label");
  gtk_widget_add_css_class(abTitle, "title-label");
  gtk_widget_add_css_class(saTitle, "title-label");
  gtk_widget_add_css_class(piBodyBox, "textIn-label");
  gtk_widget_add_css_class(labelStatus, "status-label");
  gtk_widget_add_css_class(powerLabel, "textIn-label");
  gtk_widget_add_css_class(rotSpeedLabel, "textIn-label");
  gtk_widget_add_css_class(saBodyBox, "textOut-label");
  //gtk_widget_add_css_class(mainBox, "back-template");
  gtk_widget_add_css_class(abMainBox, "textIn-label");
  gtk_widget_add_css_class(prLeftBox, "textIn-label");
  gtk_widget_add_css_class(prMidBox, "textIn-label");
  gtk_widget_add_css_class(prRightBox, "textIn-label");
  gtk_widget_add_css_class(appBox, "back-template");
  /********/

  gtk_window_present (GTK_WINDOW (win));
}
