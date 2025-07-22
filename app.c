#include "app.h"
#include "button.h"
#include "update.h"

//Global app data
sAppData gAppData={{-120,-90,-60,-30,0,30,60,90,120},{0},{0},0,0,NULL};

void PICreateBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiTitleBox, GtkWidget **aPiButtonBox, GtkWidget **aPiTextInBox, GtkWidget **aPiTextOutBox, GtkWidget **aPiLogoFileBox, GtkWidget **aPiLogoSendBox)
{
  /*Box*/
  *aPiMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPiTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 100);
  *aPiBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  *aPiTextInBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);
  *aPiTextOutBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);
  *aPiButtonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
  *aPiLogoFileBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  *aPiLogoSendBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

  gtk_box_set_homogeneous (GTK_BOX(*aPiTextInBox), TRUE);
  gtk_widget_set_halign(*aPiTextInBox, GTK_ALIGN_START);
  gtk_widget_set_valign(*aPiTextInBox, GTK_ALIGN_START);
  gtk_box_set_homogeneous (GTK_BOX(*aPiTextOutBox), TRUE);
  gtk_widget_set_halign(*aPiTextOutBox, GTK_ALIGN_START);
  gtk_widget_set_valign(*aPiTextOutBox, GTK_ALIGN_START);
  gtk_widget_set_margin_top(*aPiTextOutBox, 20);
}

void PISetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("Polar Injection for SOMOS Project");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 80);
}

void PISetLogo(GtkWidget **aLogo, GtkWidget **aLogoShiplify, GtkWidget **aLogoBrowseCheck, GtkWidget **aLogoSendCheck) 
{ 
  //*aLogo = gtk_picture_new_for_filename("res/logo_ensm.png");
  *aLogoShiplify = gtk_picture_new_for_filename("res/d-v2.png");
  *aLogoBrowseCheck = gtk_picture_new();
  *aLogoSendCheck = gtk_picture_new();
}

void PISetButtons(GtkWidget **aShiplifyBtn, GtkWidget **aSendBtn, GtkWidget **aBrowseBtn) 
{ 
  *aShiplifyBtn = gtk_button_new_with_label ("Shiplify");
  *aSendBtn = gtk_button_new_with_label ("Send");  
  *aBrowseBtn = gtk_button_new_with_label ("Browse...");
}

void PISetLabels(GtkWidget **aLabelFileSent, GtkWidget **aLabelFileSelected, GtkWidget **aLabelShiplify, GtkWidget **aLabelPolar, GtkWidget **aLabelSend, GtkWidget **aEmpty2, GtkWidget **aEmpty3) 
{
  *aLabelFileSent = gtk_label_new("  ");
  *aLabelFileSelected = gtk_label_new("  ");
  
  *aLabelShiplify = gtk_label_new("\t1 - Download your polar file from Shiplify.io      ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelShiplify), 0);
  *aLabelPolar = gtk_label_new("\t2 - Select polar file to use ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelPolar), 0);
  *aLabelSend = gtk_label_new("\t3 - Send polar file to Bridge Command ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelSend), 0);  
  *aEmpty2 = gtk_label_new("                ");
  *aEmpty3 = gtk_label_new("                ");
}

void PISetBoxes(GtkWidget **aPiBodyBox,GtkWidget **aPiMainBox,GtkWidget **aPiTitleBox,GtkWidget **aPiButtonBox,GtkWidget **aPiTextInBox,GtkWidget **aPiTextOutBox,GtkWidget **aPiLogoFileBox,GtkWidget **aPiLogoSendBox,//Boxes
		GtkWidget **aShiplifyBtn,GtkWidget **aBrowseBtn,GtkWidget **aSendBtn,//Buttons
	        GtkWidget **aLogoBrowseCheck,GtkWidget **aLogoSendCheck,//Logos
		GtkWidget **aEmpty2,GtkWidget **aTitle,GtkWidget **aLabelShiplify,GtkWidget **aLabelPolar,GtkWidget **aLabelSend,GtkWidget **aLabelFileSelected,GtkWidget **aLabelFileSent//Labels
		) 
{
  gtk_box_append(GTK_BOX (*aPiTitleBox), *aTitle);

  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelShiplify);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelPolar);
  gtk_box_append(GTK_BOX (*aPiTextInBox), *aLabelSend);

  gtk_box_append(GTK_BOX (*aPiLogoFileBox), *aLogoBrowseCheck);
  gtk_box_append(GTK_BOX (*aPiLogoFileBox), *aLabelFileSelected);

  gtk_box_append(GTK_BOX (*aPiLogoSendBox), *aLogoSendCheck);
  gtk_box_append(GTK_BOX (*aPiLogoSendBox), *aLabelFileSent);
  
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aEmpty2);
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aPiLogoFileBox);
  gtk_box_append(GTK_BOX (*aPiTextOutBox), *aPiLogoSendBox);
  
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aShiplifyBtn);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aBrowseBtn);
  gtk_box_append(GTK_BOX (*aPiButtonBox), *aSendBtn);
  
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiTextInBox);
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiButtonBox);
  gtk_box_append(GTK_BOX (*aPiBodyBox), *aPiTextOutBox);

  //gtk_box_append(GTK_BOX (*aPiMainBox), *aPiHeaderBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiTitleBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiBodyBox);
}

