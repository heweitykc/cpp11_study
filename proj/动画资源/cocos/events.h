#ifndef __EVENTS_H__
#define __EVENTS_H__

#define NET_LOGIN			"net_login"
#define NET_ADDROLE		"net_addrole"

struct Add_Role{
	int uid; int x; int y;
	bool isHero;
};

#endif