#include "app.h"
#include "sail.h"
#include "button.h"

void SaCreateBoxes(GtkWidget **aSaBodyBox, GtkWidget **aSaMainBox, GtkWidget **aSaTitleBox)
{
  /*Box*/
  *aSaMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aSaTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aSaBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
}

void SaSetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("Sail Management");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 100);
}

gboolean DisplaySpeedRotor(gpointer aData)
{
  sRotInfos *pRotInfos = static_cast<sRotInfos*>(aData);
  sAppData *pAppData = static_cast<sAppData*>(pRotInfos->appData);

  float speed = pAppData->osMsg.GetRotSpeed();
  std::string speedStr;
  speedStr = "Rotor rotation speed : (rpm) : " + std::to_string(speed);
  
  gtk_label_set_text(GTK_LABEL(pRotInfos->rotSpeedLabel), speedStr.c_str());
  
  return TRUE;
}

void SaSetRotorBox(GtkWidget **aRotorBox, GtkWidget **aOnOffBtn, GtkWidget **aChangeRotationBtn, sRotInfos *aRotInfos)
{
  static GtkWidget *onOffBox, *changeRotationBox;

  onOffBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  changeRotationBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  
  *aOnOffBtn = gtk_button_new_with_label ("Power On/off");
  *aChangeRotationBtn = gtk_button_new_with_label ("Change rotation direction");  

  gtk_widget_set_hexpand(*aOnOffBtn, FALSE);
  gtk_widget_set_vexpand(*aChangeRotationBtn, FALSE);
  
  GtkWidget *empty1 = gtk_label_new(" ");
  GtkWidget *empty2 = gtk_label_new(" ");
  GtkWidget *empty3 = gtk_label_new(" ");
  GtkWidget *empty4 = gtk_label_new(" ");
  GtkWidget *empty5 = gtk_label_new(" ");
  GtkWidget *empty6 = gtk_label_new(" ");
  GtkWidget *empty7 = gtk_label_new(" ");
  GtkWidget *empty8 = gtk_label_new(" ");
  GtkWidget *empty9 = gtk_label_new(" ");
  GtkWidget *empty10 = gtk_label_new(" ");
  GtkWidget *empty11 = gtk_label_new(" ");
  
  gtk_box_append(GTK_BOX (onOffBox), *aOnOffBtn);
  gtk_box_append(GTK_BOX (onOffBox), aRotInfos->logoCheck); 
  gtk_box_append(GTK_BOX (onOffBox), aRotInfos->powerLabel);
  gtk_box_append(GTK_BOX (onOffBox), empty7);
  gtk_box_append(GTK_BOX (onOffBox), empty8);

  gtk_box_append(GTK_BOX (changeRotationBox), *aChangeRotationBtn);
  gtk_box_append(GTK_BOX (changeRotationBox),  aRotInfos->logoRot);
  gtk_box_append(GTK_BOX (changeRotationBox), aRotInfos->rotSpeedLabel);
  gtk_box_append(GTK_BOX (changeRotationBox), empty10);
  gtk_box_append(GTK_BOX (changeRotationBox), empty11);
  
  gtk_box_append(GTK_BOX (*aRotorBox), empty1);
  gtk_box_append(GTK_BOX (*aRotorBox), empty2);
  gtk_box_append(GTK_BOX (*aRotorBox), onOffBox);
  gtk_box_append(GTK_BOX (*aRotorBox), empty3);
  gtk_box_append(GTK_BOX (*aRotorBox), empty4);
  gtk_box_append(GTK_BOX (*aRotorBox), changeRotationBox);
  gtk_box_append(GTK_BOX (*aRotorBox), empty5);
  gtk_box_append(GTK_BOX (*aRotorBox), empty6);

//gtk_box_set_homogeneous (GTK_BOX(onOffBox), TRUE);
  gtk_widget_set_halign(onOffBox, GTK_ALIGN_START);
  gtk_widget_set_valign(onOffBox, GTK_ALIGN_START);

//gtk_box_set_homogeneous (GTK_BOX(changeRotationBox), TRUE);
  gtk_widget_set_halign(changeRotationBox, GTK_ALIGN_START);
  gtk_widget_set_valign(changeRotationBox, GTK_ALIGN_START);
 
  g_signal_connect(*aOnOffBtn, "clicked", G_CALLBACK(OnOffRotor), aRotInfos);
  g_signal_connect(*aChangeRotationBtn, "clicked", G_CALLBACK(ChangeRot), aRotInfos);

  g_timeout_add(1000, DisplaySpeedRotor, aRotInfos);
}

