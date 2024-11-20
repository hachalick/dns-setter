#include <windows.h>
#include <iostream>
#include <aclapi.h>
#include <conio.h>
#include <string>

using namespace std;

bool IsRunAsAdmin() {
  BOOL isAdmin = FALSE;
  PSID adminGroup = NULL;

  // شناسه گروه Administrators را دریافت کنید
  SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
  if (AllocateAndInitializeSid(
    &ntAuthority,
    2,
    SECURITY_BUILTIN_DOMAIN_RID,
    DOMAIN_ALIAS_RID_ADMINS,
    0, 0, 0, 0, 0, 0,
    &adminGroup))
  {
    // بررسی کنید که آیا توکن جاری در گروه Administrators است
    if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
      isAdmin = FALSE;
    }
    FreeSid(adminGroup);
  }

  return isAdmin;
}

void ShowDns() {
  system("ipconfig /all");
}

void ShowNetworks() {
  system("netsh interface show interface");
}

string getString(string text_show) {
  string value;
  cout << text_show << endl;
  cin >> value;
  return value;
}

void SetDNSFirst(string interfaceName, string ip) {
  string command = "netsh interface ipv4 set dnsservers " + interfaceName + " static " + ip + " primary";
  const char* cstr = command.c_str();
  system("cls");
  cout << "start setting frist dns" << endl;
  system(cstr);
  cout << "frist dns setted" << endl;
  system("cls");
}

void SetDNSSecond(string interfaceName, string ip) {
  string command = "netsh interface ipv4 add dnsservers " + interfaceName + " " + ip + " index=2";
  const char* cstr = command.c_str();
  system("cls");
  cout << "start setting second dns" << endl;
  system(cstr);
  cout << "second dns setted" << endl;
  system("cls");
}

void DNSSetterManual() {
  string ip1;
  string ip2;
  cout << "enter first ip (8.8.8.8): ";
  cin >> ip1;
  cout << endl;
  cout << "enter second ip (8.8.8.8): ";
  cin >> ip2;
  cout << endl;
  SetDNSFirst("WiFi", ip1);
  SetDNSSecond("WiFi", ip2);
}

void DNSSetterDefault() {
  system("cls");
  char mode;
  string interfaceName = "WiFi";
  bool flagLoop = true;
  while (flagLoop) {
    cout << "\n\n\t" << "Program Setter DNS - Create By Hosein Jalali" << endl;
    cout << "\t" << "--------------------------------------------" << endl;
    cout << "\t" << "[0] back" << endl;
    cout << "\t" << "[1] set shekan" << endl;
    cout << "\t" << "[2] set 403.online" << endl;
    cout << "\t" << "[3] set begzar" << endl;
    cout << "\t" << "[4] set radar" << endl;
    cout << "\t" << "[5] set electro" << endl;
    cout << "\t" << "[6] set sheltertm" << endl;
    cout << "\t" << "[7] set pishgaman" << endl;
    cout << "\t" << "[8] set shatel" << endl;
    cout << "\t" << "[9] set cloudflare" << endl;
    cout << "\t" << "--------------------------------------------" << endl;
    cout << endl;
    mode = _getch();
    switch (mode) {
    case '0':
      flagLoop = false;
      break;
    case '1':
      // shekan
      SetDNSFirst(interfaceName, "178.22.122.100");
      SetDNSSecond(interfaceName, "185.51.200.2");
      break;
    case '2':
      // 403 online
      SetDNSFirst(interfaceName, "10.202.10.202");
      SetDNSSecond(interfaceName, "10.202.10.102");
      break;
    case '3':
      // begzar
      SetDNSFirst(interfaceName, "185.55.226.26");
      SetDNSSecond(interfaceName, "185.55.225.25");
      break;
    case '4':
      // radar
      interfaceName = getString("enter interface network:");
      SetDNSFirst(interfaceName, "10.202.10.10");
      SetDNSSecond(interfaceName, "10.202.10.11");
      break;
    case '5':
      // electro
      SetDNSFirst(interfaceName, "78.157.42.100");
      SetDNSSecond(interfaceName, "78.157.42.101");
      break;
    case '6':
      // sheltertm
      SetDNSFirst(interfaceName, "94.103.125.157");
      SetDNSSecond(interfaceName, "94.103.125.158");
      break;
    case '7':
      // pishgaman
      SetDNSFirst(interfaceName, "5.202.100.100");
      SetDNSSecond(interfaceName, "5.202.100.101 ");
      break;
    case '8':
      // shatel
      SetDNSFirst(interfaceName, "85.15.1.14");
      SetDNSSecond(interfaceName, "85.15.1.15");
      break;
    case '9':
      // cloudflare
      SetDNSFirst(interfaceName, "1.1.1.1");
      SetDNSSecond(interfaceName, "1.0.0.1");
      break;
    default:
      cout << "enter number from items" << endl;
      _getch();
      break;
    }
  }
}

int main() {
  char mode;
  bool loopProg = true;
  string interfaceName = "WiFi";
  if (IsRunAsAdmin()) {
    while (loopProg) {
      system("cls");
      cout << "\n\n\t" << "Program Setter DNS - Create By Hosein Jalali" << endl;
      cout << "\t" << "--------------------------------------------" << endl;
      cout << "\t" << "[0] exit" << endl;
      cout << "\t" << "[1] show dns" << endl;
      cout << "\t" << "[2] show networks" << endl;
      cout << "\t" << "[3] clean dns" << endl;
      cout << "\t" << "[4] manual use" << endl;
      cout << "\t" << "[5] default use" << endl;
      cout << "\t" << "--------------------------------------------" << endl;
      cout << endl;
      mode = _getch();
      switch (mode) {
      case '0':
        loopProg = false;
        _getch();
        break;
      case '1':
        ShowDns();
        _getch();
        break;
      case '2':
        ShowNetworks();
        _getch();
        break;
      case '3':
        SetDNSFirst(interfaceName, "192.168.1.1");
        break;
      case '4':
        DNSSetterManual();
        break;
      case '5':
        DNSSetterDefault();
        break;
      default:
        _getch();
        break;
      }
    }
  }
  else {
    cout << "\n\n\tThe program is NOT running as Administrator." << endl;
  }
  _getch();
  return 0;
}
