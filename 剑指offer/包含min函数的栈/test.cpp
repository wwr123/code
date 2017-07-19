class Solution {
public:
    stack<int> datastack,minstack;
    void push(int value) {
        datastack.push(value);
        if(minstack.empty())
            minstack.push(value);
        else if(value<minstack.top())
            minstack.push(value);
        else
            minstack.push(minstack.top());
    }
    void pop() {
        datastack.pop();
        minstack.pop();
    }
    int top() {
        return datastack.top();
    }
    int min() {
        return minstack.top();
    }
};