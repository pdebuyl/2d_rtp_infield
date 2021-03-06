#include <iostream>
#include <cmath>
#include <random>
#include <stdio.h>
using namespace std;

#define PRINTER(name) std::cout << "#" << #name << " = " << name << std::endl;

int movetest(double dt, double k[], double rand){
	if (rand < k[0]*dt){
		return 0;
	} else if (rand < (k[0]+k[1])*dt){
		return 1;
	} else if (rand < (k[0]+k[1]+k[2])*dt ){
		return 2;
	} else if (rand < (k[0]+k[1]+k[2]+k[3])*dt ){
		return 3;
	} else {
		return 5;
	}
}

int fliptest(double mu,int sigma, double rand,int rand2){
	if (rand < 1-mu){
		return sigma;
	} else {
		return sigma = (sigma + rand2) % 4;
	}
}

int testerror (double dt, double p[],double m[],double u[],double d[]){
	if ( (p[1]+p[2]+p[3]+p[0])*dt > 1 | (m[1]+m[2]+m[3]+m[0])*dt > 1 | (u[1]+u[2]+u[3]+u[0])*dt > 1 | (d[1]+d[2]+d[3]+d[0])*dt > 1){
		cerr << "Error: rates to high for dt" << endl;
		exit(1);
	}
	return 1;
}

