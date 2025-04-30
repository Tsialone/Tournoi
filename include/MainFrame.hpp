#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>

class FormPanel;

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    FormPanel* m_formPanel;
};

#endif
