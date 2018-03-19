#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct Point{
	long long x, y;
	int order;
};

struct Pair{
	int order1;
	int order2;
};

vector<Pair> closestPair;
long long global_min = 9223372036854775807;

int compx(const void* a, const void *b){
	if(((Point*)a)->x == ((Point*)b)->x){
		return ((Point*)a)->y - ((Point*)b)->y;
	}
	else{
		return ((Point*)a)->x - ((Point*)b)->x;
	}
}

int compy(const void* a, const void *b){
	return ((Point*)a)->y - ((Point*)b)->y;
}

bool comp_order(const Pair &a, const Pair &b){
	if(a.order1 == b.order1){
		return a.order2 < b.order2;
	}
	return a.order1 < b.order1;
}

bool uniq_order(Pair &a, Pair &b){
	return (a.order1 == b.order1 && a.order2 == b.order2);
}

long long dist(Point *a, Point *b){
	//return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
	return (a->x-b->x)*(a->x-b->x)+(a->y-b->y)*(a->y-b->y);
}

long long Bruteforce(Point Points[], int N){
	long long min = 9223372036854775807;
	for(int i = 0; i < N; i++){
		for(int j = i+1; j < N; j++){
			long long dist_tmp = dist(&Points[i], &Points[j]);
			if(dist_tmp < min){
				min = dist_tmp;	
			}
			if(dist_tmp < global_min){
				global_min = min;
				closestPair.clear();
				Pair tmp;
				tmp.order1 = Points[i].order;
				tmp.order2 = Points[j].order;
				closestPair.push_back(tmp);
			}
			else if(dist_tmp == global_min){
				Pair tmp;
				tmp.order1 = Points[i].order;
				tmp.order2 = Points[j].order;
				closestPair.push_back(tmp);
			}
		}
	}
	return min;
}

long long min(long long &x, long long &y){
	return (x < y)? x : y;
}

long long stripClosest(Point strip[], int size, long long d){
	long long min = d;
	for(int i = 0; i < size; i++){
		for(int j = i+1; j < size && (strip[j].y - strip[i].y) <= min; j++){
			long long dist_tmp = dist(&strip[i], &strip[j]);
			if(dist_tmp < min){
				min = dist_tmp;
			}
			
			if(dist_tmp < global_min){
				global_min = dist_tmp;
				closestPair.clear();
				Pair tmp;
				tmp.order1 = strip[i].order;
				tmp.order2 = strip[j].order;
				closestPair.push_back(tmp);
			}
			else if(dist_tmp == global_min){
				Pair tmp;
				tmp.order1 = strip[i].order;
				tmp.order2 = strip[j].order;
				closestPair.push_back(tmp);
			}
		}
	}

	return min;
}

long long closestUntil(Point Px[], Point Py[], int N){
	if(N <= 8){
		long long tmp = Bruteforce(Py, N);
		//printf("tmp = %f\n", tmp);
		return tmp;
	}

	int mid = 0;
	if(N%2 == 0){
		mid = N/2-1;
	}
	else{
		mid = N/2;
	}

	Point midPoint = Px[mid];

	//divide
	//Point Pyl[N];
	//Point Pyr[N];

	int lsize = 0, rsize = 0;
	for(int i = 0; i < N; i++){
		if(Py[i].x < midPoint.x){
			//Pyl[li++] = Py[i];
			lsize++;
		}
		else if(Py[i].x == midPoint.x){
			if(Py[i].y <= midPoint.y){
				lsize++;
			}
			else{
				rsize++;
			}
			//Pyr[ri++] = Py[i];
		}
		else{
			rsize++;
		}
	}

	Point *Pyl = new Point[lsize];
	Point *Pyr = new Point[rsize];
	//Point Pyl[lsize];
	//Point Pyr[rsize];

	int lidx = 0, ridx = 0;
	for(int i = 0; i < N; i++){
		if(Py[i].x < midPoint.x){
			Pyl[lidx++] = Py[i];
		}
		else if(Py[i].x == midPoint.x){
			if(Py[i].y <= midPoint.y){
				Pyl[lidx++] = Py[i];
			}
			else{
				Pyr[ridx++] = Py[i];
			}
			//Pyr[ri++] = Py[i];
		}
		else{
			Pyr[ridx++] = Py[i];
		}
	}
	//printf("mid = %d\n", mid);
	//printf("lsize = %d\n", lsize);
	//printf("rsize = %d\n", rsize);

	long long dl = closestUntil(Px, Pyl, lsize);
	long long dr = closestUntil(Px + mid + 1, Pyr, rsize);
	//printf("dl = %lld, dr = %lld\n", dl, dr);
	long long d = min(dl, dr);
	//printf("d = %lld\n", d);
	Point *strip = new Point[N];
	//Point strip[N];
	int j = 0;
	for(int i = 0; i < N; i++){
		if(abs(Py[i].x - midPoint.x) <= d){
			strip[j++] = Py[i];
		}
	}

	long long minima = stripClosest(strip, j, d);
	delete [] Pyl;
	delete [] Pyr;
	delete [] strip;
	return minima;
}

long long closest(Point Points[], int N){
	Point *Px = new Point[N];
	Point *Py = new Point[N];
	//Point Px[N];
	//Point Py[N];
	for(int i = 0; i < N; i++){
		Px[i] = Points[i];
		Py[i] = Points[i];
	}
	qsort(Px, N, sizeof(Point), compx);
	qsort(Py, N, sizeof(Point), compy);
	//printf("divide and conquer\n");
	long long minima = 0;
	minima = closestUntil(Px, Py, N);
	delete [] Px;
	delete [] Py;
	return minima;
	//return;
}
/*
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
*/
int main(void){
	int N;
	//long long x, y;
	//ReadInt(&N);
	scanf("%d", &N);
	Point *Points = new Point[N];
	for(int i = 0; i < N; i++){
		//ReadInt(&x), ReadInt(&y);
		scanf("%lld%lld", &Points[i].x, &Points[i].y);
		//Points[i].x = x, Points[i].y = y;
		Points[i].order = i+1;
		//printf("%d%d\n", Points[i].x, Points[i].y);
	}
	//printf("the smallest distance is %f\n" , closest(Points, N));
	long long minima = closest(Points, N);
	//closest(Points, N);
	for(vector<Pair>::iterator iter = closestPair.begin(); iter != closestPair.end(); iter++){
		if(iter->order1 > iter->order2){
			long long tmp = iter->order1;
			iter->order1 = iter->order2;
			iter->order2 = tmp;
		}
		//printf("order1 = %d, order2 = %d\n", iter->order1, iter->order2);
	}
	//printf("global_min = %f\n", global_min);
	
	sort(closestPair.begin(), closestPair.end(), comp_order);
	vector<Pair>::iterator last;
	last = unique (closestPair.begin(), closestPair.end(), uniq_order);
	closestPair.erase(last, closestPair.end());
	//printf("closestPair's size is %lu\n", closestPair.size());
	//printf("%.2f %lu\n", global_min, closestPair.size());
	printf("%lld %lu\n", global_min, closestPair.size());
	//printf("closestPair:\n");
	for(vector<Pair>::iterator iter = closestPair.begin(); iter != closestPair.end(); iter++){
		printf("%d %d\n", iter->order1, iter->order2);
	}
	delete [] Points;
	return 0;
}