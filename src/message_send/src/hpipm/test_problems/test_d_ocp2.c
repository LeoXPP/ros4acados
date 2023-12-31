/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High-Performance Interior Point Method.                                                *
* Copyright (C) 2019 by Gianluca Frison.                                                          *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* The 2-Clause BSD License                                                                        *
*                                                                                                 *
* Redistribution and use in source and binary forms, with or without                              *
* modification, are permitted provided that the following conditions are met:                     *
*                                                                                                 *
* 1. Redistributions of source code must retain the above copyright notice, this                  *
*    list of conditions and the following disclaimer.                                             *
* 2. Redistributions in binary form must reproduce the above copyright notice,                    *
*    this list of conditions and the following disclaimer in the documentation                    *
*    and/or other materials provided with the distribution.                                       *
*                                                                                                 *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND                 *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED                   *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                          *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR                 *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES                  *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;                    *
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND                     *
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                      *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                   *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                    *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include <blasfeo_target.h>
#include <blasfeo_common.h>
#include <blasfeo_v_aux_ext_dep.h>
#include <blasfeo_d_aux_ext_dep.h>
#include <blasfeo_i_aux_ext_dep.h>
#include <blasfeo_d_aux.h>

#include <hpipm_d_ocp_qp.h>
#include <hpipm_d_ocp_qp_sol.h>
#include <hpipm_d_ocp_qp_ipm.h>

#include "d_tools.h"



#define KEEP_X0 0

// printing
#define PRINT 1



#if ! defined(EXT_DEP)
/* creates a zero matrix */
void d_zeros(double **pA, int row, int col)
	{
	*pA = malloc((row*col)*sizeof(double));
	double *A = *pA;
	int i;
	for(i=0; i<row*col; i++) A[i] = 0.0;
	}
/* frees matrix */
void d_free(double *pA)
	{
	free( pA );
	}
/* prints a matrix in column-major format */
void d_print_mat(int m, int n, double *A, int lda)
	{
	int i, j;
	for(i=0; i<m; i++)
		{
		for(j=0; j<n; j++)
			{
			printf("%9.5f ", A[i+lda*j]);
			}
		printf("\n");
		}
	printf("\n");
	}
/* prints the transposed of a matrix in column-major format */
void d_print_tran_mat(int row, int col, double *A, int lda)
	{
	int i, j;
	for(j=0; j<col; j++)
		{
		for(i=0; i<row; i++)
			{
			printf("%9.5f ", A[i+lda*j]);
			}
		printf("\n");
		}
	printf("\n");
	}
/* prints a matrix in column-major format (exponential notation) */
void d_print_exp_mat(int m, int n, double *A, int lda)
	{
	int i, j;
	for(i=0; i<m; i++)
		{
		for(j=0; j<n; j++)
			{
			printf("%e\t", A[i+lda*j]);
			}
		printf("\n");
		}
	printf("\n");
	}
/* prints the transposed of a matrix in column-major format (exponential notation) */
void d_print_exp_tran_mat(int row, int col, double *A, int lda)
	{
	int i, j;
	for(j=0; j<col; j++)
		{
		for(i=0; i<row; i++)
			{
			printf("%e\t", A[i+lda*j]);
			}
		printf("\n");
		}
	printf("\n");
	}
/* creates a zero matrix aligned */
void int_zeros(int **pA, int row, int col)
	{
	void *temp = malloc((row*col)*sizeof(int));
	*pA = temp;
	int *A = *pA;
	int i;
	for(i=0; i<row*col; i++) A[i] = 0;
	}
/* frees matrix */
void int_free(int *pA)
	{
	free( pA );
	}
/* prints a matrix in column-major format */
void int_print_mat(int row, int col, int *A, int lda)
	{
	int i, j;
	for(i=0; i<row; i++)
		{
		for(j=0; j<col; j++)
			{
			printf("%d ", A[i+lda*j]);
			}
		printf("\n");
		}
	printf("\n");
	}
#endif



