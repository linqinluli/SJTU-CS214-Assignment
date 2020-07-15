#include<iostream>
#include<string>
#include<cmath>

using namespace std;

string str1;
string str2;

int res[1000][1000]= {0};
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
}
int L_set(int x1,int y1,int x2,int y2)
{
    int minres=9999999;
    int mintar=0;

    if(x1==x2&&y1==y2)
        return 0;
    else if(x2-x1==1&&y1==y2)
    {
        res[x2][y1]=0;
        return gap(str1[x2]);
    }
    else if(y2-y1==1&&x1==x2)
    {
        res[x1][y2]=0;
        return gap(str2[y2]);
    }
    else if(x1==x2)
    {
        int sum=0;
        for(int i=y1+1; i<=y2; i++)
        {
            res[x1][i]=0;
            sum+=gap(str2[i]);
        }
        return sum;
    }
    else if(x2-x1==1)
    {
        int one=gap(str1[x1+1])+L_set(x1+1,y1,x2,y2);
        int two=gap(str2[y1+1])+L_set(x1,y1+1,x2,y2);
        int three=mis(str1[x1+1],str2[y1+1])+L_set(x1+1,y1+1,x2,y2);
        if(one<=two&&one<=three)
        {
            res[x1+1][y1]=0;
            return one;
        }
        else if(two<=one&&two<=three)
        {
            res[x1][y1+1]=0;
            return two;
        }
        else
        {
            res[x1+1][y1+1]=0;
            return three;
        }
    }
    else
    {

        for(int i=y1; i<=y2; i++)
        {
            if(minres>L_set(x1,y1,x1+(x2-x1)/2,i)+L_set(x1+(x2-x1)/2,i,x2,y2))
            {
                minres=L_set(x1,y1,x1+(x2-x1)/2,i)+L_set(x1+(x2-x1)/2,i,x2,y2);
                mintar=i;
            }
        }
        res[x1+(x2-x1)/2][mintar]=0;
        return minres;
    }
}
int L(int x1,int y1,int x2,int y2)
{
    int minres=9999999;
    int mintar=0;

    if(x1==x2&&y1==y2)
        return 0;
    else if(x2-x1==1&&y1==y2)
    {
        res[x2][y1]=1;
        return gap(str1[x2]);
    }
    else if(y2-y1==1&&x1==x2)
    {
        res[x1][y2]=1;
        return gap(str2[y2]);
    }
    else if(x1==x2)
    {
        int sum=0;
        for(int i=y1+1; i<=y2; i++)
        {
            res[x1][i]=1;
            sum+=gap(str2[i]);
        }
        return sum;
    }
    else if(x2-x1==1)
    {
        int one=gap(str1[x1+1])+L(x1+1,y1,x2,y2);
        int two=gap(str2[y1+1])+L(x1,y1+1,x2,y2);
        int three=mis(str1[x1+1],str2[y1+1])+L(x1+1,y1+1,x2,y2);
        if(one<=two&&one<=three)
        {
            L_set(x1,y1+1,x2,y2);
            L_set(x1+1,y1+1,x2,y2);
            res[x1+1][y1]=1;
            return one;
        }
        else if(two<=one&&two<=three)
        {
            L_set(x1+1,y1+1,x2,y2);
            L_set(x1+1,y1,x2,y2);
            res[x1][y1+1]=1;
            return two;
        }
        else
        {
            L_set(x1+1,y1,x2,y2);
            L_set(x1,y1+1,x2,y2);
            res[x1+1][y1+1]=1;
            return three;
        }
    }
    else
    {

        for(int i=y1; i<=y2; i++)
        {
            if(minres>L(x1,y1,x1+(x2-x1)/2,i)+L(x1+(x2-x1)/2,i,x2,y2))
            {
                minres=L(x1,y1,x1+(x2-x1)/2,i)+L(x1+(x2-x1)/2,i,x2,y2);
                mintar=i;
            }
        }
        for(int i=y1; i<=y2; i++)
        {
            if(i==mintar)
                continue;
            L_set(x1,y1,x1+(x2-x1)/2,i);
            L_set(x1+(x2-x1)/2,i,x2,y2);
        }
        L(x1,y1,x1+(x2-x1)/2,mintar);
        L(x1+(x2-x1)/2,mintar,x2,y2);
        res[x1+(x2-x1)/2][mintar]=1;
        return minres;
    }
}
void output()
{
    int i=0,j=0,tmp1=0,tmp2=0;
    while(i!=str1.size()-1&&j!=str2.size()-1)
    {
        if(res[i+1][j]==1)
        {
            str2.insert(i+1+tmp1,"-");
            i++;
            tmp2++;


        }
        else if(res[i][j+1]==1)
        {
            str1.insert(j+1+tmp2,"-");
            j++;
            tmp1++;


        }
        else
        {
            i++;
            j++;
        }
    }
    if(str1.size()>str2.size())
    {
        for(int i=str2.size(); i<str1.size(); i++)
            str2=str2+'-';
    }
    if(str1.size()<str2.size())
        for(int i=str1.size(); i<str2.size(); i++)
            str1=str1+'-';
    for(int i=0; i<str1.size(); i++)
        if(str1[i]==str2[i]&&str1[i]=='-')
        {
            str1.erase(i,1);
            str2.erase(i,1);
            i--;
        }

}

int main()
{
    cin>>str1;
    cin>>str2;
    str1='-'+str1;
    str2='-'+str2;

    cout<<L(0,0,str1.size()-1,str2.size()-1)<<endl;

    output();

    cout<<str1<<endl;
    cout<<str2;
    return 0;
}
