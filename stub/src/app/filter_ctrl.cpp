#include "app/filter_ctrl.h"

#include "wx/dc.h"
#include "wx/dcbuffer.h"
#include "wx/statline.h"

#include "wx/colour.h"

#include "app/resource_id.h"

namespace csi {

static const wxColour kFilterLabelColor(128, 128, 128);

DEFINE_EVENT_TYPE(kEvtFilterCtrlSelectChange)

BEGIN_EVENT_TABLE(FilterCtrl, wxControl)
EVT_PAINT(FilterCtrl::OnPaint)
EVT_ERASE_BACKGROUND(FilterCtrl::OnEraseBackGround)
EVT_MOTION(FilterCtrl::OnMotion)
EVT_LEFT_UP(FilterCtrl::OnLeftUp)
END_EVENT_TABLE()

FilterCtrl::FilterCtrl(wxWindow* parent,
wxWindowID id,
const wxPoint& pos,
const wxSize& size)
: toggle_label_colour_(25, 125, 255) {

  Init();
  Create(parent, id, pos, size);
  SetForegroundColour(kFilterLabelColor);
}

FilterCtrl::~FilterCtrl() {
}

bool FilterCtrl::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) {
  if (!wxControl::Create(parent, id, pos, size, wxBORDER_NONE)) {
    return false;
  }
  SetBackgroundColour(parent->GetBackgroundColour());
  return true;
}

void FilterCtrl::AddFilter(const wxString& label) {
//   wxCoord width, height;  // TODO: Use wxSize
//   int filter_count = label_info_.size();
// 
//   GetTextExtent(label, &width, &height, NULL, NULL, &GetParent()->GetFont());  // TODO: Remove font
//   best_size_ = wxSize(width, height);
// 
//   if (filter_count > 0) {
//     // Not the first label., add more space for separator.
//     best_size_.x += 2 * LabelInfo::kSeparatorSpace + SeperatorLineWidth();
//   }
// 
//   // TODO
//   if (filter_count == 0) {
//     wxPoint point(0, 0);  // TODO: Remove 0, 0 -> wxPoint point;
//     CalculatePosition(label, point);
//   } else {
//     size_t xpos = static_line_position_[filter_count - 1].x;
//     wxPoint point(xpos + LabelInfo::kSeparatorSpace + SeperatorLineWidth(), 0);
//     CalculatePosition(label, point);
//   }
// 
//   // Record the size of filter after AddFilter
//   init_filter_size_.push_back(best_size_);
// 
//   InvalidateBestSize();
  wxCoord width, height;
  GetTextExtent(label, &width, &height, NULL, NULL, &GetParent()->GetFont());

  int filter_count = label_info_.size();

  if (filter_count == 0) {

    best_size_ = wxSize(width, height);

    wxPoint point(0, 0);
    CalculatePosition(label, point);

    // Record the size of filter after AddFilter
    init_filter_size_.push_back(best_size_);

  } else {
    size_t xpos = static_line_position_[filter_count - 1].x;

    best_size_ += wxSize(width + 2 * LabelInfo::kSeparatorSpace + SeperatorLineWidth(), 0);

    wxPoint point(xpos + LabelInfo::kSeparatorSpace + SeperatorLineWidth(), 0);
    CalculatePosition(label, point);

    // Record the size of filter after AddFilter
    init_filter_size_.push_back(best_size_);
  }
  InvalidateBestSize();
}

void FilterCtrl::SetPriorFilter(const wxString& label) {
  for (size_t i = 0; i < label_info_.size(); ++i) {
    if (label == label_info_[i]->label()) {
      label_info_[i]->set_prior_filter_flag(true);
      label_info_[i]->set_toggle(true);

      special_filter_number_ = i;
      break;
    }
  }
  Refresh(true);
}

void FilterCtrl::RemoveFilter(const wxString& label) {
  for (size_t i = 0; i < label_info_.size(); ++i) {
    wxString filter = label_info_[i]->label();

    if (filter.Find(wxUniChar('(')) != wxNOT_FOUND) {
      filter = filter.BeforeFirst(wxUniChar('('));
    }

    if (filter == label_info_[i]->label()) {

      // Change the best size of the filter
      best_size_ -= wxSize(label_info_[i]->width() + 2 * LabelInfo::kSeparatorSpace + SeperatorLineWidth(), 0);

      std::vector<std::shared_ptr<LabelInfo>>::iterator it_label = label_info_.begin() + i;
      label_info_.erase(it_label);

      // Each time a filter is deleted, the contents stored in the container need to be changed
      for (size_t j = i + 1; j < init_filter_size_.size(); ++j) {
        if (i == 0) {
          init_filter_size_[j] -= init_filter_size_[i];
        } else {
          wxSize n = init_filter_size_[i] - init_filter_size_[i - 1];
          init_filter_size_[j] -= n;
        }
      }

      std::vector<wxSize>::iterator it_size = init_filter_size_.begin() + i;
      init_filter_size_.erase(it_size);
      std::vector<wxPoint>::iterator it_line = static_line_position_.begin() + i;
      static_line_position_.erase(it_line);
      break;
    }
  }

  // TODO : The location after the current label needs to be changed
  UpdateFilterUI();
}

