Name:		mp-gui
Version:	0.0.1
Release:	alt10
Summary:	Graphical application for mkimage-profiles

License:	GPL
Group:		System/Configuration/Packaging
URL:		https://github.com/150balbes/mp-gui

Packager:	Oleg Ivanov <Leo-sp150@yandex.ru>

Source0:	%name-%version.tar.gz
Source1:	%name.bin
Source2:	%name.desktop
Source3:	%name.png


BuildRequires: gcc-c++ libqt4-devel desktop-file-utils
Requires: mkimage-profiles qt4-styles-qtcurve

%description
Graphical application for mkimage-profiles.

%prep
%setup -q
lrelease-qt4 %name.pro
DESTDIR=%buildroot PREFIX=/usr qmake-qt4 %name.pro

%build
%make_build

%install
%makeinstall
install -pD -m755 %SOURCE1 %buildroot%_bindir/%name
install -pD -m644 %SOURCE2 %buildroot%_desktopdir/%name.desktop
install -pD -m644 %SOURCE3 %buildroot%_liconsdir/%name.png

%files
%_bindir/%name
%_desktopdir/*
%_liconsdir/*

%changelog
* Tue Sep 23 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt10
- add requires qt4-styles-qtcurve

* Tue Sep 23 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt9
- add options BUILDDIR_NO_RM

* Tue Sep 23 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt7
- fix error list distro

* Tue Sep 03 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt5
- new version

* Tue Sep 03 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt4
- Edit files

* Tue Sep 01 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt3
- Edit files

* Tue Sep 01 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt2
- Edit files

* Mon Aug 31 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt1
- Initial release to Sisyphus
