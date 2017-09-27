Name:       capi-system-peripheral-io
Summary:    Tizen Peripheral Input & Output library
Version:    0.1.0
Release:    0
Group:      System & System Tools
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    %{name}.manifest
BuildRequires:  awk
BuildRequires:  cmake
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gio-2.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-system-info)

Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
Tizen Peripheral Input & Output library

%package devel
Summary:    Tizen Peripheral Input & Output library (devel)
Group:      System & System Tools/Development
Requires:   %{name} = %{version}-%{release}

%description devel
Tizen Peripheral Input & Output library (devel)

%prep
%setup -q
cp %{SOURCE1} ./%{name}.manifest

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DMAJORVER=${MAJORVER} -DFULLVER=%{version}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_libdir}/lib%{name}.so*
%license LICENSE.APLv2

%files devel
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_includedir}/*.h
%{_libdir}/lib%{name}.so
%{_libdir}/pkgconfig/%{name}.pc
