#include "entry.hpp"

#include "Frames.hpp"

/*g 
wxwidget main
*/
bool entry::OnInit()
{
    first_frm_m* mframe = new first_frm_m("To-Do Application");
    mframe->SetClientSize(800, 600);
    mframe->Show();
    return true;

}
wxIMPLEMENT_APP(entry);