void SaSetBoxes(GtkWidget **aSaBodyBox,GtkWidget **aSaMainBox,GtkWidget **aSaTitleBox,//Boxes
	        GtkWidget **aTitle, GtkWidget **aPowerLabel, GtkWidget **aRotSpeedLabel,//Labels
		GtkWidget **aLogoRotorCheck, GtkWidget **aLogoRotorDir,
		void *aAppData, sRotInfos *aRotInfos 
		) 
{
  static GtkWidget *sailTabBox, *rotorBox, *sail2Box, *sail3Box, *sail4Box, *sail5Box, *sail6Box;
  static GtkWidget *onOffBtn, *changeRotationBtn;

  gtk_box_append(GTK_BOX (*aSaTitleBox), *aTitle);

  rotorBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  sail2Box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  sail3Box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  sail4Box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  sail5Box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  sail6Box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_box_set_homogeneous (GTK_BOX(rotorBox), TRUE);
  gtk_widget_set_halign(rotorBox, GTK_ALIGN_START);
  gtk_widget_set_valign(rotorBox, GTK_ALIGN_START);

  
  *aPowerLabel = gtk_label_new(" ");
  aRotInfos->powerLabel = *aPowerLabel;
  
  *aLogoRotorCheck = gtk_picture_new_for_filename("res/cross.png");
  aRotInfos->logoCheck = *aLogoRotorCheck;

  *aRotSpeedLabel = gtk_label_new(" ");
  aRotInfos->rotSpeedLabel = *aRotSpeedLabel;
  
  *aLogoRotorDir = gtk_picture_new_for_filename("res/arrow_rot_right.png");
  aRotInfos->logoRot = *aLogoRotorDir;

  
  //Rotor section
  SaSetRotorBox(&rotorBox, &onOffBtn, &changeRotationBtn, aRotInfos);
  
  /*Tab menu*/
  GtkWidget *stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

  gtk_stack_add_titled(GTK_STACK(stack), rotorBox, "tab1", "\t\t\tRotor\t\t\t");
  gtk_stack_add_titled(GTK_STACK(stack), sail2Box, "tab2", "\t\t\tSail 2\t\t\t");
  gtk_stack_add_titled(GTK_STACK(stack), sail3Box, "tab3", "\t\t\tSail 3\t\t\t");
  gtk_stack_add_titled(GTK_STACK(stack), sail4Box, "tab4", "\t\t\tSail 4\t\t\t");
  gtk_stack_add_titled(GTK_STACK(stack), sail5Box, "tab5", "\t\t\tSail 5\t\t\t");
  gtk_stack_add_titled(GTK_STACK(stack), sail6Box, "tab6", "\t\t\tSail 6\t\t\t");
  
  GtkWidget *switcher = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));

  gtk_widget_set_halign (GTK_WIDGET(switcher), GTK_ALIGN_START);
  gtk_widget_set_valign (GTK_WIDGET(switcher), GTK_ALIGN_START);
  
  sailTabBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_box_append(GTK_BOX(sailTabBox), switcher);
  gtk_box_append(GTK_BOX(sailTabBox), stack);  

  gtk_box_append(GTK_BOX(*aSaBodyBox), sailTabBox);  
  
  gtk_box_append(GTK_BOX (*aSaMainBox), *aSaTitleBox);
  gtk_box_append(GTK_BOX (*aSaMainBox), *aSaBodyBox);
}



