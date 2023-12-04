/**
 * @name    template.cpp
 * @brief   p142ģ�����
 * @date    2022-12-02
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class FreqStack {
private:
    map<int, int> num_freq;           //���ÿ��������Ƶ��
    map<int, stack<int>> freq_num;    //���ĳƵ��Ϊ�±����������
    int max_freq;                     //��ǰ���ĳ���Ƶ��
public:
    FreqStack()
    {
        max_freq = 0;
    }

    /**
     * @brief �����Ƶ��ջ������Ԫ��
     * @param val Ԫ��ֵ
    */
    void push(int val)
    {
        //������һ�γ���
        if (num_freq.count(val))
            num_freq[val]++;
        else
            num_freq[val] = 1;

        max_freq = max(max_freq, num_freq[val]);  //�������Ƶ��ֵ

        if (freq_num.count(num_freq[val]))
            freq_num[num_freq[val]].push(val);
        else {
            stack<int> newstack;
            freq_num[num_freq[val]] = newstack;
            freq_num[num_freq[val]].push(val);
        }
    }

    /**
     * @brief ���Ƶ��ջ����Ԫ��
     * @return ������Ԫ��ֵ
    */
    int pop()
    {
        int ret = freq_num[max_freq].top();
        
        freq_num[max_freq].pop();

        num_freq[ret]--;        //��ǰ��Ƶ������

        //��ǰƵ��ȫ������ �����ڸ�Ƶ����
        if (freq_num[max_freq].empty())
            max_freq--;

        return ret;
    }
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/

int main()
{
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n--) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}
