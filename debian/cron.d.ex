#
# Regular cron jobs for the groove package
#
0 4	* * *	root	[ -x /usr/bin/groove_maintenance ] && /usr/bin/groove_maintenance
