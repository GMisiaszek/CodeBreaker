#include "MainGui.h"


namespace gui
{

    GuiApi::GuiApi(HostnameTableView& hostsToChooseTable,
                   HostnameTableView& chosenHostsTable,
                   MainWindow& mainWindow):
                   hostsToChooseTable(hostsToChooseTable),
                   chosenHostsTable(chosenHostsTable),
                   mainWindow(mainWindow)
                   {};

    void GuiApi::fillAvailableHostsTable(std::vector<std::tuple<std::string, int, int>> hosts)
    {
        hostsToChooseTable.updateHostNameList(hosts);
    }

    void GuiApi::setHostNotAddedInTextfield(std::string text)
    {
        mainWindow.setTextInAddHostTextfield(text);
    }

    void GuiApi::setFoundPasswordInTextField(std:: string text)
    {
        mainWindow.setTextInFoundPasswordTextField(text);
    }

    std::string GuiApi::getHostNameFromTextfield()
    {
        return mainWindow.mainLayout->getHostnameFromTextField();
    }

    void GuiApi::addNewHostToChosenHostsTable(std::string hostName)
    {
        mainWindow.setTextInAddHostTextfield("Host dodany!");
        hostsToChooseTable.addNewHostToTable(hostName);
    }

    PvmApi::PvmApi(pvm::PvmContainer& pvmContainer):
                   pvmContainer(pvmContainer){};

    int PvmApi::addHost(std::string hostName)
    {
        return pvmContainer.addHost(hostName.c_str());
    }

    std::string PvmApi::getPassword(int hostNumber)
    {
        return pvmContainer.getPassword(hostNumber);
    }
    
    std::vector<std::tuple<std::string, int, int>> PvmApi::getInfo()
    {
        return pvmContainer.hostInfo();
    }
    GuiPvm::GuiPvm(GuiApi& guiApi, PvmApi& pvmApi):
                                      guiApi(guiApi),
                                      pvmApi(pvmApi){};

    GridLayout::GridLayout(ScrollContainer& hostsToChooseTable,
                           ScrollContainer& chosenHostsTable,
                           GuiPvm& guiPvm)
                           :hostsToChooseTable(hostsToChooseTable),
                           chosenHostsTable(chosenHostsTable),
                           guiPvm(guiPvm){};

    void GridLayout::createLayout()
    {
        gridLayout = gtk_grid_new();
        gtk_grid_insert_column(GTK_GRID(gridLayout), 0);
        gtk_grid_insert_column(GTK_GRID(gridLayout), 1);
        gtk_grid_insert_column(GTK_GRID(gridLayout), 2);
        gtk_grid_insert_row(GTK_GRID(gridLayout), 0);
        gtk_grid_insert_row(GTK_GRID(gridLayout), 1);
        gtk_grid_insert_row(GTK_GRID(gridLayout), 2);
        gtk_grid_attach(GTK_GRID(gridLayout),hostsToChooseTable.getScrollWindow(), 0,0,1,1);
        gtk_grid_attach(GTK_GRID(gridLayout),chosenHostsTable.getScrollWindow(), 1,0,1,1);
        createAndFillButtonContainer();
        createAndFillTextfield();
        createAndFillTextfield2();
        gtk_grid_attach(GTK_GRID(gridLayout), buttonContainer, 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(gridLayout), buttonContainer2, 1, 2, 1, 1);
    }

    void GridLayout::createAndFillButtonContainer()
    {
        buttonContainer    = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
        buttonContainer2   = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
        refreshButton      = gtk_button_new_with_label("Odśwież");
        chooseHostsButton  = gtk_button_new_with_label("Wybierz hosty");
        addHostButton      = gtk_button_new_with_label("Start");
        gtk_container_add(GTK_CONTAINER(buttonContainer), refreshButton);
        gtk_container_add(GTK_CONTAINER(buttonContainer), chooseHostsButton);
        gtk_container_add(GTK_CONTAINER(buttonContainer2), addHostButton);
        g_signal_connect(refreshButton, "clicked", G_CALLBACK(callbacks::refreshButtonCallback), &guiPvm);
        g_signal_connect(addHostButton, "clicked", G_CALLBACK(callbacks::addHostButtonCallback), &guiPvm);
    }

