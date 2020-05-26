#include <iostream>
#include <vector>

using namespace std;

const size_t N = 20000000;

vector<bool> prime(N + 1, true);

void fill_table()
{
    prime[0] = prime[1] = false;

    for (auto i = 2; i < prime.size(); i++) {
        if (prime[i]) {
            for (auto j = 2 * i; j < prime.size(); j += i) {
                prime[j] = false;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fill_table();

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cout << (prime[a] ? "YES" : "NO") << '\n';
    }
    
    return 0;
}