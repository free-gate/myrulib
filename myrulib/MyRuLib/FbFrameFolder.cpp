#include "FbFrameFolder.h"
#include <wx/artprov.h>
#include "FbBookMenu.h"
#include "FbMainMenu.h"
#include "FbConst.h"
#include "FbDatabase.h"
#include "FbDownloader.h"

BEGIN_EVENT_TABLE(FbFrameFolder, FbFrameBase)
	EVT_MENU(ID_FAVORITES_DEL, FbFrameFolder::OnFavoritesDel)
	EVT_MENU(ID_APPEND_FOLDER, FbFrameFolder::OnFolderAppend)
	EVT_MENU(ID_MODIFY_FOLDER, FbFrameFolder::OnFolderModify)
	EVT_MENU(ID_DELETE_FOLDER, FbFrameFolder::OnFolderDelete)
	EVT_TREE_SEL_CHANGED(ID_MASTER_LIST, FbFrameFolder::OnFolderSelected)
END_EVENT_TABLE()

FbFrameFolder::FbFrameFolder(wxAuiMDIParentFrame * parent)
	:FbFrameBase(parent, ID_FRAME_FOLDER, _("Мои папки")), m_FolderBar(NULL)
{
	CreateControls();
}

void FbFrameFolder::CreateControls()
{
	SetMenuBar(new FbFrameMenu);

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bToolSizer = new wxBoxSizer( wxHORIZONTAL );

	m_FolderBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORZ_TEXT|wxTB_NODIVIDER|wxTB_NOICONS|wxTB_FLAT );
	m_FolderBar->SetFont(FbParams::GetFont(FB_FONT_TOOL));
	m_FolderBar->AddTool( ID_APPEND_FOLDER, _("Добавить"), wxNullBitmap);
	m_FolderBar->AddTool( ID_MODIFY_FOLDER, _("Изменить"), wxNullBitmap);
	m_FolderBar->AddTool( ID_DELETE_FOLDER, _("Удалить"), wxNullBitmap);
	m_FolderBar->Realize();
	bToolSizer->Add( m_FolderBar, 0, wxALIGN_CENTER_VERTICAL);

	m_ToolBar  = CreateToolBar(wxTB_FLAT|wxTB_NODIVIDER|wxTB_HORZ_TEXT, wxID_ANY, GetTitle());
	bToolSizer->Add( m_ToolBar, 1, wxALIGN_CENTER_VERTICAL);

	bSizer1->Add( bToolSizer, 0, wxEXPAND);

	wxSplitterWindow * splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxSP_NOBORDER);
	splitter->SetMinimumPaneSize(50);
	splitter->SetSashGravity(0.33);
	bSizer1->Add(splitter, 1, wxEXPAND);

	m_MasterList = new FbMasterList(splitter, ID_MASTER_LIST);
	m_MasterList->AddColumn (_("Папки"), 100, wxALIGN_LEFT);
	m_MasterList->SetFocus();

	long substyle = wxTR_HIDE_ROOT | wxTR_FULL_ROW_HIGHLIGHT | wxTR_COLUMN_LINES | wxTR_MULTIPLE | wxSUNKEN_BORDER;
	CreateBooksPanel(splitter, substyle);
	splitter->SplitVertically(m_MasterList, m_BooksPanel, 160);

	FillFolders();

	SetSizer( bSizer1 );

	FbFrameBase::CreateControls();
}

void FbFrameFolder::FillFolders(const int iCurrent)
{
	m_MasterList->Freeze();
	m_MasterList->DeleteRoot();

	wxTreeItemId root = m_MasterList->AddRoot(wxEmptyString);

	wxTreeItemId parent = m_MasterList->AppendItem(root, _("Закладки"));
	m_MasterList->SetItemBold(parent, true);

	wxTreeItemId item = m_MasterList->AppendItem(parent, _("Избранное"), -1, -1, new FbMasterFolder(0, FT_FOLDER));
	if (iCurrent == 0) m_MasterList->SelectItem(item);

	wxString sql = wxT("SELECT id, value FROM folders ORDER BY value");
	FbLocalDatabase database;
	wxSQLite3ResultSet result = database.ExecuteQuery(sql);
	while (result.NextRow()) {
		int id = result.GetInt(0);
		wxString name = result.GetString(1);
		wxTreeItemId item = m_MasterList->AppendItem(parent, name, -1, -1, new FbMasterFolder(id, FT_FOLDER));
		if (iCurrent == id) m_MasterList->SelectItem(item);
	}
	m_MasterList->Expand(parent);
	m_MasterList->Expand(root);

	parent = m_MasterList->AppendItem(root, _("Пометки"));
	m_MasterList->SetItemBold(parent, true);

	m_MasterList->AppendItem(parent, _("Комментарии"), -1, -1, new FbMasterFolder(1, FT_COMMENT));
	m_MasterList->AppendItem(parent, strRating[5], -1, -1, new FbMasterFolder(5, FT_RATING));
	m_MasterList->AppendItem(parent, strRating[4], -1, -1, new FbMasterFolder(4, FT_RATING));
	m_MasterList->AppendItem(parent, strRating[3], -1, -1, new FbMasterFolder(3, FT_RATING));
	m_MasterList->AppendItem(parent, strRating[2], -1, -1, new FbMasterFolder(2, FT_RATING));
	m_MasterList->AppendItem(parent, strRating[1], -1, -1, new FbMasterFolder(1, FT_RATING));
	m_MasterList->Expand(parent);

	m_MasterList->Thaw();
}