    void GridLayout::createAndFillTextfield()
    {
        addHostTextField = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(addHostTextField), "IP hosta");
        gtk_grid_attach(GTK_GRID(gridLayout), addHostTextField, 1, 1, 1, 1);
    }

    void GridLayout::createAndFillTextfield2()
    {
        foundPasswordTextField = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(gridLayout), foundPasswordTextField,2,1,1,1);
    }

    std::string GridLayout::getHostnameFromTextField()
    {
        const char* hostName = gtk_entry_get_text(GTK_ENTRY(addHostTextField));
        return std::string(hostName);
    }

    GtkWidget* GridLayout::getLayout()
    {
        return gridLayout;
    }

    void GridLayout::setTextInAddHostTextfield(std::string text)
    {
        gtk_entry_set_text(GTK_ENTRY(addHostTextField), text.c_str());
    }

    void GridLayout::setTextInFoundPasswordTextField(std::string text)
    {
        gtk_entry_set_text(GTK_ENTRY(foundPasswordTextField), text.c_str());
    }

    MainWindow::MainWindow(const char* title, gint width, gint height)
    {
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title (GTK_WINDOW (window), title);
        gtk_window_set_default_size (GTK_WINDOW (window), width, height);
    }

    void MainWindow::insertLayoutIntoWindow(ILayout& layout)
    {
        mainLayout = &layout;
        GtkWidget* gridLayout = layout.getLayout();
        gtk_container_add(GTK_CONTAINER(window), gridLayout);
    }

    void MainWindow::showWindow()
    {
        gtk_widget_realize(window);
        gtk_widget_show_all(window);
    }

    std::string MainWindow::getHostnameFromTextfield()
    {
        return mainLayout->getHostnameFromTextField();
    }

    void MainWindow::setTextInAddHostTextfield(std::string text)
    {
        mainLayout->setTextInAddHostTextfield(text);
    }

    void MainWindow::setTextInFoundPasswordTextField(std::string text)
    {
        mainLayout->setTextInFoundPasswordTextField(text);
    }

    HostnameTableView::HostnameTableView()
    {
        listStore             = GTK_LIST_STORE(gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT));
        treeView              = GTK_TREE_VIEW(gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore)));
        renderer              = gtk_cell_renderer_text_new();
        hostnameColumnName    = gtk_tree_view_column_new_with_attributes("HostName", renderer, "text", 0, NULL);
        hostnameColumnSpeed   = gtk_tree_view_column_new_with_attributes("Speed", renderer, "text", 1, NULL);
        hostnameColumnSsid    = gtk_tree_view_column_new_with_attributes("Ssid", renderer, "text", 2, NULL);
        hostSelection         = gtk_tree_view_get_selection(treeView);
        gtk_tree_selection_set_mode(hostSelection, GTK_SELECTION_MULTIPLE);
        gtk_tree_view_append_column(treeView, hostnameColumnName);
        gtk_tree_view_append_column(treeView, hostnameColumnSpeed);
        gtk_tree_view_append_column(treeView, hostnameColumnSsid);
    }

    void HostnameTableView::updateHostNameList(std::vector<std::tuple<std::string, int, int>> hostNames)
    { 
        gtk_list_store_clear(listStore);
        for(const auto hostName:hostNames)
        {
            auto [host, speed, ssid] = hostName;
            gtk_list_store_append(GTK_LIST_STORE(listStore), &listIterator);
            gtk_list_store_set(GTK_LIST_STORE(listStore), &listIterator, 0, host.c_str(), 1, (guint) speed, 2, (guint) ssid, -1);
        }
    }

    void HostnameTableView::addNewHostToTable(std::string hostName)
    {
        gtk_list_store_append(GTK_LIST_STORE(listStore), &listIterator);
        gtk_list_store_set(GTK_LIST_STORE(listStore), &listIterator, 0, hostName.c_str(), -1);
    }

    GtkTreeView* HostnameTableView::getTreeView()
    {
        return treeView;
    }

    ScrollContainer::ScrollContainer(HostnameTableView& hostnameTableView):hostnameTableView(hostnameTableView)
    {
        scrollWindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrollWindow), 500);
        gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrollWindow), 200);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWindow),
                                       GTK_POLICY_ALWAYS,
                                       GTK_POLICY_AUTOMATIC);
        vScroll      = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrollWindow));
        gtk_tree_view_set_vadjustment(GTK_TREE_VIEW (hostnameTableView.treeView), vScroll);
        gtk_container_add(GTK_CONTAINER(scrollWindow), GTK_WIDGET(hostnameTableView.treeView));
    }

    HostnameTableView& ScrollContainer::getHostnameTableView()
    {
        return hostnameTableView;
    }

    GtkWidget* ScrollContainer::getScrollWindow()
    {
        return scrollWindow;
    }

    ScrollContainer& ScrollContainer::getScrollContainer()
    {
        return *this;
    }

    ControlButton::ControlButton(const char* buttonLabel)
    {
        button = gtk_button_new_with_label(buttonLabel);

    }

    
} //end gui namespace