#include "BasicATL.h"

#include <EventQueue.h>
#include "..\EventQueue\CEventQueue.h"

#include <DataStore.h>
#include "..\DataStore\CDataStore.h"

CZoneComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_EventQueue, CEventQueue)
	OBJECT_ENTRY(CLSID_DataStoreManager, CDataStoreManager)
END_OBJECT_MAP()


/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
/////////////////////////////////////////////////////////////////////////////

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{        
		_Module.Init(ObjectMap, hInstance);
		//DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE
/////////////////////////////////////////////////////////////////////////////

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type
/////////////////////////////////////////////////////////////////////////////

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}
