/*
Jakubko rozbieha podnikanie s ovocím. Kúpil si preto ovocný sad, v ktorom sú ovocné stromy. Do sadu ale chodia rôzni neželaní návštevníci a potrebuje ho oplotiť, aby ochránil úrodu. Plot chce postavit okolo sadu tak, aby všetky stromy boli vo vnútri. Rozmýšľa teraz, koľko najmenej plotu bude potrebovať, aby oplotil všetky stromy. Ovocný sad je možné reprezentovať v rovine, stromy sú body (šírku stromov zanedbajte).

Pomôžte Jakubkovi určiť najmenšiu dĺžku plotu, ktorý potrebuje, aby mohol ovocný sad oplotiť po obvode.

Vstup: Štandardný vstup obsahuje zápis súradníc stromov v ovocnom sade. Na prvom riadku je celé číslo N (do 1000) počet stromov, a nasleduje N dvojíc celých čísel: x-ová a y-ová súradnica i-teho stromu.

Výstup: Na štandardný výstup vypíšte najmenšiu dĺžku plotu, ktorá je potrebná pre oplotenie ovocného sadu na vstupe, zaokrúhlenú na tri desatinné miesta.

Ukážka vstupu:
4
2 0
0 2
1 1
0 0
Výstup pre ukážkový vstup:
6.828
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
 #define pi 3.14159
 typedef struct v1
{
      int x, y;
}vertex;
vertex p0;
int process_vertices(  int n, vertex *v)
{
  int i;
  for(i=0;i<n;i++) scanf(" %d %d",&v[i].x,&v[i].y);
  return n;
}
void swap(vertex *v1, vertex *v2)
{
    vertex temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}
int orientation(vertex p, vertex q, vertex r)
{
 int val = (int)(q.y - p.y) * (r.x - q.x) - ( int)(q.x - p.x) * (r.y - q.y);
if (val == 0) return 0;
return (val > 0)? 1: 2;
}
 int distSq(vertex p1, vertex p2)
{
    return (int)(p1.x - p2.x)*(p1.x - p2.x) + ( int)(p1.y - p2.y)*(p1.y     - p2.y);
}
 int compare(const void *vp1, const void *vp2)
 {
   vertex *p1 = (vertex *)vp1;
    vertex *p2 = (vertex *)vp2;


    int o = orientation(p0, *p1, *p2);
    if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
 }
vertex * Convex_Hull(vertex *v,  int *count)
{
 int n = *count, ymin = v[0].y, min = 0, i,m;vertex *stack;
for(i = 1; i < n; i++)
{
    if((v[i].y < ymin) || ((v[i].y == ymin) && (v[i].x < v[min].x)))
    {
        ymin = v[i].y;
        min = i;
    }
}
swap(&v[0], &v[min]);
p0 = v[0];
if(n > 1)
    qsort(&v[1], n - 1, sizeof(vertex), compare);
     m = 1;
for(i = 1; i < n; i++)
{
    while((i < n - 1) && orientation(v[0], v[i], v[i + 1]) == 0)
        i++;
    v[m++] = v[i];
}
*count = n = m;
if(n < 3)
    return v;
  stack = (vertex *)malloc(n * sizeof(vertex));
stack[0] = v[0];
stack[1] = v[1];
stack[2] = v[2];
m = 2;
for(i = 3; i < n; i++)
{
    while(orientation(stack[m-1], stack[m], v[i]) != 2)
        m--;
    stack[++m] = v[i];
}
*count = n = ++m;
free(v);
return stack;
}


int main() {
 int t, n, i,count;

 vertex *v;


    scanf("%d", &n);


    v = (vertex *)malloc( n * sizeof(vertex));
    count = process_vertices(n, v);

    v = Convex_Hull(v, &count);
    //for(i=0;i<count;i++) printf("%d %d\n",v[i].x,v[i].y);
    //printf ("\n");

  double vzdialenost = 0;

  for (i=0;i<count-1;i++) {
    vzdialenost += sqrt ( 
      ( (v[i].x - v[i+1].x) * (v[i].x - v[i+1].x) ) + 
      ( (v[i].y - v[i+1].y) * (v[i].y - v[i+1].y) ) ) ;
    //printf("%d %d\n",v[i].x,v[i].y);
    //printf("%d %d\n",v[i+1].x,v[i+1].y);
  }
  vzdialenost += sqrt ( 
      ( (v[i].x - v[0].x) * (v[i].x - v[0].x) ) + 
      ( (v[i].y - v[0].y) * (v[i].y - v[0].y) ) ) ;
    //printf("%d %d\n",v[i].x,v[i].y);
    //printf("%d %d\n",v[0].x,v[0].y);
  
  printf("%.3lf\n",vzdialenost);

return 0;
}