void FbFrameFolder::OnFolderSelected(wxTreeEvent & event)
{
	wxTreeItemId selected = event.GetItem();
	if (selected.IsOk()) {
		m_BooksPanel->EmptyBooks();
		FbMasterData * data = m_MasterList->GetItemData(selected);
		if (data) {
			bool enabled = data->GetType() == FT_FOLDER && data->GetId();
			m_FolderBar->EnableTool(ID_MODIFY_FOLDER, enabled);
			m_FolderBar->EnableTool(ID_DELETE_FOLDER, enabled);
			data->Show(this);
		}
	}
}

void FbFrameFolder::UpdateBooklist()
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (data) data->Show(this);
}

void FbFrameFolder::OnFavoritesDel(wxCommandEvent & event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (!data) return;
	int iFolder = data->GetId();

	wxString selected = m_BooksPanel->m_BookList->GetSelected();
	wxString sql = wxString::Format(wxT("DELETE FROM favorites WHERE md5sum IN (SELECT books.md5sum FROM books WHERE id IN (%s)) AND id_folder=%d"), selected.c_str(), iFolder);

	FbCommonDatabase database;
	database.AttachConfig();
	database.ExecuteUpdate(sql);

	FbTreeListUpdater updater(m_BooksPanel->m_BookList);

	wxArrayInt items;
	m_BooksPanel->m_BookList->GetSelected(items);
	m_BooksPanel->m_BookList->DeleteItems(items);
}

void FbFrameFolder::OnFolderAppend(wxCommandEvent & event)
{
	wxString name = wxGetTextFromUser(_("Введите имя новой папки:"), _("Добавить папку?"), wxEmptyString, this);
	if (name.IsEmpty()) return;

	FbLocalDatabase database;
	int id = database.NewId(FB_NEW_FOLDER);
	wxString sql = wxT("INSERT INTO folders(value,id) VALUES(?,?)");
	wxSQLite3Statement stmt = database.PrepareStatement(sql);
	stmt.Bind(1, name);
	stmt.Bind(2, id);
	stmt.ExecuteUpdate();

	FbMenuFolders::EmptyFolders();
	m_BooksPanel->EmptyBooks();
	FillFolders(id);
}

void FbFrameFolder::OnFolderModify(wxCommandEvent & event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (!data) return;
	if (data->GetType() != FT_FOLDER) return;
	int id = data->GetId();
	if (!id) return;

	wxTreeItemId item = m_MasterList->GetSelection();
	wxString name = m_MasterList->GetItemText(item);;
	name = wxGetTextFromUser(_("Введите новое имя папки:"), _("Изменить папку?"), name, this);
	if (name.IsEmpty()) return;

	FbLocalDatabase database;
	wxString sql = wxT("UPDATE folders SET value=? WHERE id=?");
	wxSQLite3Statement stmt = database.PrepareStatement(sql);
	stmt.Bind(1, name);
	stmt.Bind(2, id);
	stmt.ExecuteUpdate();

	FbMenuFolders::EmptyFolders();
	FillFolders(id);
}

void FbFrameFolder::OnFolderDelete(wxCommandEvent & event)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (!data) return;
	if (data->GetType() != FT_FOLDER) return;
	int id = data->GetId();
	if (!id) return;

	wxTreeItemId item = m_MasterList->GetSelection();
	wxString name = m_MasterList->GetItemText(item);;
	wxString msg = wxString::Format(_("Удалить папку «%s»?"), name.c_str());
	int answer = wxMessageBox(msg, _("Удалить папку?"), wxOK | wxCANCEL, this);
	if (answer != wxOK) return;

	FbLocalDatabase database;
	wxString sql = wxT("DELETE FROM folders WHERE id=?");
	wxSQLite3Statement stmt = database.PrepareStatement(sql);
	stmt.Bind(1, id);
	stmt.ExecuteUpdate();

	sql = wxT("DELETE FROM favorites WHERE id_folder=?");
	stmt = database.PrepareStatement(sql);
	stmt.Bind(1, id);
	stmt.ExecuteUpdate();

	FbMenuFolders::EmptyFolders();
	m_BooksPanel->EmptyBooks();
	FillFolders(0);
}

void FbFrameFolder::UpdateFolder(const int iFolder, const FbFolderType type)
{
	FbMasterData * data = m_MasterList->GetSelectedData();
	if (!data) return;
	if (data->GetType()!= type) return;

	bool bNeedUpdate = false;
	switch (type) {
		case FT_FOLDER:
			bNeedUpdate = data->GetId()==iFolder;
			break;
		default:
			bNeedUpdate = true;
			break;
	}

	if (bNeedUpdate) data->Show(this);
}

void FbFrameFolder::ShowFullScreen(bool show)
{
	if (m_FolderBar) m_FolderBar->Show(!show);
	if (m_ToolBar) m_ToolBar->Show(!show);
	Layout();
}
