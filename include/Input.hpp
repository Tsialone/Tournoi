#ifndef INPUT_HPP
#define INPUT_HPP

#include <wx/wx.h>

class Input : public wxPanel {
public:
    Input(wxWindow* parent, wxWindowID id, const wxString& labelText, const wxString& placeholder);

    wxString GetValue() const;
    int getIdJoueur ();
    void setIdJoueur (int idJoueur);
    void SetValue(const wxString& value);
    void DestroyInput();
    wxString GenerateRandomTime();
    

private:
    int idJoueur;
    wxStaticText* m_label;

    wxTextCtrl* m_textCtrl;
};

#endif
