// #ifndef FILTERCTRL_APP_RESOURCE_ID_H_
// #define FILTERCTRL_APP_RESOURCE_ID_H_
// 
// enum {
//   ID_FILTER_CTRL_START = 0,
// 
//   // filter id in main frame
//   ID_MAIN_FRAME_FILTER_CEPH,
//   ID_MAIN_FRAME_FILTER_PANO,
//   ID_MAIN_FRAME_FILTER_INTRAORAL,
//   ID_MAIN_FRAME_FILTER_FMS,
//   ID_MAIN_FRMAE_FILTER_VOLUME,
//   ID_MAIN_FRAME_FILTER_CAD,
//   ID_MAIN_FRAME_FILTER_MODEL,
//   ID_MAIN_FRAME_FILTER_NOT_CLASSIFIED,
//   ID_MAIN_FRAME_FILTER_ALL,
// 
//   // menu id in main frame
//   ID_MENU_INFO_ABOUT,
//   ID_MENU_BACKGROUND_COLOUR,
//   ID_MENU_SELECT_DIRECTORY,
// 
//   ID_FILTER_CTRL_END
// };
// #endif  // FILTERCTRL_APP_RESOURCE_ID_H_
#ifndef INCLUDED_GALLERY_RESOURCE_ID_H
#define INCLUDED_GALLERY_RESOURCE_ID_H

#include "wx/defs.h"

namespace csi {
  \

  enum {
    ID_GALLERY_CTRL_START = 0,

    // dental arch child windows id
    ID_GALLERY_DENTALARCH_PANEL,
    ID_GALLERY_DENTAL_ARCH,
    ID_GALLERY_FILTER_FMS,
    ID_GALLERY_FILTER_IO,
    ID_GALLERY_FILTER_PANO,
    ID_GALLERY_FILTER_CEPH,
    ID_GALLERY_FILTER_VOL,
    ID_GALLERY_FILTER_XO,
    ID_GALLERY_FILTER_MODEL,
    ID_GALLERY_FILTER_CAD,
    ID_GALLERY_FILTER_SCREENSHOT,
    ID_GALLERY_FILTER_EXTRACTED_SLICE,
    ID_GALLERY_FILTER_OTHERS,
    ID_GALLERY_FILTER_ALL,
    ID_GALLERY_BUTTON_PERMANENT,
    ID_GALLERY_BUTTON_MILK,

    // IDs for right click menu.
    ID_GALLERY_MENU,
    ID_GALLERY_MENU_OPEN,
    ID_GALLERY_MENU_SET_DEFAULT_PROGRAM,
    ID_GALLERY_MENU_CONVERT_TO,
    ID_GALLERY_MENU_SHOW_INFO_WINDOW,
    ID_GALLERY_MENU_LOCALIZE,
    ID_GALLERY_MENU_SEND_TO_PACS,
    ID_GALLERY_MENU_RETRIEVE_FROM_PACS,
    ID_GALLERY_MENU_DELETE,
    ID_GALLERY_MENU_COPY,
    ID_GALLERY_MENU_PRINT,
    ID_GALLERY_MENU_EXPORT_TO_FOLDER,
    ID_GALLERY_MENU_EXPORT_TO_EMAIL,
    ID_GALLERY_MENU_EXPORT_TO_DICOMDIR,
    ID_GALLERY_MENU_EXPORT_TO_CSCONNECT,
    ID_GALLERY_MENU_EXPORT_TO_MILLINGMACHINE,
    ID_GALLERY_MENU_ASSIGN_TO_ANOTHER_PATIENT,
    // ID for drag drop export event.
    ID_DRAG_DROP_EXPORT_EVENT,

    // PB Gallery
    ID_PB_GALLERY_THUMBNAIL_BUTTON,
    ID_PB_GALLERY_DETAIL_BUTTON,
    ID_PB_GALLERY_PREVIEW_BUTTON,
    ID_PB_GALLERY_CAROUSEL_BUTTON,
    ID_PB_GALLERY_DATE_LABEL,
    ID_PB_GALLERY_TYPE_LABEL,
    ID_PB_GALLERY_FILTER_LABEL,

    // PB gallery preview view.
    ID_PB_GALLERY_PREVIEW_VIEW_COMMENTS_TEXT_CTRL,

    // PB gallery carousel view.
    ID_PB_GALLERY_CAROUSEL_VIEW_COMMENTS_TEXT_CTRL,

    ID_GALLERY_WAITING_ANIMATION,

    //----------------------------------------------------------------------------

    ID_GALLERY_CTRL_END = 100
  };

}  // namespace csi

#endif