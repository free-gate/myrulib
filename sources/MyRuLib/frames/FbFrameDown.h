#ifndef __FBFRAMEDOWN_H__
#define __FBFRAMEDOWN_H__

#include "FbFrameBase.h"

class FbFrameDown : public FbFrameBase
{
	public:
		FbFrameDown(wxAuiMDIParentFrame * parent);
		wxString GetTitle() const { return _("Downloads"); };
		void UpdateFolder(const int iFolder, const FbFolderType type);
	protected:
		virtual void CreateControls();
	private:
		void CreateColumns();
		void CreateBookInfo();
		void FillFolders(const int iCurrent = 0);
		void DeleteItems(const wxTreeItemId &root, wxArrayInt &items);
		wxToolBar m_ToolBar;
	private:
		void OnFavoritesDel(wxCommandEvent & event);
		void OnFolderAppend(wxCommandEvent & event);
		void OnFolderModify(wxCommandEvent & event);
		void OnFolderDelete(wxCommandEvent & event);
		void OnStart(wxCommandEvent & event);
		void OnPause(wxCommandEvent & event);
		void OnFolderSelected(wxTreeEvent & event);
		void OnMoveUp(wxCommandEvent& event);
		void OnMoveDown(wxCommandEvent& event);
		DECLARE_EVENT_TABLE()
		DECLARE_CLASS(FbFrameDown)
};

#endif // __FBFRAMEDOWN_H__
