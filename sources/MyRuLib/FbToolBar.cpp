#include "FbToolBar.h"
#include "FbParams.h"

FbToolBarImages::FbToolBarImages(wxToolBar & toolbar, const wxString &sample)
	: m_toolbar(toolbar)
{
    m_font_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
    m_tool_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
    m_brush = wxBrush(m_tool_colour, wxSOLID);
	m_font = FbParams::GetFont(FB_FONT_TOOL);

	wxBitmap bitmap(10, 10);
	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetFont(m_font);
	m_size = dc.GetTextExtent(sample);
	m_size.IncBy(2, 0);
	m_toolbar.SetToolBitmapSize(m_size);

	m_rect = m_size;
}

wxBitmap FbToolBarImages::operator[](const wxString &text)
{
	wxBitmap bitmap(m_size.GetX(), m_size.GetY());
	wxMemoryDC dc;
	dc.SelectObject(bitmap);
	dc.SetTextForeground(m_font_colour);
	dc.SetBrush(m_brush);
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.DrawRectangle(m_rect);
	dc.SetFont(m_font);
	dc.DrawLabel(text, wxNullBitmap, m_rect, wxALIGN_CENTER);
	dc.SelectObject(wxNullBitmap);

	#ifdef __WXGTK__
	bitmap.SetMask(new wxMask(bitmap, m_tool_colour));
	#endif // __WXGTK__

	return bitmap;
}