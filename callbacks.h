#include<gtk/gtk.h>

#ifndef CALLBACKS_H
#define CALLBACKS_H
namespace callbacks
{
    
    void refreshButtonCallback(GtkWidget*, gpointer);
    void chooseHostNuberButtonCallback(GtkWidget*, gpointer);
    void addHostButtonCallback(GtkWidget*, gpointer);

} // end namespace callbacks
#endif