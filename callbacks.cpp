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
        std::vector<std::string> hosts{"123"};
        guiPvm.pvmApi.getInfo();
        guiPvm.guiApi.fillAvailableHostsTable(hosts);
    }
    void addHostButtonCallback(GtkWidget* widget, gpointer pointer)
    {
        auto& guiPvm  = *static_cast<gui::GuiPvm*>(pointer);
        auto hostName = guiPvm.guiApi.getHostNameFromTextfield();
        int result    = guiPvm.pvmApi.addHost(hostName);
        switch(result)
        {

            case PVM_SYSERR:
            {
                guiPvm.guiApi.setHostNotAddedInTextfield("Pvm system err");
                break;
            }
            case ALREADY_ADDED:
            {
                guiPvm.guiApi.setHostNotAddedInTextfield("Host already added");
                break;
            }
            case DUPLICATE_HOST:
            {
                guiPvm.guiApi.setHostNotAddedInTextfield("Duplicate host");
                break;
            }
            default:
            {
                guiPvm.guiApi.setHostNotAddedInTextfield(std::to_string(result));
                break;
            }
        }
    }
}