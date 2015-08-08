#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef struct { int x,y,ind,op; } tip;
  
typedef struct avl {
        int nr, h, hdif, v;
        long long sum, vsum;
        avl *l, *r;
        avl() { l=0; r=0; sum=nr=h=hdif=vsum=0; }
        };
avl *root;
tip a[200005];
int n,m,i,j;
long long sol[100005];
long long inf=2000000000,sum,nr;
  
bool cmp1(tip a, tip b) {
    if (a.x+a.y!=b.x+b.y) return a.x+a.y<b.x+b.y;    
    else return a.op<b.op;
}
  
bool cmp2(tip a, tip b) {
    if (a.x+a.y!=b.x+b.y) return a.x+a.y<b.x+b.y;    
    else return a.op>b.op;
}
  
avl *update(avl *nod) {
    
  
  if (nod->l!=0&&nod->r!=0) {
                            nod->h=max(nod->l->h,nod->r->h)+1;
                            nod->hdif=nod->r->h-nod->l->h;
                            nod->vsum=nod->sum+nod->l->vsum+nod->r->vsum;
                            nod->nr=1+nod->l->nr+nod->r->nr;
                            }
  else if (nod->l==0&&nod->r!=0) {
       nod->h=nod->r->h+1;
       nod->hdif=nod->r->h;
       nod->vsum=nod->sum+nod->r->vsum;
       nod->nr=1+nod->r->nr;
       }
  else if (nod->r==0&&nod->l!=0) {
       nod->h=nod->l->h+1;
       nod->hdif=-nod->l->h;
       nod->vsum=nod->sum+nod->l->vsum;
       nod->nr=1+nod->l->nr;
       }
  else {
       nod->h=1;
       nod->hdif=0;
       nod->vsum=nod->sum;
       nod->nr=1;
       }
         
  return nod;
      
}
  
avl *rotleft(avl *nod) {
    
  avl *aux=nod->r;
  nod->r=aux->l;
  aux->l=nod;
    
  nod=update(nod);
  aux=update(aux);
    
  return aux;   
      
}
  
avl *rotright(avl *nod) {
    
  avl *aux=nod->l;
  nod->l=aux->r;
  aux->r=nod;
    
  nod=update(nod);
  aux=update(aux);
    
  return aux;   
      
}
  
avl *balance(avl *nod) {
   nod=update(nod);
     
   if (nod->hdif==-2&&nod->l->hdif<=0) nod=rotright(nod);
   else if (nod->hdif==-2) { nod->l=rotleft(nod->l); nod=rotright(nod); }
   else if (nod->hdif==2&&nod->r->hdif>=0) nod=rotleft(nod);
   else if (nod->hdif==2) { nod->r=rotright(nod->r); nod=rotleft(nod); }
     
   return nod;   
      
}
  
avl *insert(avl *nod,long long val,long long sum) {
    if (nod==0) {//inserez nodul nou 
                nod=new avl;
                nod->v=val;
                nod->vsum=sum;
                nod->sum=sum;
                nod->nr=1;
                return nod;
                }
                  
    if (val<nod->v) nod->l=insert(nod->l,val,sum);
    else nod->r=insert(nod->r,val,sum);
      
    return balance(nod);
}
  
void query(avl *nod, long long v) {
    if (nod==0) return;
      
    if (v>nod->v) query(nod->r,v);
    else { 
         if (nod->r!=0) { 
                        sum+=nod->r->vsum;
                        nr+=nod->r->nr;
                        }
         sum+=nod->sum;
         nr+=1;
         query(nod->l,v);
         } 
           
}
  
void query1(avl *nod, long long v) {
    if (nod==0) return;
      
    if (v>=nod->v) query1(nod->r,v);
    else { 
         if (nod->r!=0) { 
                        sum+=nod->r->vsum;
                        nr+=nod->r->nr;
                        }
         sum+=nod->sum;
         nr+=1;
         query1(nod->l,v);
         } 
           
}
  
int main(void) {

    cin>>n>>m;
    for (i=1; i<=n; ++i) { cin>>a[i].x>>a[i].y; a[i].op=1; }
    for (i=1; i<=m; ++i) { cin>>a[i+n].x>>a[i+n].y; a[i+n].ind=i; a[i+n].op=2; }
      
    
    sort(a+1,a+n+m+1,cmp1);
      
    root=0;
    for (i=1; i<=n+m; ++i)
     if (a[i].op==1) {//update
          root=insert(root,a[i].y-a[i].x,inf-a[i].x);
     }
     else {//query
     sum=0;
     nr=0;
     query(root,a[i].y-a[i].x);
     sol[a[i].ind]+=sum-nr*(inf-a[i].x);
     }
       
    
     root=0;
     for (i=n+m; i>=1; --i) 
     if (a[i].op==1) {//update
          root=insert(root,a[i].x-a[i].y,inf+a[i].x);
     }
     else {//query
     sum=0;
     nr=0;
     query(root,a[i].x-a[i].y);
     sol[a[i].ind]+=sum-nr*(inf+a[i].x);
     }
       
     
     for (i=1; i<=n+m; ++i) swap(a[i].x,a[i].y);
       
    sort(a+1,a+n+m+1,cmp2);
      
    root=0;
    for (i=1; i<=n+m; ++i)
     if (a[i].op==1) {//update
          root=insert(root,a[i].y-a[i].x,inf-a[i].x);
     }
     else {//query
     sum=0;
     nr=0;
     query1(root,a[i].y-a[i].x);
     sol[a[i].ind]+=sum-nr*(inf-a[i].x);
     }
       
     
     root=0;
     for (i=n+m; i>=1; --i) 
     if (a[i].op==1) {//update
          root=insert(root,a[i].x-a[i].y,inf+a[i].x);
     }
     else {//query
     sum=0;
     nr=0;
     query1(root,a[i].x-a[i].y);
     sol[a[i].ind]+=sum-nr*(inf+a[i].x);
     }
     
     for (i=1; i<=m; ++i) cout<<sol[i]<<"\n";
      
    return 0;
}
