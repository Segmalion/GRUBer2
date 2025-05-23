//---------------------------------------------------------------------------

#ifndef ARMH
#define ARMH
//---------------------------------------------------------------------------
struct ArmDevESET {
    std::vector<TDateTime> dateTime;
    UnicodeString device_details;
	UnicodeString serial;
    short catNum = 0;
    bool Status;
};
struct ArmDevUSB {
    TDateTime regDateTime1, regDateTime2;
    UnicodeString name, description, type, serial;
    UnicodeString nameDev, cat;
    short catNum = 0;
	bool know = false;
};
//---------------------------------------------------------------------------
class Arm {
private:
    int number;
    UnicodeString patch;
    UnicodeString dir;
    UnicodeString serial;
    UnicodeString name;
    UnicodeString model;
    UnicodeString cat;
    UnicodeString coment;
    bool isAlert = false;
    short catNum = 0;
    UnicodeString dep;
    TDateTime date;
    std::vector<ArmDevESET> devEset;
	std::vector<ArmDevUSB> devUSB;
public:
};

#endif
