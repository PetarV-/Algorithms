#include <iostream>
using namespace std;
int main()
{
    int **a, i, j, m, k;
    cout << "Enter row\n";
    cin >> m;
    a = new int *[m];
    for (i = 0; i < m; i++)
        a[i] = new int[m];
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++)
            cin >> a[i][j];
    for (k = 0; k < m; k++)
    {
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < m; j++)
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
