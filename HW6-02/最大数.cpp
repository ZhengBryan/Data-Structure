/**
 * @file    template.cpp
 * @name    ģ�����
 * @date    2022-11-22
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
class Solution {
private:
    //��ÿ������תΪstring����Ƚ� ����vector��
    vector<string> numarray;
    
    /**
     * @brief ����������תΪstring����
     * @param nums �������������
    */
    void convert(vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); i++)
            numarray.push_back(to_string(nums[i]));
    }
    
    /**
     * @brief ����string�Ƚϴ�С
     * @param a �ַ���a
     * @param b �ַ���b
    */
    static bool LT(string a, string b)
    {
        return a + b < b + a;
    }
public:
    std::string largestNumber(std::vector<int>& nums)
    {
        string output;
        convert(nums);
        sort(numarray.begin(), numarray.end(), LT);
        for (int i = numarray.size() - 1; i >= 0 ; i--)
            output +=  numarray[i];
        return output;
    }
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    Solution s;
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}