#include<bits/stdc++.h>
using namespace std;
/*
author:     Eddy Cael Mamani Canaviri
Language:   C++
Date:       11/11/2016
Sample problem: http://codeforces.com/contest/126/problem/B
*/


char s[1000001];
int  z[1000001];
int n;
void build_Z()
   {
   int L,R;
   L=R=0;
   For(int i = 1; i < n ; ++i)
      {
      if(i>R)
         {
         L=R=i;
         while(R<n && s[R-L]==s[R])
            R++;
         z[i]=R-L;
         R--;
         }
      else
         {
         int k=i-L;
         if(z[k]<R-i+1)
            z[i]=z[k];
         else
            {
            L=i;
            while(R<n && s[R-L]==s[R])
               R++;
            z[i]=R-L;
            R--;
            }
         }
      }
   }
   /*
   Given a string S of length n, the Z Algorithm produces 
   an array Z where Z[i] is the length of the longest 
   substring starting from S[i] which is also a prefix 
   of S
   */
int main()
   {
   scanf("%s",s);
   n=strlen(s);
   build_Z();
   int ans=-1,mx=0;
   for(int  i = 1 ; i < n ; ++ i){
      // fixprefixsuffix
      // 012345678901234
      //Z=00000300001300
      if(z[i]==n-i) // is suffix
         if(mx>=n-i){ // >= because is possible a superposition
            ans=n-i;
            break;
            }
      mx = max ( mx , z[i]);
      }
   if(ans > -1){
      for(int  i = 0 ; i < n ; ++ i)
         putchar(s[i]);
      }
   else puts("Just a legend");
   return 0;
   }

