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
	UnicodeString grubTemp;
public:
	Dir();
	void check();
	//сеттеры
	void setGrubFull(UnicodeString str);
	//геттеры
	UnicodeString getGrubFull();
	UnicodeString getToolFull();
    UnicodeString get_grubTemp();
};
#endif
