#include "FbFrameFavour.h"
#include <wx/artprov.h>
#include "FbConst.h"
#include "FbDatabase.h"
#include "FbManager.h"
#include "BooksPanel.h"
#include "FbGenres.h"
#include "FbClientData.h"
#include "MyRuLibApp.h"

BEGIN_EVENT_TABLE(FbFrameFavour, FbFrameBase)
    EVT_MENU(ID_MODE_TREE, FbFrameFavour::OnChangeMode)
    EVT_MENU(ID_MODE_LIST, FbFrameFavour::OnChangeMode)
    EVT_LISTBOX(ID_FOLDER_LIST, FbFrameFavour::OnFolderSelected)
END_EVENT_TABLE()

FbFrameFavour::FbFrameFavour(wxAuiMDIParentFrame * parent, wxWindowID id,const wxString & title)
    :FbFrameBase(parent, id, title)
{
    CreateControls();
}

void FbFrameFavour::CreateControls()
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	SetMenuBar(CreateMenuBar());

	wxToolBar * toolbar = CreateToolBar(wxTB_FLAT|wxTB_NODIVIDER|wxTB_HORZ_TEXT, wxID_ANY, GetTitle());
	bSizer1->Add( toolbar, 0, wxGROW);

	wxSplitterWindow * splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxSP_NOBORDER);
	splitter->SetMinimumPaneSize(50);
	splitter->SetSashGravity(0.33);
	bSizer1->Add(splitter, 1, wxEXPAND);

	m_FolderList = new wxListBox(splitter, ID_FOLDER_LIST);
	FillFolders();

	long substyle = wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT | wxTR_COLUMN_LINES | wxTR_MULTIPLE | wxSUNKEN_BORDER;
	m_BooksPanel.Create(splitter, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxNO_BORDER, substyle);
	splitter->SplitVertically(m_FolderList, &m_BooksPanel, 160);

    m_BooksPanel.CreateColumns(GetListMode(FB_MODE_FAVOUR));

	SetSizer( bSizer1 );
	Layout();
}

wxToolBar * FbFrameFavour::CreateToolBar(long style, wxWindowID winid, const wxString& name)
{
    wxToolBar * toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, style, name);
	toolbar->AddTool(wxID_SAVE, _("Экспорт"), wxArtProvider::GetBitmap(wxART_FILE_SAVE), _("Запись на внешнее устройство"));
	toolbar->Realize();
    return toolbar;
}

void FbFrameFavour::FillFolders()
{
	m_FolderList->Freeze();
	m_FolderList->Clear();

    m_FolderList->Append(_("Избранное"), new FbClientData(0));

	FbDatabase & m_database = * wxGetApp().GetConfigDatabase();
    wxString sql = wxT("SELECT id, value FROM folders ORDER BY value");
    wxSQLite3ResultSet result = m_database.ExecuteQuery(sql);
    while (result.NextRow()) {
        int id = result.GetInt(0);
        wxString name = result.GetString(1);
        m_FolderList->Append(name, new FbClientData(id));
    }

	m_FolderList->Thaw();
}

class FrameFavourThread: public FbFrameBaseThread
{
    public:
        FrameFavourThread(wxWindow * frame, FbListMode mode, const int folder)
			:FbFrameBaseThread(frame, mode), m_folder(folder), m_number(sm_skiper.NewNumber()) {};
        virtual void *Entry();
    private:
		static FbThreadSkiper sm_skiper;
        int m_folder;
        int m_number;
};

FbThreadSkiper FrameFavourThread::sm_skiper;

void * FrameFavourThread::Entry()
{
	wxCriticalSectionLocker locker(sm_queue);

	if (sm_skiper.Skipped(m_number)) return NULL;
	EmptyBooks();

	wxString condition = wxT("books.md5sum IN (SELECT DISTINCT md5sum FROM favorites WHERE id_folder = ?)");
	wxString sql = GetSQL(condition);

	FbCommonDatabase database;
	database.AttachConfig();
	FbGenreFunction function;
    wxSQLite3Statement stmt = database.PrepareStatement(sql);
    stmt.Bind(1, m_folder);
    wxSQLite3ResultSet result = stmt.ExecuteQuery();

	if (sm_skiper.Skipped(m_number)) return NULL;
    FillBooks(result);

	return NULL;
}

void FbFrameFavour::OnFolderSelected(wxCommandEvent & event)
{
	FbClientData * data = (FbClientData*)event.GetClientObject();

	if (data) {
		wxThread * thread = new FrameFavourThread(this, m_BooksPanel.GetListMode(), data->GetID());
		if ( thread->Create() == wxTHREAD_NO_ERROR ) thread->Run();
	}
}

void FbFrameFavour::OnChangeMode(wxCommandEvent& event)
{
	FbListMode mode = event.GetId() == ID_MODE_TREE ? FB2_MODE_TREE : FB2_MODE_LIST;
	SetListMode(FB_MODE_FAVOUR, mode);

	m_BooksPanel.CreateColumns(mode);

    int iSelected = m_FolderList->GetSelection();
    if (iSelected == wxNOT_FOUND) return;
    FbClientData * data = (FbClientData*) m_FolderList->GetClientObject(iSelected);

	if (data) {
		wxThread * thread = new FrameFavourThread(this, m_BooksPanel.GetListMode(), data->GetID());
		if ( thread->Create() == wxTHREAD_NO_ERROR ) thread->Run();
	}
}
