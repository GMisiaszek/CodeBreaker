#include "callbacks.h"
#include "MainGui.h"
#include <iostream>
#include <string>
#include <cstdlib>

#define PVM_SYSERR -14
#define ALREADY_ADDED -30
#define DUPLICATE_HOST -28

namespace callbacks
{
    void refreshButtonCallback(GtkWidget* widget, gpointer pointer)
    {
        auto& guiPvm = *static_cast<gui::GuiPvm*>(pointer);
        auto&& hosts = guiPvm.pvmApi.getInfo();
        guiPvm.guiApi.fillAvailableHostsTable(hosts);
    }
    void addHostButtonCallback(GtkWidget* widget, gpointer pointer)
    {
        auto& guiPvm  = *static_cast<gui::GuiPvm*>(pointer);
        std::string password = guiPvm.pvmApi.getPassword(stoi(guiPvm.guiApi.getHostNameFromTextfield()));
        guiPvm.guiApi.setFoundPasswordInTextField(password);
        
    }
    void selectHosts(GtkWidget* widget, gpointer pointer)
    {
        
    }
}