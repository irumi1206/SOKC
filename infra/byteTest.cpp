#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
int main(){
    char8_t message[]=u8"0123456789abcdefghijklmnopqrstuvwxyzㄱㄴㄷㄹ";
    for(int i=0;i<std::char_traits<char8_t>::length(message);++i) printf("%d",message[i]);
}