void FilterCtrl::RemoveAllFilter() {
  best_size_ = wxSize(0, 0);
  label_info_.clear();
  static_line_position_.clear();
}

void FilterCtrl::SetToggle(const wxString& label, bool toggle) {
  for (auto& value : label_info_) {
    wxString filter = value->label();

    if (filter.Find(wxUniChar('(')) != wxNOT_FOUND) {  // TODO: wxT('(')
      filter = filter.BeforeFirst(wxUniChar('('));
    }
    if (filter == label) {
      value->set_toggle(toggle);
      Refresh(true);
      break;
    }
  }
}

std::vector<wxString> FilterCtrl::GetToggledLabels() const {
  std::vector<wxString> toggled_label;

  // return toggled label
  for (auto& value : label_info_) {
    if (value->toggle()) {
      wxString label = value->label();
      if (label.Find(wxUniChar('(')) != wxNOT_FOUND) {
        label = label.BeforeFirst(wxUniChar('('));
      }
      toggled_label.push_back(label);
    }
  }
  return toggled_label;
}

wxSize FilterCtrl::DoGetBestSize() const {
  return best_size_;
}

void FilterCtrl::Init() {
  all_ordinary_filter_close_ = true;
  special_filter_number_ = ID_GALLERY_CTRL_END;
}

inline const wxCoord FilterCtrl::SeperatorLineWidth() {
  wxCoord width = 0;
  GetTextExtent(_T("|"), &width, NULL);
  return width;
}

void FilterCtrl::OnPaint(wxPaintEvent& evt) {
  wxBufferedPaintDC dc(this);
  dc.Clear();

  if (label_info_.size() == 1) {
    DrawFirstFilter(dc);
  } else {
    DrawAllFilter(dc);
  }
}

void FilterCtrl::DrawFirstFilter(wxDC& dc) {
  dc.SetFont(GetParent()->GetFont());
  std::vector<std::shared_ptr<LabelInfo>>::iterator it = label_info_.begin();
  if (it == label_info_.end()) {
    return;
  }

  if ((*it)->toggle()) {
    dc.SetTextForeground(toggle_label_colour_);
  } else {
    dc.SetTextForeground(GetForegroundColour());
  }

  dc.DrawText((*it)->label(),
              (*it)->position().x,
              (*it)->position().y);
}

void FilterCtrl::DrawAllFilter(wxDC& dc) {
  dc.SetFont(GetParent()->GetFont());
  DrawFirstFilter(dc);
  size_t count = label_info_.size();

  for (size_t i = 1; i < count; ++i) {
    dc.SetTextForeground(GetForegroundColour());
    dc.DrawText("|", wxPoint(static_line_position_[i - 1].x, static_line_position_[i - 1].y));

    if (label_info_[i]->toggle()) {
      dc.SetTextForeground(toggle_label_colour_);
    } else {
      dc.SetTextForeground(GetForegroundColour());
    }

    dc.DrawText(label_info_[i]->label(),
                label_info_[i]->position().x,
                label_info_[i]->position().y);
  }
}

void FilterCtrl::OnEraseBackGround(wxEraseEvent& evt) {
}  // Reduce screen flicker

void FilterCtrl::OnSize(wxSizeEvent& evt) {
  evt.Skip();
}

void FilterCtrl::OnLeftUp(wxMouseEvent& evt) {
  for (auto& value : label_info_) {
    wxRect rect(value->position(),
                wxSize(value->width(), value->height()));

    if (rect.Contains(evt.GetPosition())) {
      if (value->prior_filter_flag()) {
        value->set_toggle(true);

        // close all labels except the special filter
        for (auto& filter : label_info_) {
          if (filter != value) {
            filter->set_toggle(false);
          }
        }
      } else {
        OtherFilterAlterState(value);
      }
    }
  }

  Refresh(true);
  Update();

  PostEvent(kEvtFilterCtrlSelectChange);
}

