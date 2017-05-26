#ifndef IMAGEVIEWER_APP_MAIN_FRAME_H_
#define IMAGEVIEWER_APP_MAIN_FRAME_H_

#include <map>

#include "wx/sizer.h"
#include "wx/scrolwin.h"
#include "wx/frame.h"
#include "wx/statbmp.h"
#include "wx/filedlg.h"
#include "wx/dnd.h"

class MainFrame : public wxFrame {
  DECLARE_EVENT_TABLE()

public:
  // TODO: Use wxPoint and wxSize as parameters.
  // TODO: Use const wxString& instead of const wxChar* for title.
  MainFrame(const wxString& title, const wxPoint& mypoint, const wxSize& mysize);
  virtual ~MainFrame();

protected:
  void OnExit();
  void CreateControls();
  void MenuFileExit(wxCommandEvent& evt);
};

#endif  // IMAGEVIEWER_APP_MAIN_FRAME_H_
