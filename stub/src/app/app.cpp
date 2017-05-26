#include "app/app.h"

#include "wx/toolbar.h"
#include "wx/button.h"

#include "app/main_frame.h"
#include "app/filter_ctrl.h"
#include "app/resource_id.h"

IMPLEMENT_APP(App)

bool App::OnInit() {
  if (!wxApp::OnInit()) {
    return false;
  }

  MainFrame* image_frame = new MainFrame(_T("FilterCtrl"), wxDefaultPosition, wxDefaultSize);
  image_frame->SetBackgroundColour(*wxWHITE);
  image_frame->SetSize(wxSize(600, 350));
  CreateFilter(image_frame);

  image_frame->Show(true);

  return true;
}

void App::CreateFilter(MainFrame* main_frame) {
  wxBoxSizer* top_sizer = new wxBoxSizer(wxVERTICAL);

  csi::FilterCtrl* filter_ctrl = new csi::FilterCtrl(main_frame, wxID_ANY, wxDefaultPosition, wxDefaultSize);
  wxFont default_font(16, wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL);
  main_frame->SetFont(default_font);

  filter_ctrl->AddFilter(_T("Cephalometric"));
  filter_ctrl->AddFilter(_T("Intraoral"));
  filter_ctrl->AddFilter(_T("Panoramic"));
//  filter_ctrl->AddFilter(_T("CAD"));
  filter_ctrl->AddFilter(_T("FMS"));
  filter_ctrl->AddFilter(_T("Not Classified"));
  filter_ctrl->AddFilter(_T("All"));

  filter_ctrl->SetPriorFilter(_T("All"));
//  filter_ctrl->RemoveFilter(_T("FMS"));
//  filter_ctrl->RemoveFilter(_T("Ceph"));
//   filter_ctrl->RemoveFilter(_T("Panoramic"));


  top_sizer->Add(filter_ctrl, 0, wxALIGN_CENTER, 5);

  main_frame->SetSizer(top_sizer);
  main_frame->Layout();
}
