#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_map>
using namespace std;

#define weight 3

void tittleRecord(unordered_map<string, int>& priority, string& tittle, 
                vector<pair<int, int>>& cnt) {
    int start = 0, length = tittle.size(), p = 0;
    for(int i = 0; i < length; ++i) {
        if(tittle[i] == ' ') {
            string tmp = tittle.substr(start, i - start);
            if(priority.count(tmp)) {
                cnt[priority[tmp]].first++;
            } else {
                priority[tmp] = p++;
                cnt.push_back(make_pair(1, 0));
            }
            start = i + 1;
        }
    }
    if(start != length) {
        string tmp = tittle.substr(start, length - start);
        if(priority.count(tmp)) {
            cnt[priority[tmp]].first++;
        } else {
            priority[tmp] = p;
            cnt.push_back(make_pair(1, 0));
        }
    }
}

void bodyRecord(unordered_map<string, int>& priority, string& body, 
                vector<pair<int, int>>& cnt) {
    int start = 0, length = body.size(), p = priority.size();
    for(int i = 0; i < length; ++i) {
        if(body[i] == ' ') {
            string tmp = body.substr(start, i - start);
            if(priority.count(tmp)) {
                cnt[priority[tmp]].second++;
            } else {
                priority[tmp] = p++;
                cnt.push_back(make_pair(0, 1));
            }
            start = i + 1;
        }
    }
    if(start != length) {
        string tmp = body.substr(start, length - start);
        if(priority.count(tmp)) {
            cnt[priority[tmp]].second++;
        } else {
            priority[tmp] = p;
            cnt.push_back(make_pair(0, 1));
        }
    }
}

void wordSort(unordered_map<string, int>& priority, vector<string>& words, vector<pair<int, int>>& cnt, int l, int r) {
    if(l >= r) return;
    
    int pick = l + rand() % (r - l + 1);
    swap(words[pick], words[l]);
    swap(cnt[pick], cnt[l]);

    int idx = l + 1, fir = cnt[l].first, sec = cnt[l].second, p = priority[words[l]];
    int sum = weight * fir + sec;
    for(int i = l + 1; i <= r; ++i) {
        int ts = weight * cnt[i].first + cnt[i].second; 
        if(ts > sum 
        || ts == sum && cnt[i].first > fir 
        || ts == sum && cnt[i].first == fir && priority[words[i]] > p) {
            swap(words[i], words[idx]);
            swap(cnt[i], cnt[idx]);
            idx++;
        }
    }
    swap(words[l], words[idx - 1]);
    swap(cnt[l], cnt[idx - 1]);

    wordSort(priority, words, cnt, l, idx - 1);
    wordSort(priority, words, cnt, idx, r);
}

int main() {
    unordered_map<string, int> priority;
    vector<pair<int, int>> cnt;

    string tittle, body;
    getline(cin, tittle);
    tittleRecord(priority, tittle, cnt);
    getline(cin, body);
    bodyRecord(priority, body, cnt);
    vector<string> words(cnt.size());
    for(auto& [w, i] : priority) {
        words[i] = w;
    }
    wordSort(priority, words, cnt, 0, cnt.size() - 1);
    int n = words.size();
    cout << setiosflags(ios::left);
    cout << "rank" << "word" << "nums" << endl;
    for(int i = 0; i < n; ++i) {
        cout << i + 1 << words[i] << (weight * cnt[i].first + cnt[i].second) << endl;
    }
    return 0;
}