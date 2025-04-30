#ifndef FORMPANEL_HPP
#define FORMPANEL_HPP
#include <wx/wx.h>

class FormPanel : public wxPanel {
public:
    FormPanel(wxWindow* parent);
    void initialisation ();
    void  premierePhase ();

private:
    wxTextCtrl* m_nameCtrl;
    wxTextCtrl* m_emailCtrl;
    wxButton* m_submitBtn;
    wxComboBox* combo;

    void OnComboSelect(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);
};

#endif
