#pragma once
#include <wx/wx.h>
#include <wx/mediactrl.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>




class first_frm_m : public wxFrame  //First frame on start
{
public:
    first_frm_m(const wxString& title);

    wxMediaCtrl* Video;

    void OnMediaStop(wxMediaEvent& evt);

    wxButton* next_button;

    void next_b(wxCommandEvent& event);





};

class second_frm_m : public wxFrame  //second frame on start  (selection window)
{
public:
    second_frm_m(const wxString& title, const wxPoint& position, const wxSize& size);
    wxButton* add_update_face_button;
    wxButton* back_button;
    wxButton* unlock_button;
    wxButton* lock_button;
    void back(wxCommandEvent& event);
    void Add_update(wxCommandEvent& event);
    void unlock_(wxCommandEvent& event);
    void lock(wxCommandEvent& event);

};



class unlock : public wxFrame 
{
public:
    unlock(const wxString& title, const wxPoint& position, const wxSize& size);



    wxPanel* panel_3;
    wxBoxSizer* m_sizer;
    wxTimer m_timer;
    wxCheckListBox* checklist;
    wxButton* s;


    void Lock_FP();










};




