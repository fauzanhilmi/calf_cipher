#include "calf_cipher.hpp"
#include <bits/stdc++.h>	//include everything
#define MAXINT 2147483648
using namespace std;

string htos (string s_in);
string stoh (string s_in);

int main() {
	//TEST S_BLOCKS / STRING SPLITTING
	/*calf_cipher cc; string x = "";
	string s = "Lorem ipsum dolor sit amet, nam rebum fugit alterum eu. Id vidit delenit urbanitas vis, regione electram pri ex, dicam consul causae sit te. Stet semper mel ei. Velit debet imperdiet qui an, cu oratio omnium sanctus nec. Vim solet nonumy labore ea, assum invidunt recusabo ea has. Veritus necessitatibus vis at, sed ex esse duis. Mei ne rebum erant luptatum, altera volutpat molestiae sea et. Te pri alii blandit perfecto. Quo at ridens periculis, in numquam dolorem qui. Qui cu mundi vivendo sapientem. Cum doctus apeirian accusamus cu, usu ei civibus apeirian. Posse ridens vix id. Ius ne explicari reprehendunt, cu pri inani ornatus, tation theophrastus ne eam. Ea nec quis justo, cu habeo timeam debitis vim. Has eu eirmod antiopam concludaturque, in probo dolore mnesarchum quo, per impedit nominavi no. Partem aperiri gloriatur est in. Usu nostro postulant at. Populo civibus albucius nec id, pro congue eruditi explicari ne, duo et velit scripserit ullamcorper. Duo at purto platonem, pro ex solet tation appareat. Tale sale ut qui. His in soleat posidonium. Ea sea aeque euripidis, eum ad nihil omnesque salutandi. Nisl commune accumsan ad eos. Tibique mediocrem vituperatoribus nec ex, usu ne stet augue praesent. Veri necessitatibus ea ius, melius scribentur deterruisset nec ad. Pro no noster hendrerit.";//
	x = cc.do_encipher(s,x);
	for(int i=0; i<cc.s_blocks.size(); i++) {
		cout<<cc.s_blocks[i]<<" "<<cc.s_blocks[i].size()<<endl;
	}*/
	
	/*
	string s1 = "haha";
	//char c1 = s1 & FF:
	int x = (s1[0]<<24)+(s1[1]<<16)+(s1[2]<<8)+(s1[3]);
	cout<<x<<endl;
	cout<<char(x>>24)<<" "<<char(x>>16)<<" "<<char(x>>8)<<" "<<char((x)&0xFF);
	//cout<<(unsigned int)s1;*/
	long long x = 2147483647;
	x+=2147483647;
	int res = x%MAXINT;
	cout<<res;
	return 0;
}

string htos (string s_in) {
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
			//stringstream str;
			//int num = (int) strtol(temp,NULL,16);
			ans += char(num);
		}
	}
	return ans;
}

string stoh (string s_in) {
	string temp="",ans="";
	for(int i=0; i<s_in.size(); i++) {
		temp="";
		unsigned char uc = s_in[i];
		int num = (int) uc;
		stringstream str;
		str<<hex<<num;
		temp = str.str();
		string prev = ans;
		ans = ans + temp;
		//cout<<prev<<" + "<<temp<<" = "<<ans<<endl;
	}
	return ans;
}

