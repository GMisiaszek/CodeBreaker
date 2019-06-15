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
        void fillAvailableHostsTable(std::vector<std::tuple<std::string, int, int>>);
        std::string getHostNameFromTextfield();
        void addNewHostToChosenHostsTable(std::string hostName);
        void setHostNotAddedInTextfield(std::string);
        void setFoundPasswordInTextField(std::string);
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
        std::string getPassword(int hostNumber);
        std::vector<std::tuple<std::string, int, int>> getInfo();
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
        virtual void setTextInFoundPasswordTextField(std::string) = 0;
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
        GtkWidget* foundPasswordTextField;
        GtkWidget* addHostTextfieldContainer;

        GridLayout(ScrollContainer&, ScrollContainer&, GuiPvm&);
        virtual ~GridLayout(){};

        virtual void createLayout() override;
        virtual GtkWidget* getLayout() override;
        virtual std::string getHostnameFromTextField() override;
        virtual void setTextInAddHostTextfield(std::string) override;
        void setTextInFoundPasswordTextField(std::string) override;

        private:
        void createAndFillButtonContainer();
        void createAndFillTextfield();
        void createAndFillTextfield2();

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
        void setTextInFoundPasswordTextField(std::string);

    };

    struct HostnameTableView
    {
        
        HostnameTableView();
        ~HostnameTableView()
        {
            std::cout<<"Hostname destruktor"<<std::endl;
        }
        void updateHostNameList(std::vector<std::tuple<std::string, int, int>>);
        void addNewHostToTable(std::string hostName);
        GtkTreeView* getTreeView();
        GtkTreeView*         treeView;
        GtkTreeIter        listIterator;
        GtkListStore*      listStore;
        GtkTreeViewColumn* hostnameColumnName;
        GtkTreeViewColumn* hostnameColumnSpeed;
        GtkTreeViewColumn* hostnameColumnSsid;
        GtkCellRenderer*   renderer;
        GtkWidget*         scrolledWindow;
        GtkTreeSelection*  hostSelection;

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
