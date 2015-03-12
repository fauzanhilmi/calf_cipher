#include <bits/stdc++.h> 	//include everything
#define left first			//biar lebih kebayang
#define right second		//biar lebih kebayang

class calf_cipher{
	private:
		//...
	public:
		calf_cipher();
		
		string do_encipher(pair<string,string> p_in, string g_key);
		string do_decipher(pair<string,string> p_in, string g_key);
		
		pair<string,string> do_feistel(pair<string,string>);
		string do_operator(string s_in, string i_key, int mode);
		string sub_bytes(string s_in);
};

