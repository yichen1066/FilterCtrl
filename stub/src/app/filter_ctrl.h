#ifndef FILTERCTRL_APP_FILTER_CTRL_H_
#define FILTERCTRL_APP_FILTER_CTRL_H_

#include <map>
#include <memory>

#include "wx/control.h"
#include "wx/font.h"

namespace csi {

class LabelInfo {
  DECLARE_NO_COPY_CLASS(LabelInfo)

public:
  enum {
    kSeparatorSpace = 5
  };

public:
  LabelInfo(const wxString& label,
            const wxCoord& width,
            const wxCoord& height,
            const wxPoint& position,
            bool state)
            : label_(label)
            , width_(width)
            , height_(height)
            , position_(position)
            , toggle_(state)
            , prior_filter_(0) {
  }

  const wxString& label() const{  // TODO: Return const &
    return label_;
  }

  void set_label(const wxString& label) {
    label_ = label;
  }

  wxCoord width() {  // TODO: Remove const
    return width_;
  }

  wxCoord height() {  // TODO: Remove const
    return height_;
  }

  const wxPoint& position() const {  // TODO: Return const &
    return position_;
  }

  void set_position(const wxPoint& position) {
    position_ = position;
  }

  bool toggle() {
    return toggle_;
  }

  void set_toggle(bool toggle) {
    toggle_ = toggle;
  }

  bool prior_filter_flag() const {
    return prior_filter_;
  }

  void set_prior_filter_flag(bool prior_filter) {
    prior_filter_ = prior_filter;
  }

private:
  // TODO: Use wxSize
  wxCoord width_;
  wxCoord height_;

  wxString label_;
  wxPoint position_;

  bool toggle_;
  bool prior_filter_;
};

class FilterCtrl : public wxControl {
  DECLARE_NO_COPY_CLASS(FilterCtrl)
  DECLARE_EVENT_TABLE()

public:
  FilterCtrl(wxWindow* parent,
             wxWindowID id,
             const wxPoint& pos,
             const wxSize& size);
  virtual ~FilterCtrl();

  bool Create(wxWindow* parent,
              wxWindowID id,
              const wxPoint& pos,
              const wxSize& size);

  void AddFilter(const wxString& label);
  void SetPriorFilter(const wxString& label);
  void RemoveFilter(const wxString& label);
  void RemoveAllFilter();

  void SetToggle(const wxString& label, bool toggle);

  // TODO: Return label1_bit | label2_bit -> int
  std::vector<wxString> GetToggledLabels() const;

  const wxSize best_size() const {
    return best_size_;
  }

protected:
  virtual wxSize DoGetBestSize() const override;

  void Init();
  const wxCoord SeperatorLineWidth();

  void OnPaint(wxPaintEvent& evt);
  void DrawFirstFilter(wxDC& dc);
  void DrawAllFilter(wxDC& dc);
  void OnEraseBackGround(wxEraseEvent& evt);
  void OnSize(wxSizeEvent& evt);

  void OnLeftUp(wxMouseEvent& evt);
  void OnMotion(wxMouseEvent& evt);

  void OtherFilterAlterState(std::shared_ptr<LabelInfo> label);

  wxPoint static_line_position(size_t i) const;
  size_t PositionIndex(const wxSize& client_size) const;

  void set_static_line_position(wxPoint position, size_t i) {
    static_line_position_[i] = position;
  }

  void CalculatePosition(const wxString& lable, const wxPoint& positon);
  bool IsAllOtherFilterClose();

  void NextFilterPosition(wxPoint current_line, std::shared_ptr<LabelInfo> label);
  void NextLinePosition(wxPoint current_line, int next_line_num);
  void UpdateFilterUI();
  void PostEvent(wxEventType evt_type);

  size_t ReSizeIndex(const wxSize& client_size) const;

private:

  bool all_ordinary_filter_close_;

  wxSize best_size_;
  size_t special_filter_number_;

  wxColour toggle_label_colour_;

  std::vector<std::shared_ptr<LabelInfo>> label_info_;
  std::vector<wxPoint> static_line_position_;

  // Record the initial size of the filter after AddFilter
  // TODO: Remove
  std::vector<wxSize> init_filter_size_;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(kEvtFilterCtrlSelectChange, 0)
END_DECLARE_EVENT_TYPES()

}  // namespace csi

#endif  // FILTERCTRL_APP_FILTER_CTRL_H_