sBrowseData* PISetBrowsePolarData(GtkWidget **aWin, GtkWidget **aLabelFileSelected, GtkWidget **aLogoBrowseCheck, char *aFilePath)
{
  static sBrowseData brData = {0};
  
  /*Browse polar data*/
  brData.win = GTK_WINDOW (*aWin);
  brData.path = aFilePath;
  brData.labelOut = GTK_LABEL(*aLabelFileSelected);
  brData.logo = *aLogoBrowseCheck;
  /********/

  return &brData;
}

sSendData* PISetSendPolarData(GtkWidget **aLabelFileSent, GtkWidget **aLogoSendCheck,char *aFilePath)
{
  static sSendData sdData = {0};
  
  /*Send polar data*/
  sdData.path = aFilePath;
  sdData.labelOut = GTK_LABEL(*aLabelFileSent);
  sdData.logo = *aLogoSendCheck;
  /********/

  return &sdData;
}

void PRCreateBoxes(GtkWidget **aPrBodyBox, GtkWidget **aPrMainBox, GtkWidget **aPrTitleBox)
{
  /*Box*/
  *aPrMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPrTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPrBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
}

void PRSetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("Polar Reader for SOMOS Project");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 10);
}

void PRSetBoxes(GtkWidget **aPrBodyBox,GtkWidget **aPrMainBox,GtkWidget **aPrTitleBox,//Boxes
	        GtkWidget **aTitle,//Labels
		GtkWidget **aArea//Cairo
		) 
{
  gtk_box_append(GTK_BOX (*aPrTitleBox), *aTitle);
  gtk_box_append(GTK_BOX (*aPrBodyBox), *aArea);
  
  gtk_box_append(GTK_BOX (*aPrMainBox), *aPrTitleBox);
  gtk_box_append(GTK_BOX (*aPrMainBox), *aPrBodyBox);
}

void PRDrawPoint(cairo_t *aCr, float aX, double aY, int aSize=1)
{
    float radius=5*aSize;
    cairo_arc(aCr, aX, aY, radius, 0, 2*M_PI);
    cairo_fill(aCr);
}

static void PRDrawPolar(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData)
{
  float cx=0, cy=0, rMax=0, x=0, y=0, tx=0, ty=0, fly=0, flx=0, oYx=0, oYy=0, fosy=0;
  float fXx=0, fXy=0, fYx=0, fYy=0, rad=0, rStart=0, offset=0, oXx=0, oXy=0, fosx=0;
  char angleLabel[8]={0}, forceLabel[32]={0};

  sAppData *data = (sAppData*)aData;
  float *forceLegend = data->forceLegend;
  float *forceX = data->forceX;
  float *forceY = data->forceY;
  float fOsX = data->fOsX;
  float fOsY = data->fOsY;
  
  cx = aWidth/2;
  cy = aHeight/2;
  rMax = RADIUS_MAX;
  
  //White background
  //cairo_set_source_rgb(aCr, 1, 1, 1);
  //cairo_paint(aCr);

  //Polar colour
  cairo_set_source_rgb(aCr, 0.6, 0.6, 0.8);
  cairo_set_line_width(aCr, 2.0);

  //Set font
  cairo_select_font_face(aCr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(aCr, 14);

  //Draw circles
  for (int r=1; r <= FORCE_LINE_COUNT; r++)
    {
      cairo_set_source_rgb(aCr, 0.6, 0.6, 0.8);
      cairo_set_line_width(aCr, 2.0);
      if(r == ((FORCE_LINE_COUNT+1)/2))
	{
	  cairo_set_source_rgb(aCr, 0.3, 0.8, 0.6);
	  cairo_set_line_width(aCr, 3.0);
	}
      cairo_arc(aCr, cx, cy, r*(rMax/(FORCE_LINE_COUNT)), -M_PI_2, M_PI_2);      
      cairo_stroke(aCr);      
    }

  //Set text force value
  for (int r=1; r <= FORCE_LINE_COUNT; r++)
    {
      fly= cy + (r*(rMax/FORCE_LINE_COUNT));
      flx = cx - 80;

      snprintf(forceLabel, sizeof(forceLabel), "%.1f kN", forceLegend[r-1]);
      cairo_move_to(aCr, flx, fly); 
      cairo_show_text(aCr, forceLabel);

    }

  //Old values to trace between 2 points
  oXx=cx;
  oXy=cy;
  
  //Draw polar and angle
  for (int i=0,j=0; i <= 190,j<ANGLE_STEP_COUNT;i+=ANGLE_STEP_DEGRES,j++)
    {
      rad = i * M_PI/180;
      x = cx + rMax*sin(rad);
      y = cy + rMax*cos(rad);

      //Polar web
      cairo_set_source_rgb(aCr, 0.6, 0.6, 0.8);
      cairo_move_to(aCr, cx, cy);
      cairo_line_to(aCr, x, y);
      cairo_stroke(aCr);

      //Text angle position
      tx = cx + (rMax+15)*sin(rad);
      ty = cy - (rMax+15)*cos(rad);
      snprintf(angleLabel, sizeof(angleLabel), "%d°", i);
      cairo_move_to(aCr, tx - 10, ty + 4); 
      cairo_show_text(aCr, angleLabel);

      //Draw Point to polar view
      /*Zero is not right in the middle*/
      offset=(rMax/FORCE_LINE_COUNT)/2;
      rStart=(rMax/2)+offset;
      
      fXx = cx + (((rMax/2 - offset)*forceX[j]/FORCE_MAX)+(rStart))*sin(rad);
      fXy = cy - (((rMax/2 - offset)*forceX[j]/FORCE_MAX)+(rStart))*cos(rad);
      cairo_set_source_rgb(aCr, 1, 0.5, 0.5);
      PRDrawPoint(aCr, fXx, fXy);
      
      cairo_move_to(aCr, oXx, oXy);
      cairo_line_to(aCr, fXx, fXy);
      cairo_stroke(aCr);
      oXx=fXx;
      oXy=fXy;
    }
  
  //Draw OwnShip curseur
  cairo_set_source_rgb(aCr, 0.2, 0.2, 0.8);
  rad=(data->osMsg.GetAWA())*M_PI/180;
  fosx = cx + (((rMax/2 - offset)*fOsX/FORCE_MAX)+(rStart))*sin(rad);
  fosy = cy - (((rMax/2 - offset)*fOsX/FORCE_MAX)+(rStart))*cos(rad);
  PRDrawPoint(aCr, fosx, fosy, 2);
}

gboolean PRWaitToStart(gpointer aUserData)
{
  static gboolean isStarted = false;

  if(!isStarted)
    {
      //Get nc file
      if(0 == gAppData.sails.Open("polar.nc", "TotalSails_X", "TotalSails_Y"))
	{
	  gAppData.sails.Init("STW_kt", "TWS_kt", "TWA_deg");

	  //Get Wind and speed from BC
	  if(0 == gAppData.hCom.Connect(ENET_SERVER_HOST, 18304))
	    {
	      g_timeout_add(100, UpdateFromBC, &gAppData);
	      g_timeout_add(500, UpdatePolar, &gAppData);
	      isStarted = true;
	    }
	}
      else
	std::cout << "No polar file to read !" << std::endl;

    }
  return true;
}

void AbCreateBoxes(GtkWidget **aAbBodyBox, GtkWidget **aAbMainBox, GtkWidget **aAbTitleBox)
{
  /*Box*/
  *aAbMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aAbTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aAbBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
}

void AbSetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("About Polar Management");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 100);
}


