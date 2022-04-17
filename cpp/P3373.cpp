#include<bits/stdc++.h>
using namespace std;
namespace Fread{
const int SIZE= 1 << 16;
	char buf[SIZE],*S,*T;
	inline char getchar(){if(S==T){T=(S=buf)+
	fread(buf,1,SIZE,stdin);if(S==T)return'\n';}return *S++;}
} // namespace Fread
namespace Fwrite {
const int SIZE= 1 << 16;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct NTR{~NTR(){flush();}}ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread::getchar
	#define putchar Fwrite::putchar
#endif
inline void rd(int&x){x=0;
    char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=10*x+ch-'0',ch=getchar();
}
inline void wr(int x){
    static int a[45];
    int top=0;
    while(x)a[++top]=x%10,x/=10;
    while(top)putchar(a[top--]+'0');
    putchar('\n');
}
int n,p,m;
inline void add(int &x,int y){
    x+=y;
    if(x>=p)x-=p;
}
inline int Add(int x,int y){
    add(x,y);return x;
}
inline void mul(int&x,int y){
    x=1ll*x*y%p;
}
inline int Mul(int x,int y){
    mul(x,y);return x;
}
#define maxn 100010
int ch[maxn][2],ad[maxn],ml[maxn],dat[maxn],tot;
mt19937 rnd(time(NULL));
int a[maxn],siz[maxn],sm[maxn];
inline int New(int x){
    a[++tot]=x;
    sm[tot]=x;
    ml[tot]=1;
    dat[tot]=rnd();
    siz[tot]=1;
    return tot;
}
inline void pushup(int x){
    siz[x]=siz[ch[x][0]]+1+siz[ch[x][1]];
    sm[x]=Add(sm[ch[x][0]],Add(a[x],sm[ch[x][1]]));
}
inline void cad(int x,int d){
    add(ad[x],d);
    add(a[x],d);
    add(sm[x],Mul(d,siz[x]));
}
inline void cml(int x,int d){
    mul(ml[x],d);
    mul(a[x],d);
    mul(ad[x],d);
    mul(sm[x],d);
}
inline void pushdown(int x){
    if(ml[x]==1&&ad[x]==0)return;
    if(ch[x][0]){
        cml(ch[x][0],ml[x]);
        cad(ch[x][0],ad[x]);
    }
    if(ch[x][1]){
        cml(ch[x][1],ml[x]);
        cad(ch[x][1],ad[x]);
    }
    ml[x]=1,ad[x]=0;
}
inline void Split(int rt,int k,int &x,int &y){
    if(!rt)x=y=0;
    else{
        pushdown(rt);
        if(1+siz[ch[rt][0]]<=k)x=rt,Split(ch[x][1],k-1-siz[ch[x][0]],ch[x][1],y);
        else y=rt,Split(ch[y][0],k,x,ch[y][0]);
        pushup(rt);
    }
}
inline int Merge(int x,int y){
    if(!x||!y)return x+y;
    pushdown(x),pushdown(y);
    if(dat[x]<dat[y]){
        ch[x][1]=Merge(ch[x][1],y);
        pushup(x);return x;
    }else{
        ch[y][0]=Merge(x,ch[y][0]);
        pushup(y);return y;
    }
}
signed main(){
    rd(n),rd(m),rd(p);
    int x,y,z,rt=0;
    while(n--){
        rd(z);
        rt=Merge(rt,New(z));
    }
    while(m--){
        int op,l,r,c;
        rd(op),rd(l),rd(r);
        if(op==1){
            rd(c);
            Split(rt,r,x,y);
            Split(x,l-1,x,z);
            cml(z,c);
            rt=Merge(Merge(x,z),y);
        }
        if(op==2){
          rd(c);
            Split(rt,r,x,y);
            Split(x,l-1,x,z);
            cad(z,c);
            rt=Merge(Merge(x,z),y);
        }
        if(op==3){
            Split(rt,r,x,y);
            Split(x,l-1,x,z);
            wr(sm[z]);
            rt=Merge(Merge(x,z),y);
        }
    }
}