#include "FbReplaceDlg.h"
#include <wx/artprov.h>
#include "FbAuthorThread.h"
#include "FbConst.h"
#include "FbAuthorDlg.h"
#include "FbMasterData.h"

BEGIN_EVENT_TABLE( FbReplaceDlg, wxDialog )
	EVT_TEXT_ENTER( ID_FIND_TXT, FbReplaceDlg::OnFindEnter )
	EVT_BUTTON( ID_FIND_BTN, FbReplaceDlg::OnFindEnter )
END_EVENT_TABLE()

FbReplaceDlg::FbReplaceDlg( const wxString& title, int id )
	: FbDialog ( NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ), m_id(id)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizerGrid;
	fgSizerGrid = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerGrid->AddGrowableCol( 1 );
	fgSizerGrid->SetFlexibleDirection( wxBOTH );
	fgSizerGrid->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticText * m_static1 = new wxStaticText( this, wxID_ANY, _("Replace") + COLON, wxDefaultPosition, wxDefaultSize, 0 );
	m_static1->Wrap( -1 );
	fgSizerGrid->Add( m_static1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_Text = new wxTextCtrl( this, ID_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_Text->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	m_Text->SetMinSize( wxSize( 300,-1 ) );

	fgSizerGrid->Add( m_Text, 0, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );

	wxStaticText * m_static2 = new wxStaticText( this, wxID_ANY, _("Find") + COLON, wxDefaultPosition, wxDefaultSize, 0 );
	m_static2->Wrap( -1 );
	fgSizerGrid->Add( m_static2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizerFind;
	bSizerFind = new wxBoxSizer( wxHORIZONTAL );

	m_FindText = new wxTextCtrl( this, ID_FIND_TXT, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_PROCESS_ENTER );
	m_FindText->SetMinSize( wxSize( 250,-1 ) );
	m_FindText->SetFocus();

	bSizerFind->Add( m_FindText, 1, wxALIGN_CENTER_VERTICAL, 5 );

	m_FindBtn = new wxBitmapButton( this, ID_FIND_BTN, wxArtProvider::GetBitmap(wxART_FIND), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerFind->Add( m_FindBtn, 0, wxRIGHT|wxLEFT, 5 );

	fgSizerGrid->Add( bSizerFind, 0, wxEXPAND, 5 );

	bSizerMain->Add( fgSizerGrid, 0, wxEXPAND, 5 );

	m_FindList = new FbMasterList(this, ID_FIND_LIST, wxTR_HIDE_ROOT | wxTR_NO_LINES | wxTR_FULL_ROW_HIGHLIGHT | wxTR_COLUMN_LINES | wxSUNKEN_BORDER);
	bSizerMain->Add( m_FindList, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	m_FindList->AddColumn(_("Author"), 40, wxALIGN_LEFT);
	m_FindList->AddColumn(_("Num."), 10, wxALIGN_RIGHT);

	wxStdDialogButtonSizer * sdbSizerBtn = CreateStdDialogButtonSizer( wxOK | wxCANCEL );
	bSizerMain->Add( sdbSizerBtn, 0, wxEXPAND | wxALL, 5 );

	this->SetSizer( bSizerMain );
	this->Layout();
}

bool FbReplaceDlg::Load()
{
	wxString sql = wxT("SELECT full_name, last_name FROM authors WHERE id=?");
	wxSQLite3Statement stmt = m_database.PrepareStatement(sql);
	stmt.Bind(1, m_id);
	wxSQLite3ResultSet result = stmt.ExecuteQuery();

	if (result.NextRow()) {
		m_Text->SetValue(result.GetAsString(0));
		wxString last_name = result.GetAsString(1);
		if (!last_name.IsEmpty()) (new FbAuthorThreadLast(this, last_name))->Execute();
		return true;
	}
	return false;
}

void FbReplaceDlg::OnFindEnter( wxCommandEvent& event )
{
	wxString text = m_FindText->GetValue();
	if (!text.IsEmpty()) (new FbAuthorThreadRepl(m_FindList, text, m_id))->Execute();
}

int FbReplaceDlg::GetSelected()
{
	wxTreeItemId selected = m_FindList->GetSelection();
	if (selected.IsOk()) {
		FbMasterData * data = m_FindList->GetItemData(selected);
		if (data) return data->GetId();
	};
	return 0;
}

void FbReplaceDlg::EndModal(int retCode)
{
	if ( retCode == wxID_OK) {
		int author = GetSelected();
		if (author) {
			wxString msg = _("Merge authors?");
			wxString title = GetTitle() + wxT("…");
			bool ok = wxMessageBox(msg, title, wxOK | wxCANCEL | wxICON_QUESTION) == wxOK;
			if (!ok) return;
		} else {
			wxMessageBox(_("Author not selected by replacement."), GetTitle());
			return;
		}
	}
	FbDialog::EndModal(retCode);
}

int FbReplaceDlg::DoUpdate()
{
	int selected = GetSelected();
	FbAuthorDlg::ReplaceAuthor(m_id, selected);
	return selected;
}

wxString FbReplaceDlg::GetFullName()
{
	wxTreeItemId selected = m_FindList->GetSelection();
	return selected.IsOk() ? m_FindList->GetItemText(selected) : (wxString)wxEmptyString;
}

int FbReplaceDlg::Execute(int author, wxString& newname)
{
	FbReplaceDlg dlg(_("Replace author"), author);
	bool ok = dlg.Load() && dlg.ShowModal() == wxID_OK;
	if (ok) newname = dlg.GetFullName();
	return ok ? dlg.DoUpdate() : 0;
}
