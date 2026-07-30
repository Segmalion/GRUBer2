//---------------------------------------------------------------------------

#pragma hdrstop

#include <winsock2.h>
#include <iphlpapi.h>
#include <vector>

#include "Net.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib, "iphlpapi.lib")

// Перелічує усі фізичні мережеві адаптери (Ethernet/Wi-Fi, включно з USB-
// перехідниками) незалежно від їх поточного статусу - виключає loopback,
// tunnel-адаптери та найпоширеніші віртуальні адаптери (Hyper-V, VMware,
// VirtualBox, VPN-клієнти, TAP тощо), розпізнані за описом.
std::vector<NetAdapterInfo> getAllNetAdapters()
{
	std::vector<NetAdapterInfo> result;

	ULONG bufLen = 15000;
	std::vector<BYTE> buffer(bufLen);
	PIP_ADAPTER_ADDRESSES pAddresses = (PIP_ADAPTER_ADDRESSES)buffer.data();
	ULONG flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER;

	DWORD ret = GetAdaptersAddresses(AF_INET, flags, NULL, pAddresses, &bufLen);
	if (ret == ERROR_BUFFER_OVERFLOW) {
		buffer.resize(bufLen);
		pAddresses = (PIP_ADAPTER_ADDRESSES)buffer.data();
		ret = GetAdaptersAddresses(AF_INET, flags, NULL, pAddresses, &bufLen);
	}
	if (ret != NO_ERROR) return result;

	for (PIP_ADAPTER_ADDRESSES p = pAddresses; p != NULL; p = p->Next) {
		if (p->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
		if (p->IfType == IF_TYPE_TUNNEL) continue;
		// фізичні медіа - дротовий Ethernet (в т.ч. USB-перехідники) та Wi-Fi
		if (p->IfType != IF_TYPE_ETHERNET_CSMACD && p->IfType != IF_TYPE_IEEE80211) continue;

		UnicodeString desc = UnicodeString(p->Description).LowerCase();
		if (desc.Pos("virtual") || desc.Pos("vmware") || desc.Pos("hyper-v")
			|| desc.Pos("virtualbox") || desc.Pos("tap-") || desc.Pos("vpn")
			|| desc.Pos("npcap") || desc.Pos("loopback")) continue;

		NetAdapterInfo info;
		info.name = UnicodeString(p->FriendlyName);
		info.active = (p->OperStatus == IfOperStatusUp);
		if (p->FirstUnicastAddress != NULL) {
			sockaddr_in *sa_in = (sockaddr_in*)p->FirstUnicastAddress->Address.lpSockaddr;
			BYTE *b = (BYTE*)&sa_in->sin_addr;
			info.ip = UnicodeString(b[0]) + "." + UnicodeString(b[1]) + "." + UnicodeString(b[2]) + "." + UnicodeString(b[3]);
		}
		if (p->PhysicalAddressLength == 6) {
			wchar_t macBuf[18];
			swprintf(macBuf, 18, L"%02X:%02X:%02X:%02X:%02X:%02X",
					 p->PhysicalAddress[0], p->PhysicalAddress[1], p->PhysicalAddress[2],
					 p->PhysicalAddress[3], p->PhysicalAddress[4], p->PhysicalAddress[5]);
			info.mac = UnicodeString(macBuf);
		}
		result.push_back(info);
	}
	return result;
}
//---------------------------------------------------------------------------
