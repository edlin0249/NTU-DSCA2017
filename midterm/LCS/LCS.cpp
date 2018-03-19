#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
int dp[105][105];

vector<string> LCS;
string string1;
string string2;
int lcsnum;
size_t len_1;
size_t len_2;

bool cmp(string i, string j){
	return i.compare(j) < 0 ? true : false;
}

void backtrack(size_t l1, size_t l2, int idx, string seq){	
	if(dp[l1][l2] == 0){
		if(idx == -1){
			LCS.push_back(seq.substr(0, dp[len_1][len_2]));
			lcsnum++;
		}
		return ;
	}
	
	for(size_t i = 1; i <= l1; i++){
		for(size_t j = 1; j <= l2; j++){
			if(string1[i-1] == string2[j-1] && dp[i][j] == dp[l1][l2]){
				seq[idx] = string1[i-1];
				backtrack(i-1, j-1, idx-1, seq);
			}
		}
	}
	
	return;
}

int main(void){
	
	cin >> string1;
	len_1 = string1.length();
	
	cin >> string2;
	len_2 = string2.length();
	memset(dp, 0, sizeof(dp));

	for(int i = 1; i <= len_1; i++){
		for(int j = 1; j <= len_2; j++){
			if(string1[i-1] == string2[j-1]){
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			else{
				dp[i][j] = dp[i-1][j] > dp[i][j-1] ? dp[i-1][j] : dp[i][j-1];
			}
		}
	}
	
	//find LCS
	lcsnum = 0;
	string seq(150, 0);
	//seq.resize(150);

	backtrack(len_1, len_2, dp[len_1][len_2]-1, seq);
	
	//qsort(LCS, lcsnum, sizeof(char[105]), cmp);
	sort(LCS.begin(), LCS.end(), cmp);	
	printf("%d %d\n", dp[len_1][len_2], lcsnum);
	
	//vector<string>::iter;
	for(vector<string>::iterator iter = LCS.begin(); iter != LCS.end(); iter++){
		cout << *iter << "\n";
	}
	return 0;
}
