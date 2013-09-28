#ifndef __FBFRAMEGENR_H__
#define __FBFRAMEGENR_H__

#include <wx/wx.h>
#include <wx/toolbar.h>
#include <wx/aui/tabmdi.h>
#include <wx/html/htmlwin.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include "wx/FbSQLite3.h"
#include "FbFrameBase.h"
#include "FbBookEvent.h"
#include "FbSmartPtr.h"

class FbFrameGenr : public FbFrameBase
{
	public:
		FbFrameGenr(wxAuiNotebook * parent, bool select = false);
	protected:
		virtual FbFrameThread * CreateCounter();
		virtual wxString GetCountSQL();
	private:
		void CreateBookInfo();
		void CreateColumns();
	private:
		void OnBooksCount(FbCountEvent& event);
		void OnModel( FbModelEvent & event );
		DECLARE_CLASS(FbFrameGenr)
		DECLARE_EVENT_TABLE()
};

#endif // __FBFRAMEGENR_H__
