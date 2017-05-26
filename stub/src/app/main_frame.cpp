#include "app/main_frame.h"

#include "wx/string.h"
#include "wx/menu.h"

#include "app/app.h"


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_EXIT, MainFrame::MenuFileExit)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title,
                     const wxPoint& mypoint,
                     const wxSize& mysize)
    : wxFrame(NULL, wxID_ANY, title, mypoint, mysize) {
  CreateControls();
}

MainFrame::~MainFrame() {
}

void MainFrame::CreateControls() {
  wxMenu* menu = new wxMenu();
  menu->Append(wxID_EXIT, _T("&Exit\tAlt+F4"));

  wxMenuBar* file_menu = new wxMenuBar();
  file_menu->Append(menu, _T("&File"));
  SetMenuBar(file_menu);
}

void MainFrame::MenuFileExit(wxCommandEvent& evt) {
  Close();
}
