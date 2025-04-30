#include "FormPanel.hpp"
#include "Input.hpp"
#include "Data.hpp"
#include "Fonction.hpp"
#include <vector>
#include <iostream>
#include "Joueur.hpp"
#include "Course.hpp"
#include <wx/msgdlg.h>
#include "JoueurCourse.hpp"
#include "Phase.hpp"

#include <wx/string.h>
#include <wx/wx.h>

using namespace std;
FormPanel::FormPanel(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{

    initialisation();
    m_submitBtn = new wxButton(this, wxID_ANY, "Validez");
    m_submitBtn->SetPosition(wxPoint(400, 10));
    m_submitBtn->Bind(wxEVT_BUTTON, &FormPanel::OnSubmit, this);
    wxArrayString choices;
    choices.Add("1");
    choices.Add("2");
    choices.Add("3");
    choices.Add("4");
    choices.Add("5");



    wxStaticText *titre_groupe = new wxStaticText(this, wxID_ANY, "Phase: ", wxDefaultPosition, wxSize(100, -1));
    titre_groupe->SetPosition(wxPoint(650, 20));
    combo = new wxComboBox(this, wxID_ANY, "Choisissez...",
                           wxPoint(700, 20), wxSize(200, -1), choices,
                           wxCB_DROPDOWN);

    // Événement quand une option est choisie
    combo->Bind(wxEVT_COMBOBOX, &FormPanel::OnComboSelect, this);

    // Input* timeInput = new Input(this, wxID_ANY, "Heure :", "hh:mm:ss:ff");
    // timeInput->SetPosition(wxPoint(10, 10)); // correct : majuscule S
    // timeInput->SetSize(wxSize(300, 40));
    // wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // m_nameCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    // m_emailCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    // m_submitBtn = new wxButton(this, wxID_ANY, "Envoyer");

    // vbox->Add(new wxStaticText(this, wxID_ANY, "Nom :"), 0, wxALL, 5);
    // vbox->Add(m_nameCtrl, 0, wxALL, 5);
    // vbox->Add(new wxStaticText(this, wxID_ANY, "Email :"), 0, wxALL, 5);
    // vbox->Add(m_emailCtrl, 0, wxALL, 5);
    // vbox->Add(m_submitBtn, 0, wxALL | wxALIGN_CENTER, 10);

    // SetSizer(vbox);

    // m_submitBtn->Bind(wxEVT_BUTTON, &FormPanel::OnSubmit, this);
}

void FormPanel::OnComboSelect(wxCommandEvent &event)
{
    wxString selection = combo->GetValue();
    Phase p = Phase::getById(stoi(selection.ToStdString()));
    p.initListStat(this);
    // wxMessageBox("Vous avez choisi : " + selection, "Choix");
}
void FormPanel::OnSubmit(wxCommandEvent &event)
{

    cout << "\n"
         << endl;
    // sauvegarde les valeurs des input

    // cout << "debug " << endl;
    vector<Input *> inputs = Data::curent_inputs;
    // cout << "size " << inputs.size() << endl;

    for (Input *input : inputs)
    {
        Course *newCourse = new Course(Fonction::getLastId("Course"), "C" + to_string(input->getIdJoueur()) + "P" + to_string(Data::idPhase));
        newCourse->save();
        JoueurCourse *newJoueurCourse = new JoueurCourse(Fonction::getLastId("JoueurCourse"), input->getIdJoueur(), newCourse->getId(), Data::idPhase, string(input->GetValue().ToUTF8()));
        newJoueurCourse->save();
        // cout << "idJ: " << input->getIdJoueur() << " time: " << input->GetValue() << endl;
    }
    // cout << "debug1 " << endl;

    // apiterahana ny current groupe
    vector<Groupe> new_current = {};
    int index_voisinage = 10 * Data::idPhase;
    int k = 0;

    for (Groupe g : Data::current_groupe)
    {
        if (k % 2 == 0 and g.getJoueurs().size() > 0)
        {
            index_voisinage++;
        }
        // cout << "groupe: " << g.getName() << endl;
        Groupe *fils = g.miteraka(Data::idPhase);
        fils->setIdVoisin(index_voisinage);
        fils->update();
        new_current.push_back(*fils);
        // cout << "getIdVoisin: " << fils->getIdVoisin() << endl;
        // cout << "getId: " << fils->getId() << endl;
        // cout << "fils: " << fils->getName() << endl;
        // cout << "fils_joueur_phase: " << *fils->getIdPhase() << endl;
        // for (Joueur j : fils->getJoueurs())
        // {
        // cout << "j: " << j.getName() << endl;
        // }
        k++;
    }
    Data::current_groupe = new_current;
    for (Input *input : Data::curent_inputs)
    {
        input->DestroyInput();
        // Course *newCourse = new Course(Fonction::getLastId("Course"), "C" + to_string(input->getIdJoueur()) + "P" + to_string(Data::idPhase));
        // newCourse->save();
        // JoueurCourse *newJoueurCourse = new JoueurCourse(Fonction::getLastId("JoueurCourse"), input->getIdJoueur(), newCourse->getId(), Data::idPhase, string(input->GetValue().ToUTF8()));
        // newJoueurCourse->save();
        // cout << "idJ: " << input->getIdJoueur() << " time: " << input->GetValue() << endl;
    }
    Data::curent_inputs.clear();
    // if (Data::idPhase == 1) {
    cout << "idPhase: " << Data::idPhase << endl;
    initialisation();
    // }
    Data::idPhase++;

    // wxString name = m_nameCtrl->GetValue();
    // wxString email = m_emailCtrl->GetValue();
    // cout << "hello " << endl;
    // wxMessageBox("Nom: ", wxOK | wxICON_INFORMATION);
}
void FormPanel::initialisation()
{
    double margin_y = 40;
    double y = 30;
    double x = 50;
    vector<Groupe> all_g = Data::current_groupe;
    for (int i = 0; i < all_g.size(); i++)
    {
        vector<Joueur> children = all_g[i].getJoueurs();
        cout << "phase" + to_string(Data::idPhase) + ": " << all_g[i].getName() << endl;

        for (Joueur jj : children)
        {
            // cout << "idJoueur: " << jj.getId() << " temps: " <<   Fonction::tempsToString(*jj.getTempsByPhase(Data::idPhase))    << endl;
            cout << "idJoueur: " << jj.getId() << " temps: " << Fonction::tempsToString(*jj.getTempsByPhase(Data::idPhase)) << endl;
        }
        // cout << "newInput: +++++++++++++++++++++++++++++++" << children.size() << endl;
        // wxStaticText* titre_groupe = new wxStaticText(this, wxID_ANY, all_g[i].getName(), wxDefaultPosition, wxSize(100, -1));
        // titre_groupe->SetPosition(wxPoint(250, y-30));
        for (int j = 0; j < children.capacity(); j++)
        {
            Input *timeInput = new Input(this, wxID_ANY, children[j].getName() + "-" + all_g[i].getName(), "hh:mm:ss:ff");
            timeInput->setIdJoueur(children[j].getId());
            timeInput->SetPosition(wxPoint(x, y));
            timeInput->SetSize(wxSize(300, 30));
            Data::curent_inputs.push_back(timeInput);
            y += margin_y;
        }
        y += margin_y + 20;
    }
}
