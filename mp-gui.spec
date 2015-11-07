Name:		mp-gui
Version:	0.0.8
Release:	alt2
Summary:	Graphical application for mkimage-profiles

License:	GPL
Group:		Development/Tools
URL:		https://github.com/150balbes/mp-gui
Packager:	Oleg Ivanov <Leo-sp150@yandex.ru>

Source0:	%name-%version.tar.gz
Source2:	%name.desktop
Source3:	%name.png
Source4:	%name.d.tar

BuildRequires: gcc-c++ libqt4-devel desktop-file-utils
Requires: mkimage-profiles >= 1.1.76-alt4.mpgui
Requires: qt4-styles-qtcurve
Requires: sisyphus-mirror
Requires: aplay

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
install -pD -m755 %name %buildroot%_bindir/%name
install -pD -m644 %SOURCE2 %buildroot%_desktopdir/%name.desktop
install -pD -m644 %SOURCE3 %buildroot%_liconsdir/%name.png
mkdir -p %buildroot%_sysconfdir/mp-gui.d
tar xf %SOURCE4 -C %buildroot%_sysconfdir/

%post
mkdir -p /var/ftp/ALTLinux
chmod 777 /var/ftp/ALTLinux
chmod 666 /etc/mp-gui.d/sisyphus-mirror/*
chmod 666 /etc/mp-gui.d/apt/apt-conf/*
chmod 666 /etc/mp-gui.d/apt/sources/*

%files
%_bindir/%name
%_desktopdir/*
%_liconsdir/*
%_sysconfdir/%name.d/*

%changelog
* Tue Nov 08 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.8-alt2
- new desktop.png

* Tue Oct 20 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.8-alt1
- new ver

* Tue Oct 14 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.7-alt5
- edit form

* Tue Oct 13 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.7-alt2
- add i586

* Tue Oct 08 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.6-alt3
- edit apt sources

* Mon Aug 31 2015 Oleg Ivanov <Leo-sp150@yandex.ru> 0.0.1-alt1
- Initial release to Sisyphus
