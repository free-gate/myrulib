///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 29 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include <wx/artprov.h>
#include <wx/statline.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/notebook.h>
#include <wx/textdlg.h>
#include <wx/settings.h>
#include "FbParams.h"
#include "FbConst.h"
#include "FbBookEvent.h"
#include "SettingsDlg.h"
#include "ZipReader.h"
#include "MyRuLibApp.h"
#include "FbViewerDlg.h"

///////////////////////////////////////////////////////////////////////////

class TypeListCtrl: public wxListCtrl
{
	public:
		TypeListCtrl( wxWindow *parent, wxWindowID winid = wxID_ANY, long style = wxLC_REPORT);
		void OnSize(wxSizeEvent& event);
		DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TypeListCtrl, wxListCtrl)
	EVT_SIZE(TypeListCtrl::OnSize)
END_EVENT_TABLE()

TypeListCtrl::TypeListCtrl( wxWindow *parent, wxWindowID winid, long style)
	:wxListCtrl( parent, winid, wxDefaultPosition, wxDefaultSize, style)
{
}

void TypeListCtrl::OnSize(wxSizeEvent& event)
{
	event.Skip();

	if (GetColumnCount() == 2){
//		int w = GetClientSize().x - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X) - 6;
		int w = GetClientSize().x;
		SetColumnWidth(1, 50);
		SetColumnWidth(1, w - 50);
	}
}

///////////////////////////////////////////////////////////////////////////

