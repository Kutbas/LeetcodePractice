#include <bits/stdc++.h>
#include <mutex>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    // 1
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> f(n + 1), g(n + 1), ret(n);
        f[0] = g[n - 1] = 1;

        for (int i = 1; i <= n; i++)
            f[i] = f[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            g[i] = g[i + 1] * nums[i + 1];

        for (int i = 0; i < n; i++)
            ret[i] = f[i] * g[i];

        return ret;
    }

    // 2
    string decodeString(string s)
    {
        stack<string> st;
        string ret;
        stack<int> nums;
        int num = 0;

        for (char ch : s)
        {
            if (isdigit(ch))
                num = num * 10 + (ch - '0');
            else if (ch == '[')
            {
                st.push(ret);
                ret = "";
                nums.push(num);
                num = 0;
            }
            else if (ch == ']')
            {
                string tmp = st.top();
                st.pop();
                int k = nums.top();
                nums.pop();
                while (k--)
                    tmp += ret;
                ret = tmp;
            }
            else
                ret += ch;
        }

        return ret;
    }

    // 3
    int m, n;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] == 0)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }

        while (q.size())
        {
            int sz = q.size();
            while (sz--)
            {
                auto [a, b] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int x = a + dx[k], y = b + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] == -1)
                    {
                        q.push({x, y});
                        dist[x][y] = dist[a][b] + 1;
                    }
                }
            }
        }

        return dist;
    }

    // 5
    unordered_map<char, int> in;
    unordered_map<char, unordered_set<char>> edges;
    bool check = false;
    string alienOrder(vector<string> &words)
    {
        for (auto &word : words)
            for (auto &ch : word)
                in[ch] = 0;

        for (int i = 0; i < words.size(); i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                add(words[i], words[j]);
                if (check)
                    return "";
            }

        queue<char> q;
        for (auto [a, b] : in)
        {
            if (b == 0)
                q.push(a);
        }

        string ret;
        while (q.size())
        {
            auto t = q.front();
            q.pop();
            ret += t;

            for (char a : edges[t])
                if (--in[a] == 0)
                    q.push(a);
        }

        for (auto [a, b] : in)
            if (b != 0)
                return "";

        return ret;
    }

    void add(string &s1, string &s2)
    {
        int n = min(s1.size(), s2.size()), i = 0;

        for (; i < n; i++)
        {
            if (s1[i] != s2[i])
            {
                char a = s1[i], b = s2[i]; // a->b;
                if (!edges.count(a) || !edges[a].count(b))
                {
                    in[b]++;
                    edges[a].insert(b);
                }
                break;
            }
        }

        // abc ab
        if (i < s1.size() && i == s2.size())
            check = true;
    }

    // 7
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        int i = postorder.size() - 1;
        return _buildTree(inorder, postorder, i, 0, inorder.size() - 1);
    }

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int &posti, int inBegin, int inEnd)
    {
        if (inBegin > inEnd)
            return nullptr;

        TreeNode *root = new TreeNode(postorder[posti]);

        int rooti = inBegin;
        while (rooti <= inEnd)
            if (postorder[posti] == inorder[rooti])
                break;
            else
                rooti++;

        --posti;
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inEnd);
        root->left = _buildTree(inorder, postorder, posti, inBegin, rooti - 1);

        return root;
    }
};

// 4
class LRUCache
{
public:
    LRUCache(int capacity) : _capacity(capacity)
    {
    }

    int get(int key)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            auto it = ret->second;
            _list.splice(_list.begin(), _list, it);
            return it->second;
        }
        return -1;
    }

    void put(int key, int value)
    {
        auto ret = _hash.find(key);
        if (ret != _hash.end())
        {
            auto it = ret->second;
            it->second = value;
            _list.splice(_list.begin(), _list, it);
        }
        else
        {
            if (_capacity == _hash.size())
            {
                pair<int, int> back = _list.back();
                _hash.erase(back.first);
                _list.pop_back();
            }
            _list.push_front({key, value});
            _hash[key] = _list.begin();
        }
    }

private:
    typedef list<pair<int, int>>::iterator LstItor;
    int _capacity;
    list<pair<int, int>> _list;
    unordered_map<int, LstItor> _hash;
};

// 6
const int N = 1010;
int n, v;
int V[N], W[N];
int dp[N][N];

int main()
{
    cin >> n >> v;
    for (int i = 1; i <= n; i++)
        cin >> V[i] >> W[i];

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= V[i])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - V[i]] + W[i]);
        }

    cout << dp[n][v] << endl;

    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= v; i++)
        dp[0][i] = -1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= v; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= V[i] && dp[i - 1][j - V[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - V[i]] + W[i]);
        }

    cout << (dp[n][v] == -1 ? 0 : dp[n][v]) << endl;

    return 0;
}

// 8
string s;

string change(string &s)
{
    if (s[0] >= 'A' && s[0] <= 'Z')
        s[0] = tolower(s[0]);
    return s;
}

int main()
{
    getline(cin, s);

    regex re{R"([a-zA-Z]+)"};
    sregex_token_iterator begin(s.begin(), s.end(), re, 0);
    sregex_token_iterator end;

    vector<string> words(begin, end);
    map<string, int> hash;

    for (auto &word : words)
    {
        string tmp = change(word);
        hash[tmp]++;
    }

    for (auto &[a, b] : hash)
        cout << a << ":" << b << endl;

    return 0;
}