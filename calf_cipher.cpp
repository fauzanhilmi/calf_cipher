#include "calf_cipher.hpp"

const unsigned char calf_cipher::s_box[256] = {
		   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
		   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
		   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
		   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
		   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
		   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
		   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
		   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
		   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
		   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
		   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
		   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
		   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
		   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
		   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
		   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
		};

calf_cipher::calf_cipher() {}
		
string calf_cipher::XOR(string s1, string s2) {
	string ans="";
	assert(s1.size()==s2.size());
	for(int i=0; i<s1.size(); i++) {
		char c = s1[i]^s2[i];
		ans += c;
	}
	return ans;
}

string calf_cipher::PLUS (string s1, string s2) {//and mod 2^32!
	int MAX_INT = 2147483648; //2^32
	string ans="",temp1 = "", temp2 = "";
	assert(s1.size()==s2.size());
	for(int i=0; i<=s1.size(); i++) {
		if(i%4==0) {
			if(i>0) { //the addition & mod part
				long long tot1=0,tot2=0;
				tot1 += ((temp1[0]<<24) + (temp1[1]<<16) + (temp1[2]<<8) + (temp1[3]));
				tot2 += ((temp2[0]<<24) + (temp2[1]<<16) + (temp2[2]<<8) + (temp2[3]));
				long long res = (tot1 + tot2) % MAX_INT;
				
				char c1,c2,c3,c4;
				c1 = (char)((res>>24)&0xFF);  
				c2 = (char)((res>>16)&0xFF); 
				c3 = (char)((res>>8)&0xFF); 
				c4 = (char)(res&0xFF);
				ans += c1; 
				ans += c2; 
				ans += c3; 
				ans += c4; 
			}
			if(i<s1.size()) {
				temp1 = ""; temp2 = "";
				temp1 += s1[i]; temp2 += s2[i];
			}
		}
		else {
			temp1 += s1[i]; temp2 += s2[i];
		}
	}
	return ans;
}

unsigned long long calf_cipher::get_string_value(string s) {
	int size = s.size();
	unsigned long long ans=0;
	int shift = 0;
	for(int i=size-1; i>=0; i--) {
		unsigned long long temp = (unsigned long long)s[i];
		ans += (unsigned long long)(temp<<(shift*8));
		shift++;
	}
	return ans;
}

string calf_cipher::single_encipher(string s_in, string i_key) {
	string r_key = i_key;
	string l_in = s_in.substr(0,s_in.length()/2);
	string r_in = s_in.substr(s_in.length()/2);
	pair<string,string> p_in (l_in, r_in);
	pair<string,string> p_out = p_in;
	
	//do the feister round 17 times
	for(int i=0; i<17; i++) { 
		p_out = do_feistel(p_out, r_key);
		r_key = get_md5(r_key);
	}
	string ans = p_out.left + p_out.right;
	return ans;
}

string calf_cipher::single_decipher(string s_in, string i_key) { //TODO
	vector<string> r_key;
	r_key.push_back(i_key);

	string l_in = s_in.substr(0,s_in.length()/2);
	string r_in = s_in.substr(s_in.length()/2);
	pair<string,string> p_in (r_in, l_in);
	pair<string,string> p_out = p_in;
	
	//generate round key
	for(int i = 1; i < 17; i++)
		r_key.push_back(get_md5(r_key[i-1]));

	//do the feister round 17 times
	for(int i=16; i>=0; i--) { 
		p_out = do_feistel(p_out, r_key[i]);
	}
	string ans = p_out.right + p_out.left;
	return ans;
}

string calf_cipher::do_encipher(string s_in, string g_key) { //BELUM BUAT SEMUA BLOCK!
	s_blocks.clear(); //clear blocks of string
	
	//partitioning s_in into s_blocks
	string temp="";
	for(int i=0; i<s_in.size(); i++) {
		if(i%16==0) {
			if(i>0) s_blocks.push_back(temp);
			temp = "";
		}
		temp += s_in[i];
	}
	if(temp!="") { //handling last string, padding zeroes in the back until length = 32 
		string last_s = temp;
		int remainder = 16 - last_s.size();
		for(int i=0; i<remainder; i++) last_s += (char)0;
		s_blocks.push_back(last_s);
	}
	
	//get round1 key
	string r_key = get_md5(g_key);
	string ans="";
	
	//encipher each block, it is ECB mode
	for(int i=0; i<s_blocks.size(); i++) {
		string s_b = single_encipher(s_blocks[i], r_key);
		ans += s_b;
	}
	return ans;
}

string calf_cipher::do_decipher(string s_in, string g_key) { //TODO
	s_blocks.clear(); //clear blocks of string
	//partitioning s_in into s_blocks
	string temp="";
	for(int i=0; i<s_in.size(); i++) {
		if(i%16==0) {
			if(i>0) s_blocks.push_back(temp);
			temp = "";
		}
		temp += s_in[i];
	}
	if(temp!="") { //handling last string, padding zeroes in the back until length = 32 
		string last_s = temp;
		int remainder = 16 - last_s.size();
		for(int i=0; i<remainder; i++) last_s += (char)0;
		s_blocks.push_back(last_s);
	}
	
	//get round1 key
	string r_key = get_md5(g_key);
	string ans="";
	
	//encipher each block, it is ECB mode
	for(int i=0; i<s_blocks.size(); i++) {
		string s_b = single_decipher(s_blocks[i], r_key);
		ans += s_b;
	}
	return ans;
}
		
pair<string,string> calf_cipher::do_feistel(pair<string,string> p, string i_key) {
	//cut key into two halves, then OP them to get 64-bit key
	string l_i_key = i_key.substr(0,i_key.length()/2);
	string r_i_key = i_key.substr(i_key.length()/2);
	unsigned long long l_key_val = get_string_value(l_i_key);
	unsigned long long r_key_val = get_string_value(r_i_key);
	int mode = (int)((r_key_val)%4);
	string key = do_operator(l_i_key,r_i_key,mode);
	
	string r_in = p.right;
	string l_in = p.left; 
	assert(r_in.size()==l_in.size());
		
	//new left bytes are simply old right bytes
	string l_new = r_in;
	
	//start the round
	//sub_bytes right bytes BELUM!
	r_in = sub_bytes(r_in);
	
	//op right bytes
	r_in = do_operator(r_in, key, mode);
	
	//xor both bytes to get new right bytes
	string r_new = XOR(l_in, r_in);
	
	//return them
	pair<string,string> p_ans (l_new, r_new);
	return p_ans;
}

string calf_cipher::do_operator(string s_in, string i_key, int mode) {
	string ans = "";
	switch(mode) {
		case 0:
			ans = XOR(s_in,i_key);
			break;
		case 1:
			ans = PLUS(s_in,i_key);
			break;
		case 2:
			ans = PLUS( (XOR(s_in,i_key)), i_key);
			break;
		case 3:
			ans = XOR( (PLUS(s_in,i_key)), i_key);
			break;
	}
	return ans;
}

string calf_cipher::sub_bytes(string s_in) {
	string s_out = "";
	for (int i = 0; i < s_in.size(); i++) s_out+=s_box[s_in[i]];
	return s_out;
}
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

