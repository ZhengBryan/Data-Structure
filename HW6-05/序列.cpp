#include <iostream>
#include <algorithm>
#include <queue>
#define MAXN 2010
using namespace std;

/**
 * @brief �����µ�һ��new_arr�� ά���µ�ǰnС��
 * @param ans �Ѿ������е�ǰnС��
 * @param new_arr �¶����һ��
 * @param n ÿ��Ԫ�ظ���
*/
void maintain_sum(int* ans, int* new_arr, int n)
{
    priority_queue<int> q;

    // O(n^2)��ʱ�临�Ӷ� ���αȽ�ԭ�ȶ���
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            //�µ�һ��sum �����ж��Ƿ�Ҫ����
            int sum = ans[i] + new_arr[j];

            //qҪ�������n���Ĵ�С
            if (q.size() < n) 
                q.push(sum);
            else if (sum < q.top()){
                q.pop();
                q.push(sum);
            }
            //��֦ ��Ϊ�������о����� ����ǰ�Ѿ���������֮�������������
            else 
                break;
        }
    }

    //q�Ǵ���� ans��������򱣳ִ�С���� ��˷�����
    for (int i = n - 1; i >= 0; i--){
        ans[i] = q.top();
        q.pop();
    }

}
int main()
{
    int T, m, n;

    //ansͨ�����ϸ����ۼӱ��ָ���Ϊn�� ������i��֮��ǰi�и���һ��Ԫ�ص�ǰnС������
    int ans[MAXN];
    //new_arr�����������һ��
    int new_arr[MAXN];

    cin >> T;

    while (T--){
        cin >> m >> n;

        for (int i = 0; i < n; i++)
            cin >> ans[i];

        //�����Ƿ���֮��ļ�֦ ����ԼO(nlogn)ʱ�临�Ӷ�
        sort(ans, ans + n);

        for (int i = 1; i < m; i++){
            for (int j = 0; j < n; j++)
                cin >> new_arr[j];
            sort(new_arr, new_arr + n);
            maintain_sum(ans, new_arr, n);
        }

        for (int i = 0; i < n; ++i)
            cout << ans[i] << " ";

        cout << endl;
    }

    return 0;
}