//---------------------------------------------------------------------------

#ifndef DirH
#define DirH
//---------------------------------------------------------------------------
class Dir {
private:
	UnicodeString progFull;
	UnicodeString baseName, baseFull;
	UnicodeString dateName, dateFull;
	UnicodeString grubName, grubFull;
public:
	Dir();
	void check();
	//сеттеры
	void setGrubFull(UnicodeString str);
	//геттеры
	UnicodeString getGrubFull();
	UnicodeString getToolFull();
};
#endif
