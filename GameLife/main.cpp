#include "GameL.h"
int main() {
	GameL& obj = GameL::get_instance(10);
	obj.run();
	return 0;
}