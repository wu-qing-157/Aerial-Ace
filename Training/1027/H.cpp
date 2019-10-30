

const int maxn = 1e5 + 10;
char s[maxn];

int cnt[3], sum[maxn];



int main() {
	int n; scanf("%d%s", &n, s + 1);
	for (int i = n; i >= 1; i--) {
		if (s[i] == '0') cnt[0]++;
		else if (s[i] == '1') {
			if (cnt[0])	cnt[0]--;
			else cnt[1]++;		
		} else {
			if (cnt[0]) cnt[0]--;
			else if (cnt[1]) cnt[1]--;
			else cnt[2]++;
		}
		int tmp = std::min(cnt[1], cnt[2]);
		cnt[1] -= tmp;
		cnt[2] -= tmp;
		tmp = std::min(cnt[0], std::max(cnt[1], cnt[2]));
		
	}
	
}
