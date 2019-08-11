#include <cstdio>

const int test_case_size = 12;
const int test_cases[test_case_size] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
typedef long long ll;
/*ll multiply_mod(ll x, ll y, ll p)
{
	ll t = (x * y - (ll) ((long double) x / p * y + 1e-3) * p) % p;
	return t < 0 ? t + p : t;
}*/
ll multiply_mod(ll x, ll y, ll p)
{
	ll ret = 0;
	for (; y; x = (x + x) % p, y >>= 1)
		y & 1 ? ret = (ret + x) % p : 0;
	return ret;
}
ll add_mod(ll x, ll y, ll p) {
	return (0ull + x + y) % p;
}
ll power_mod(ll x, ll exp, ll p) {
	ll ans = 1;
	while (exp) {
		if (exp & 1)
			ans = multiply_mod(ans, x, p);
		x = multiply_mod(x, x, p);
		exp >>= 1;
	}
	return ans;
}
bool miller_rabin_check(ll prime, ll base) {
	ll number = prime - 1;
	for (; ~number & 1; number >>= 1)
		continue;
	ll result = power_mod(base, number, prime);
	for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1)
		result = multiply_mod(result, result, prime);
	return result == prime - 1 || (number & 1) == 1;
}
bool miller_rabin(ll number)
{
	if (number < 2) return false;
	if (number < 4) return true;
	if (~number & 1) return false;
	for (int i = 0; i < test_case_size && test_cases[i] < number; ++i)
		if (!miller_rabin_check(number, test_cases[i]))
			return false;
	return true;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		ll x; scanf("%lld", &x);
		ll ans = 1;
		for (ll i = x - 2; i; --i)
		{
			if (miller_rabin(i))
			{
				printf("%lld\n", ans);
				break;
			}
			ans = multiply_mod(ans, power_mod(i, x - 2, x), x);
		}
	}
	return 0;
}