SettingsDlg::FbPanelFont::FbPanelFont(wxWindow *parent)
	:wxPanel(parent)
{
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizerList;
	fgSizerList = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerList->AddGrowableCol( 1 );
	fgSizerList->SetFlexibleDirection( wxBOTH );
	fgSizerList->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	AppendItem(fgSizerList, _("List of authors and books:"), ID_FONT_MAIN);
	AppendItem(fgSizerList, _("Toolbar:"), ID_FONT_TOOL);
	AppendItem(fgSizerList, _("Information:"), ID_FONT_HTML);
	AppendItem(fgSizerList, _("Dialog windows:"), ID_FONT_DLG);

	bSizerMain->Add( fgSizerList, 0, wxEXPAND, 5 );

	wxButton * btnClear = new wxButton( this, ID_FONT_CLEAR, _("Reset fonts settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMain->Add( btnClear, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	this->SetSizer( bSizerMain );
	this->Layout();
}

void SettingsDlg::FbPanelFont::AppendItem(wxFlexGridSizer* fgSizer, const wxString& name, wxWindowID winid)
{
	wxStaticText * stTitle;
	stTitle = new wxStaticText( this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, 0 );
	stTitle->Wrap( -1 );
	fgSizer->Add( stTitle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxFontPickerCtrl * fpValue;
	fpValue = new wxFontPickerCtrl( this, winid, wxNullFont, wxDefaultPosition, wxDefaultSize, wxFNTP_DEFAULT_STYLE|wxFNTP_USE_TEXTCTRL );
	fpValue->SetMaxPointSize( 100 );
	fgSizer->Add( fpValue, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
}

///////////////////////////////////////////////////////////////////////////

SettingsDlg::FbPanelInternet::FbPanelInternet(wxWindow *parent)
	:wxPanel(parent)
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxCheckBox * m_checkBox13 = new wxCheckBox( this, ID_AUTO_DOWNLD, _("Automatically begin files downloading"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_checkBox13, 0, wxEXPAND|wxALL, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	wxCheckBox * m_checkBox12 = new wxCheckBox( this, ID_USE_PROXY, _("Use proxy-server"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_checkBox12, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	wxComboBox * m_comboBox2 = new wxComboBox( this, ID_PROXY_ADDR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBox2->Append( wxT("192.168.0.1:3128") );
	m_comboBox2->Append( wxT("172.16.0.1:3128") );
	m_comboBox2->Append( wxT("10.0.0.1:3128") );
	bSizer13->Add( m_comboBox2, 1, wxALL, 5 );

	bSizer2->Add( bSizer13, 0, wxEXPAND, 5 );

	wxCheckBox * checkBox3 = new wxCheckBox( this, ID_HTTP_IMAGES, _("Load images for author's description"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( checkBox3, 0, wxALL, 5 );

	wxStaticText * m_staticText6 = new wxStaticText( this, wxID_ANY, _("Folder to save downloads:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer2->Add( m_staticText6, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5 );

	wxBoxSizer* bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	wxTextCtrl * m_textCtrl6 = new wxTextCtrl( this, ID_DOWNLOAD_DIR_TXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl6->SetMinSize( wxSize( 300,-1 ) );
	bSizer14->Add( m_textCtrl6, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBitmapButton * m_bpButton6 = new wxBitmapButton( this, ID_DOWNLOAD_DIR_BTN, wxArtProvider::GetBitmap(wxART_FOLDER_OPEN), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer14->Add( m_bpButton6, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );

	bSizer2->Add( bSizer14, 0, wxEXPAND, 5 );

	wxCheckBox * m_checkBox14 = new wxCheckBox( this, ID_DEL_DOWNLOAD, _("Delete downloaded files when download query removed"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_checkBox14, 0, wxALL, 5 );

	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );
}

SettingsDlg::FbPanelTypes::FbPanelTypes(wxWindow *parent)
	:wxPanel(parent)
{
	wxBoxSizer * bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );

	wxToolBar * toolbar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORZ_TEXT|wxTB_NODIVIDER );
	toolbar->AddTool( ID_APPEND_TYPE, _("Append"), wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK));
	toolbar->AddTool( ID_MODIFY_TYPE, _("Modify"), wxArtProvider::GetBitmap(wxART_FILE_OPEN));
	toolbar->AddTool( ID_DELETE_TYPE, _("Delete"), wxArtProvider::GetBitmap(wxART_DEL_BOOKMARK));
	toolbar->Realize();

	bSizer->Add( toolbar, 0, wxALL|wxEXPAND, 5 );

	TypeListCtrl * typelist = new TypeListCtrl( this, ID_TYPELIST, wxLC_REPORT|wxLC_VRULES|wxSUNKEN_BORDER );
	typelist->InsertColumn(0, _("Extension"), wxLIST_FORMAT_LEFT, 50);
	typelist->InsertColumn(1, _("Program"), wxLIST_FORMAT_LEFT, 300);

	bSizer->Add( typelist, 1, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );

	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
}

SettingsDlg::FbPanelInterface::FbPanelInterface(wxWindow *parent)
	:wxPanel(parent)
{
	wxCheckBox * checkbox;
	wxBoxSizer * bSizer = new wxBoxSizer( wxVERTICAL );

	checkbox = new wxCheckBox( this, ID_SAVE_FULLPATH, _("Save full path of the file when importing"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( checkbox, 0, wxALL, 5 );

	wxStaticText * text = new wxStaticText( this, wxID_ANY, _("Temporary folder:"), wxDefaultPosition, wxDefaultSize, 0 );
	text->Wrap( -1 );
	bSizer->Add( text, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5 );

	{
		wxBoxSizer* bSizerDir = new wxBoxSizer( wxHORIZONTAL );

		wxTextCtrl * edit = new wxTextCtrl( this, ID_TEMP_DIR_TXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
		edit->SetMinSize( wxSize( 300,-1 ) );
		bSizerDir->Add( edit, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

		wxBitmapButton * button = new wxBitmapButton( this, ID_TEMP_DIR_BTN, wxArtProvider::GetBitmap(wxART_FOLDER_OPEN), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
		bSizerDir->Add( button, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );

		bSizer->Add( bSizerDir, 0, wxEXPAND, 5 );
	}

	checkbox = new wxCheckBox( this, ID_TEMP_DEL, _("Delete temporary files when you exit the program"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( checkbox, 0, wxALL, 5 );

	checkbox = new wxCheckBox( this, ID_REMOVE_FILES, _("Delete files when you delete a book"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( checkbox, 0, wxALL, 5 );
/*
	checkbox = new wxCheckBox( this, ID_AUTOHIDE_COLUMN, _("Прятать колонку соответствующую вкладке"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( checkbox, 0, wxALL, 5 );
*/
	wxBoxSizer * bSizerLimit = new wxBoxSizer( wxHORIZONTAL );

	checkbox = new wxCheckBox( this, ID_LIMIT_CHECK, _("Limit the maximum size of lists:"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerLimit->Add( checkbox, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );

	wxTextCtrl * maxedit = new wxTextCtrl( this, ID_LIMIT_COUNT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerLimit->Add( maxedit, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	bSizer->Add( bSizerLimit, 0, 0, 5 );

	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
}

SettingsDlg::FbPanelExport::FbPanelExport(wxWindow *parent)
	:wxPanel(parent)
{
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	wxStaticText * m_staticText6 = new wxStaticText( this, wxID_ANY, _("Destination folder:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer8->Add( m_staticText6, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );


	wxTextCtrl * m_textCtrl6 = new wxTextCtrl( this, ID_EXTERNAL_TXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl6->SetMinSize( wxSize( 300,-1 ) );

	bSizer9->Add( m_textCtrl6, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBitmapButton * m_bpButton6 = new wxBitmapButton( this, ID_EXTERNAL_BTN, wxArtProvider::GetBitmap(wxART_FOLDER_OPEN), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizer9->Add( m_bpButton6, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );

	bSizer8->Add( bSizer9, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->AddGrowableCol( 0 );
	fgSizer10->AddGrowableCol( 1 );

	wxCheckBox * m_checkBox2 = new wxCheckBox( this, ID_TRANSLIT_FOLDER, _("Transliterate folder name"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_checkBox2, 0, wxALL|wxEXPAND, 5 );

	wxCheckBox * m_checkBox3 = new wxCheckBox( this, ID_TRANSLIT_FILE, _("Transliterate filename"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_checkBox3, 0, wxALL|wxEXPAND, 5 );

	wxString m_radioBox1Choices[] = {
		_("A / Author / Series / #_book"),
		_("A / Author / Book"),
		_("Author / Series / #_book"),
		_("Author / Book"),
	};
	int m_radioBox1NChoices = sizeof( m_radioBox1Choices ) / sizeof( wxString );
	wxRadioBox * m_radioBox1 = new wxRadioBox( this, ID_FOLDER_FORMAT, _("Exported collection structure"), wxDefaultPosition, wxDefaultSize, m_radioBox1NChoices, m_radioBox1Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox1->SetSelection( 0 );
	fgSizer10->Add( m_radioBox1, 0, wxALL|wxEXPAND, 5 );

	wxString m_radioBox2Choices[] = { _("filename.fb2"), _("filename.fb2.zip") };
	int m_radioBox2NChoices = sizeof( m_radioBox2Choices ) / sizeof( wxString );
	wxRadioBox * m_radioBox2 = new wxRadioBox( this, ID_FILE_FORMAT, _("Format of exporting collection"), wxDefaultPosition, wxDefaultSize, m_radioBox2NChoices, m_radioBox2Choices, 1, wxRA_SPECIFY_COLS );
	m_radioBox2->SetSelection( 0 );
	fgSizer10->Add( m_radioBox2, 0, wxALL|wxEXPAND, 5 );

	bSizer8->Add( fgSizer10, 0, wxEXPAND, 5 );
/*
	m_checkBox2 = new wxCheckBox( this, ID_USE_SYMLINKS, _("Создавть cимвольные ссылки для соавторов"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_checkBox2, 0, wxALL, 5 );
*/
	this->SetSizer( bSizer8 );
	this->Layout();
	bSizer8->Fit( this );
}

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( SettingsDlg, wxDialog )
	EVT_BUTTON( ID_TEMP_DIR_BTN, SettingsDlg::OnSelectFolderClick )
	EVT_BUTTON( ID_DOWNLOAD_DIR_BTN, SettingsDlg::OnSelectFolderClick )
	EVT_BUTTON( ID_EXTERNAL_BTN, SettingsDlg::OnSelectFolderClick )
	EVT_BUTTON( ID_FONT_CLEAR, SettingsDlg::OnFontClear )
	EVT_MENU( ID_APPEND_TYPE, SettingsDlg::OnAppendType )
	EVT_MENU( ID_MODIFY_TYPE, SettingsDlg::OnModifyType )
	EVT_MENU( ID_DELETE_TYPE, SettingsDlg::OnDeleteType )
	EVT_LIST_ITEM_ACTIVATED(ID_TYPELIST, SettingsDlg::OnTypelistActivated)
END_EVENT_TABLE()

SettingsDlg::SettingsDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
	: FbDialog( parent, id, title, pos, size, style )
{
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	#if defined(__WIN32__)
	long nbStyle = wxNB_MULTILINE;
	#else
	long nbStyle = wxNB_LEFT;
	#endif

	wxNotebook * notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, nbStyle );
	notebook->AddPage( new FbPanelInterface(notebook), _("General"), true );
	notebook->AddPage( new FbPanelInternet(notebook), _("Network"), false );
	notebook->AddPage( new FbPanelTypes(notebook), _("File types"), false );
	notebook->AddPage( new FbPanelExport(notebook), _("Export"), false );
	notebook->AddPage( new FbPanelFont(notebook), _("Fonts"), false );

	bSizerMain->Add( notebook, 1, wxEXPAND | wxALL, 5 );

	wxStdDialogButtonSizer * sdbSizerBtn = CreateStdDialogButtonSizer( wxOK | wxCANCEL );
	bSizerMain->Add( sdbSizerBtn, 0, wxEXPAND | wxALL, 5 );

	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );

	SetAffirmativeId(wxID_OK);
	SetEscapeId(wxID_CANCEL);
}

SettingsDlg::~SettingsDlg()
{
}

void SettingsDlg::OnSelectFolderClick( wxCommandEvent& event )
{
	wxTextCtrl * textCtrl = (wxTextCtrl*)FindWindowById( event.GetId() - 1);

	if (!textCtrl) return;

	wxDirDialog dlg(
		this,
		_("Select folder"),
		textCtrl->GetValue(),
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST | wxDD_NEW_DIR_BUTTON
	);

	if (dlg.ShowModal() == wxID_OK)  textCtrl->SetValue(dlg.GetPath());
}

void SettingsDlg::Assign(bool write)
{
	enum Type {
		tText,
		tCheck,
		tRadio,
		tCombo,
		tFont,
		tCount,
	};

	struct Struct{
		int param;
		ID control;
		Type type;
	};

	const Struct ids[] = {
		{FB_AUTO_DOWNLD, ID_AUTO_DOWNLD, tCheck},
		{FB_USE_PROXY, ID_USE_PROXY, tCheck},
		{FB_PROXY_ADDR, ID_PROXY_ADDR, tCombo},
		{FB_TEMP_DEL, ID_TEMP_DEL, tCheck},
		{FB_TEMP_DIR, ID_TEMP_DIR_TXT, tText},
		{FB_DOWNLOAD_DIR, ID_DOWNLOAD_DIR_TXT, tText},
		{FB_DEL_DOWNLOAD, ID_DEL_DOWNLOAD, tCheck},
		{FB_EXTERNAL_DIR, ID_EXTERNAL_TXT, tText},
		{FB_TRANSLIT_FOLDER, ID_TRANSLIT_FOLDER, tCheck},
		{FB_TRANSLIT_FILE, ID_TRANSLIT_FILE, tCheck},
		{FB_FOLDER_FORMAT, ID_FOLDER_FORMAT, tRadio},
		{FB_FILE_FORMAT, ID_FILE_FORMAT, tRadio},
		{FB_FONT_MAIN, ID_FONT_MAIN, tFont},
		{FB_FONT_HTML, ID_FONT_HTML, tFont},
		{FB_FONT_TOOL, ID_FONT_TOOL, tFont},
		{FB_FONT_DLG, ID_FONT_DLG, tFont},
		{FB_HTTP_IMAGES, ID_HTTP_IMAGES, tCheck},
		{FB_REMOVE_FILES, ID_REMOVE_FILES, tCheck},
		{FB_SAVE_FULLPATH, ID_SAVE_FULLPATH, tCheck},
		{FB_LIMIT_CHECK, ID_LIMIT_CHECK, tCheck},
		{FB_LIMIT_COUNT, ID_LIMIT_COUNT, tCount},
	};

	const size_t idsCount = sizeof(ids) / sizeof(Struct);

	FbParams params;

	for (size_t i=0; i<idsCount; i++) {
		switch (ids[i].type) {
			case tText:
				if (wxTextCtrl * control = (wxTextCtrl*)FindWindowById(ids[i].control)) {
					if (write)
						params.SetText(ids[i].param, control->GetValue());
					else
						control->SetValue(params.GetText(ids[i].param));
				} break;
			case tCheck:
				if (wxCheckBox * control = (wxCheckBox*)FindWindowById(ids[i].control)) {
					if (write)
						params.SetValue(ids[i].param, control->GetValue());
					else
						control->SetValue(params.GetValue(ids[i].param) != 0);
				} break;
			case tRadio:
				if (wxRadioBox * control = (wxRadioBox*)FindWindowById(ids[i].control)) {
					if (write)
						params.SetValue(ids[i].param, control->GetSelection());
					else
						control->SetSelection(params.GetValue(ids[i].param));
				} break;
			case tCombo:
				if (wxComboBox * control = (wxComboBox*)FindWindowById(ids[i].control)) {
					if (write)
						params.SetText(ids[i].param, control->GetValue());
					else
						control->SetValue(params.GetText(ids[i].param));
				} break;
			case tFont:
				if (wxFontPickerCtrl * control = (wxFontPickerCtrl*)FindWindowById(ids[i].control)) {
					if (write)
						params.SetText(ids[i].param, control->GetSelectedFont().GetNativeFontInfoDesc());
					else
						control->SetSelectedFont(FbParams::GetFont(ids[i].param) );
				} break;
			case tCount:
				if (wxTextCtrl * control = (wxTextCtrl*)FindWindowById(ids[i].control)) {
					if (write) {
						wxString text = control->GetValue();
						long value = 0;
						if (text.ToLong(&value) && value>0)
							params.SetValue(ids[i].param, value);
						else
							params.ResetValue(ids[i].param);
					} else {
						int count = params.GetValue(ids[i].param);
						wxString text = wxString::Format(wxT("%d"), count);
						control->SetValue(text);
					}
				} break;
		}
	}

	if (write) FbCommandEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATE_FONTS).Post();
};

void SettingsDlg::Execute(wxWindow* parent)
{
	SettingsDlg dlg(parent, wxID_ANY, _("Program settings"), wxDefaultPosition, wxDefaultSize);

	try {
		dlg.Assign(false);
		dlg.FillTypelist();
	} catch (wxSQLite3Exception & e) {
		wxLogError(e.GetMessage());
		return;
	}

	if (dlg.ShowModal() == wxID_OK) {
		try {
			dlg.SaveTypelist();
			dlg.Assign(true);
			ZipReader::Init();
			FbTempEraser::sm_erase = FbParams::GetValue(FB_TEMP_DEL);
		} catch (wxSQLite3Exception & e) {
			wxLogError(_("Database open error: ") + e.GetMessage());
		}
	}
};

void SettingsDlg::FillTypelist()
{
	wxListCtrl* typelist = (wxListCtrl*) FindWindowById(ID_TYPELIST);
	if (!typelist) return;

	wxString sql = wxT("\
		SELECT \
			books.file_type, types.command, \
			CASE WHEN books.file_type='fb2' THEN 1 ELSE 2 END AS number\
		FROM ( \
			 SELECT DISTINCT LOWER(file_type) AS file_type FROM BOOKS GROUP BY file_type \
			 UNION SELECT DISTINCT file_type FROM types \
			 UNION SELECT 'fb2' \
			 UNION SELECT 'pdf' \
			 UNION SELECT 'djvu' \
			 UNION SELECT 'txt' \
		) AS books \
		  LEFT JOIN config.types as types ON books.file_type = types.file_type \
		ORDER BY number, books.file_type \
	 ");

	FbCommonDatabase database;
	database.AttachConfig();
	wxSQLite3ResultSet result = database.ExecuteQuery(sql);

	typelist->Freeze();

	long item = 0;
	while ( result.NextRow() ) {
		wxString file_type = result.GetString(wxT("file_type"));
		wxString command = result.GetString(wxT("command"));
		if (file_type.IsEmpty()) continue;
		if (file_type == wxT("exe")) continue;
		item = typelist->InsertItem(item + 1, file_type);
		typelist->SetItem(item, 1, command);
		typelist->SetItemData(item, m_commands.Add(command));
	}
	typelist->Thaw();
}

void SettingsDlg::OnTypelistActivated( wxListEvent & event )
{
	SelectApplication();
	event.Skip();
}

void SettingsDlg::SelectApplication()
{
	wxListCtrl* typelist = (wxListCtrl*) FindWindowById(ID_TYPELIST);
	if (!typelist) return;

	wxArrayTreeItemIds selections;
	size_t count = typelist->GetSelectedItemCount();

	if (!count) return;

	wxString title = _("Select the application to view files");
	wxString command;
	long item = typelist->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item >= 0) command = m_commands[typelist->GetItemData(item)];

	if ( FbViewerDlg::Execute( this, wxEmptyString, command) )
	{
		size_t index = m_commands.Add(command);
		long item = -1;
		while (true) {
			item = typelist->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			if (item == -1) break;
			typelist->SetItem(item, 1, command);
			typelist->SetItemData(item, index);
		}
	}
}

void SettingsDlg::SaveTypelist()
{
	wxListCtrl* typelist = (wxListCtrl*) FindWindowById(ID_TYPELIST);
	if (!typelist) return;

	FbLocalDatabase database;
	FbAutoCommit transaction(database);

	for (size_t i=0; i<m_deleted.Count(); i++) {
		wxString sql = wxT("DELETE FROM types WHERE file_type=?");
		wxSQLite3Statement stmt = database.PrepareStatement(sql);
		stmt.Bind(1, m_deleted[i]);
		stmt.ExecuteUpdate();
	}

	long item = -1;
	while (true) {
		item = typelist->GetNextItem(item, wxLIST_NEXT_ALL);
		if (item == wxNOT_FOUND) break;
		wxString file_type = typelist->GetItemText(item);
		wxString command = m_commands[typelist->GetItemData(item)];
		if ( command.IsEmpty() ) {
			wxString sql = wxT("DELETE FROM types WHERE file_type=?");
			wxSQLite3Statement stmt = database.PrepareStatement(sql);
			stmt.Bind(1, file_type);
			stmt.ExecuteUpdate();
		} else {
			wxString sql = wxT("INSERT OR REPLACE INTO types(file_type, command) values(?,?)");
			wxSQLite3Statement stmt = database.PrepareStatement(sql);
			stmt.Bind(1, file_type);
			stmt.Bind(2, command);
			stmt.ExecuteUpdate();
		}
	}
}

void SettingsDlg::OnAppendType( wxCommandEvent& event )
{
	wxListCtrl* typelist = (wxListCtrl*) FindWindowById(ID_TYPELIST);
	if (!typelist) return;

	wxString filetype = wxGetTextFromUser(_("Input new filetype"), _("Settings"));
	if (filetype.IsEmpty()) return;
	filetype = filetype.Lower();

	long item = -1;
	bool bExists = false;
	long stateMask = wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED;
	while (true) {
		item = typelist->GetNextItem(item, wxLIST_NEXT_ALL);
		if (item == wxNOT_FOUND) break;
		long state = 0;
		if (typelist->GetItemText(item) == filetype) {
			state = wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED;
			bExists = true;
		}
		typelist->SetItemState(item, state, stateMask);
	}

	if (bExists) return;

	item = typelist->InsertItem(0, filetype);
	typelist->SetItemState(item, stateMask, stateMask);
}

void SettingsDlg::OnModifyType( wxCommandEvent& event )
{
	SelectApplication();
}

void SettingsDlg::OnDeleteType( wxCommandEvent& event )
{
	wxListCtrl* typelist = (wxListCtrl*) FindWindowById(ID_TYPELIST);
	if (!typelist) return;

	typelist->Freeze();

	long item = -1;
	while (true) {
		item = typelist->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == wxNOT_FOUND) break;
		m_deleted.Add(typelist->GetItemText(item));
		typelist->DeleteItem(item);
	}

	typelist->Thaw();
}

void SettingsDlg::SetFont(wxWindowID id, wxFont font)
{
	wxFontPickerCtrl * control = (wxFontPickerCtrl*) FindWindowById(id);
	if (control) control->SetSelectedFont(font);
}

void SettingsDlg::OnFontClear( wxCommandEvent& event )
{
	wxFont font = wxSystemSettingsNative::GetFont(wxSYS_DEFAULT_GUI_FONT);
	SetFont(ID_FONT_MAIN, font);
	SetFont(ID_FONT_TOOL, font);
	SetFont(ID_FONT_HTML, font);
	SetFont(ID_FONT_DLG, font);
}
