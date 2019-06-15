
#include <gtk/gtk.h>
#include "MainGui.h"
#include "pvmcontainer.h"
#include <memory>

static void
activate ()
{
        
}

int main (int argc, char **argv)
{
  gtk_init(&argc, &argv);
  pvm::PvmContainer pvmContainer;
  gui::MainWindow mainWindow("CodeBreaker", 600, 600);
  gui::HostnameTableView hostsToChoose = *(new gui::HostnameTableView());
  gui::HostnameTableView chosenHosts   = *(new gui::HostnameTableView()) ;
  gui::ScrollContainer   scrollContainer_1(hostsToChoose);
  gui::ScrollContainer   scrollContainer_2(chosenHosts);
  gui::GuiApi guiApi(hostsToChoose, chosenHosts, mainWindow);
  gui::PvmApi pvmApi(pvmContainer);
  gui::GuiPvm guiPvm(guiApi, pvmApi);
  gui::GridLayout gridLayout(scrollContainer_1, scrollContainer_2, guiPvm);
  gridLayout.createLayout();
  mainWindow.insertLayoutIntoWindow(gridLayout);
  mainWindow.showWindow();
        
  gtk_main();
  return 0;

}
