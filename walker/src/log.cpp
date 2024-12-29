#include <log.hpp>
void mylog(String a){
	debug_message(a.c_str());
}

void mylog(int a){
	char result[8];
	dtostrf(a, 6, 2, result); // Leave room for too large numbers!
	debug_message(result);
}

void mylog(float a){
	char result[8];
	dtostrf(a, 6, 2, result); // Leave room for too large numbers!
	debug_message(result);
}
void mylog(size_t a){
	char result[8];
	dtostrf(a, 6, 2, result); // Leave room for too large numbers!
	debug_message(result);
}

