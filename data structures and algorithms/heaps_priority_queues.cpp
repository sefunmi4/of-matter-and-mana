#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

class Heaps_Priority_Queues {
public:
    Heaps_Priority_Queues() {}
    ~Heaps_Priority_Queues() {}
    Heaps_Priority_Queues(const Heaps_Priority_Queues& other) = default;
    Heaps_Priority_Queues(Heaps_Priority_Queues&& other) noexcept = default;
    Heaps_Priority_Queues& operator=(const Heaps_Priority_Queues& other) = default;
    Heaps_Priority_Queues& operator=(Heaps_Priority_Queues&& other) noexcept = default;

    // 1. Kth Largest Element in a Stream
    class KthLargest {
    private:
        priority_queue<int, vector<int>, greater<int>> minHeap;
        int k;

    public:
        KthLargest(int k, vector<int>& nums) : k(k) {
            for (int num : nums) {
                minHeap.push(num);
                if (minHeap.size() > k) minHeap.pop();
            }
        }

        int add(int val) {
            minHeap.push(val);
            if (minHeap.size() > k) minHeap.pop();
            return minHeap.top();
        }
    };

    // 2. Last Stone Weight
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> maxHeap(stones.begin(), stones.end());

        while (maxHeap.size() > 1) {
            int x = maxHeap.top(); maxHeap.pop();
            int y = maxHeap.top(); maxHeap.pop();
            if (x != y) maxHeap.push(x - y);
        }

        return maxHeap.empty() ? 0 : maxHeap.top();
    }

    // 3. K Closest Points to Origin
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, vector<int>>> maxHeap;

        for (const auto& point : points) {
            int dist = point[0] * point[0] + point[1] * point[1];
            maxHeap.push({dist, point});
            if (maxHeap.size() > k) maxHeap.pop();
        }

        vector<vector<int>> res;
        while (!maxHeap.empty()) {
            res.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return res;
    }

    // 4. Kth Largest Element in an Array
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) minHeap.pop();
        }
        return minHeap.top();
    }

    // 5. Task Scheduler
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        for (char task : tasks) count[task - 'A']++;

        priority_queue<int> maxHeap;
        for (int c : count) if (c > 0) maxHeap.push(c);

        queue<pair<int, int>> cooldown;
        int time = 0;

        while (!maxHeap.empty() || !cooldown.empty()) {
            time++;

            if (!maxHeap.empty()) {
                int freq = maxHeap.top() - 1;
                maxHeap.pop();
                if (freq > 0) cooldown.push({freq, time + n});
            }

            if (!cooldown.empty() && cooldown.front().second == time) {
                maxHeap.push(cooldown.front().first);
                cooldown.pop();
            }
        }

        return time;
    }

    // 6. Design Twitter
    class Twitter {
    private:
        int timeStamp = 0;
        unordered_map<int, vector<pair<int, int>>> tweets;
        unordered_map<int, unordered_set<int>> follows;

    public:
        Twitter() {}

        void postTweet(int userId, int tweetId) {
            tweets[userId].push_back({timeStamp--, tweetId});
        }

        vector<int> getNewsFeed(int userId) {
            follows[userId].insert(userId);
            priority_queue<tuple<int, int, int, int>> maxHeap;

            for (int f : follows[userId]) {
                auto& t = tweets[f];
                if (!t.empty()) {
                    int idx = t.size() - 1;
                    maxHeap.push({t[idx].first, t[idx].second, f, idx - 1});
                }
            }

            vector<int> res;
            while (!maxHeap.empty() && res.size() < 10) {
                auto [time, tweetId, user, idx] = maxHeap.top(); maxHeap.pop();
                res.push_back(tweetId);
                if (idx >= 0) {
                    maxHeap.push({tweets[user][idx].first, tweets[user][idx].second, user, idx - 1});
                }
            }
            return res;
        }

        void follow(int followerId, int followeeId) {
            follows[followerId].insert(followeeId);
        }

        void unfollow(int followerId, int followeeId) {
            if (followeeId != followerId) {
                follows[followerId].erase(followeeId);
            }
        }
    };

    // 7. Find Median from Data Stream
    class MedianFinder {
    private:
        priority_queue<int> maxHeap; // Left half
        priority_queue<int, vector<int>, greater<int>> minHeap; // Right half

    public:
        MedianFinder() {}

        void addNum(int num) {
            maxHeap.push(num);
            minHeap.push(maxHeap.top());
            maxHeap.pop();

            if (minHeap.size() > maxHeap.size()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }

        double findMedian() {
            if (maxHeap.size() == minHeap.size()) {
                return (maxHeap.top() + minHeap.top()) / 2.0;
            } else {
                return maxHeap.top();
            }
        }
    };

private:
    // No private members
};