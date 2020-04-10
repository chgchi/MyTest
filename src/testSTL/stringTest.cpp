/*
 * stringTest.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: echgchi
 */

#include "stringTest.h"
#include <ifaddrs.h>
#include <net/if.h>
#include <arpa/inet.h>

void stringTest::SetUpTestCase() {

}

void stringTest::TearDownTestCase() {

}

void spiltString(std::string str,std::string pattern, std::vector<std::string>& result)
{
    std::string::size_type pos;

    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }

    return;
}


std::string get_next_token(const std::string &s, std::string::size_type &pos)
{
    static const std::string white_space = " \t\r\n";
    static const std::string symbols = "#=;()[]<>";
    static const std::string quotes = "\"'";
    static const std::string alpha_numeric = "{}abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "1234567890_./\\:,+-@~?|!$%"
            "^&*()[]<>";

    std::string::size_type start;

    pos = start = s.find_first_not_of(white_space, pos);

    if (std::string::npos == pos) return "";

    //is this an alpha or symbol ?
    char c = s.c_str()[pos];

    if ( std::string::npos != symbols.find( c ) )
    {
        pos = s.find_first_not_of( symbols, start );
    }
    else if ( std::string::npos != quotes.find( c ) )
    {
        pos = s.find_first_of( quotes, start + 1 );
        if (std::string::npos != pos ) ++pos;
    }
    else
    {
        pos = s.find_first_not_of( alpha_numeric, start );
    }

    // if its at the end then return the whole string.
    if (std::string::npos == pos)
    {
        return s.substr(start, std::string::npos);
    }

    std::string::size_type length = pos - start;

    return s.substr(start,length);

}

TEST_F (stringTest, test1) {

	  std::string str="/REGEX/^([A-Fa-f0-9]{2}:){5}[A-Fa-f0-9]{2}$";

	  std::string str2 = str.substr (0,strlen("/REGEX/"));   //  /REGEX/

	  std::string str3 = str.substr (strlen("/REGEX/"));     // ^([A-Fa-f0-9]{2}:){5}[A-Fa-f0-9]{2}$

	  std::cout << str2 << '\n' << str3 << '\n';



}

TEST_F (stringTest, test2) {

    std::vector<std::string> realmFrom;
    std::string realmSource = "User-Name||Calling-Station-id";

    spiltString(realmSource, "||", realmFrom);

    for (std::vector<std::string>::iterator it = realmFrom.begin(); it != realmFrom.end(); ++it)
    {
        printf("%s",(*it).c_str());
        printf("\n");
    }

}


TEST_F (stringTest, test3) {

    std::string::size_type pos = 0;
    std::string tmpstr = "/REGEX/^([A-Fa-F0-9]{2}:){5}[A-Fa-f0-9]{2}$";
    std::string result;
    result = get_next_token(tmpstr, pos);
    printf("%s\n", result.c_str());


}

TEST_F (stringTest, test4) {

    unsigned int intIP = 0x0A579D42;
    const char* pszResult = NULL;
    char sz[INET6_ADDRSTRLEN] = {0};
    intIP = htonl(intIP);
    pszResult = ::inet_ntop(AF_INET, &intIP, sz, sizeof(sz));

    printf("0A579D42 get string IP %s\n", sz);
}

TEST_F (stringTest, test5) {

    //unsigned int intIP = 0x0A579D42;
    char intIP[4] = {(char)0x0A, (char)0x57, (char)0x9D, (char)0x42};

    const char* pszResult = NULL;
    char sz[INET6_ADDRSTRLEN] = {0};
    //intIP = htonl(intIP);
    pszResult = ::inet_ntop(AF_INET, intIP, sz, sizeof(sz));

    printf("0A579D42 get string IP %s\n", sz);
}


TEST_F (stringTest, test6) {

    //unsigned int intIP = 0x0A579D42;
    char intIP[4] = {(char)0x01, (char)0xf2, (char)0x03, (char)0x04};



    printf("test 6 get string IP %d\n", (int)intIP[1]);
}
