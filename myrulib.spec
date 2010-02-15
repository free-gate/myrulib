Name: myrulib
Version: 0.19
Release: alt1

Summary: Tool for maintaining fb2 files collection
Url: http://myrulib.lintest.ru/
Source: %name-%version.tar
License: GPL

Packager: Anton V. Boyarshinov <boyarsh@altlinux.org>
Group: Office

BuildRequires: wxGTK-devel gcc-c++ libsqlite3-devel libexpat-devel 

%description
Tool for maintaining home library, contaning fb2 files. Supports search,
export and so on.

%prep
%setup

%build
%make_build CFLAGS="%optflags" CXXFLAGS="%optflags"

%install
%makeinstall_std
mkdir -p %buildroot/usr/share/icons/hicolor/32x32/apps/
install MyRuLib/desktop/home-32x32.png %buildroot/usr/share/icons/hicolor/32x32/apps/myrulib.png
mkdir -p  %buildroot/usr/share/icons/hicolor/64x64/apps/
install MyRuLib/desktop/home-64x64.png %buildroot/usr/share/icons/hicolor/64x64/apps/myrulib.png

%files
%_bindir/myrulib
/usr/share/applications/myrulib.desktop
/usr/share/icons/hicolor/32x32/apps/myrulib.png
/usr/share/icons/hicolor/64x64/apps/myrulib.png

%changelog
* Mon Feb 15 2010 Anton V. Boyarshinov <boyarsh@altlinux.ru> 0.19-alt1
- new version

* Tue Dec 29 2009 Anton V. Boyarshinov <boyarsh@altlinux.ru> 0.17-alt1
- new version
- compilation flags added

* Wed Dec 09 2009 Anton V. Boyarshinov <boyarsh@altlinux.ru> 0.16-alt1
- initial build

