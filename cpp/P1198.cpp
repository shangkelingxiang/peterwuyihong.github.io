#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 100010
int ch[maxn][2],siz[maxn],rt,tot,dat[maxn];
int sm[maxn],tg[maxn],a[maxn];
mt19937 rnd(time(NULL));
void pushup(int x){
    siz[x]=siz[ch[x][0]]+1+siz[ch[x][1]];
    sm[x]=sm[ch[x][0]]+a[x]+sm[ch[x][1]];
}
int New(int x){
    a[++tot]=x;
    dat[tot]=rnd();
    siz[tot]=1;
    sm[tot]=x;
    return tot;
}
void add(int x,int d){
    tg[x]+=d;
    sm[x]+=siz[x]*d;
    a[x]+=d;
}
void pushdown(int x){
    add(ch[x][0],tg[x]);
    add(ch[x][1],tg[x]);
    tg[x]=0;
}
void Split(int rt,int k,int&x,int &y){
    if(!rt)x=y=0;
    else{
        pushdown(rt);
        if(siz[ch[rt][0]]+1<=k)x=rt,Split(ch[x][1],k-1-siz[ch[x][0]],ch[x][1],y);
        else y=rt,Split(ch[y][0],k,x,ch[y][0]);
        pushup(rt);
    }
}
int Merge(int x,int y){
    if(!x||!y)return x^y;
    pushdown(x),pushdown(y);
    if(dat[x]<dat[y]){
        ch[x][1]=Merge(ch[x][1],y);
        pushup(x);return x;
    }else{
        ch[y][0]=Merge(x,ch[y][0]);
        pushup(y);return y;
    }
}
int x,y,z;
signed main(){
    int n,m;
    cin>>n>>m;
    while(n--){
        cin>>z;
        rt=Merge(rt,New(z));
    }
    while(m--){
        string op;
        int l,r,d;
        cin>>op>>l>>r;
        if(op=="Q"){
            Split(rt,r,x,y);
            Split(x,l-1,x,z);
            cout<<sm[z]<<endl;
            rt=Merge(Merge(x,z),y);
        }else{
            cin>>d;
            Split(rt,r,x,y);
            Split(x,l-1,x,z);
            add(z,d);
            rt=Merge(Merge(x,z),y);
        }
    }
}