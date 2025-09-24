#ifndef POLAR_READER_HPP
#define POLAR_READER_HPP

#include <gtk/gtk.h>

#define FORCE_LINE_COUNT (9)
#define RADIUS_MAX (350)
#define ANGLE_STEP_COUNT (13)
#define FORCE_MAX (120)
#define ANGLE_STEP_DEGRES (15)

/****************** Structure definitions **************/
typedef struct
{
  float forceLegend[FORCE_LINE_COUNT];
  float forceX[ANGLE_STEP_COUNT];
  float forceY[ANGLE_STEP_COUNT];
  float fOsX;
  float fOsY;
  GtkWidget *areaX;
  GtkWidget *areaY;
  GtkWidget *areaSum;
  GtkLabel *fLabel;
}sPrData;


/****************** Polar Injection prototype definitions **************/
void PRCreateBoxes(GtkWidget **aPrBodyBox, GtkWidget **aPrMainBox, GtkWidget **aPrTitleBox, GtkWidget **aPrLeftBox, GtkWidget **aPrMidBox, GtkWidget **aPrRightBox);
void PRSetTitle(GtkWidget **aTitle);
void PRSetLabels(GtkWidget **aLabelPolarX, GtkWidget **aLabelPolarY, GtkWidget **aLabelVector, GtkWidget **aLabelAngleForce);
void PRSetBoxes(GtkWidget **aPrBodyBox, GtkWidget **aPrMainBox, GtkWidget **aPrTitleBox, GtkWidget **aPrLeftBox, GtkWidget **aPrMidBox, GtkWidget **aPrRightBox,GtkWidget **aTitle, GtkWidget **aLabelPolarX, GtkWidget **aLabelPolarY, GtkWidget **aLabelVector, GtkWidget **aLabelAngleForce,GtkWidget **aAreaX, GtkWidget **aAreaY, GtkWidget **aAreaSum);
void PRDrawPoint(cairo_t *aCr, float aX, double aY, int aSize=1);
void PRDrawPolarX(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData);
void PRDrawPolarY(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData);
void PRDrawSum(GtkDrawingArea *aArea, cairo_t *aCr, int aWidth, int aHeight, gpointer aData);


#endif
