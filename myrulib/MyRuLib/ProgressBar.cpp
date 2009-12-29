#include "ProgressBar.h"

// Event table
BEGIN_EVENT_TABLE(ProgressBar, wxStatusBar)
   EVT_SIZE(ProgressBar::OnSize)
END_EVENT_TABLE()

ProgressBar::ProgressBar(wxWindow *parent, wxWindowID id, long style, const wxString &name)
	: wxStatusBar(parent, id, style, name)
{
	Create(parent, id, style, name);
}

bool ProgressBar::Create(wxWindow* parent, wxWindowID id, long style, const wxString& name)
{
	bool res = wxStatusBar::Create(parent, id, style, name);
	if (res) {
		m_progress.Create(this, -1, 100, wxPoint(0, 0), wxDefaultSize, wxGA_HORIZONTAL | wxGA_SMOOTH);
		m_progress.SetRange(1000);
		SetProgress(0);
		Resize();
	}
	return res;
}

void ProgressBar::Resize()
{
	if (GetFieldsCount()<=1) return ;

	wxRect r;
	GetFieldRect(1, r);
	m_progress.SetSize(r);
}

void ProgressBar::SetProgress(int progress)
{
   m_progress.Show(progress > 0);
   m_progress.SetValue(progress);
   Resize();
}
