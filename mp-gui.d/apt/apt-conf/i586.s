// these must be unset to avoid picking up
// /etc/apt/{apt.conf.d,sources.list.d,}/
Dir::Etc::main "/dev/null";
Dir::Etc::parts "/var/empty";
Dir::Etc::SourceParts "/var/empty";

// this is what caused the whole trouble
Dir::Etc::sourcelist "/etc/mp-gui.d/apt/i586-s/sources.list";
