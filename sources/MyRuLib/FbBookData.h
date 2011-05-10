#ifndef __FBBOOKDATA_H__
#define __FBBOOKDATA_H__

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/wxsqlite3.h>
#include "FbThread.h"

class FbTempEraser {
	public:
		static void Add(const wxString &filename);
		static bool sm_erase;
	private:
		wxStringList filelist;
		FbTempEraser() {};
		virtual ~FbTempEraser();
};

class BookTreeItemData
{
	public:
		BookTreeItemData(BookTreeItemData * data):
			m_id(data->GetId()),
			title(data->title),
			file_type(data->file_type),
			file_size(data->file_size),
			sequence(data->sequence),
			number(data->number),
			genres(data->genres),
			rating(data->rating),
			language(data->language)
		{ };
		BookTreeItemData(wxSQLite3ResultSet & result);
		int GetId() const { return m_id; };
	private:
        static void Assign(wxSQLite3ResultSet &res, const wxString& column, int &value);
        static void Assign(wxSQLite3ResultSet &res, const wxString& column, wxString &value);
		int m_id;
	public:
		wxString title;
		wxString file_type;
		int file_size;
		wxString sequence;
		int number;
		wxString genres;
		int rating;
		wxString language;
};

class FbItemData
{
	public:
		virtual void Show(wxEvtHandler * frame, bool bVertical, bool bEditable = false) const = 0;
		virtual void Open() const {};
		virtual int GetId() const { return 0; };
		bool operator == (const FbItemData & data) const { return GetId() == data.GetId(); };
};

class FbBookData: public FbItemData
{
	public:
		FbBookData(int id): m_id(id) {}
		FbBookData(const FbBookData & data): m_id(data.m_id) {}
		FbBookData(const BookTreeItemData & data): m_id(data.GetId()) {}
		virtual int GetId() const { return m_id; }
		virtual void Show(wxEvtHandler * frame, bool bVertical, bool bEditable = false) const;
		virtual void Open() const;
		void LoadIcon() const;
	private:
		void DoDownload() const;
		void DoOpen(wxInputStream & in, const wxString &md5sum) const;
		void SaveFile(wxInputStream & in, const wxString &filepath) const;
		bool GetUserCommand(wxSQLite3Database &database, const wxString &filetype, wxString &command) const;
        bool GetSystemCommand(const wxString &filepath, const wxString &filetype, wxString &command) const;
		wxString GetExt() const;
	private:
		int m_id;
};

class FbAuthorData: public FbItemData
{
	public:
		FbAuthorData(int author): m_author(author) {};
		int GetAuthor() const { return m_author; };
		virtual void Show(wxEvtHandler * frame, bool bVertical, bool bEditable = false) const;
	private:
		int m_author;

		class ShowThread: public FbThread
		{
			public:
				ShowThread(wxEvtHandler * frame, int author): m_frame(frame), m_author(author) {};
			protected:
				virtual void * Entry();
			private:
				wxEvtHandler * m_frame;
				int m_author;
		};
};

#endif // __FBBOOKDATA_H__
