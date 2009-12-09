Name: myrulib
Version: 0.16
Release: alt1

Summary: Tool for maintaining fb2 files collection
Url: http://myrulib.lintest.ru/
Source: %name-%version.tar
License: GPL

Packager: Anton V. Boyarshinov <boyarsh@altlinux.org>
Group: Office

%description
Tool for maintaining home library, contaning fb2 files. Supports search,
export and so on.

%prep
%setup

%build
%make_build

%install
%makeinstall

%files
%_bindir/myrulib
/usr/share/applications/myrulib.desktop
/usr/share/myrulib/home-32x32.png

%changelog
* Wed Dec 09 2009 Anton V. Boyarshinov <boyarsh@altlinux.ru> 0.16-alt1
- initial build 

