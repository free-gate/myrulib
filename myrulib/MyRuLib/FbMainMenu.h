#ifndef __FBMAINMENU_H__
#define __FBMAINMENU_H__

#include <wx/wx.h>
#include "FbMenu.h"

class FbMenuBar: public wxMenuBar
{
	protected:

		class MenuFrame: public FbMenu {
			public: MenuFrame();
		};

		class MenuLib: public FbMenu {
			public:
				MenuLib();
		};

		class MenuSetup: public FbMenu {
			public:
				MenuSetup();
		};

		class MenuHelp: public FbMenu {
			public: MenuHelp();
		};

		class MenuRecent: public FbMenu {
			public: MenuRecent();
		};
};

class FbMainMenu: public FbMenuBar
{
	public:
		FbMainMenu();

	protected:

		class MenuFile: public FbMenu {
			public: MenuFile();
		};

		class MenuView: public FbMenu {
			public: MenuView();
		};

};

class FbFrameMenu: public FbMenuBar
{
	public:
		FbFrameMenu();

	private:

		class MenuFile: public FbMenu {
			public: MenuFile();
		};

		class MenuBook: public FbMenu {
			public: MenuBook();
		};

		class MenuView: public FbMenu {
			public: MenuView();
		};
};

#endif // __FBMAINMENU_H__