/************************************************
Mass-spring system: nx/2 masses connected each other with springs (in a row), and the first and the last one to walls. nu (<=nx) controls act on the first nu masses. The system is sampled with sampling time Ts.
************************************************/
void mass_spring_system(double Ts, int nx, int nu, double *A, double *B, double *b, double *x0)
	{

	int nx2 = nx*nx;

	int info = 0;

	int pp = nx/2; // number of masses

/************************************************
* build the continuous time system
************************************************/

	double *T; d_zeros(&T, pp, pp);
	int ii;
	for(ii=0; ii<pp; ii++) T[ii*(pp+1)] = -2;
	for(ii=0; ii<pp-1; ii++) T[ii*(pp+1)+1] = 1;
	for(ii=1; ii<pp; ii++) T[ii*(pp+1)-1] = 1;

	double *Z; d_zeros(&Z, pp, pp);
	double *I; d_zeros(&I, pp, pp); for(ii=0; ii<pp; ii++) I[ii*(pp+1)]=1.0; // = eye(pp);
	double *Ac; d_zeros(&Ac, nx, nx);
	dmcopy(pp, pp, Z, pp, Ac, nx);
	dmcopy(pp, pp, T, pp, Ac+pp, nx);
	dmcopy(pp, pp, I, pp, Ac+pp*nx, nx);
	dmcopy(pp, pp, Z, pp, Ac+pp*(nx+1), nx);
	free(T);
	free(Z);
	free(I);

	d_zeros(&I, nu, nu); for(ii=0; ii<nu; ii++) I[ii*(nu+1)]=1.0; //I = eye(nu);
	double *Bc; d_zeros(&Bc, nx, nu);
	dmcopy(nu, nu, I, nu, Bc+pp, nx);
	free(I);

/************************************************
* compute the discrete time system
************************************************/

	double *bb; d_zeros(&bb, nx, 1);
	dmcopy(nx, 1, bb, nx, b, nx);

	dmcopy(nx, nx, Ac, nx, A, nx);
	dscal_3l(nx2, Ts, A);
	expm(nx, A);

	d_zeros(&T, nx, nx);
	d_zeros(&I, nx, nx); for(ii=0; ii<nx; ii++) I[ii*(nx+1)]=1.0; //I = eye(nx);
	dmcopy(nx, nx, A, nx, T, nx);
	daxpy_3l(nx2, -1.0, I, T);
	dgemm_nn_3l(nx, nu, nx, T, nx, Bc, nx, B, nx);
	free(T);
	free(I);

	int *ipiv = (int *) malloc(nx*sizeof(int));
	dgesv_3l(nx, nu, Ac, nx, ipiv, B, nx, &info);
	free(ipiv);

	free(Ac);
	free(Bc);
	free(bb);


/************************************************
* initial state
************************************************/

	if(nx==4)
		{
		x0[0] = 5;
		x0[1] = 10;
		x0[2] = 15;
		x0[3] = 20;
		}
	else
		{
		int jj;
		for(jj=0; jj<nx; jj++)
			x0[jj] = 1;
		}

	}



