#include "app.h"
#include "button.h"
#include "update.h"
#include "pthread.h"
#include "about.h"
#include "sail.h"

//Global app data
sPrData gPrData={{-400,-320,-240,-160,-80,0,80,160,240,320,400},{0},{0},0,0,NULL,NULL,NULL,NULL};
sAppData gAppData;


static void *AppThreadManagement(void *aData)
{
  bool isNetStarted = false, isNcLoaded = false;
  char filePathSave[SIZE_PATH_MAX]={0};
  sPolarData *pPolarData = static_cast<sPolarData*>(aData);
  guint idUpdateBC = 0, idUpdatePolar = 0;
  
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
      //Lock data, also use in list.c
      pthread_mutex_lock(&pPolarData->lock);

      //Polar file update
      if(isNcLoaded && (0 != strcmp(filePathSave, pPolarData->fileName)))
	{
	  gAppData.sails.Close();
	  std::cout << "Polar file closed : " << filePathSave << std::endl;
	  memset(filePathSave, 0, SIZE_PATH_MAX);
	  isNcLoaded = false;

	  //Remove periodic callback
	  if(idUpdateBC) g_source_remove(idUpdateBC);
	  if(idUpdatePolar) g_source_remove(idUpdatePolar);
	}
      
      //Get nc file
      if(!isNcLoaded && (0 == gAppData.sails.Open(pPolarData->fileName, "TotalSails_X", "TotalSails_Y")))
	{
	  if(0 ==  gAppData.sails.Init("STW_kt", "TWS_kt", "TWA_deg"))
	    {
	      std::cout << "Polar file loaded : " << pPolarData->fileName << std::endl;

	      //Add peridic update callback
	      idUpdatePolar = g_timeout_add(100, UpdatePolar, &gAppData);

	      isNcLoaded = true;
	    }
	}

      //Save polar file currently open
      strcpy(filePathSave, pPolarData->fileName);

      //Unlock data
      pthread_mutex_unlock(&pPolarData->lock);

      //Pause the thread 
      sleep(2);
    }

  return NULL;
}

void AppScenarioList(GtkStringList **aScenarioItems, GtkWidget **aScenarioDropDown, sPolarData *aPolarData) 
{
  *aScenarioItems = gtk_string_list_new(NULL);
  gtk_string_list_append(*aScenarioItems, "No Scenario");
  gtk_string_list_append(*aScenarioItems, "CopenhagenFerry - 1 rotor (30x5)");
  gtk_string_list_append(*aScenarioItems, "Fake Cargo Maersk - 2 rotors (18x3)");
  gtk_string_list_append(*aScenarioItems, "SC-Connector - 2 rotors (30x5)");
  gtk_string_list_append(*aScenarioItems, "KVLCC2 - 4 rotors (24x4)");
  gtk_string_list_append(*aScenarioItems, "KVLCC2 - 5 rotors (30x5)");
  
  *aScenarioDropDown = gtk_drop_down_new(G_LIST_MODEL(*aScenarioItems), NULL);
  g_signal_connect(*aScenarioDropDown, "notify::selected", G_CALLBACK(SelectScenario), aPolarData);
}

