#include "Server.h"
#include "const.h"
using namespace std;

int main() {
	Server s(port);
	s.run();
	return 0;
}