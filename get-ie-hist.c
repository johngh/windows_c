/*
 * From http://www.rohitab.com/discuss/topic/26622-how-do-i-use-regqueryvalueex/
 *
 */

#include <stdio.h>
#include <windows.h>
#include <shlwapi.h> //for wnsprintf
#define  TURLs TEXT("Software\\Microsoft\\Internet Explorer\\TypedURLs")

int GetIEHistory(int nHowMany) {

	char szTemp[8];
	HKEY hKey;
	DWORD dwLength, dwType;
	
	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\TypedURLs", 0,
		KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS) return 0;
	
	int nURL;
	for(nURL = 0; nURL < nHowMany; nURL++){
		sprintf(szTemp, "url%d", (nURL + 1));
		if(RegQueryValueExA(hKey, szTemp, NULL, NULL, NULL, &dwLength) == ERROR_SUCCESS){
			char *szURL = (char *)malloc(dwLength);
			if(RegQueryValueExA(hKey, szTemp, NULL, &dwType, szURL, &dwLength) == ERROR_SUCCESS){
				if(dwType == REG_SZ) printf ("%s %d\n", szURL, dwLength);
			}
			free(szURL);
		}
	}
	
	RegCloseKey(hKey);
	return 1;

}


int main(int argc, char* argv[]) {

	PBYTE History[5] = { 0 };
	int i, Get;
	
	Get = GetIEHistory(5);
	if (Get > 0)
	{
		for(i = 0; i < Get; i++)
		{
			printf("%s\n", History[i]);
			free(History[i]);
		}
	}
	 
	return 0;
}
