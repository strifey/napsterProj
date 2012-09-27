#ifndef NAPSTER_H
#define NAPSTER_H

//All sigs I might need to send/recv/compare against
#define ADD 'A'
#define DEL 'D'
#define LST 'L'
#define ADD_S "A"
#define DEL_S "D"
#define LST_S "L"
#define DELIM_S "|"

//Const char flags
char SUCESS = 'S';
char UNSCESS ='U';
char DELIM = '|';
char ACK = 'Y'; 

//Max size to send allowable
#define MAXBUFF 1400

//Set server port
#define PORT "12001"

#endif
