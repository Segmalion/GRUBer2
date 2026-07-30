//---------------------------------------------------------------------------

#ifndef NetH
#define NetH

#include <vector>
//---------------------------------------------------------------------------
struct NetAdapterInfo {
	UnicodeString name;
	UnicodeString ip;
	UnicodeString mac;
	bool active = false;
	TDateTime lastActive;
};
// Усі фізичні мережеві адаптери (LAN/WAN/USB) - активні й неактивні,
// без віртуальних/loopback/tunnel. lastActive тут не заповнюється -
// це поле веде Arm, зіставляючи з раніше збереженими даними.
std::vector<NetAdapterInfo> getAllNetAdapters();
//---------------------------------------------------------------------------
#endif
