class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int val, res;
        while (!stack1.empty()) {
            val = stack1.top();
            stack1.pop();
            stack2.push(val);
        }
        res = val;
        stack2.pop();
        while (!stack2.empty()) {
            val = stack2.top();
            stack2.pop();
            stack1.push(val);
        }
        return res;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
