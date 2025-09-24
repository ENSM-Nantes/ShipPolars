#include "app.h"
#include "button.h"
#include "update.h"
#include "pthread.h"
#include "about.h"

//Global app data
sPrData gPrData={{-120,-90,-60,-30,0,30,60,90,120},{0},{0},0,0,NULL,NULL,NULL,NULL};
sAppData gAppData;


static void *AppWaitToStart(void *aData)
{
  static bool isStarted = false;

  while(!isStarted)
    {
      //Get nc file
      if(0 == gAppData.sails.Open("polar.nc", "TotalSails_X", "TotalSails_Y"))
	{
	  gAppData.sails.Init("STW_kt", "TWS_kt", "TWA_deg");

	  //Get Wind and speed from BC
	  if(0 == gAppData.hCom.Connect(ENET_SERVER_HOST, 18304))
	    {
	      g_timeout_add(100, UpdateFromBC, &gAppData);
	      g_timeout_add(100, UpdatePolar, &gAppData);
	      isStarted = true;
	    }
	}
      else
	std::cout << "No polar file to read !" << std::endl;

      sleep(2);
    }

  return NULL;
}



void AppActivate(GApplication *app, gpointer aUserData)
{
  /*Generic App variables*/
  GtkWidget *overlay, *win, *tabBox, *headerBox, *logo, *empty1;
  /********/
  /*Polar Injection variables*/
  static char filePath[SIZE_PATH_MAX] = {0};
  sSendData *pSendData;
  sBrowseData *pBrowseData;
  static GtkWidget *piBodyBox, *piMainBox,  *piTitleBox, *piButtonBox, *piTextInBox, *piTextOutBox, *piLogoFileBox, *piLogoSendBox;
  static GtkWidget *piShiplifyBtn, *piBrowseBtn, *piSendBtn;
  static GtkWidget *empty2, *empty3, *piTitle, *labelShiplify, *labelPolar, *labelSend, *labelFileSelected, *labelFileSent, *labelFooter;
  static GtkWidget *logoBrowseCheck, *logoSendCheck, *logoShiplify;
  /********/
  /*Polar Reader variables*/
  static GtkWidget *prBodyBox, *prMainBox, *prTitleBox, *prLeftBox, *prMidBox, *prRightBox;
  static GtkWidget *prTitle;
  static GtkWidget *labelPolarX, *labelPolarY, *labelVector, *labelAngleForce;
  static GtkWidget *prPolarXArea, *prPolarYArea, *prSumArea;
  pthread_t tPrIdle; 
  /********/
  /*About variables*/
  static GtkWidget *abBodyBox, *abMainBox,  *abTitleBox;
  static GtkWidget *abTitle, *abInfos;
  /********/
  
  /*Window*/
  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "Polar Manager");
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


  /*Set App Thread*/
  pthread_create(&tPrIdle, NULL, AppWaitToStart, NULL);
  pthread_detach(tPrIdle);
  /********/
  
  //Polar Injection  create boxes
  PICreateBoxes(&piBodyBox, &piMainBox, &piTitleBox, &piButtonBox, &piTextInBox, &piTextOutBox, &piLogoFileBox, &piLogoSendBox);

  //Polar Injection title
  PISetTitle(&piTitle);

  //Polar Injection logo
  PISetLogo(&logo, &logoShiplify, &logoBrowseCheck, &logoSendCheck) ;

  //Polar Injection buttons
  PISetButtons(&piShiplifyBtn, &piSendBtn, &piBrowseBtn) ;

  //Polar Injection labels
  PISetLabels(&labelFileSent, &labelFileSelected, &labelShiplify, &labelPolar, &labelSend, &empty2, &empty3);

  /*Polar Injection boxes*/
  PISetBoxes(&piBodyBox, &piMainBox, &piTitleBox, &piButtonBox, &piTextInBox, &piTextOutBox, &piLogoFileBox, &piLogoSendBox,//Boxes
	     &piShiplifyBtn, &piBrowseBtn, &piSendBtn,//Buttons
	     &logoBrowseCheck, &logoSendCheck,//Logos
	     &empty2, &piTitle, &labelShiplify, &labelPolar, &labelSend, &labelFileSelected, &labelFileSent//Labels
	     ); 

  /*Polar Injection Set Data Callback*/
  pBrowseData = PISetBrowsePolarData(&win, &labelFileSelected, &logoBrowseCheck, filePath);
  pSendData = PISetSendPolarData(&labelFileSent, &logoSendCheck, filePath);  
  /********/
  
  /*Polar Injection Connect Callback*/
  g_signal_connect(piShiplifyBtn, "clicked", G_CALLBACK(OpenShiplify), NULL);
  g_signal_connect(piBrowseBtn, "clicked", G_CALLBACK(BrowsePolar), pBrowseData);
  g_signal_connect(piSendBtn, "clicked", G_CALLBACK(SendPolar), pSendData);
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
  abInfos = gtk_label_new("\tName : Polar Management\n\r\tVersion : v1.1\n\r\tProject : SOMOS Project 2025\n\r\tOwner : ENSM-Nantes\n\r\tContact : florent.richard@supmaritime.fr\n\r\tWebsite : somos-project.fr");
  
  /*About boxes*/
  AbSetBoxes(&abBodyBox,&abMainBox,&abTitleBox,//Boxes
	     &abTitle,&abInfos//Labels
	     );
  
  /*Tab menu*/
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

  gtk_stack_add_titled(GTK_STACK(stack), piMainBox, "tab1", "Polar Injection");
  gtk_stack_add_titled(GTK_STACK(stack), prMainBox, "tab2", "Polar Reader");
  gtk_stack_add_titled(GTK_STACK(stack), abMainBox, "tab3", "About");
  
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
  labelFooter = gtk_label_new("Polar Management v1.0 - SOMOS Project 2025 - ENSM Nantes");
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
