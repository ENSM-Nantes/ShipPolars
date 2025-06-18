#include "app.h"
#include "button.h"

void AppActivate(GApplication *app)
{
  GtkWidget *overlay;
  GtkWidget *win, *bodyBox, *mainBox, *headerBox, *titleBox, *buttonBox, *textInBox, *textOutBox, *logoFileBox, *logoSendBox;
  GtkWidget *shiplifyBtn, *browseBtn, *sendBtn;
  GtkWidget *empty1, *empty2, *title, *labelShiplify, *labelPolar, *labelSend, *labelFileSelected, *labelFileSent, *labelFooter;
  GtkWidget *logo, *logoBrowseCheck, *logoSendCheck, *logoShiplify;

  static char filePath[SIZE_PATH_MAX] = {0};
  static sBrowseData brData = {0};
  static sSendData sdData = {0};
  
  /*Window*/
  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "Polar Injection");
  gtk_window_set_default_size (GTK_WINDOW (win), 1920, 1200);
  gtk_window_set_resizable(GTK_WINDOW(win), TRUE);
  gtk_window_set_decorated(GTK_WINDOW(win), TRUE);
  /********/

  /*Box*/
  mainBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  headerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 100);
  titleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 100);
  bodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  textInBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
  textOutBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);
  buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
  logoFileBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  logoSendBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

  gtk_box_set_homogeneous (GTK_BOX(textInBox), TRUE);
  gtk_widget_set_halign(textInBox, GTK_ALIGN_START);
  gtk_widget_set_valign(textInBox, GTK_ALIGN_START);
  gtk_box_set_homogeneous (GTK_BOX(textOutBox), TRUE);
  gtk_widget_set_halign(textOutBox, GTK_ALIGN_START);
  gtk_widget_set_valign(textOutBox, GTK_ALIGN_START);
  gtk_widget_set_margin_top(textOutBox, 20);
  /********/  

  /*Overlay*/
  overlay = gtk_overlay_new();
  gtk_window_set_child(GTK_WINDOW(win), overlay);
  gtk_overlay_set_child (GTK_OVERLAY(overlay), mainBox);
  /********/
  
  
  /*Logo*/
  logo = gtk_picture_new_for_filename("res/logo_ensm.png");
  logoShiplify = gtk_picture_new_for_filename("res/d-v2.png");
  logoBrowseCheck = gtk_picture_new();
  logoSendCheck = gtk_picture_new();
  /********/
  
  /*Title*/
  title = gtk_label_new("Polar Injection for SOMOS Project");
  gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(title, 80);
  /********/
    
  /*Buttons*/
  shiplifyBtn = gtk_button_new_with_label ("Shiplify");
  sendBtn = gtk_button_new_with_label ("Send");  
  browseBtn = gtk_button_new_with_label ("Browse...");
  /********/
  
  /*Labels*/
  labelFileSent = gtk_label_new("  ");
  labelFileSelected = gtk_label_new("  ");
  labelFooter = gtk_label_new("Polar Injection v1.0 - SOMOS Project 2025 - ENSM Nantes");
  gtk_widget_set_halign(labelFooter, GTK_ALIGN_END);
  gtk_widget_set_valign(labelFooter, GTK_ALIGN_END);

  labelShiplify = gtk_label_new("\t1 - Download your polar file from Shiplify.io      ");
  gtk_label_set_xalign(GTK_LABEL(labelShiplify), 0);
  labelPolar = gtk_label_new("\t2 - Select polar file to use ");
  gtk_label_set_xalign(GTK_LABEL(labelPolar), 0);
  labelSend = gtk_label_new("\t3 - Send polar file to Bridge Command ");
  gtk_label_set_xalign(GTK_LABEL(labelSend), 0);  
  empty1 = gtk_label_new("                ");
  empty2 = gtk_label_new("                ");
  /********/

  /*CSS*/
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "res/style.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_add_css_class(headerBox, "header-label");
  gtk_widget_add_css_class(labelFooter, "footer-label");
  gtk_widget_add_css_class(title, "title-label");
  gtk_widget_add_css_class(mainBox, "back-template");
  gtk_widget_add_css_class(textInBox, "textIn-label");
  gtk_widget_add_css_class(textOutBox, "textOut-label");
  /********/
  
  /*Set Data Callback*/

  /*Browse polar data*/
  brData.win = GTK_WINDOW (win);
  brData.path = filePath;
  brData.labelOut = GTK_LABEL(labelFileSelected);
  brData.logo = logoBrowseCheck;
  /********/

  /*Send polar data*/
  sdData.path = filePath;
  sdData.labelOut = GTK_LABEL(labelFileSent);
  sdData.logo = logoSendCheck;
  /********/
  
  /********/
  
  /*Connect Callback*/
  g_signal_connect(shiplifyBtn, "clicked", G_CALLBACK(OpenShiplify), NULL);
  g_signal_connect(browseBtn, "clicked", G_CALLBACK(BrowsePolar), &brData);
  g_signal_connect(sendBtn, "clicked", G_CALLBACK(SendPolar), &sdData);
  /********/

  /*Add Box*/    
  gtk_box_append(GTK_BOX (headerBox), logo);
  gtk_box_append(GTK_BOX (headerBox), empty1);

  gtk_box_append(GTK_BOX (titleBox), title);

  gtk_box_append(GTK_BOX (textInBox), labelShiplify);
  gtk_box_append(GTK_BOX (textInBox), labelPolar);
  gtk_box_append(GTK_BOX (textInBox), labelSend);

  gtk_box_append(GTK_BOX (logoFileBox), logoBrowseCheck);
  gtk_box_append(GTK_BOX (logoFileBox), labelFileSelected);

  gtk_box_append(GTK_BOX (logoSendBox), logoSendCheck);
  gtk_box_append(GTK_BOX (logoSendBox), labelFileSent);
  
  gtk_box_append(GTK_BOX (textOutBox), empty2);
  gtk_box_append(GTK_BOX (textOutBox), logoFileBox);
  gtk_box_append(GTK_BOX (textOutBox), logoSendBox);
  
  gtk_box_append(GTK_BOX (buttonBox), shiplifyBtn);
  gtk_box_append(GTK_BOX (buttonBox), browseBtn);
  gtk_box_append(GTK_BOX (buttonBox), sendBtn);
  
  gtk_box_append(GTK_BOX (bodyBox), textInBox);
  gtk_box_append(GTK_BOX (bodyBox), buttonBox);
  gtk_box_append(GTK_BOX (bodyBox), textOutBox);

  gtk_box_append(GTK_BOX (mainBox), headerBox);
  gtk_box_append(GTK_BOX (mainBox), titleBox);
  gtk_box_append(GTK_BOX (mainBox), bodyBox);

  /********/

  /*Add overlay*/
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), labelFooter);
  /*************/

  
  gtk_window_present (GTK_WINDOW (win));
}
