Name:		mp-gui
Version:	0.0.5
Release:	alt1
Summary:	Graphical application for mkimage-profiles

License:	GPL
Group:		System/Configuration/Packaging
URL:		https://github.com/150balbes/mp-gui
Packager:	Oleg Ivanov <Leo-sp150@yandex.ru>

Source0:	%name-%version.tar.gz
Source1:	%name.bin
Source2:	%name.desktop
Source3:	%name.png
Source4:	%name.d.tar

BuildRequires: gcc-c++ libqt4-devel desktop-file-utils
Requires: mkimage-profiles qt4-styles-qtcurve
Requires: sisyphus-mirror

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
mkdir -p %buildroot%_sysconfdir/mp-gui.d
tar xf %SOURCE4 -C %buildroot%_sysconfdir/

%post
mkdir -p /var/ftp/ALTLinux
chmod 777 /var/ftp/ALTLinux

%files
%_bindir/%name
%_desktopdir/*
%_liconsdir/*
%_sysconfdir/%name.d/*

%changelog
* Tue Oct 01 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.5-alt1
- edit repo

* Tue Sep 30 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.4-alt1
- add sisyphus-mirror

* Tue Sep 29 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.3-alt3
- add apt.config

* Tue Sep 28 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.2-alt1
- new version

* Tue Sep 25 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt11
- add save settings

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
