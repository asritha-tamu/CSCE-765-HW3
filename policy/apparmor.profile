#include <tunables/global>

/opt/agentlab/legacy_log_parser {
  #include <abstractions/base>

  /opt/agentlab/legacy_log_parser mr,
  /lib/x86_64-linux-gnu/ld-*.so* mr,
  /lib/x86_64-linux-gnu/libc.so.6 mr,

  /opt/agentlab/inbox/ r,
  /opt/agentlab/inbox/** r,

  /opt/agentlab/markers/ rw,
  /opt/agentlab/markers/** rw,

  audit deny /opt/agentsec/decoy.txt rwklx,

  deny /bin/sh x,
  deny /bin/bash x,
  deny /usr/bin/dash x,
  deny /usr/bin/bash x,
  deny /usr/bin/** x,
}