int main(int argc, char *argv[]){
    const double pi2 = 6.28318530718;
	const double tmax = stod(argv[4]);
	const double lx = 1;
	const double ly = 1;
	const double dx = 0.1;
	const double dy = 0.1;
	/* const int nx = int(lx/dx); */
	/* const int ny = int(ly/dx); */
	const int nx = 4;
	const int ny = 2;
	const int nx1 = 1;
	const int nx2 = 2;
	const int nxh = 2;
	const int nyh = 1;
    const int N = 500; 
	double rand = 0;
	int rand2 = 0;

    /* init */
    int x = 0;
    int y = 0;

    /* sim */
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<double> dist(0,1);
	std::uniform_int_distribution<int> distsigma(0,3);
	std::uniform_int_distribution<int> distx(0,nx);
	std::uniform_int_distribution<int> disty(0,ny);

	double c = stod(argv[1]);
	double a = stod(argv[2]);
	double dt = stod(argv[3]);
	int sigma = distsigma(rng);

	PRINTER(dt);
	PRINTER(a);
	PRINTER(c);
	PRINTER(N);
	PRINTER(tmax);

	for (double e = -0.5; e <= 0.5; e+=0.1){

		double bp = 0.5*(c+e);
		double bm = 0.5*(-c+e);
		double bu = 0.5*(c);
		double bd = 0.5*(-c);
		double be = 0.5*(e);
		
		double p[4] = {(bp+sqrt(bp*bp+1))/dx,1/((bp+sqrt(bp*bp+1))*dx),1/((bu+sqrt(bu*bu+1))*dx),1/((bu+sqrt(bu*bu+1))*dx)};
		double m[4] = {(bm+sqrt(bm*bm+1))/dx,1/((bm+sqrt(bm*bm+1))*dx),1/((bu+sqrt(bu*bu+1))*dx),1/((bu+sqrt(bu*bu+1))*dx)};
		double u[4] = {(be+sqrt(be*be+1))/dx,1/((be+sqrt(be*be+1))*dx),(bu+sqrt(bu*bu+1))/dx,1/((bu+sqrt(bu*bu+1))*dx)};
		double d[4] = {(be+sqrt(be*be+1))/dx,1/((be+sqrt(be*be+1))*dx),(bd+sqrt(bd*bd+1))/dx,1/((bd+sqrt(bd*bd+1))*dx)};
		int move = 0;	
		testerror(dt,p,m,u,d);
		int count = 0;
		for (int i=1; i <= N; i++){
			x = distx(rng);
			y = disty(rng);
			for (double t = 0; t < 100; t += dt){
				rand = dist(rng);
				rand2 = distsigma(rng);
				sigma = fliptest(a*dt,sigma,rand,rand2);
				if (sigma == 0){
					rand = dist(rng);
					move = movetest(dt,p,rand);
					if (move == 0){
						x++;
						if (x == (nx+1)){
							x=1;
						} else if (x == (nxh+1) && y <= nyh){
							x--;
						}
					} else if (move == 1){
						x--;
						if (x == -1){
							x = nx -1;
						} else if (x == nxh && y <= nyh){
							x++;
						}
					} else if (move == 2){
						y++;
						if (x <= nxh && y == (nyh+1)){
							y--;
						} else if (y == (ny+1)){
							y = ny;
						} else if (x <= nxh && y == (nyh+1)){
							y--;
						}
					} else if (move == 3){
						y--;
						if (y == -1){
							y = 0;
						} else if (x <= nxh && y == nyh){
							y++;
						}
					}
				} else if (sigma == 1){
					rand = dist(rng);
					move = movetest(dt,m,rand);
					if (move == 0){
						x++;
						if (x == (nx+1)){
							x=1;
						} else if (x == (nxh+1) && y <= nyh){
							x--;
						}
					} else if (move == 1){
						x--;
						if (x == -1){
							x = nx -1;
						} else if (x == nxh && y <= nyh){
							x++;
						}
					} else if (move == 2){
						y++;
						if (y == (ny+1)){
							y = ny;
						} else if (x <= nxh && y == (nyh+1)){
							y--;
						}
					} else if (move == 3){
						y--;
						if (y == -1){
							y = 0;
						} else if (x <= nxh && y == nyh){
							y++;
						}
					}
				} else if (sigma == 2){
					rand = dist(rng);
					move = movetest(dt,u,rand);
					if (move == 0){
						x++;
						if (x == (nx+1)){
							x=1;
						} else if (x == (nxh+1) && y <= nyh){
							x--;
						}
					} else if (move == 1){
						x--;
						if (x == -1){
							x = nx -1;
						} else if (x == nxh && y <= nyh){
							x++;
						}
					} else if (move == 2){
						y++;
						if (y == (ny+1)){
							y = ny;
						} else if (x <= nxh && y == (nyh+1)){
							y--;
						}
					} else if (move == 3){
						y--;
						if (y == -1){
							y = 0;
						} else if (x <= nxh && y == nyh){
							y++;
						}
					}
				} else {
					rand = dist(rng);
					move = movetest(dt,d,rand);
					if (move == 0){
						x++;
						if (x == (nx+1)){
							x=1;
						} else if (x == (nxh+1) && y <= nyh){
							x--;
						}
					} else if (move == 1){
						x--;
						if (x == -1){
							x = nx -1;
						} else if (x == nxh && y <= nyh){
							x++;
						}
					} else if (move == 2){
						y++;
						if (y == (ny+1)){
							y = ny;
						} else if (x <= nxh && y == (nyh+1)){
							y--;
						}
					} else if (move == 3){
						y--;
						if (y == -1){
							y = 0;
						} else if (x <= nxh && y == nyh){
							y++;
						}
					}
				}
				/* cout << x << ";" << y << endl; */
			}
			for (double t = 0; t < tmax; t += dt){
				rand = dist(rng);
				rand2 = distsigma(rng);
				sigma = fliptest(a*dt,sigma,rand,rand2);
				if (sigma == 0){
					rand = dist(rng);
					move = movetest(dt,p,rand);
					if (move == 0){
						x++;
						if (x == (nx+1) && y <= nyh){
							x--;
						}else if (x == (nx+1)){
							count++;
							x=2;
						}
					} else if (move == 1){
						x--;
						if (x == 0 && y <= nyh){
							x++;
						}else if (x == 0){
							x = nx -1;
							count--;
						}
					} else if (move == 2){
						y++;
						if (x >= nx2 && y == (nyh+1)){
							y--;
						} else if (y == (ny+1)){
							y = ny;
						}
					} else if (move == 3){
						y--;
						if (x >= nx && y == nyh){
							y++;
						}else if (y == -1){
							y = 0;
						}
					}
				} else if (sigma == 1){
					rand = dist(rng);
					move = movetest(dt,m,rand);
					if (move == 0){
						x++;
						if (x == (nx+1) && y <= nyh){
							x--;
						}else if (x == (nx+1)){
							count++;
							x=2;
						}
					} else if (move == 1){
						x--;
						if (x == 0 && y <= nyh){
							x++;
						}else if (x == 0){
							x = nx -1;
							count--;
						}
					} else if (move == 2){
						y++;
						if (x >= nx2 && y == (nyh+1)){
							y--;
						} else if (y == (ny+1)){
							y = ny;
						}
					} else if (move == 3){
						y--;
						if (x >= nx && y == nyh){
							y++;
						}else if (y == -1){
							y = 0;
						}
					}
				} else if (sigma == 2){
					rand = dist(rng);
					move = movetest(dt,u,rand);
					if (move == 0){
						x++;
						if (x == (nx+1) && y <= nyh){
							x--;
						}else if (x == (nx+1)){
							count++;
							x=2;
						}
					} else if (move == 1){
						x--;
						if (x == 0 && y <= nyh){
							x++;
						}else if (x == 0){
							x = nx -1;
							count--;
						}
					} else if (move == 2){
						y++;
						if (x >= nx2 && y == (nyh+1)){
							y--;
						} else if (y == (ny+1)){
							y = ny;
						}
					} else if (move == 3){
						y--;
						if (x >= nx && y == nyh){
							y++;
						}else if (y == -1){
							y = 0;
						}
					}
				} else {
					rand = dist(rng);
					move = movetest(dt,d,rand);
					if (move == 0){
						x++;
						if (x == (nx+1) && y <= nyh){
							x--;
						}else if (x == (nx+1)){
							count++;
							x=2;
						}
					} else if (move == 1){
						x--;
						if (x == 0 && y <= nyh){
							x++;
						}else if (x == 0){
							x = nx -1;
							count--;
						}
					} else if (move == 2){
						y++;
						if (x >= nx2 && y == (nyh+1)){
							y--;
						} else if (y == (ny+1)){
							y = ny;
						}
					} else if (move == 3){
						y--;
						if (x >= nx && y == nyh){
							y++;
						}else if (y == -1){
							y = 0;
						}
					}
				}
				/* cout << move << ";" << sigma << endl; */
				/* cout << x << ";" << y << ";" << count << endl; */
			}
		}
		cout << e << ";" << count/(tmax*N) << endl;
	}
	return 0;
}