void FilterCtrl::OnMotion(wxMouseEvent& evt) {
  int xpos = evt.GetPosition().x;
  for (auto& value : label_info_) {

    if ((xpos <= (value->position().x + value->width())) && (xpos >= value->position().x)) {
      SetCursor(wxCURSOR_HAND);
    }
    if ((xpos >= (value->position().x + value->width())) && (xpos <= value->position().x + value->width() +
      2 * LabelInfo::kSeparatorSpace)) {
      SetCursor(wxCURSOR_ARROW);
    }
  }
  Update();
}

void FilterCtrl::OtherFilterAlterState(std::shared_ptr<LabelInfo> label) {
  if (!label->toggle()) {
    label->set_toggle(true);
  } else {
    label->set_toggle(false);
  }

  // for the special filter
  if (special_filter_number_ < label_info_.size()) {
    label_info_[special_filter_number_]->set_toggle(false);
  }

  if (IsAllOtherFilterClose()) {
    label_info_[special_filter_number_]->set_toggle(true);
  }
}

wxPoint FilterCtrl::static_line_position(size_t i) const {
  if (static_line_position_.size() != 0) {
    return static_line_position_[i];
  }
  return wxPoint(0, 0);
}

size_t FilterCtrl::PositionIndex(const wxSize& client_size) const {
  for (size_t i = 1; i < label_info_.size(); ++i) {
    if ((client_size.x >= init_filter_size_[i - 1].x) && (client_size.x <= init_filter_size_[i].x)) {
      return i;
    }
  }
  return label_info_.size() + 1;
}

void FilterCtrl::CalculatePosition(const wxString& lable, const wxPoint& positon) {
  wxCoord width, height;
  GetTextExtent(lable, &width, &height, NULL, NULL, &GetParent()->GetFont());

  std::shared_ptr<LabelInfo> str_info_class_(new LabelInfo(lable, width, height, positon, false));
  label_info_.push_back(str_info_class_);

  // Calculate the position of static line
  wxPoint line_position = positon + wxPoint(width + LabelInfo::kSeparatorSpace, 0);
  static_line_position_.push_back(line_position);
}

bool FilterCtrl::IsAllOtherFilterClose() {
  size_t label_size = label_info_.size();
  if (special_filter_number_ == ID_GALLERY_CTRL_END) {
    return false;
  }

  // Check whether all labels except the special label are in closed state
  for (size_t i = 0; i < label_size; ++i) {
    if ((i != special_filter_number_) && label_info_[i]->toggle()) {
      all_ordinary_filter_close_ = false;
      break;
    } else {
      all_ordinary_filter_close_ = true;
    }
  }
  return all_ordinary_filter_close_;
}

void FilterCtrl::NextFilterPosition(wxPoint current_line, std::shared_ptr<LabelInfo> label) {
  wxPoint point = wxPoint(LabelInfo::kSeparatorSpace + SeperatorLineWidth(), 0);
  label->set_position(current_line + point);
}

void FilterCtrl::NextLinePosition(wxPoint current_line, int next_line_num) {
  wxPoint point(current_line.x +
                LabelInfo::kSeparatorSpace * 2 +
                label_info_[next_line_num]->width(), current_line.y);
  set_static_line_position(point, next_line_num);
}

void FilterCtrl::UpdateFilterUI() {
  size_t filter_count = label_info_.size();

  // Update the position of all labels
  for (size_t i = 0; i < filter_count; ++i) {
    if (i == 0) {
      wxPoint point(0, 0);
      label_info_[i]->set_position(point);
      set_static_line_position(point + wxPoint(label_info_[i]->width() + LabelInfo::kSeparatorSpace, 0), i);
      best_size_ = wxSize(label_info_[i]->width(), label_info_[i]->height());
    } else {
      size_t xpos = static_line_position_[i - 1].x;
      wxPoint point(xpos + LabelInfo::kSeparatorSpace + SeperatorLineWidth(), 0);
      label_info_[i]->set_position(point);

      set_static_line_position(point + wxPoint(label_info_[i]->width() + LabelInfo::kSeparatorSpace, 0), i);
      best_size_ += wxSize(label_info_[i]->width() +
                           LabelInfo::kSeparatorSpace * 2 + SeperatorLineWidth(), 0);
    }

    // Update the special filter id
    if (label_info_[i]->prior_filter_flag()) {
      special_filter_number_ = i;
    }
  }
  Refresh(true);
}

void FilterCtrl::PostEvent(wxEventType evt_type) {
  wxCommandEvent evt(evt_type, GetId());
  evt.SetEventObject(this);
  GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

}  // namespace csi
