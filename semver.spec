Name: semver
Version: 0.0.2
Release: 1%{?dist}
Summary: Semantic versioning is back! In C form!
License: BSD
URL: https://github.com/deoxxa/semver-c
Source0: %{name}-%{version}.tar.bz2

%package devel
Summary: Build files for Semantic versioning

%description
What do you do when you want semver but you don't have node installed? Write it
in C, of course! HA HA.

There's a library buried underneath the command-line program and it should be
easy enough to integrate into another application. I haven't really tested this
theory though so you're sort of on your own there.

%description devel

%prep
%autosetup

%build
make %{?_smp_mflags}

%install
mkdir -p %{buildroot}%{_bindir}
install bin/semver %{buildroot}%{_bindir}/semver-c
install bin/semver-dump %{buildroot}%{_bindir}
install bin/semver-sort %{buildroot}%{_bindir}
install bin/semver-range %{buildroot}%{_bindir}

mkdir -p %{buildroot}%{_libdir}
install bin/libsemver.so %{buildroot}%{_libdir}

mkdir -p %{buildroot}%{_includedir}
install include/semver.h %{buildroot}%{_includedir}

%files
%{_bindir}/*
%{_libdir}/libsemver.so

%files devel
%{_includedir}/semver.h
