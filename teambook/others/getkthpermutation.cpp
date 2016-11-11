vector<int>v;
//finding the number of permutation 0.....n-1
int main()
{
    string s;
    while(getline(cin,s)){
        stringstream ss;
        ss<<s;
        int pos=0,u;
        v.clear();
        while(ss>>u){
            v.push_back(u-1);
        }
        vector<int>le(v.size(),0);
        for(int i=0;i<v.size();i++){
            for(int j=i+1;j<v.size();j++){
                if(v[i]>v[j])le[i]++;
            }
        }
        long long ans=0LL,fact=0LL,por=1LL;
        for(int i=le.size()-1;i>=0;i--){
            if(fact!=0LL)por*=fact;
            fact++;
            ans=ans+por*le[i];
        }
        cout<<ans+1<<"\n";
    }
    return 0;
}
