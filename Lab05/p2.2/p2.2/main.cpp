#include<iostream>
#include<string>
#include<cmath>
#include<fstream>

using namespace std;

string str1;
string str2;

int res1[100002] {0};
int res2[100000]= {0};
int res3[100000]= {0};
int mis(char one,char two)
{
    if(one=='-')
        return 0;
    int x=abs(one-two);
    if(x==0)
        return 0;
    else if(x=='T'-'A')
        return 1;
    else if(x=='G'-'A')
        return 5;
    else if(x=='C'-'A')
        return 1;
    else if(x=='T'-'G')
        return 9;
    else if(x=='T'-'C')
        return 1;
    else if(x=='G'-'C')
        return 1;
}
int gap(char tar)
{
    if(tar=='A')
        return 1;
    else if(tar=='T')
        return 2;
    else if(tar=='G')
        return 1;
    else if(tar=='C')
        return 3;
    else if(tar=='-')
        return 0;
}

int main()
{
    fstream in;
    in.open("Data-P2a.txt");
    in>>str1;
    in.close();
    in.open("Data-P2b.txt");
    in>>str2;
    in.close();
    int m=str1.size();
    int n=str2.size();

    str1='-'+str1;
    str2='-'+str2;
    int tmp=0;

    for(int i=0; i<=m; i++)
    {
        tmp+=gap(str1[i]);
        res1[i]=tmp;
    }
    tmp=0;
    for(int j=0; j<=n; j++)
    {
        tmp+=gap(str2[j]);
        res2[j]=tmp;
    }
    res1[0]=0;
    res2[0]=0;
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            res3[0]=res1[i];
            res3[j]=min(min(mis(str1[i],str2[j])+res2[j-1],res2[j]+gap(str1[i])),res3[j-1]+gap(str2[j]));

        }
        for(int j=0; j<=n; j++)
                res2[j]=res3[j];
    }
    cout<<res3[n];
    return 0;

    return 0;
}
