#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

struct book
{
    int width=0;
    int thick=0;
};

book bookshelf[2000];
int dp[2001][4002];
int main()
{
    fstream in;
    int w,t,number,whole_width=0;
    int tmp=1;
    in.open("Data-P1.txt");
    in>>number;
    while(in>>t>>w)
    {
        bookshelf[tmp].thick=t;
        bookshelf[tmp].width=w;
        tmp++;
    }

    for(int i=1; i<=number; i++)
        for(int t=0; t<=2*number; t++)
        {
            dp[i][t]=dp[i-1][t]+bookshelf[i].width;
            if(t>=bookshelf[i].thick)
                dp[i][t]=min(dp[i-1][t-bookshelf[i].thick],dp[i-1][t]+bookshelf[i].width);

        }
    in.close();

    for(int i=1; i<=2*number; i++)
        if(i>=dp[number][i])
        {
            cout<<i-1;
            break;
        }

    return 0;
}
