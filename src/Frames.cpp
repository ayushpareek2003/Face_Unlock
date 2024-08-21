#include "Frames.h"
#include "add_update.h"
#include "opencv2/objdetect.hpp"
#include <filesystem>
#include <fstream>

first_frm_m::first_frm_m(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);


    panel->SetBackgroundColour(*wxBLACK);

    // Create wxMediaCtrl and set its size to fill the entire panel



    Video = new wxMediaCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);

    wxString filename = wxT("D:/videos/animation.mp4");

    if (!Video->Load(filename))
    {
        wxMessageBox("Failed to load the animation video", "Error", wxICON_ERROR);
        return;
    }

    Video->Bind(wxEVT_MEDIA_STOP, &first_frm_m::OnMediaStop, this, Video->GetId());

    // Create the vertical sizer for the main layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add the video to the sizer with proportion 1 to take all available space
    mainSizer->Add(Video, 1, wxEXPAND | wxALL, 5);

    // Create the horizontal sizer for the button at the bottom
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->AddStretchSpacer(1);  // Add stretchable space before the button


    next_button = new wxButton(panel, wxID_ANY, "Next", wxDefaultPosition, wxSize(100, 35));
    buttonSizer->Add(next_button, 0, wxALL, 5);
    buttonSizer->AddStretchSpacer(1);  // Add stretchable space after the button

    // Add the button sizer to the main sizer at the bottom
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    // Set the sizer for the panel
    panel->SetSizer(mainSizer);
    panel->Layout();

    next_button->Bind(wxEVT_BUTTON, &first_frm_m::next_b, this);

}

void first_frm_m::OnMediaStop(wxMediaEvent& evt)
{
    Video->Seek(0);
    Video->Play();
        int durationInSeconds = 6;
       auto duration = std::chrono::seconds(durationInSeconds);
       std::this_thread::sleep_for(duration);
      Video->Pause();

}

void first_frm_m::next_b(wxCommandEvent& event)
{

   second_frm_m* s_f = new second_frm_m("Face_ID", this->GetPosition(), this->GetSize());
   s_f->Show();
   this->Hide();
  

}

second_frm_m::second_frm_m(const wxString& title, const wxPoint& position,const wxSize& size):wxFrame(nullptr, wxID_ANY, title, position, size)    //feature selection 
{
    wxPanel* panel_2 = new wxPanel(this, wxID_ANY);
    panel_2->SetBackgroundColour(*wxBLACK);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

   
    wxBoxSizer* addUpdateButtonSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* backButtonSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* lockButtonSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* unlockButtonSizer = new wxBoxSizer(wxVERTICAL);

    
    add_update_face_button = new wxButton(panel_2, wxID_ANY, "Add/Update Face Data", wxDefaultPosition, wxDefaultSize);
    back_button = new wxButton(panel_2, wxID_ANY, "Back", wxDefaultPosition, wxDefaultSize);
    lock_button = new wxButton(panel_2, wxID_ANY, "Lock", wxDefaultPosition, wxDefaultSize);
    unlock_button = new wxButton(panel_2, wxID_ANY, "Unlock", wxDefaultPosition, wxDefaultSize);

  
    addUpdateButtonSizer->AddStretchSpacer(1);
    addUpdateButtonSizer->Add(add_update_face_button, 0, wxALL | wxEXPAND, 5);
    addUpdateButtonSizer->AddStretchSpacer(1);

    backButtonSizer->AddStretchSpacer(1);
    backButtonSizer->Add(back_button, 0, wxALL | wxEXPAND, 5);
    backButtonSizer->AddStretchSpacer(1);

    lockButtonSizer->AddStretchSpacer(1);
    lockButtonSizer->Add(lock_button, 0, wxALL | wxEXPAND, 5);
    lockButtonSizer->AddStretchSpacer(1);

    unlockButtonSizer->AddStretchSpacer(1);
    unlockButtonSizer->Add(unlock_button, 0, wxALL | wxEXPAND, 5);
    unlockButtonSizer->AddStretchSpacer(1);
//
//    // Add the button sizers to the main sizer
    mainSizer->Add(backButtonSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);  // Center Left
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(unlockButtonSizer, 0, wxALIGN_TOP | wxALL, 5);  // Center Top
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(addUpdateButtonSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);  // Center Right
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(lockButtonSizer, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);  // Center Right


    //binding our buttons
    add_update_face_button->Bind(wxEVT_BUTTON,&second_frm_m::Add_update, this);
    unlock_button->Bind(wxEVT_BUTTON, &second_frm_m::unlock_, this);

    // Set the sizer for panel_2
    panel_2->SetSizer(mainSizer);
    panel_2->Layout();



}

void second_frm_m::back(wxCommandEvent& event)
{

}

void second_frm_m::Add_update(wxCommandEvent& event)
{
    //int flag = 0;
    ////if (flag == 1){
    ////    // agr flag=1 means ki data exist usko delete krengey uska code baadme
    ////}
    /*cv::CascadeClassifier face_cascade("D:\\harcascade\\haarcascade_frontalface_default.xml");*/
    add_update call; 
    call.Data_au();


}


void second_frm_m::unlock_(wxCommandEvent& event)
{
    unlock* frm_3 = new unlock("Face_ID", this->GetPosition(), this->GetSize());
    frm_3->SetClientSize(this->GetSize());
    frm_3->SetPosition(this->GetPosition());
    frm_3->Show();
    this->Hide();
   
}

void second_frm_m::lock(wxCommandEvent& event)
{


}

unlock::unlock(const wxString& title,const wxPoint& point,const wxSize& size) :wxFrame(nullptr, wxID_ANY, title)  
//setting up face data (first launch and in feature selection)
{

    // Create the main panel
    wxPanel* panel_3 = new wxPanel(this, wxID_ANY,this->GetPosition(), this->GetSize());
    panel_3->SetBackgroundColour(*wxBLACK);



    // Create the main horizontal sizer
    wxBoxSizer* m_sizer = new wxBoxSizer(wxHORIZONTAL);
    

    // Create the checklist and its vertical sizer
    wxBoxSizer* checklistsiz = new wxBoxSizer(wxVERTICAL);
    checklist = new wxCheckListBox(panel_3, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    // Add stretch spacers to center the checklist vertically
    checklistsiz->AddStretchSpacer(1);
    checklistsiz->Add(checklist, 0, wxALL | wxEXPAND, 5);
    checklistsiz->AddStretchSpacer(1);

    // Add the checklist sizer to the panel's sizer
  

    // Add the panel to the main sizer with specific proportions
    m_sizer->Add(panel_3, 1, wxEXPAND | wxALL, 5);

    // Optionally add a stretch spacer to push the checklist to the left
    m_sizer->AddStretchSpacer(1);

    // Set the main sizer and trigger the layout recalculation
    this->SetSizerAndFit(m_sizer);
    this->Layout();

  
}

void unlock::Lock_FP() {
    
  
    const std::string path = "Path_to_file_conatining paths of locked folders";
    std::ifstream filesys(path);
    std::vector<std::string> paths;
    int a;
    filesys >> a;

    for (int i = 0; i < a; i++) {
        std::string temp;
        filesys >> temp;
        paths.push_back(temp);


    }




}
