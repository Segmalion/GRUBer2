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
};

std::vector<User> currentUsers();
//---------------------------------------------------------------------------
#endif
