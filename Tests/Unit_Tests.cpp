#include "H/Test_Lexer.h"
#include "H/Test_Back_End.h"
#include "../H/UI/Safe.h"

extern const string Magenta;
extern const string Reset;

#ifdef Test
int main(int argc, char** argv) {
	cout << Magenta << "Lexer tests:" << Reset << endl;
	Lexer_Test L_Test;
	cout << Magenta << "\n\nBack end tests:" << Reset << endl;
	Back_End_Test B_Test;
	return 0;
}
#endif