/**
 * @date 2024.11.05
 * @author yuanluo2
 * @brief a digital clock written in C++, with wxWidgets 3.2
 * @details program based on at least c++11, try to compile with:
 *          g++ digital_clock.cpp `wx-config --libs --cxxflags` -O3 -o digital_clock
 */
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/datetime.h>
#include <wx/display.h>

class DigitalClockFrame : public wxFrame {
    wxTimer* timer;
    wxStaticText* text;

    wxDECLARE_EVENT_TABLE();

    void window_not_resizable() {
        SetWindowStyleFlag(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));
    }

    void window_always_on_top() {
        SetWindowStyleFlag(GetWindowStyleFlag() | wxSTAY_ON_TOP);
    }

    wxPoint determine_position() {
        wxDisplay display(wxDisplay::GetFromWindow(this));
        wxRect screenRect = display.GetClientArea();
        int x = screenRect.GetRight() - GetSize().GetWidth();
        int y = screenRect.GetTop() + 30;
        return wxPoint(x, y);
    }

    void update_time() {
        wxDateTime now = wxDateTime::Now();
        wxString nowStr = now.FormatISOTime();
        text->SetLabel(nowStr);
    }
public:
    DigitalClockFrame(const wxString& title) 
        : wxFrame{ nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 120) }
    {
        window_not_resizable();
        window_always_on_top();

        wxPanel* panel = new wxPanel(this, wxID_ANY);
        panel->SetBackgroundColour(wxColour(0, 0, 0));   // set to black.

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxFont font{ 39, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD };
        text = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        text->SetFont(font);
        text->SetForegroundColour(wxColour(57, 197, 187));

        sizer->Add(text, 1, wxALIGN_CENTER | wxALL, 20);
        panel->SetSizer(sizer);

        timer = new wxTimer(this, wxID_ANY);
        timer->Start(1000);   // update every second.

        SetPosition(determine_position());
        update_time();
    }

    void event_on_timer(wxTimerEvent& event) {
        update_time();
    }
};

wxBEGIN_EVENT_TABLE(DigitalClockFrame, wxFrame)
    EVT_TIMER(wxID_ANY, DigitalClockFrame::event_on_timer)
wxEND_EVENT_TABLE()

class App : public wxApp {
public:
    virtual bool OnInit() override {
        DigitalClockFrame* frame = new DigitalClockFrame("Miku Clock");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(App);
