#include "calf_cipher.hpp"

calf_cipher::calf_cipher() {}
		
string calf_cipher::XOR(string s1, string s2) {
	string ans="";
	assert(s1.size()==s2.size());
	for(int i=0; i<s1.size(); i++) {
		char c = s1[i]^s2[i];
		cout<<s1[i]<<" ^ "<<s2[i]<<" = "<<c<<endl;
		ans += c;
	}
	return ans;
}

string calf_cipher::PLUS (string s1, string s2) {//and mod 2^32!
	string ans="";
	assert(s1.size()==s2.size() && s1.size()==16);
	for(int i=0; i<s1.size(); i++) {
		char temp = (s1[i]+s2[i])%256;
		
	}
	return ans;
}
string calf_cipher::do_encipher(string s_in, string g_key) {
	s_blocks.clear(); //clear blocks of string
	string temp;
	for(int i=0; i<s_in.size(); i++) {
		if(i%32==0) {
			if(i>0) s_blocks.push_back(temp);
			temp = "";
		}
		temp += s_in[i];
	}
	if(temp!="") { //handling last string, padding zeroes in the back until length = 32 
		string last_s = temp;
		int remainder = 32 - last_s.size();
		for(int i=0; i<remainder; i++) last_s += (char)0;
		s_blocks.push_back(last_s);
	}
	
	//get round1 key
	string r1_key = get_md5(g_key);
	
	return "";
}
string calf_cipher::do_decipher(string s_in, string g_key) {
		
}
		
pair<string,string> calf_cipher::do_feistel(pair<string,string> p, string i_key) {
	string r_in = p.right;
	string l_in = p.left;
	
	r_in = r_in;//disub_bytes
	
}

string calf_cipher::do_operator(string s_in, string i_key, int mode) {
	string ans = "";
	/*switch(mode) {
		case 0:
			ans =  
	}*/
}
string calf_cipher::sub_bytes(string s_in) {}
string calf_cipher::get_md5(string s_in) {
	string hex_s = md5(s_in);
	string ans = "",temp="";
	for(int i=0; i<hex_s.size(); i++) {
		if(i%2==0) {
			temp = "";
			temp += hex_s[i];
		}
		else {
			temp += hex_s[i];
			int num;
			istringstream(temp)>>hex>>num;
			ans += char(num);
		}
	}
	return ans;
}

