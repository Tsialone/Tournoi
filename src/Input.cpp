#include "Input.hpp"

Input::Input(wxWindow* parent, wxWindowID id, const wxString& labelText, const wxString& placeholder)
    : wxPanel(parent, wxID_ANY) {

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    m_label = new wxStaticText(this, wxID_ANY, labelText, wxDefaultPosition, wxSize(100, -1)); // largeur fixe
    wxString randomValue = GenerateRandomTime();
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, randomValue);

    if (!placeholder.IsEmpty()) {
        m_textCtrl->SetHint(placeholder); 
    }

    hbox->Add(m_label, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    hbox->Add(m_textCtrl, 1, wxEXPAND);

    SetSizer(hbox);
}
wxString Input::GenerateRandomTime() {
    wxString randomTime;
    for (int i = 0; i < 4; ++i) {
        // Générer un nombre aléatoire entre 0 et 59 pour les minutes et les secondes
        int value = (i == 0) ? (std::rand() % 24) : (std::rand() % 60); // 0-23 pour les heures, 0-59 pour les autres
        randomTime += wxString::Format("%02d", value);
        if (i < 3) {
            randomTime += ":"; // Ajouter un séparateur
        }
    }
    return randomTime;
}
void Input::DestroyInput() {
    // Détruire les contrôles
    if (m_label) {
        m_label->Destroy();
        m_label = nullptr; // Éviter les pointeurs pendants
    }
    if (m_textCtrl) {
        m_textCtrl->Destroy();
        m_textCtrl = nullptr; // Éviter les pointeurs pendants
    }
    
    // Détruire le panneau lui-même
    this->Destroy();
}
int Input::getIdJoueur() {
    return idJoueur;
}
void Input::setIdJoueur(int idJoueur){
    this->idJoueur =  idJoueur;
}

wxString Input::GetValue() const {
    return m_textCtrl->GetValue();
}

void Input::SetValue(const wxString& value) {
    m_textCtrl->SetValue(value);
}