int main()
	{


	// local variables

	int ii, jj;

	int rep, nrep=1000;

	struct timeval tv0, tv1;



	// problem size

	int nx_ = 8; // number of states (it has to be even for the mass-spring system test problem)
	int nu_ = 3; // number of inputs (controllers) (it has to be at least 1 and at most nx/2 for the mass-spring system test problem)
	int N  = 5; // horizon lenght



	// stage-wise variant size

	int nx[N+1];
#if KEEP_X0
	nx[0] = nx_;
#else
	nx[0] = 0;
#endif
	for(ii=1; ii<=N; ii++)
		nx[ii] = nx_;
//	nx[N] = 0;

	int nu[N+1];
	for(ii=0; ii<N; ii++)
		nu[ii] = nu_+2*nx[ii]/2;
//	nu[N] = 0;
	nu[N] = 2*nx[N]/2; // soft constraints

#if 1
	int nb[N+1];
#if KEEP_X0
	nb[0] = nu[0]+nx[0]/2;
#else
	nb[0] = nu[0];
#endif
	for(ii=1; ii<N; ii++)
		nb[ii] = nu[1];//+nx[1]/2;
	nb[N] = nu[N];//+nx[N]/2;

	int ng[N+1];
	ng[0] = 0;
	for(ii=1; ii<N; ii++)
		ng[ii] = 2*nx[ii]/2;
	ng[N] = 2*nx[N]/2;

	int ns[N+1];
	ns[0] = 0;
	for(ii=1; ii<N; ii++)
		ns[ii] = 0;
	ns[N] = 0;//nx[N]/2;
#elif 0
	int nb[N+1];
	nb[0] = 0;
	for(ii=1; ii<N; ii++)
		nb[ii] = 0;
	nb[N] = 0;

	int ng[N+1];
#if KEEP_X0
	ng[0] = nu[0]+nx[0]/2;
#else
	ng[0] = nu[0];
#endif
	for(ii=1; ii<N; ii++)
		ng[ii] = nu[1]+nx[1]/2;
	ng[N] = nx[N]/2;
#else
	int nb[N+1];
	nb[0] = nu[0] + nx[0]/2;
	for(ii=1; ii<N; ii++)
		nb[ii] = nu[ii] + nx[ii]/2;
	nb[N] = nu[N] + nx[N]/2;

	int ng[N+1];
#if KEEP_X0
	ng[0] = nx[0]/2;
#else
	ng[0] = 0;
#endif
	for(ii=1; ii<N; ii++)
		ng[ii] = nx[1]/2;
	ng[N] = nx[N]/2;
#endif

/************************************************
* dynamical system
************************************************/

	double *A; d_zeros(&A, nx_, nx_); // states update matrix

	double *B; d_zeros(&B, nx_, nu_); // inputs matrix

	double *b; d_zeros(&b, nx_, 1); // states offset
	double *x0; d_zeros(&x0, nx_, 1); // initial state

	double Ts = 0.5; // sampling time
	mass_spring_system(Ts, nx_, nu_, A, B, b, x0);

	for(jj=0; jj<nx_; jj++)
		b[jj] = 0.0;

	for(jj=0; jj<nx_; jj++)
		x0[jj] = 0;
	x0[0] = 2.5;
	x0[1] = 2.5;

	double *b0; d_zeros(&b0, nx_, 1);
	dgemv_n_3l(nx_, nx_, A, nx_, x0, b0);
	daxpy_3l(nx_, 1.0, b, b0);

	double *B1; d_zeros(&B1, nx[2], nu[1]);
	for(jj=0; jj<nu_; jj++)
		for(ii=0; ii<nx_; ii++)
			B1[ii+nx_*jj] = B[ii+nx_*jj];

#if PRINT
	d_print_mat(nx_, nx_, A, nx_);
	d_print_mat(nx_, nu_, B, nx_);
	d_print_mat(nx[2], nu[1], B1, nx[2]);
	d_print_mat(1, nx_, b, 1);
	d_print_mat(1, nx_, x0, 1);
	d_print_mat(1, nx_, b0, 1);
#endif

/************************************************
* cost function
************************************************/

	double *Q; d_zeros(&Q, nx_, nx_);
	for(ii=0; ii<nx_; ii++) Q[ii*(nx_+1)] = 0.0;

	double *R0; d_zeros(&R0, nu[0], nu[0]);
	for(ii=0; ii<nu_; ii++) R0[ii*(nu[0]+1)] = 2.0;

	double *R1; d_zeros(&R1, nu[1], nu[1]);
	for(ii=0; ii<nu_; ii++) R1[ii*(nu[1]+1)] = 2.0;
	for(; ii<nu[1]; ii++) R1[ii*(nu[1]+1)] = 1000.0;

	double *RN; d_zeros(&RN, nu[N], nu[N]);
	for(ii=0; ii<nu[N]; ii++) RN[ii*(nu[N]+1)] = 1000.0;

	double *S0; d_zeros(&S0, nu[0], nx[0]);

	double *S1; d_zeros(&S1, nu[1], nx[1]);

	double *SN; d_zeros(&SN, nu[N], nx[N]);

	double *q; d_zeros(&q, nx_, 1);
	for(ii=0; ii<nx_; ii++) q[ii] = 0.0;

	double *r1; d_zeros(&r1, nu[1], 1);
	for(ii=0; ii<nu_; ii++) r1[ii] = 0.0;
	for(; ii<nu[1]; ii++) r1[ii] = 100.0;

	double *rN; d_zeros(&rN, nu[N], 1);
	for(ii=0; ii<nu[N]; ii++) rN[ii] = 100.0;

	double *r0; d_zeros(&r0, nu[0], 1);
//	dgemv_n_3l(nu[0], nx[0], S0, nu[0], x0, r0);
//	daxpy_3l(nu[0], 1.0, r1, r0);

#if 0
	double *QN; d_zeros(&QN, nx_, nx_);
	for(ii=0; ii<2; ii++) QN[ii*(nx_+1)] = 1e15;
	for(ii=0; ii<nx_; ii++) QN[ii*(nx_+1)] += Q[ii*(nx_+1)];
	double *qN; d_zeros(&qN, nx_, 1);
	qN[0] = - 0.1;
	qN[1] = - 0.1;
	for(ii=0; ii<2; ii++) qN[ii] *= 1e15;
	for(ii=0; ii<nx_; ii++) qN[ii] += q[ii];
#endif

#if PRINT
	d_print_mat(nx_, nx_, Q, nx_);
	d_print_mat(nu[0], nu[0], R0, nu[0]);
	d_print_mat(nu[1], nu[1], R1, nu[1]);
	d_print_mat(nu[N], nu[N], RN, nu[N]);
	d_print_mat(nu[0], nx[0], S0, nu[0]);
	d_print_mat(nu[1], nx[1], S1, nu[1]);
	d_print_mat(nu[N], nx[N], SN, nu[N]);
	d_print_mat(1, nx_, q, 1);
	d_print_mat(1, nu[0], r0, 1);
	d_print_mat(1, nu[1], r1, 1);
	d_print_mat(1, nu[N], rN, 1);
//	d_print_mat(nx_, nx_, QN, nx_);
//	d_print_mat(1, nx_, qN, 1);
#endif

	// maximum element in cost functions
	double mu0 = 2.0;

/************************************************
* box & general constraints
************************************************/

	int *idxb0; int_zeros(&idxb0, nb[0], 1);
	double *d_lb0; d_zeros(&d_lb0, nb[0], 1);
	double *d_ub0; d_zeros(&d_ub0, nb[0], 1);
	double *d_lg0; d_zeros(&d_lg0, ng[0], 1);
	double *d_ug0; d_zeros(&d_ug0, ng[0], 1);
	for(ii=0; ii<nb[0]; ii++)
		{
		if(ii<nu[0]) // input
			{
			d_lb0[ii] = - 0.5; // umin
			d_ub0[ii] =   0.5; // umax
			}
		else // state
			{
			d_lb0[ii] = - 4.0; // xmin
			d_ub0[ii] =   4.0; // xmax
			}
		idxb0[ii] = ii;
		}
	for(ii=0; ii<ng[0]; ii++)
		{
		if(ii<nu[0]-nb[0]) // input
			{
			d_lg0[ii] = - 0.5; // umin
			d_ug0[ii] =   0.5; // umax
			}
		else // state
			{
			d_lg0[ii] = - 4.0; // xmin
			d_ug0[ii] =   4.0; // xmax
			}
		}

	int *idxb1; int_zeros(&idxb1, nb[1], 1);
	double *d_lb1; d_zeros(&d_lb1, nb[1], 1);
	double *d_ub1; d_zeros(&d_ub1, nb[1], 1);
	double *d_lg1; d_zeros(&d_lg1, ng[1], 1);
	double *d_ug1; d_zeros(&d_ug1, ng[1], 1);
	for(ii=0; ii<nb[1]; ii++)
		{
		if(ii<nu_) // input
			{
			d_lb1[ii] = - 0.5; // umin
			d_ub1[ii] =   0.5; // umax
			}
		else if(ii<nu[1]) // input
			{
			d_lb1[ii] = 0.0; // umin
			d_ub1[ii] = 1e12; // umax
			}
		else // state
			{
			d_lb1[ii] = - 4.0; // xmin
			d_ub1[ii] =   4.0; // xmax
			}
		idxb1[ii] = ii;
		}
	for(ii=0; ii<ng[1]; ii++)
		{
		d_lg1[ii] = - 1.0; // xmin
		d_ug1[ii] =   1e12; // xmax
		}


	int *idxbN; int_zeros(&idxbN, nb[N], 1);
	double *d_lbN; d_zeros(&d_lbN, nb[N], 1);
	double *d_ubN; d_zeros(&d_ubN, nb[N], 1);
	double *d_lgN; d_zeros(&d_lgN, ng[N], 1);
	double *d_ugN; d_zeros(&d_ugN, ng[N], 1);
	for(ii=0; ii<nb[N]; ii++)
		{
		if(ii<nu[N]) // input
			{
			d_lbN[ii] = 0.0; // umin
			d_ubN[ii] = 1e12; // umax
			}
		else // state
			{
			d_lbN[ii] = - 4.0; // xmin
			d_ubN[ii] =   4.0; // xmax
			}
		idxbN[ii] = ii;
		}
	for(ii=0; ii<ng[N]; ii++)
		{
		d_lgN[ii] = - 1.0; // dmin
		d_ugN[ii] =   1e12; // dmax
		}

	double *C0; d_zeros(&C0, ng[0], nx[0]);
	double *D0; d_zeros(&D0, ng[0], nu[0]);
	for(ii=0; ii<nu[0]-nb[0] & ii<ng[0]; ii++)
		D0[ii+(nb[0]+ii)*ng[0]] = 1.0;
	for(; ii<ng[0]; ii++)
		C0[ii+(nb[0]+ii-nu[0])*ng[0]] = 1.0;

	double *C1; d_zeros(&C1, ng[1], nx[1]);
	double *D1; d_zeros(&D1, ng[1], nu[1]);
	for(ii=0; ii<ng[N]; ii++)
		{
		D1[ii+(nu_+ii)*ng[1]] = 1.0;
		}
	for(ii=0; ii<ng[1]/2; ii++)
		{
		C1[ii+ii*ng[1]] = 1.0;
		C1[ng[1]/2+ii+ii*ng[1]] = -1.0;
		}

	double *CN; d_zeros(&CN, ng[N], nx[N]);
	double *DN; d_zeros(&DN, ng[N], nu[N]);
	for(ii=0; ii<ng[N]; ii++)
		{
		DN[ii+ii*ng[N]] = 1.0;
		}
	for(ii=0; ii<ng[N]/2; ii++)
		{
		CN[ii+ii*ng[N]] = 1.0;
		CN[ng[N]/2+ii+ii*ng[N]] = -1.0;
		}

#if PRINT
	// box constraints
	int_print_mat(1, nb[0], idxb0, 1);
	d_print_mat(1, nb[0], d_lb0, 1);
	d_print_mat(1, nb[0], d_ub0, 1);
	int_print_mat(1, nb[1], idxb1, 1);
	d_print_mat(1, nb[1], d_lb1, 1);
	d_print_mat(1, nb[1], d_ub1, 1);
	int_print_mat(1, nb[N], idxbN, 1);
	d_print_mat(1, nb[N], d_lbN, 1);
	d_print_mat(1, nb[N], d_ubN, 1);
	// general constraints
	d_print_mat(1, ng[0], d_lg0, 1);
	d_print_mat(1, ng[0], d_ug0, 1);
	d_print_mat(ng[0], nu[0], D0, ng[0]);
	d_print_mat(ng[0], nx[0], C0, ng[0]);
	d_print_mat(1, ng[1], d_lg1, 1);
	d_print_mat(1, ng[1], d_ug1, 1);
	d_print_mat(ng[1], nu[1], D1, ng[1]);
	d_print_mat(ng[1], nx[1], C1, ng[1]);
	d_print_mat(1, ng[N], d_lgN, 1);
	d_print_mat(1, ng[N], d_ugN, 1);
	d_print_mat(ng[N], nu[N], DN, ng[N]);
	d_print_mat(ng[N], nx[N], CN, ng[N]);
#endif

//	return 0;
/************************************************
* soft constraints
************************************************/

	double *Zl0; d_zeros(&Zl0, ns[0], 1);
	for(ii=0; ii<ns[0]; ii++)
		Zl0[ii] = 1e3;
	double *Zu0; d_zeros(&Zu0, ns[0], 1);
	for(ii=0; ii<ns[0]; ii++)
		Zu0[ii] = 1e3;
	double *zl0; d_zeros(&zl0, ns[0], 1);
	for(ii=0; ii<ns[0]; ii++)
		zl0[ii] = 1e2;
	double *zu0; d_zeros(&zu0, ns[0], 1);
	for(ii=0; ii<ns[0]; ii++)
		zu0[ii] = 1e2;
	int *idxs0; int_zeros(&idxs0, ns[0], 1);
	for(ii=0; ii<ns[0]; ii++)
		idxs0[ii] = nu[0]+ii;

	double *Zl1; d_zeros(&Zl1, ns[1], 1);
	for(ii=0; ii<ns[1]; ii++)
		Zl1[ii] = 1e3;
	double *Zu1; d_zeros(&Zu1, ns[1], 1);
	for(ii=0; ii<ns[1]; ii++)
		Zu1[ii] = 1e3;
	double *zl1; d_zeros(&zl1, ns[1], 1);
	for(ii=0; ii<ns[1]; ii++)
		zl1[ii] = 1e2;
	double *zu1; d_zeros(&zu1, ns[1], 1);
	for(ii=0; ii<ns[1]; ii++)
		zu1[ii] = 1e2;
	int *idxs1; int_zeros(&idxs1, ns[1], 1);
	for(ii=0; ii<ns[1]; ii++)
		idxs1[ii] = nu[1]+ii;

	double *ZlN; d_zeros(&ZlN, ns[N], 1);
	for(ii=0; ii<ns[N]; ii++)
		ZlN[ii] = 1e3;
	double *ZuN; d_zeros(&ZuN, ns[N], 1);
	for(ii=0; ii<ns[N]; ii++)
		ZuN[ii] = 1e3;
	double *zlN; d_zeros(&zlN, ns[N], 1);
	for(ii=0; ii<ns[N]; ii++)
		zlN[ii] = 1e2;
	double *zuN; d_zeros(&zuN, ns[N], 1);
	for(ii=0; ii<ns[N]; ii++)
		zuN[ii] = 1e2;
	int *idxsN; int_zeros(&idxsN, ns[N], 1);
	for(ii=0; ii<ns[N]; ii++)
		idxsN[ii] = nu[N]+ii;

/************************************************
* array of matrices
************************************************/

	double *hA[N];
	double *hB[N];
	double *hb[N];
	double *hQ[N+1];
	double *hS[N+1];
	double *hR[N+1];
	double *hq[N+1];
	double *hr[N+1];
	double *hd_lb[N+1];
	double *hd_ub[N+1];
	double *hd_lg[N+1];
	double *hd_ug[N+1];
	double *hC[N+1];
	double *hD[N+1];
	int *hidxb[N+1];
	double *hZl[N+1];
	double *hZu[N+1];
	double *hzl[N+1];
	double *hzu[N+1];
	int *hidxs[N+1]; // XXX

	hA[0] = A;
	hB[0] = B;
	hb[0] = b0;
	hQ[0] = Q;
	hS[0] = S0;
	hR[0] = R0;
	hq[0] = q;
	hr[0] = r0;
	hidxb[0] = idxb0;
	hd_lb[0] = d_lb0;
	hd_ub[0] = d_ub0;
	hd_lg[0] = d_lg0;
	hd_ug[0] = d_ug0;
	hC[0] = C0;
	hD[0] = D0;
	hZl[0] = Zl0;
	hZu[0] = Zu0;
	hzl[0] = zl0;
	hzu[0] = zu0;
	hidxs[0] = idxs0;
	for(ii=1; ii<N; ii++)
		{
		hA[ii] = A;
		hB[ii] = B1;
		hb[ii] = b;
		hQ[ii] = Q;
		hS[ii] = S1;
		hR[ii] = R1;
		hq[ii] = q;
		hr[ii] = r1;
		hidxb[ii] = idxb1;
		hd_lb[ii] = d_lb1;
		hd_ub[ii] = d_ub1;
		hd_lg[ii] = d_lg1;
		hd_ug[ii] = d_ug1;
		hC[ii] = C1;
		hD[ii] = D1;
		hZl[ii] = Zl1;
		hZu[ii] = Zu1;
		hzl[ii] = zl1;
		hzu[ii] = zu1;
		hidxs[ii] = idxs1;
		}
	hQ[N] = Q;
	hS[N] = SN;
	hR[N] = RN;
	hq[N] = q;
	hr[N] = rN;
	hidxb[N] = idxbN;
	hd_lb[N] = d_lbN;
	hd_ub[N] = d_ubN;
	hd_lg[N] = d_lgN;
	hd_ug[N] = d_ugN;
	hC[N] = CN;
	hD[N] = DN;
	hZl[N] = ZlN;
	hZu[N] = ZuN;
	hzl[N] = zlN;
	hzu[N] = zuN;
	hidxs[N] = idxsN;

/************************************************
* ocp qp
************************************************/

	hpipm_size_t qp_size = d_memsize_ocp_qp(N, nx, nu, nb, ng, ns);
	printf("\nqp size = %d\n", qp_size);
	void *qp_mem = malloc(qp_size);

	struct d_ocp_qp qp;
	d_create_ocp_qp(N, nx, nu, nb, ng, ns, &qp, qp_mem);
	d_cvt_colmaj_to_ocp_qp(hA, hB, hb, hQ, hS, hR, hq, hr, hidxb, hd_lb, hd_ub, hC, hD, hd_lg, hd_ug, hZl, hZu, hzl, hzu, hidxs, &qp);
#if 0
	printf("\nN = %d\n", qp.N);
	for(ii=0; ii<N; ii++)
		d_print_strmat(qp.nu[ii]+qp.nx[ii]+1, qp.nx[ii+1], qp.BAbt+ii, 0, 0);
	for(ii=0; ii<N; ii++)
		blasfeo_print_tran_dvec(qp.nx[ii+1], qp.b+ii, 0);
	for(ii=0; ii<=N; ii++)
		d_print_strmat(qp.nu[ii]+qp.nx[ii]+1, qp.nu[ii]+qp.nx[ii], qp.RSQrq+ii, 0, 0);
	for(ii=0; ii<=N; ii++)
		blasfeo_print_tran_dvec(qp.nu[ii]+qp.nx[ii], qp.rq+ii, 0);
	for(ii=0; ii<=N; ii++)
		int_print_mat(1, nb[ii], qp.idxb[ii], 1);
	for(ii=0; ii<=N; ii++)
		blasfeo_print_tran_dvec(qp.nb[ii], qp.d_lb+ii, 0);
	for(ii=0; ii<=N; ii++)
		blasfeo_print_tran_dvec(qp.nb[ii], qp.d_ub+ii, 0);
	for(ii=0; ii<=N; ii++)
		d_print_strmat(qp.nu[ii]+qp.nx[ii], qp.ng[ii], qp.DCt+ii, 0, 0);
	for(ii=0; ii<=N; ii++)
		blasfeo_print_tran_dvec(qp.ng[ii], qp.d_lg+ii, 0);
	for(ii=0; ii<=N; ii++)
		blasfeo_print_tran_dvec(qp.ng[ii], qp.d_ug+ii, 0);
	return;
#endif

/************************************************
* ocp qp sol
************************************************/

	hpipm_size_t qp_sol_size = d_memsize_ocp_qp_sol(N, nx, nu, nb, ng, ns);
	printf("\nqp sol size = %d\n", qp_sol_size);
	void *qp_sol_mem = malloc(qp_sol_size);

	struct d_ocp_qp_sol qp_sol;
	d_create_ocp_qp_sol(N, nx, nu, nb, ng, ns, &qp_sol, qp_sol_mem);

/************************************************
* ipm
************************************************/

	struct d_ipm_ocp_qp_arg arg;
	arg.alpha_min = 1e-8;
	arg.mu_max = 1e-12;
	arg.iter_max = 20;
	arg.mu0 = 100.0;

	hpipm_size_t ipm_size = d_memsize_ipm_ocp_qp(&qp, &arg);
	printf("\nipm size = %d\n", ipm_size);
	void *ipm_mem = malloc(ipm_size);

	struct d_ipm_ocp_qp_workspace workspace;
	d_create_ipm_ocp_qp(&qp, &arg, &workspace, ipm_mem);

	int hpipm_return; // 0 normal; 1 max iter

	gettimeofday(&tv0, NULL); // start

	for(rep=0; rep<nrep; rep++)
		{
//		hpipm_return = d_solve_ipm_ocp_qp(&qp, &qp_sol, &workspace);
		hpipm_return = d_solve_ipm2_ocp_qp(&qp, &qp_sol, &workspace);
		}

	gettimeofday(&tv1, NULL); // stop

	double time_ocp_ipm = (tv1.tv_sec-tv0.tv_sec)/(nrep+0.0)+(tv1.tv_usec-tv0.tv_usec)/(nrep*1e6);

/************************************************
* extract and print solution
************************************************/

	double *u[N+1]; for(ii=0; ii<=N; ii++) d_zeros(u+ii, nu[ii], 1);
	double *x[N+1]; for(ii=0; ii<=N; ii++) d_zeros(x+ii, nx[ii], 1);
	double *ls[N+1]; for(ii=0; ii<=N; ii++) d_zeros(ls+ii, ns[ii], 1);
	double *us[N+1]; for(ii=0; ii<=N; ii++) d_zeros(us+ii, ns[ii], 1);
	double *pi[N]; for(ii=0; ii<N; ii++) d_zeros(pi+ii, nx[ii+1], 1);
	double *lam_lb[N+1]; for(ii=0; ii<=N; ii++) d_zeros(lam_lb+ii, nb[ii], 1);
	double *lam_ub[N+1]; for(ii=0; ii<=N; ii++) d_zeros(lam_ub+ii, nb[ii], 1);
	double *lam_lg[N+1]; for(ii=0; ii<=N; ii++) d_zeros(lam_lg+ii, ng[ii], 1);
	double *lam_ug[N+1]; for(ii=0; ii<=N; ii++) d_zeros(lam_ug+ii, ng[ii], 1);
	double *lam_ls[N+1]; for(ii=0; ii<=N; ii++) d_zeros(lam_ls+ii, ns[ii], 1);
	double *lam_us[N+1]; for(ii=0; ii<=N; ii++) d_zeros(lam_us+ii, ns[ii], 1);

	d_cvt_ocp_qp_sol_to_colmaj(&qp, &qp_sol, u, x, ls, us, pi, lam_lb, lam_ub, lam_lg, lam_ug, lam_ls, lam_us);

#if 1
	printf("\nsolution\n\n");
	printf("\nu\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, nu[ii], u[ii], 1);
	printf("\nx\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, nx[ii], x[ii], 1);
	printf("\nls\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ns[ii], ls[ii], 1);
	printf("\nus\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ns[ii], us[ii], 1);
	printf("\npi\n");
	for(ii=0; ii<N; ii++)
		d_print_mat(1, nx[ii+1], pi[ii], 1);
	printf("\nlam_lb\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, nb[ii], lam_lb[ii], 1);
	printf("\nlam_ub\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, nb[ii], lam_ub[ii], 1);
	printf("\nlam_lg\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ng[ii], lam_lg[ii], 1);
	printf("\nlam_ug\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ng[ii], lam_ug[ii], 1);
	printf("\nlam_ls\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ns[ii], lam_ls[ii], 1);
	printf("\nlam_us\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ns[ii], lam_us[ii], 1);

	printf("\nt_lb\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, nb[ii], (qp_sol.t+ii)->pa, 1);
	printf("\nt_ub\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, nb[ii], (qp_sol.t+ii)->pa+nb[ii]+ng[ii], 1);
	printf("\nt_lg\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ng[ii], (qp_sol.t+ii)->pa+nb[ii], 1);
	printf("\nt_ug\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ng[ii], (qp_sol.t+ii)->pa+2*nb[ii]+ng[ii], 1);
	printf("\nt_ls\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ns[ii], (qp_sol.t+ii)->pa+2*nb[ii]+2*ng[ii], 1);
	printf("\nt_us\n");
	for(ii=0; ii<=N; ii++)
		d_print_mat(1, ns[ii], (qp_sol.t+ii)->pa+2*nb[ii]+2*ng[ii]+ns[ii], 1);
#endif

/************************************************
* extract and print residuals
************************************************/

	double *res_r[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_r+ii, nu[ii], 1);
	double *res_q[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_q+ii, nx[ii], 1);
	double *res_ls[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_ls+ii, ns[ii], 1);
	double *res_us[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_us+ii, ns[ii], 1);
	double *res_b[N]; for(ii=0; ii<N; ii++) d_zeros(res_b+ii, nx[ii+1], 1);
	double *res_d_lb[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_d_lb+ii, nb[ii], 1);
	double *res_d_ub[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_d_ub+ii, nb[ii], 1);
	double *res_d_lg[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_d_lg+ii, ng[ii], 1);
	double *res_d_ug[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_d_ug+ii, ng[ii], 1);
	double *res_d_ls[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_d_ls+ii, ns[ii], 1);
	double *res_d_us[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_d_us+ii, ns[ii], 1);
	double *res_m_lb[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_m_lb+ii, nb[ii], 1);
	double *res_m_ub[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_m_ub+ii, nb[ii], 1);
	double *res_m_lg[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_m_lg+ii, ng[ii], 1);
	double *res_m_ug[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_m_ug+ii, ng[ii], 1);
	double *res_m_ls[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_m_ls+ii, ns[ii], 1);
	double *res_m_us[N+1]; for(ii=0; ii<=N; ii++) d_zeros(res_m_us+ii, ns[ii], 1);

	d_cvt_ocp_qp_res_to_colmaj(&qp, &workspace.res_workspace, res_r, res_q, res_ls, res_us, res_b, res_d_lb, res_d_ub, res_d_lg, res_d_ug, res_d_ls, res_d_us, res_m_lb, res_m_ub, res_m_lg, res_m_ug, res_m_ls, res_m_us);

#if 1
	printf("\nresiduals\n\n");
	printf("\nres_r\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, nu[ii], res_r[ii], 1);
	printf("\nres_q\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, nx[ii], res_q[ii], 1);
	printf("\nres_ls\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ns[ii], res_ls[ii], 1);
	printf("\nres_us\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ns[ii], res_us[ii], 1);
	printf("\nres_b\n");
	for(ii=0; ii<N; ii++)
		d_print_exp_mat(1, nx[ii+1], res_b[ii], 1);
	printf("\nres_d_lb\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, nb[ii], res_d_lb[ii], 1);
	printf("\nres_d_ub\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, nb[ii], res_d_ub[ii], 1);
	printf("\nres_d_lg\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ng[ii], res_d_lg[ii], 1);
	printf("\nres_d_ug\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ng[ii], res_d_ug[ii], 1);
	printf("\nres_d_ls\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ns[ii], res_d_ls[ii], 1);
	printf("\nres_d_us\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ns[ii], res_d_us[ii], 1);
	printf("\nres_m_lb\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, nb[ii], res_m_lb[ii], 1);
	printf("\nres_m_ub\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, nb[ii], res_m_ub[ii], 1);
	printf("\nres_m_lg\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ng[ii], res_m_lg[ii], 1);
	printf("\nres_m_ug\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ng[ii], res_m_ug[ii], 1);
	printf("\nres_m_ls\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ns[ii], res_m_ls[ii], 1);
	printf("\nres_m_us\n");
	for(ii=0; ii<=N; ii++)
		d_print_exp_mat(1, ns[ii], res_m_us[ii], 1);
#endif

/************************************************
* print ipm statistics
************************************************/

	printf("\nipm return = %d\n", hpipm_return);

	printf("\nipm iter = %d\n", workspace.iter);
	printf("\nalpha_aff\tmu_aff\t\tsigma\t\talpha\t\tmu\n");
	d_print_exp_tran_mat(5, workspace.iter, workspace.stat, 5);

	printf("\nocp ipm time = %e [s]\n\n", time_ocp_ipm);

/************************************************
* free memory
************************************************/

	d_free(A);
	d_free(B);
	d_free(B1);
	d_free(b);
	d_free(x0);
	d_free(Q);
//	d_free(QN);
	d_free(R0);
	d_free(R1);
	d_free(RN);
	d_free(S0);
	d_free(S1);
	d_free(SN);
	d_free(q);
//	d_free(qN);
	d_free(r0);
	d_free(r1);
	d_free(rN);
	int_free(idxb0);
	d_free(d_lb0);
	d_free(d_ub0);
	int_free(idxb1);
	d_free(d_lb1);
	d_free(d_ub1);
	int_free(idxbN);
	d_free(d_lbN);
	d_free(d_ubN);
	d_free(C0);
	d_free(D0);
	d_free(d_lg0);
	d_free(d_ug0);
	d_free(C1);
	d_free(D1);
	d_free(d_lg1);
	d_free(d_ug1);
	d_free(CN);
	d_free(DN);
	d_free(d_lgN);
	d_free(d_ugN);
	d_free(Zl0);
	d_free(Zu0);
	d_free(zl0);
	d_free(zu0);
	int_free(idxs0);
	d_free(Zl1);
	d_free(Zu1);
	d_free(zl1);
	d_free(zu1);
	int_free(idxs1);
	d_free(ZlN);
	d_free(ZuN);
	d_free(zlN);
	d_free(zuN);
	int_free(idxsN);

	for(ii=0; ii<N; ii++)
		{
		d_free(u[ii]);
		d_free(x[ii]);
		d_free(ls[ii]);
		d_free(us[ii]);
		d_free(pi[ii]);
		d_free(lam_lb[ii]);
		d_free(lam_ub[ii]);
		d_free(lam_lg[ii]);
		d_free(lam_ug[ii]);
		d_free(lam_ls[ii]);
		d_free(lam_us[ii]);
		d_free(res_r[ii]);
		d_free(res_q[ii]);
		d_free(res_ls[ii]);
		d_free(res_us[ii]);
		d_free(res_b[ii]);
		d_free(res_d_lb[ii]);
		d_free(res_d_ub[ii]);
		d_free(res_d_lg[ii]);
		d_free(res_d_ug[ii]);
		d_free(res_d_ls[ii]);
		d_free(res_d_us[ii]);
		d_free(res_m_lb[ii]);
		d_free(res_m_ub[ii]);
		d_free(res_m_lg[ii]);
		d_free(res_m_ug[ii]);
		d_free(res_m_ls[ii]);
		d_free(res_m_us[ii]);
		}
	d_free(u[ii]);
	d_free(x[ii]);
	d_free(ls[ii]);
	d_free(us[ii]);
	d_free(lam_lb[ii]);
	d_free(lam_ub[ii]);
	d_free(lam_lg[ii]);
	d_free(lam_ug[ii]);
	d_free(lam_ls[ii]);
	d_free(lam_us[ii]);
	d_free(res_r[ii]);
	d_free(res_q[ii]);
	d_free(res_ls[ii]);
	d_free(res_us[ii]);
	d_free(res_d_lb[ii]);
	d_free(res_d_ub[ii]);
	d_free(res_d_lg[ii]);
	d_free(res_d_ug[ii]);
	d_free(res_d_ls[ii]);
	d_free(res_d_us[ii]);
	d_free(res_m_lb[ii]);
	d_free(res_m_ub[ii]);
	d_free(res_m_lg[ii]);
	d_free(res_m_ug[ii]);
	d_free(res_m_ls[ii]);
	d_free(res_m_us[ii]);

	free(qp_mem);
	free(qp_sol_mem);
	free(ipm_mem);

/************************************************
* return
************************************************/

	return 0;

	}