void AppActivate(GApplication *app, gpointer aUserData)
{
  /*Generic App variables*/
  GtkWidget *overlay, *win, *tabBox, *headerBox, *logo, *empty1;
  static GtkStringList *scenarioListItems;
  static GtkWidget *scenarioListDropDown;
  /********/
  /*Polar Injection variables*/
  static char filePath[SIZE_PATH_MAX]={0};
  sSendData *pSendData;
  sBrowseData *pBrowseData;
  static GtkWidget *piBodyBox, *piMainBox,  *piTitleBox, *piButtonBox, *piTextInBox, *piTextOutBox, *piLogoFileBox, *piLogoSendBox;
  static GtkWidget *piShiplifyBtn, *piBrowseBtn, *piSendBtn, *piRemoveBtn;
  static GtkWidget *empty2, *empty3, *empty4, *empty5, *piTitle, *labelShiplify, *labelPolar, *labelSend, *labelFileSelected, *labelFileSent, *labelFooter, *labelScenario, *labelOr, *labelRemove;
  static GtkWidget *logoBrowseCheck, *logoSendCheck, *logoShiplify;
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

  //App Scenario list
  sPolarData *polarData = (sPolarData*)malloc(sizeof(sPolarData));
  polarData->sizeFileName = SIZE_MAX_SCENARIO_NAME;
  polarData->fileName = static_cast<char*>(malloc(polarData->sizeFileName));
  strcpy(polarData->fileName, "polar.nc");
  pthread_mutex_init(&polarData->lock, nullptr);
  AppScenarioList(&scenarioListItems, &scenarioListDropDown, polarData); 

  /*Set App Thread*/
  pthread_create(&tPrIdle, nullptr, AppThreadManagement, polarData);
  pthread_detach(tPrIdle);
  /********/
  
  //Polar Injection  create boxes
  PICreateBoxes(&piBodyBox, &piMainBox, &piTitleBox, &piButtonBox, &piTextInBox, &piTextOutBox, &piLogoFileBox, &piLogoSendBox);

  //Polar Injection title
  PISetTitle(&piTitle);

  //Polar Injection logo
  PISetLogo(&logo, &logoShiplify, &logoBrowseCheck, &logoSendCheck) ;

  //Polar Injection buttons
  PISetButtons(&piShiplifyBtn, &piSendBtn, &piBrowseBtn, &piRemoveBtn) ;
 
  //Polar Injection labels
  PISetLabels(&labelFileSent, &labelFileSelected, &labelShiplify, &labelPolar, &labelSend, &empty2, &empty3, &empty4, &empty5, &labelScenario, &labelOr, &labelRemove);

  /*Polar Injection boxes*/
  PISetBoxes(&piBodyBox, &piMainBox, &piTitleBox, &piButtonBox, &piTextInBox, &piTextOutBox, &piLogoFileBox, &piLogoSendBox,//Boxes
	     &piShiplifyBtn, &piBrowseBtn, &piSendBtn, &scenarioListDropDown, &piRemoveBtn,//Buttons/Lists
	     &logoBrowseCheck, &logoSendCheck,//Logos
	     &empty2, &empty3, &empty4, &empty5, &piTitle, &labelShiplify, &labelPolar, &labelSend, &labelFileSelected, &labelFileSent, &labelScenario, &labelOr, &labelRemove//Labels
	     ); 

  /*Polar Injection Set Data Callback*/
  pBrowseData = PISetBrowsePolarData(&win, &labelFileSelected, &logoBrowseCheck, filePath);
  pSendData = PISetSendPolarData(&labelFileSent, &logoSendCheck, filePath);  
  /********/
  
  /*Polar Injection Connect Callback*/
  g_signal_connect(piShiplifyBtn, "clicked", G_CALLBACK(OpenShiplify), NULL);
  g_signal_connect(piBrowseBtn, "clicked", G_CALLBACK(BrowsePolar), pBrowseData);
  g_signal_connect(piSendBtn, "clicked", G_CALLBACK(SendPolar), pSendData);
  g_signal_connect(piRemoveBtn, "clicked", G_CALLBACK(RemovePolar), NULL);
  /********/

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

  gtk_stack_add_titled(GTK_STACK(stack), piMainBox, "tab1", "Polar Selection");
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
  labelFooter = gtk_label_new("ShipPolars v1.3 - SOMOS Project 2026 - ENSM Nantes");
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
  gtk_widget_add_css_class(powerLabel, "textIn-label");
  gtk_widget_add_css_class(rotSpeedLabel, "textIn-label");
  gtk_widget_add_css_class(saBodyBox, "textOut-label");
  //gtk_widget_add_css_class(mainBox, "back-template");
  gtk_widget_add_css_class(piTextInBox, "textIn-label");
  gtk_widget_add_css_class(piTextOutBox, "textOut-label");
  gtk_widget_add_css_class(abMainBox, "textIn-label");
  gtk_widget_add_css_class(prLeftBox, "textIn-label");
  gtk_widget_add_css_class(prMidBox, "textIn-label");
  gtk_widget_add_css_class(prRightBox, "textIn-label");
  gtk_widget_add_css_class(appBox, "back-template");
  /********/
  
  gtk_window_present (GTK_WINDOW (win));
}
