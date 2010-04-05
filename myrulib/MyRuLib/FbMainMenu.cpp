#include "FbMainMenu.h"
#include "FbConst.h"

FbMenuBar::MenuFrame::MenuFrame()
{
	AppendImg(ID_MENU_SEARCH, _("Search"), wxART_FIND);
	AppendSeparator();
	Append(ID_FRAME_AUTHOR, _("Authors"));
	Append(ID_FRAME_GENRES, _("Genres"));
	Append(ID_FRAME_SEQUEN, _("Series"));
	Append(ID_FRAME_DATE,   _("Calendar"));
	Append(ID_FRAME_ARCH,   _("Archive"));
	AppendSeparator();
	Append(ID_FRAME_FOLDER, _("My folders"));
	Append(ID_FRAME_DOWNLD, _("Downloads"));
}

FbMenuBar::MenuLib::MenuLib()
{
	Append(ID_MENU_DB_OPEN, _("Open (or create) collection"));
	Append(ID_RECENT_ALL, _("Open recent"), new MenuRecent());
	AppendSeparator();
	Append(ID_MENU_DB_INFO,  _("Information about collection"));
	Append(ID_MENU_OPTIMIZE, _("Clear empty variables"));
	Append(ID_MENU_VACUUM,   _("Optimize DB"));
	AppendSeparator();
	Append(ID_MENU_CONFIG, _("Options"));
}

FbMenuBar::MenuSetup::MenuSetup()
{
	Append(wxID_PREFERENCES, _("Settings"));
}

FbMenuBar::MenuHelp::MenuHelp()
{
	Append(ID_OPEN_WEB, _("Website"));
	AppendImg(wxID_ABOUT, _("About"), wxART_HELP_PAGE);
}

FbMainMenu::FbMainMenu(): FbMenuBar()
{
	Append(new MenuFile,   _("&File"));
	Append(new MenuLib,    _("&Library"));
	Append(new MenuFrame,  _("&Catalog"));
	Append(new MenuView,   _("&View"));
	Append(new MenuSetup,  _("&Tools"));
	Append(new MenuWindow, _("&Window"));
	Append(new MenuHelp,   _("&?"));
}

FbMainMenu::MenuFile::MenuFile()
{
	AppendImg(wxID_NEW,  _("Add file") + (wxString)wxT("\tCtrl+N"), wxART_NEW);
	AppendImg(wxID_OPEN, _("Add folder") + (wxString)wxT("\tCtrl+O"), wxART_FOLDER_OPEN);
	AppendSeparator();
	AppendImg(wxID_EXIT, _("Выход") + (wxString)wxT("\tAlt-F4"), wxART_QUIT);
}

FbMainMenu::MenuView::MenuView()
{
	Append(wxID_ANY, _("Tabs"), new MenuTabArt());
	AppendSeparator();
	Append(ID_FULLSCREEN, _("Fullscreen mode") + (wxString)wxT("\tF11"));
	Append(ID_LOG_TEXTCTRL, _("Show log window") + (wxString)wxT("\tF12"));
	Append(wxID_ANY, _("Language"), new MenuLocalize());
}

FbFrameMenu::MenuFile::MenuFile()
{
	AppendImg(wxID_NEW,  _("Add file") + (wxString)wxT("\tCtrl+N"), wxART_NEW);
	AppendImg(wxID_OPEN, _("Add folder") + (wxString)wxT("\tCtrl+O"), wxART_FOLDER_OPEN);
	AppendSeparator();
	AppendImg(wxID_SAVE, _("Export books") + (wxString)wxT("\tCtrl+S"), wxART_FILE_SAVE);
	AppendImg(wxID_EXIT, _("Exit") + (wxString)wxT("\tAlt-F4"), wxART_QUIT);
}

FbFrameMenu::MenuBook::MenuBook()
{
	Append(wxID_SELECTALL, _("Select all") + (wxString)wxT("\tCtrl+A"));
	Append(ID_UNSELECTALL, _("Undo selection"));
	AppendSeparator();
	Append(ID_ORDER_MENU, _("Sort by"), new FbMenuSort());
	AppendCheckItem(ID_FILTER_USE, _("Use filter"));
	Append(ID_FILTER_NOT, _("Clear filter"));
	AppendSeparator();
	Append(ID_EDIT_COMMENTS, _("Comments"));
}

FbFrameMenu::MenuView::MenuView()
{
	Append(wxID_ANY, _("List of books"), new MenuListMode());
	Append(wxID_ANY, _("Preview area"), new MenuPreview());
	Append(wxID_ANY, _("Tabs"), new MenuTabArt());
	Append(ID_SHOW_COLUMNS, _("Table columns"));
	AppendSeparator();
	Append(ID_FULLSCREEN, _("Fullscreen mode") + (wxString)wxT("\tF11"));
	Append(ID_LOG_TEXTCTRL, _("Show log window") + (wxString)wxT("\tF12"));
	Append(wxID_ANY, _("Language"), new MenuLocalize());
}

FbMenuBar::MenuRecent::MenuRecent()
{
}

FbMenuBar::MenuListMode::MenuListMode()
{
	AppendRadioItem(ID_MODE_TREE, _("Hierarchical"));
	AppendRadioItem(ID_MODE_LIST, _("Simple list"));
}

FbMenuBar::MenuTabArt::MenuTabArt()
{
	AppendRadioItem(ID_ART_DEFAULT,  _("Standart"));
	AppendRadioItem(ID_ART_COMPACT,  _("Compact"));
	AppendRadioItem(ID_ART_STANDART, _("Convex"));
	AppendRadioItem(ID_ART_TOOLBAR,  _("Buttons"));
}

FbMenuBar::MenuPreview::MenuPreview()
{
	AppendRadioItem(ID_SPLIT_VERTICAL,   _("Right"));
	AppendRadioItem(ID_SPLIT_HORIZONTAL, _("Bottom"));
	AppendRadioItem(ID_SPLIT_NOTHING,    _("Not specified"));
}

FbMenuBar::MenuWindow::MenuWindow()
{
	Append(ID_WINDOW_CLOSE,    _("Close window"));
	Append(ID_WINDOW_CLOSEALL, _("Close all"));
	AppendSeparator();
	Append(ID_WINDOW_NEXT,     _("Next"));
	Append(ID_WINDOW_PREV,     _("Previous"));
}

FbMenuBar::MenuLocalize::MenuLocalize()
{
    AppendRadioItem(ID_MENU_ENGLISH, _("English"));
    AppendRadioItem(ID_MENU_RUSSIAN, _("Russian"));
    AppendRadioItem(ID_MENU_UKRAINIAN, _("Ukrainian"));
    AppendRadioItem(ID_MENU_BELARUSIAN, _("Belarusian"));
}
