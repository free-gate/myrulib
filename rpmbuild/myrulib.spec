#
# spec file for package myrulib (Version 0.27)
#
# Copyright (c) 2009-2011 Denis Kandrashin, Kyrill Detinov
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.
#

Name:           myrulib
Version:        0.28.6
Release:        0
License:        GPL-3.0
Summary:        E-Book Library Manager
URL:            http://myrulib.lintest.ru
Group:          Productivity/Other
Source0:        http://www.lintest.ru/pub/%{name}-%{version}.tar.bz2
BuildRequires:  gcc-c++
BuildRequires:  libfaxpp-devel
Conflicts:      myrulib-cr
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%if 0%{?suse_version}
BuildRequires:  update-desktop-files
%if 0%{?suse_version} >= 1140
BuildRequires:  sqlite3-devel
BuildRequires:  wxWidgets-devel
%else
BuildRequires:  wxGTK-devel >= 2.8.10
%endif
%endif

%if 0%{?mandriva_version}
BuildRequires:  libwxgtku2.8-devel >= 2.8.10
%endif

%if 0%{?fedora_version}
BuildRequires:  wxGTK-devel >= 2.8.10
BuildRequires:  desktop-file-utils
%if 0%{?fedora_version} >= 15
BuildRequires:  libsqlite3x-devel
%endif
%endif

%description
MyRuLib is an application for organizing your own collection of e-books.



Authors:
--------
    Denis Kandrashin <mail@lintest.ru>

%prep
%setup -q
[ ! -x configure ] && %{__chmod} +x configure

%build
%configure \
    --with-faxpp=yes \
    --without-strip

%if 0%{?fedora_version} >= 13
make LDFLAGS="-Wl,--add-needed" %{?_smp_mflags}
%else
make %{?_smp_mflags}
%endif

%install
%if 0%{?fedora_version} || 0%{?mandriva_version}
rm -rf %{buildroot}
%endif

make DESTDIR=%{buildroot} install
%find_lang %{name}

%if 0%{?suse_version}
%suse_update_desktop_file %{name}
%endif

%if 0%{?fedora_version}
desktop-file-validate %{buildroot}%{_datadir}/applications/%{name}.desktop
%endif

%if 0%{?suse_version} >= 1140
%post
%desktop_database_post
%icon_theme_cache_post

%postun
%desktop_database_postun
%icon_theme_cache_postun
%endif

%if 0%{?mandriva_version}
%post
%update_menus

%postun
%clean_menus
%endif

%clean
rm -rf %{buildroot}

%files -f %{name}.lang
%defattr(-,root,root)
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/*/%{name}.png
%{_datadir}/pixmaps/%{name}.png

%changelog
