//---------------------------------------------------------------------------

#ifndef UsersH
#define UsersH

#include <vector>


//---------------------------------------------------------------------------
struct User {
	UnicodeString name;
	UnicodeString fullName;
	unsigned int password_age;  // насколько стар пароль
	UnicodeString priv; 		// привилегии - GUEST, USER, ADMIN
	bool flags_ACCOUNTDISABLE, flags_LOCKOUT, flags_DONT_EXPIRE_PASSWD, flags_PASSWORD_EXPIRED;
	unsigned int password_expired;      // время с устаревания пароля
	unsigned int logon_bad, logon_good; // кол-во входа в систему
	unsigned int last_logon; // час останнього входу, секунди з 1970 (0 = ще не заходив)
	UnicodeString accountType; // "Microsoft" або "Локальна"
};

std::vector<User> currentUsers();
//---------------------------------------------------------------------------
#endif
