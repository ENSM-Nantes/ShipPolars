#include "app.h"
#include "button.h"

void PICreateBoxes(GtkWidget **aPiBodyBox, GtkWidget **aPiMainBox, GtkWidget **aPiHeaderBox, GtkWidget **aPiTitleBox, GtkWidget **aPiButtonBox, GtkWidget **aPiTextInBox, GtkWidget **aPiTextOutBox, GtkWidget **aPiLogoFileBox, GtkWidget **aPiLogoSendBox)
{
  /*Box*/
  *aPiMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPiHeaderBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
  *aPiTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 100);
  *aPiBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  *aPiTextInBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
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
  *aLogo = gtk_picture_new_for_filename("res/logo_ensm.png");
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

void PISetLabels(GtkWidget **aLabelFileSent, GtkWidget **aLabelFileSelected, GtkWidget **aLabelShiplify, GtkWidget **aLabelPolar, GtkWidget **aLabelSend, GtkWidget **aEmpty1, GtkWidget **aEmpty2, GtkWidget **aEmpty3) 
{
  *aLabelFileSent = gtk_label_new("  ");
  *aLabelFileSelected = gtk_label_new("  ");
  
  *aLabelShiplify = gtk_label_new("\t1 - Download your polar file from Shiplify.io      ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelShiplify), 0);
  *aLabelPolar = gtk_label_new("\t2 - Select polar file to use ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelPolar), 0);
  *aLabelSend = gtk_label_new("\t3 - Send polar file to Bridge Command ");
  gtk_label_set_xalign(GTK_LABEL(*aLabelSend), 0);  
  *aEmpty1 = gtk_label_new("                ");
  *aEmpty2 = gtk_label_new("                ");
  *aEmpty3 = gtk_label_new("                ");
}

void PISetBoxes(GtkWidget **aPiBodyBox,GtkWidget **aPiMainBox,GtkWidget **aPiHeaderBox,GtkWidget **aPiTitleBox,GtkWidget **aPiButtonBox,GtkWidget **aPiTextInBox,GtkWidget **aPiTextOutBox,GtkWidget **aPiLogoFileBox,GtkWidget **aPiLogoSendBox,//Boxes
		GtkWidget **aShiplifyBtn,GtkWidget **aBrowseBtn,GtkWidget **aSendBtn,//Buttons
		GtkWidget **aLogo,GtkWidget **aLogoBrowseCheck,GtkWidget **aLogoSendCheck,//Logos
		GtkWidget **aEmpty1,GtkWidget **aEmpty2,GtkWidget **aTitle,GtkWidget **aLabelShiplify,GtkWidget **aLabelPolar,GtkWidget **aLabelSend,GtkWidget **aLabelFileSelected,GtkWidget **aLabelFileSent//Labels
		) 
{
  gtk_box_append(GTK_BOX (*aPiHeaderBox), *aLogo);
  gtk_box_append(GTK_BOX (*aPiHeaderBox), *aEmpty1);

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

  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiHeaderBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiTitleBox);
  gtk_box_append(GTK_BOX (*aPiMainBox), *aPiBodyBox);
}

sBrowseData* PISetBrowsePolarData(GtkWidget **aWin, GtkWidget **aLabelFileSelected, GtkWidget **aLogoBrowseCheck)
{
  static sBrowseData brData = {0};
  static char filePath[SIZE_PATH_MAX] = {0};
  
  /*Browse polar data*/
  brData.win = GTK_WINDOW (*aWin);
  brData.path = filePath;
  brData.labelOut = GTK_LABEL(*aLabelFileSelected);
  brData.logo = *aLogoBrowseCheck;
  /********/

  return &brData;
}

sSendData* PISetSendPolarData(GtkWidget **aLabelFileSent, GtkWidget **aLogoSendCheck)
{
  static sSendData sdData = {0};
  static char filePath[SIZE_PATH_MAX] = {0};
  
  /*Send polar data*/
  sdData.path = filePath;
  sdData.labelOut = GTK_LABEL(*aLabelFileSent);
  sdData.logo = *aLogoSendCheck;
  /********/

  return &sdData;
}

void AppActivate(GApplication *app)
{
  sSendData *pSendData;
  sBrowseData *pBrowseData;
  GtkWidget *overlay, *win, *tabBox;
  static GtkWidget *piBodyBox, *piMainBox, *piHeaderBox, *piTitleBox, *piButtonBox, *piTextInBox, *piTextOutBox, *piLogoFileBox, *piLogoSendBox;
  static GtkWidget *shiplifyBtn, *browseBtn, *sendBtn;
  static GtkWidget *empty1, *empty2, *empty3, *title, *labelShiplify, *labelPolar, *labelSend, *labelFileSelected, *labelFileSent, *labelFooter;
  static GtkWidget *logo, *logoBrowseCheck, *logoSendCheck, *logoShiplify;
  
  /*Window*/
  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "Polar Management");
  gtk_window_set_default_size (GTK_WINDOW (win), 1920, 1200);
  gtk_window_set_resizable(GTK_WINDOW(win), TRUE);
  gtk_window_set_decorated(GTK_WINDOW(win), TRUE);
  /********/

  //Polar Injection  create boxes
  PICreateBoxes(&piBodyBox, &piMainBox, &piHeaderBox, &piTitleBox, &piButtonBox, &piTextInBox, &piTextOutBox, &piLogoFileBox, &piLogoSendBox);

  //Polar Injection title
  PISetTitle(&title);

  //Polar Injection logo
  PISetLogo(&logo, &logoShiplify, &logoBrowseCheck, &logoSendCheck) ;

  //Polar Injection buttons
  PISetButtons(&shiplifyBtn, &sendBtn, &browseBtn) ;

  //Polar Injection labels
  PISetLabels(&labelFileSent, &labelFileSelected, &labelShiplify, &labelPolar, &labelSend, &empty1, &empty2, &empty3);
  
  /*Tab menu*/
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

  gtk_stack_add_titled(GTK_STACK(stack), piMainBox, "tab1", "Polar Injection");
  gtk_stack_add_titled(GTK_STACK(stack), empty2, "tab2", "Polar Reader");

  GtkWidget *switcher = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

  tabBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(tabBox), switcher);
  gtk_box_append(GTK_BOX(tabBox), stack);  
  /********/
  
  /*Overlay*/
  overlay = gtk_overlay_new();
  gtk_window_set_child(GTK_WINDOW(win), overlay);
  gtk_overlay_set_child (GTK_OVERLAY(overlay), tabBox);
  /********/
      
  /*Set Data Callback*/
  pBrowseData = PISetBrowsePolarData(&win, &labelFileSelected, &logoBrowseCheck);
  pSendData = PISetSendPolarData(&labelFileSent, &logoSendCheck);  
  /********/
  
  /*Connect Callback*/
  g_signal_connect(shiplifyBtn, "clicked", G_CALLBACK(OpenShiplify), NULL);
  g_signal_connect(browseBtn, "clicked", G_CALLBACK(BrowsePolar), pBrowseData);
  g_signal_connect(sendBtn, "clicked", G_CALLBACK(SendPolar), pSendData);
  /********/
  
  /*Add Box*/    
  /********/
  PISetBoxes(&piBodyBox, &piMainBox, &piHeaderBox, &piTitleBox, &piButtonBox, &piTextInBox, &piTextOutBox, &piLogoFileBox, &piLogoSendBox,//Boxes
		  &shiplifyBtn, &browseBtn, &sendBtn,//Buttons
		  &logo, &logoBrowseCheck, &logoSendCheck,//Logos
		  &empty1, &empty2, &title, &labelShiplify, &labelPolar, &labelSend, &labelFileSelected, &labelFileSent//Labels
		  ); 

  //Footer overlay, display on all pages
  labelFooter = gtk_label_new("Polar Management v1.0 - SOMOS Project 2025 - ENSM Nantes");
  gtk_widget_set_halign(labelFooter, GTK_ALIGN_END);
  gtk_widget_set_valign(labelFooter, GTK_ALIGN_END);
      
  /*Add overlay*/
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), labelFooter);
  /*************/

  /*CSS*/
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "res/style.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_add_css_class(piHeaderBox, "header-label");
  gtk_widget_add_css_class(labelFooter, "footer-label");
  gtk_widget_add_css_class(title, "title-label");
  //gtk_widget_add_css_class(mainBox, "back-template");
  gtk_widget_add_css_class(piTextInBox, "textIn-label");
  gtk_widget_add_css_class(piTextOutBox, "textOut-label");
  gtk_widget_add_css_class(tabBox, "back-template");
  /********/
  
  gtk_window_present (GTK_WINDOW (win));
}
