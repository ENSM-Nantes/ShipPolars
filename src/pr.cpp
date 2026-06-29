#include "pr.h"
#include "app.h"

void PRCreateBoxes(GtkWidget **aPrBodyBox, GtkWidget **aPrMainBox, GtkWidget **aPrTitleBox, GtkWidget **aPrLeftBox, GtkWidget **aPrMidBox, GtkWidget **aPrRightBox)
{
  /*Box*/
  *aPrMainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPrTitleBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPrBodyBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  *aPrLeftBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  *aPrMidBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
  *aPrRightBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
}

void PRSetTitle(GtkWidget **aTitle)
{
  *aTitle = gtk_label_new("Polar Reader for SOMOS Project");
  gtk_widget_set_halign(*aTitle, GTK_ALIGN_CENTER);
  gtk_widget_set_margin_bottom(*aTitle, 10);
}

void PRSetLabels(GtkWidget **aLabelPolarX, GtkWidget **aLabelPolarY, GtkWidget **aLabelVector, GtkWidget **aLabelAngleForce) 
{
  *aLabelPolarX = gtk_label_new("\t\t Axial Polar");
  gtk_label_set_xalign(GTK_LABEL(*aLabelPolarX), 0);
  *aLabelPolarY = gtk_label_new("\t\t\t\t\tLateral Polar");
  gtk_label_set_xalign(GTK_LABEL(*aLabelPolarY), 0);
  *aLabelVector = gtk_label_new("\tVectorial Sum");
  gtk_label_set_xalign(GTK_LABEL(*aLabelVector), 0);
  *aLabelAngleForce = gtk_label_new("\n\n\n\n\tForce : \n\n\tAngle :");
  gtk_label_set_xalign(GTK_LABEL(*aLabelAngleForce), 0);
}

void PRSetBoxes(GtkWidget **aPrBodyBox, GtkWidget **aPrMainBox, GtkWidget **aPrTitleBox, GtkWidget **aPrLeftBox, GtkWidget **aPrMidBox, GtkWidget **aPrRightBox,//Boxes
	        GtkWidget **aTitle, GtkWidget **aLabelPolarX, GtkWidget **aLabelPolarY, GtkWidget **aLabelVector, GtkWidget **aLabelAngleForce,//Labels
		GtkWidget **aAreaX, GtkWidget **aAreaY, GtkWidget **aAreaSum//Cairo
		) 
{
  gtk_box_append(GTK_BOX (*aPrTitleBox), *aTitle);

  gtk_box_append(GTK_BOX (*aPrMidBox), *aLabelVector);
  gtk_box_append(GTK_BOX (*aPrMidBox), *aLabelAngleForce);
  gtk_box_append(GTK_BOX (*aPrMidBox), *aAreaSum);
  
  gtk_box_append(GTK_BOX (*aPrLeftBox), *aLabelPolarX);
  gtk_box_append(GTK_BOX (*aPrLeftBox), *aAreaX);
    
  gtk_box_append(GTK_BOX (*aPrRightBox), *aLabelPolarY);
  gtk_box_append(GTK_BOX (*aPrRightBox), *aAreaY);

  gtk_box_append(GTK_BOX (*aPrBodyBox), *aPrLeftBox);
  gtk_box_append(GTK_BOX (*aPrBodyBox), *aPrMidBox);
  gtk_box_append(GTK_BOX (*aPrBodyBox), *aPrRightBox);
  
  gtk_box_append(GTK_BOX (*aPrMainBox), *aPrTitleBox);
  gtk_box_append(GTK_BOX (*aPrMainBox), *aPrBodyBox);
}

void PRDrawPoint(cairo_t *aCr, float aX, double aY, int aSize)
{
  float radius=5*aSize;
  cairo_arc(aCr, aX, aY, radius, 0, 2*M_PI);
  cairo_fill(aCr);
}

