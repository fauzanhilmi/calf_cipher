#pragma once

#include <bits/stdc++.h>	//include everything
#include "md5.h"
using namespace std;

#define left first			//biar lebih kebayang
#define right second		//biar lebih kebayang

class calf_cipher{
	private:
		vector<string> s_blocks;
		static const unsigned char s_box[256];
		
		//private methods
		string XOR (string s1, string s2);		
		string PLUS (string s1, string s2); //and mod 2^32!
		unsigned long long get_string_value(string s);
		string single_encipher(string s_in, string i_key);
		string single_decipher(string s_in, string i_key);
		
		pair<string,string> do_feistel(pair<string,string> p, string i_key);
		string do_operator(string s_in, string i_key, int mode);
		string sub_bytes(string s_in);
		string get_md5(string s_in);
	public:	
		bool isCBC, isCFB;
		calf_cipher();
		
		string do_encipher(string s_in, string g_key);
		string do_decipher(string s_in, string g_key);
};