void AbSetBoxes(GtkWidget **aAbBodyBox,GtkWidget **aAbMainBox,GtkWidget **aAbTitleBox,//Boxes
	        GtkWidget **aTitle, GtkWidget **aInfos//Labels
		) 
{
  gtk_box_append(GTK_BOX (*aAbTitleBox), *aTitle);
  
  gtk_box_append(GTK_BOX (*aAbBodyBox), *aInfos);
  
  gtk_box_append(GTK_BOX (*aAbMainBox), *aAbTitleBox);
  gtk_box_append(GTK_BOX (*aAbMainBox), *aAbBodyBox);
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
  static GtkWidget *prBodyBox, *prMainBox,  *prTitleBox;
  static GtkWidget *prTitle;
  static GtkWidget *prArea;
  /********/
  /*About variables*/
  static GtkWidget *abBodyBox, *abMainBox,  *abTitleBox;
  static GtkWidget *abTitle, *abInfos;
  /********/
  
  /*Window*/
  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "Polar Management");
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
  PRCreateBoxes(&prBodyBox, &prMainBox, &prTitleBox);

  //Polar Reader title
  PRSetTitle(&prTitle);

  /*Polar Reader core*/
  
  //Cairo area drawing 
  prArea = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (prArea), 900);
  gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (prArea), 800);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(prArea), PRDrawPolar, &gAppData, NULL);
  gtk_widget_set_margin_start(prArea, 500);  
  gAppData.area = prArea;

  //Idle
  g_timeout_add(1000, PRWaitToStart, NULL);
  
  /*Polar Reader boxes*/
  PRSetBoxes(&prBodyBox,&prMainBox,&prTitleBox,//Boxes
	     &prTitle,//Labels
	     &prArea//Cairo
	     );

  //About create boxes
  AbCreateBoxes(&abBodyBox, &abMainBox, &abTitleBox);

  //About title
  AbSetTitle(&abTitle);
  abInfos = gtk_label_new("\tName : Polar Management\n\r\tVersion : v1.0\n\r\tProject : SOMOS Project 2025\n\r\tOwner : ENSM-Nantes\n\r\tContact : florent.richard@supmaritime.fr\n\r\tWebsite : somos-project.fr");
  
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
  gtk_widget_add_css_class(appBox, "back-template");
  /********/


  
  gtk_window_present (GTK_WINDOW (win));
}
