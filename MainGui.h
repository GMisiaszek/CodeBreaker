#include <gtk/gtk.h>
#include "callbacks.h"
#include "pvmcontainer.h"
#include <vector>
#include <string>
#include <iostream>
#ifndef MAIN_GUI
#define MAIN_GUI
namespace gui
{
    //forward declarations
    struct HostnameTableView;
    struct ScrollContainer;
    struct MainWindow;

    struct GuiApi
    {
        void fillAvailableHostsTable(std::vector<std::string>);
        std::string getHostNameFromTextfield();
        void addNewHostToChosenHostsTable(std::string hostName);
        void setHostNotAddedInTextfield(std::string);
        GuiApi(HostnameTableView&, HostnameTableView&, MainWindow&);
        ~GuiApi()
        {
            std::cout<<"Destruktor"<<std::endl;
        }
        private:
        HostnameTableView& hostsToChooseTable;
        HostnameTableView& chosenHostsTable;
        MainWindow& mainWindow;
        
        
    };

    struct PvmApi
    {
        pvm::PvmContainer& pvmContainer;
        PvmApi(pvm::PvmContainer&);

        int addHost(std::string);
        void getInfo();
    };

    struct GuiPvm
    {
        GuiApi& guiApi;
        PvmApi& pvmApi;
        GuiPvm(GuiApi&,PvmApi&);

    };

    struct ILayout
    {
        GtkWidget* gridLayout;
        GtkWidget* buttonContainer;
        GtkWidget* buttonContainer2;
        virtual void createLayout() = 0;
        virtual GtkWidget* getLayout() = 0;
        virtual std::string getHostnameFromTextField() = 0;
        virtual void setTextInAddHostTextfield(std::string) = 0;
    };

    struct GridLayout:ILayout
    {
        gui::ScrollContainer& hostsToChooseTable;
        gui::ScrollContainer& chosenHostsTable; 
        gui::GuiPvm& guiPvm;
        GtkWidget* refreshButton;
        GtkWidget* chooseHostsButton;
        GtkWidget* addHostButton;
        GtkWidget* addHostTextField;
        GtkWidget* addHostTextfieldContainer;

        GridLayout(ScrollContainer&, ScrollContainer&, GuiPvm&);
        virtual ~GridLayout(){};

        virtual void createLayout() override;
        virtual GtkWidget* getLayout() override;
        virtual std::string getHostnameFromTextField() override;
        virtual void setTextInAddHostTextfield(std::string) override;

        private:
        void createAndFillButtonContainer();
        void createAndFillTextfield();

    };

    struct MainWindow
    {
        MainWindow(const char*, gint, gint);
        GtkWidget* window;
        ILayout* mainLayout;
        void insertLayoutIntoWindow(ILayout&);
        void showWindow();
        std::string getHostnameFromTextfield();
        void setTextInAddHostTextfield(std::string);

    };

    struct HostnameTableView
    {
        
        HostnameTableView();
        ~HostnameTableView()
        {
            std::cout<<"Hostname destruktor"<<std::endl;
        }
        void updateHostNameList(std::vector<std::string>);
        void addNewHostToTable(std::string hostName);
        GtkTreeView* getTreeView();
        GtkTreeView*         treeView;
        GtkTreeIter        listIterator;
        GtkListStore*      listStore;
        GtkTreeViewColumn* hostnameColumn;
        GtkCellRenderer*   renderer;
        GtkWidget*         scrolledWindow;

    };

    struct ScrollContainer
    {
        ScrollContainer();
        ScrollContainer(HostnameTableView&);
        GtkWidget* getScrollWindow();
        ScrollContainer& getScrollContainer();
        HostnameTableView& getHostnameTableView();
        HostnameTableView& hostnameTableView;
        ~ScrollContainer()
        {
            std::cout<<"Scroll Container"<<std::endl;
        }
        private:

        
        GtkWidget*         scrollWindow;
        GtkAdjustment*     vScroll;     
    };

    struct ControlButton
    {
       ControlButton(const char*);
       GtkWidget* button;

    };
}
#endif