void PRDrawPolarX(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData)
{
  float cx=0, cy=0, rMax=0, x=0, y=0, tx=0, ty=0, fly=0, flx=0, oYx=0, oYy=0, fosy=0;
  float fXx=0, fXy=0, fYx=0, fYy=0, rad=0, rStart=0, offset=0, oXx=0, oXy=0, fosx=0;
  char angleLabel[8]={0}, forceLabel[32]={0};

  sAppData *data = (sAppData*)aData;
  sPrData *pPrData = (sPrData*)data->prData;
  
  float *forceLegend = pPrData->forceLegend;
  float *forceX = pPrData->forceX;
  float *forceY = pPrData->forceY;
  float fOsX = pPrData->fOsX;
  float fOsY = pPrData->fOsY;
  
  cx = aWidth/4;
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

void PRDrawPolarY(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData)
{
  float cx=0, cy=0, rMax=0, x=0, y=0, tx=0, ty=0, fly=0, flx=0, oYx=0, oYy=0, fosy=0;
  float fXx=0, fXy=0, fYx=0, fYy=0, rad=0, rStart=0, offset=0, oXx=0, oXy=0, fosx=0;
  char angleLabel[8]={0}, forceLabel[32]={0};

  sAppData *data = (sAppData*)aData;
  sPrData *pPrData = (sPrData*)data->prData;

  float *forceLegend = pPrData->forceLegend;
  float *forceX = pPrData->forceX;
  float *forceY = pPrData->forceY;
  float fOsX = pPrData->fOsX;
  float fOsY = pPrData->fOsY;
  
  cx = aWidth/2;
  cy = aHeight/2;
  rMax = RADIUS_MAX;
  
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
      
      fYx = cx + (((rMax/2 - offset)*forceY[j]/FORCE_MAX)+(rStart))*sin(rad);
      fYy = cy - (((rMax/2 - offset)*forceY[j]/FORCE_MAX)+(rStart))*cos(rad);
      cairo_set_source_rgb(aCr, 1, 0.5, 0.5);
      PRDrawPoint(aCr, fYx, fYy);
      
      cairo_move_to(aCr, oXx, oXy);
      cairo_line_to(aCr, fYx, fYy);
      cairo_stroke(aCr);
      oXx=fYx;
      oXy=fYy;
    }
  
  //Draw OwnShip curseur
  cairo_set_source_rgb(aCr, 0.2, 0.2, 0.8);
  rad=(data->osMsg.GetAWA())*M_PI/180;
  fosx = cx + (((rMax/2 - offset)*fOsY/FORCE_MAX)+(rStart))*sin(rad);
  fosy = cy - (((rMax/2 - offset)*fOsY/FORCE_MAX)+(rStart))*cos(rad);
  PRDrawPoint(aCr, fosx, fosy, 2);
}

void PRDrawSum(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData)
{
  float cx=0, cy=0, len=0, angle=0, shaftLen=0, shaftWidth=0, headLen=0, headWidth=0, totalLen=0, offset=0;

  sAppData *data = (sAppData*)aData;
  sPrData *pPrData = (sPrData*)data->prData;

  bool onOff = data->osMsg.GetRotOnOff();
  
  float fOsX = pPrData->fOsX;
  float fOsY = pPrData->fOsY;

  if(onOff)
    {
      cx = aWidth/2;
      cy = aHeight/1.5;
  
      len = 180;
      angle = atan2(-fOsX, fOsY);
    
      cairo_save(aCr);
      cairo_translate(aCr, cx, cy);
      cairo_rotate(aCr, angle);

      shaftLen = len * 0.8;
      shaftWidth = 48;
      headLen = len * 0.2;
      headWidth = 70;
      totalLen = shaftLen + headLen;
      offset = -totalLen/2;
    
      cairo_move_to(aCr, offset, -shaftWidth/2);
      cairo_line_to(aCr, offset+shaftLen, -shaftWidth/2);
      cairo_line_to(aCr, offset+shaftLen, -headWidth/2);
      cairo_line_to(aCr, offset+shaftLen + headLen, 0);
      cairo_line_to(aCr, offset+shaftLen, headWidth/2);
      cairo_line_to(aCr, offset+shaftLen, shaftWidth/2);
      cairo_line_to(aCr, offset, shaftWidth/2);
      cairo_close_path(aCr);

      if(fOsX > 0)
	cairo_set_source_rgb(aCr, 0, 0.8, 0);
      else
	cairo_set_source_rgb(aCr, 0.8, 0, 0);

      cairo_fill_preserve(aCr);
      cairo_set_source_rgb(aCr, 1, 1, 1);
      cairo_set_line_width(aCr, 6);
      cairo_stroke(aCr);
      cairo_restore(aCr);
    }
}
