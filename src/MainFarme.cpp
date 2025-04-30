#include "MainFrame.hpp"
#include "FormPanel.hpp"
#include "Input.hpp"
MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1500, 900)) {

    m_formPanel = new FormPanel(this);
    this->Centre();
}
