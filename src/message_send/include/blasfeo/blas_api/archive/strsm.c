/**************************************************************************************************
*                                                                                                 *
* This file is part of BLASFEO.                                                                   *
*                                                                                                 *
* BLASFEO -- BLAS for embedded optimization.                                                      *
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

#include "../include/blasfeo_target.h"
#include "../include/blasfeo_common.h"
#include "../include/blasfeo_s_aux.h"
#include "../include/blasfeo_s_kernel.h"



#if defined(FORTRAN_BLAS_API)
#define blasfeo_strsm strsm_
#endif



#if defined(FALLBACK_TO_EXTERNAL_BLAS)
void strsv_(char *uplo, char *transa, char *diag, int *m, float *A, int *lda, float *x, int *incx);
void sscal_(int *m, float *alpha, float *x, int *incx);
#endif



void blasfeo_strsm(char *side, char *uplo, char *transa, char *diag, int *pm, int *pn, float *alpha, float *A, int *plda, float *B, int *pldb)
	{

#if defined(PRINT_NAME)
	printf("\nblasfeo_strsm %c %c %c %c %d %d %f %p %d %p %d\n", *side, *uplo, *transa, *diag, *pm, *pn, *alpha, A, *plda, B, *pldb);
#endif

	int m = *pm;
	int n = *pn;
	int lda = *plda;
	int ldb = *pldb;

#if defined(DIM_CHECK)
	if( !(*side=='l' | *side=='L' | *side=='r' | *side=='R') )
		{
		printf("\nBLASFEO: strsm: wrong value for side\n");
		return;
		}
	if( !(*uplo=='l' | *uplo=='L' | *uplo=='u' | *uplo=='U') )
		{
		printf("\nBLASFEO: strsm: wrong value for uplo\n");
		return;
		}
	if( !(*transa=='c' | *transa=='C' | *transa=='n' | *transa=='N' | *transa=='t' | *transa=='T') )
		{
		printf("\nBLASFEO: strsm: wrong value for transa\n");
		return;
		}
	if( !(*diag=='n' | *diag=='N' | *diag=='u' | *diag=='U') )
		{
		printf("\nBLASFEO: strsm: wrong value for diag\n");
		return;
		}
#endif

	char c_n = 'n';
	char c_t = 't';
	int i_1 = 1;

#if defined(FALLBACK_TO_EXTERNAL_BLAS)
	// fallback to dtrsv if B is a vector
	if(n==1 & (*side=='l' | *side=='L'))
		{
		strsv_(uplo, transa, diag, pm, A, plda, B, &i_1);
		if(*alpha!=1.0)
			{
			sscal_(pm, alpha, B, &i_1);
			}
		return;
		}
	else if(m==1 & (*side=='r' | *side=='r'))
		{
		if(*transa=='n' | *transa=='N')
			{
			strsv_(uplo, &c_t, diag, pn, A, plda, B, pldb);
			}
		else
			{
			strsv_(uplo, &c_n, diag, pn, A, plda, B, pldb);
			}
		if(*alpha!=1.0)
			{
			sscal_(pn, alpha, B, pldb);
			}
		return;
		}
#endif



	int ii, jj;

	const int ps_4 = 4;
	const int ps_8 = 8;

	if(m<=0 | n<=0)
		return;

#if defined(TARGET_GENERIC)
	float pd0[K_MAX_STACK];
#else
	ALIGNED( float pd0[K_MAX_STACK], 64 );
#endif

#if defined(TARGET_GENERIC)
	float pU0[1*4*K_MAX_STACK];
#else
	ALIGNED( float pU0[1*4*K_MAX_STACK], 64 );
#endif

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!
	const int m_kernel = 4;

	int k0;
	// TODO update if necessary !!!!!
	if(*side=='l' | *side=='L')
		k0 = m;
	else
		k0 = n;

	int sdu0 = (k0+3)/4*4;
	sdu0 = sdu0<K_MAX_STACK ? sdu0 : K_MAX_STACK;

	struct blasfeo_pm_smat sA, sB;
	float *pU, *pB, *dA, *dB;
	int sda, sdb, sdu;
	int sA_size, sB_size;
	void *mem;
	char *mem_align;
	int m1, n1;
	int idx, m4, mn4, n4, nn4;
	int pack_tran = 0;



	if(*side=='l' | *side=='L') // _l
		{
		if(*uplo=='l' | *uplo=='L') // _ll
			{
			if(*transa=='n' | *transa=='N') // _lln
				{
				if(*diag=='n' | *diag=='N') // _llnn
					{
					goto llnn;
					}
				else //if(*diag=='u' | *diag=='U') // _llnu
					{
					goto llnu;
					}
				}
			else //if(*transa=='t' | *transa=='T' | *transa=='c' | *transa=='C') // _llt
				{
				if(*diag=='n' | *diag=='N') // _lltn
					{
					goto lltn;
					}
				else //if(*diag=='u' | *diag=='U') // _lltu
					{
					goto lltu;
					}
				}
			}
		else //if(*uplo=='u' | *uplo=='U') // _lu
			{
			if(*transa=='n' | *transa=='N') // _lun
				{
				if(*diag=='n' | *diag=='N') // _lunn
					{
					goto lunn;
					}
				else //if(*diag=='u' | *diag=='U') // _lunu
					{
					goto lunu;
					}
				}
			else //if(*transa=='t' | *transa=='T' | *transa=='c' | *transa=='C') // _lut
				{
				if(*diag=='n' | *diag=='N') // _lutn
					{
					goto lutn;
					}
				else //if(*diag=='u' | *diag=='U') // _lutu
					{
					goto lutu;
					}
				}
			}
		}
	else //if(*side=='r' | *side=='R') // _r
		{
		if(*uplo=='l' | *uplo=='L') // _rl
			{
			if(*transa=='n' | *transa=='N') // _rln
				{
				if(*diag=='n' | *diag=='N') // _rlnn
					{
					goto rlnn;
					}
				else //if(*diag=='u' | *diag=='U') // _rlnu
					{
					goto rlnu;
					}
				}
			else //if(*transa=='t' | *transa=='T' | *transa=='c' | *transa=='C') // _rlt
				{
				if(*diag=='n' | *diag=='N') // _rltn
					{
					goto rltn;
					}
				else //if(*diag=='u' | *diag=='U') // _rltu
					{
					goto rltu;
					}
				}
			}
		else //if(*uplo=='u' | *uplo=='U') // _ru
			{
			if(*transa=='n' | *transa=='N') // _run
				{
				if(*diag=='n' | *diag=='N') // _runn
					{
					goto runn;
					}
				else //if(*diag=='u' | *diag=='U') // _runu
					{
					goto runu;
					}
				}
			else //if(*transa=='t' | *transa=='T' | *transa=='c' | *transa=='C') // _rut
				{
				if(*diag=='n' | *diag=='N') // _rutn
					{
					goto rutn;
					}
				else //if(*diag=='u' | *diag=='U') // _rutu
					{
					goto rutu;
					}
				}
			}
		}


/************************************************
* llnn
************************************************/
llnn:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 0;
		goto llnn_1;
		}
	else
		{
		goto llnn_0;
		}
	return;

llnn_0:
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<m; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		for(jj=0; jj<m-3; jj+=4)
			{
			kernel_strsm_nt_rl_inv_4x4_lib4c44c(jj, pU, A+jj, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, dA+jj);
			}
		if(jj<m)
			{
			kernel_strsm_nt_rl_inv_4x4_vs_lib4c44c(jj, pU, A+jj, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, dA+jj, n-ii, m-jj);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto llnn_0_left_4;
		}
	goto llnn_0_return;

llnn_0_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	for(jj=0; jj<m; jj+=4)
		{
		kernel_strsm_nt_rl_inv_4x4_vs_lib4c44c(jj, pU, A+jj, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, dA+jj, n-ii, m-jj);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
goto llnn_0_return;

llnn_0_return:
	return;



llnn_1:
	m1 = (m+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, m1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, m1, m1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, m, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, m, m, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;
	dB = sB.dA;

	if(pack_tran) // upper to lower
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(ii+4, A+ii*lda, lda, pB+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_tn_4_vs_lib4(m, A+ii*lda, lda, pB+ii*sdb, m-ii);
			}
		}
	else // lower to lower
		{
		// TODO pack 8 or 12 ??? or pack tt
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(ii+4, A+ii, lda, pB+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_nn_4_vs_lib4(m, A+ii, lda, pB+ii*sdb, m-ii);
			}
		}

	for(ii=0; ii<m; ii++)
		dB[ii] = 1.0/A[ii+ii*lda];

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		for(jj=0; jj<m-3; jj+=4)
			{
			kernel_strsm_nt_rl_inv_4x4_lib4(jj, pU, sB.pA+jj*sdb, alpha, pU+jj*ps_4, pU+jj*ps_4, sB.pA+jj*ps_4+jj*sdb, dB+jj);
			}
		if(jj<m)
			{
			kernel_strsm_nt_rl_inv_4x4_vs_lib4(jj, pU, sB.pA+jj*sdb, alpha, pU+jj*ps_4, pU+jj*ps_4, sB.pA+jj*ps_4+jj*sdb, dB+jj, n-ii, m-jj);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto llnn_1_left_4;
		}
	goto llnn_1_return;

llnn_1_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	for(jj=0; jj<m; jj+=4)
		{
		kernel_strsm_nt_rl_inv_4x4_vs_lib4(jj, pU, sB.pA+jj*sdb, alpha, pU+jj*ps_4, pU+jj*ps_4, sB.pA+jj*ps_4+jj*sdb, dB+jj, n-ii, m-jj);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
goto llnn_1_return;

llnn_1_return:
	free(mem);
	return;



/************************************************
* llnu
************************************************/
llnu:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 0;
		goto llnu_1;
		}
	else
		{
		goto llnu_0;
		}
	return;

llnu_0:
	pU = pU0;
	sdu = sdu0;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		for(jj=0; jj<m-3; jj+=4)
			{
			kernel_strsm_nt_rl_one_4x4_lib4c44c(jj, pU, A+jj, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda);
			}
		if(jj<m)
			{
			kernel_strsm_nt_rl_one_4x4_vs_lib4c44c(jj, pU, A+jj, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, n-ii, m-jj);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto llnu_0_left_4;
		}
	goto llnu_0_return;

llnu_0_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	for(jj=0; jj<m; jj+=4)
		{
		kernel_strsm_nt_rl_one_4x4_vs_lib4c44c(jj, pU, A+jj, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, n-ii, m-jj);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
goto llnu_0_return;

llnu_0_return:
	return;



llnu_1:
	m1 = (m+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, m1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, m1, m1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, m, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, m, m, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;

	if(pack_tran) // upper to lower
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(ii+4, A+ii*lda, lda, pB+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_tn_4_vs_lib4(m, A+ii*lda, lda, pB+ii*sdb, m-ii);
			}
		}
	else // lower to lower
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(ii+4, A+ii, lda, pB+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_nn_4_vs_lib4(m, A+ii, lda, pB+ii*sdb, m-ii);
			}
		}

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		for(jj=0; jj<m-3; jj+=4)
			{
			kernel_strsm_nt_rl_one_4x4_lib4(jj, pU, sB.pA+jj*sdb, alpha, pU+jj*ps_4, pU+jj*ps_4, sB.pA+jj*ps_4+jj*sdb);
			}
		if(jj<m)
			{
			kernel_strsm_nt_rl_one_4x4_vs_lib4(jj, pU, sB.pA+jj*sdb, alpha, pU+jj*ps_4, pU+jj*ps_4, sB.pA+jj*ps_4+jj*sdb, n-ii, m-jj);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto llnu_1_left_4;
		}
	goto llnu_1_return;

llnu_1_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	for(jj=0; jj<m; jj+=4)
		{
		kernel_strsm_nt_rl_one_4x4_vs_lib4(jj, pU, sB.pA+jj*sdb, alpha, pU+jj*ps_4, pU+jj*ps_4, sB.pA+jj*ps_4+jj*sdb, n-ii, m-jj);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
goto llnu_1_return;

llnu_1_return:
	free(mem);
	return;



/***********************
* lltn
***********************/
lltn:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 1;
		goto lunn_1;
		}
	else
		{
		goto lltn_0;
		}
	return;

lltn_0:
	// XXX limits of ii and jj swapped !!!
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<m; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mn4 = m%4;
	m4 = m - mn4;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		if(mn4!=0)
			{
			idx = m4;
			kernel_strsm_nn_rl_inv_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx, n-ii, mn4);
			}
		for(jj=0; jj<m4-3; jj+=4)
			{
			idx = m4-jj-4;
			kernel_strsm_nn_rl_inv_4x4_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lltn_0_left_4;
		}
	goto lltn_0_return;

lltn_0_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	if(mn4!=0)
		{
		idx = m4;
		kernel_strsm_nn_rl_inv_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx, n-ii, mn4);
		}
	for(jj=0; jj<m4-3; jj+=4)
		{
		idx = m4-jj-4;
		kernel_strsm_nn_rl_inv_4x4_vs_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx, n-ii, 4);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
	goto lltn_0_return;

lltn_0_return:
	return;



/***********************
* lltu
***********************/
lltu:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 1;
		goto lunu_1;
		}
	else
		{
		goto lltu_0;
		}
	return;

lltu_0:
	// XXX limits of ii and jj swapped !!!
	pU = pU0;
	sdu = sdu0;

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mn4 = m%4;
	m4 = m - mn4;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		if(mn4!=0)
			{
			idx = m4;
			kernel_strsm_nn_rl_one_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, n-ii, mn4);
			}
		for(jj=0; jj<m4-3; jj+=4)
			{
			idx = m4-jj-4;
			kernel_strsm_nn_rl_one_4x4_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lltu_0_left_4;
		}
	goto lltu_0_return;

lltu_0_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	if(mn4!=0)
		{
		idx = m4;
		kernel_strsm_nn_rl_one_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, n-ii, mn4);
		}
	for(jj=0; jj<m4-3; jj+=4)
		{
		idx = m4-jj-4;
		kernel_strsm_nn_rl_one_4x4_vs_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+4+idx*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, n-ii, 4);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
	goto lltu_0_return;

lltu_0_return:
	return;



/************************************************
* lunu
************************************************/
lunu:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 0;
		goto lunu_1;
		}
	else
		{
		goto lunu_0;
		}

lunu_0:
	// XXX limits of ii and jj swapped !!!
	pU = pU0;
	sdu = sdu0;

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mn4 = m%4;
	m4 = m - mn4;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		if(mn4!=0)
			{
			idx = m4;
			kernel_strsm_nt_ru_one_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, n-ii, mn4);
			}
		for(jj=0; jj<m4-3; jj+=4)
			{
			idx = m4-jj-4;
			kernel_strsm_nt_ru_one_4x4_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lunu_0_left_4;
		}
	goto lunu_0_return;

lunu_0_left_4:
	kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
	if(mn4!=0)
		{
		idx = m4;
		kernel_strsm_nt_ru_one_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, n-ii, mn4);
		}
	for(jj=0; jj<m4-3; jj+=4)
		{
		idx = m4-jj-4;
		kernel_strsm_nt_ru_one_4x4_vs_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, n-ii, 4);
		}
	kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
	goto lunu_0_return;

lunu_0_return:
	return;



lunu_1:
	// XXX limits of ii and jj swapped !!!
	m1 = (m+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, m1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, m1, m1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, m, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, m, m, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;

	if(pack_tran) // lower to upper
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_tn_4_vs_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, m-ii);
			}
		}
	else // upper to upper
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_nn_4_vs_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, m-ii);
			}
		}

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mn4 = m%4;
	m4 = m - mn4;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		if(mn4!=0)
			{
			idx = m4;
			kernel_strsm_nt_ru_one_4x4_vs_lib4(0, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, n-ii, mn4);
			}
		for(jj=0; jj<m4-3; jj+=4)
			{
			idx = m4-jj-4;
			kernel_strsm_nt_ru_one_4x4_lib4(jj+mn4, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lunu_1_left_4;
		}
	goto lunu_1_return;

lunu_1_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	if(mn4!=0)
		{
		idx = m4;
		kernel_strsm_nt_ru_one_4x4_vs_lib4(0, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, n-ii, mn4);
		}
	for(jj=0; jj<m4-3; jj+=4)
		{
		idx = m4-jj-4;
		kernel_strsm_nt_ru_one_4x4_vs_lib4(jj+mn4, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, n-ii, 4);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
	goto lunu_1_return;

lunu_1_return:
	free(mem);
	return;



/************************************************
* lunn
************************************************/
lunn:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 0;
		goto lunn_1;
		}
	else
		{
		goto lunn_0;
		}

lunn_0:
	// XXX limits of ii and jj swapped !!!
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<m; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mn4 = m%4;
	m4 = m - mn4;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		if(mn4!=0)
			{
			idx = m4;
			kernel_strsm_nt_ru_inv_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx, n-ii, mn4);
			}
		for(jj=0; jj<m4-3; jj+=4)
			{
			idx = m4-jj-4;
			kernel_strsm_nt_ru_inv_4x4_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lunn_0_left_4;
		}
	goto lunn_0_return;

lunn_0_left_4:
	kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
	if(mn4!=0)
		{
		idx = m4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib4c44c(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx, n-ii, mn4);
		}
	for(jj=0; jj<m4-3; jj+=4)
		{
		idx = m4-jj-4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib4c44c(jj+mn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, pU+idx*ps_4, pU+idx*ps_4, A+idx+idx*lda, lda, dA+idx, n-ii, 4);
		}
	kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
	goto lunn_0_return;

lunn_0_return:
	return;



lunn_1:
	// XXX limits of ii and jj swapped !!!
	m1 = (m+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, m1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, m1, m1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, m, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, m, m, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;
	dB = sB.dA;

	if(pack_tran) // lower to upper
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_tn_4_vs_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, m-ii);
			}
		}
	else // upper to upper
		{
		for(ii=0; ii<m-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<m)
			{
			kernel_spack_nn_4_vs_lib4(m-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, m-ii);
			}
		}

	for(ii=0; ii<m; ii++)
		dB[ii] = 1.0/A[ii+ii*lda];

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mn4 = m%4;
	m4 = m - mn4;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		if(mn4!=0)
			{
			idx = m4;
			kernel_strsm_nt_ru_inv_4x4_vs_lib4(0, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, dB+idx, n-ii, mn4);
			}
		for(jj=0; jj<m4-3; jj+=4)
			{
			idx = m4-jj-4;
			kernel_strsm_nt_ru_inv_4x4_lib4(jj+mn4, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, dB+idx);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lunn_1_left_4;
		}
	goto lunn_1_return;

lunn_1_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	if(mn4!=0)
		{
		idx = m4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib4(0, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, dB+idx, n-ii, mn4);
		}
	for(jj=0; jj<m4-3; jj+=4)
		{
		idx = m4-jj-4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib4(jj+mn4, pU+(idx+4)*ps_4, pB+(idx+4)*ps_4+idx*sdb, alpha, pU+idx*ps_4, pU+idx*ps_4, pB+idx*ps_4+idx*sdb, dB+idx, n-ii, 4);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
	goto lunn_1_return;

lunn_1_return:
	free(mem);
	return;



/************************************************
* lutn
************************************************/
lutn:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 1;
		goto llnn_1;
		}
	else
		{
		goto lutn_0;
		}

lutn_0:
	// XXX limits of ii and jj swapped !!!
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<m; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		for(jj=0; jj<m-3; jj+=4)
			{
			kernel_strsm_nn_ru_inv_4x4_lib4c44c(jj, pU, A+jj*lda, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, dA+jj);
			}
		if(jj<m)
			{
			kernel_strsm_nn_ru_inv_4x4_vs_lib4c44c(jj, pU, A+jj*lda, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, dA+jj, n-ii, m-jj);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lutn_0_left_4;
		}
	goto lutn_0_return;

lutn_0_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	for(jj=0; jj<m; jj+=4)
		{
		kernel_strsm_nn_ru_inv_4x4_vs_lib4c44c(jj, pU, A+jj*lda, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, dA+jj, n-ii, m-jj);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
goto lutn_0_return;

lutn_0_return:
	return;



/************************************************
* lutu
************************************************/
lutu:
	if(m>=12 | n>=12 | m>K_MAX_STACK)
		{
		pack_tran = 1;
		goto llnu_1;
		}
	else
		{
		goto lutu_0;
		}

lutu_0:
	// XXX limits of ii and jj swapped !!!
	pU = pU0;
	sdu = sdu0;

	ii = 0;
	for(; ii<n-3; ii+=4)
		{
		kernel_spack_tn_4_lib4(m, B+ii*ldb, ldb, pU);
		for(jj=0; jj<m-3; jj+=4)
			{
			kernel_strsm_nn_ru_one_4x4_lib4c44c(jj, pU, A+jj*lda, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda);
			}
		if(jj<m)
			{
			kernel_strsm_nn_ru_one_4x4_vs_lib4c44c(jj, pU, A+jj*lda, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, n-ii, m-jj);
			}
		kernel_sunpack_nt_4_lib4(m, pU, B+ii*ldb, ldb);
		}
	if(ii<n)
		{
		goto lutu_0_left_4;
		}
	goto lutu_0_return;

lutu_0_left_4:
	kernel_spack_tn_4_vs_lib4(m, B+ii*ldb, ldb, pU, n-ii);
	for(jj=0; jj<m; jj+=4)
		{
		kernel_strsm_nn_ru_one_4x4_vs_lib4c44c(jj, pU, A+jj*lda, lda, alpha, pU+jj*ps_4, pU+jj*ps_4, A+jj+jj*lda, lda, n-ii, m-jj);
		}
	kernel_sunpack_nt_4_vs_lib4(m, pU, B+ii*ldb, ldb, n-ii);
goto lutu_0_return;

lutu_0_return:
	return;



/************************************************
* rlnn
************************************************/
rlnn:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 1;
		goto rutn_1;
		}
	else
		{
		goto rlnn_0;
		}

rlnn_0:
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<n; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nn4 = n%4;
	n4 = n - nn4;

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		if(nn4!=0)
			{
			idx = n4;
			kernel_strsm_nn_rl_inv_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx, m-ii, nn4);
			kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
			}
		for(jj=0; jj<n4-3; jj+=4)
			{
			idx = n4-jj-4;
			kernel_strsm_nn_rl_inv_4x4_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx);
			kernel_spack_nn_4_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4);
			}
		}
	if(ii<m)
		{
		goto rlnn_0_left_4;
		}
	goto rlnn_0_return;

rlnn_0_left_4:
	if(nn4!=0)
		{
		idx = n4;
		kernel_strsm_nn_rl_inv_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx, m-ii, nn4);
		kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	for(jj=0; jj<n4-3; jj+=4)
		{
		idx = n4-jj-4;
		kernel_strsm_nn_rl_inv_4x4_vs_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx, m-ii, 4);
		kernel_spack_nn_4_vs_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	goto rlnn_0_return;

rlnn_0_return:
	return;



/************************************************
* rlnu
************************************************/
rlnu:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 1;
		goto rutu_1;
		}
	else
		{
		goto rlnu_0;
		}

rlnu_0:
	pU = pU0;
	sdu = sdu0;

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nn4 = n%4;
	n4 = n - nn4;

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		if(nn4!=0)
			{
			idx = n4;
			kernel_strsm_nn_rl_one_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, m-ii, nn4);
			kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
			}
		for(jj=0; jj<n4-3; jj+=4)
			{
			idx = n4-jj-4;
			kernel_strsm_nn_rl_one_4x4_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda);
			kernel_spack_nn_4_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4);
			}
		}
	if(ii<m)
		{
		goto rlnu_0_left_4;
		}
	goto rlnu_0_return;

rlnu_0_left_4:
	if(nn4!=0)
		{
		idx = n4;
		kernel_strsm_nn_rl_one_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, m-ii, nn4);
		kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	for(jj=0; jj<n4-3; jj+=4)
		{
		idx = n4-jj-4;
		kernel_strsm_nn_rl_one_4x4_vs_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+(idx+4)+idx*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, m-ii, 4);
		kernel_spack_nn_4_vs_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	goto rlnu_0_return;

rlnu_0_return:
	return;



/************************************************
* rltn
************************************************/
rltn:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 0;
		goto rltn_1;
		}
	else
		{
		goto rltn_0;
		}

rltn_0:
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<n; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	ii = 0;
	for(ii=0; ii<m-3; ii+=4)
		{
		for(jj=0; jj<n-3; jj+=4)
			{
			kernel_strsm_nt_rl_inv_4x4_lib4cccc(jj, pU, A+jj, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, dA+jj);
			kernel_spack_nn_4_lib4(4, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		if(jj<n)
			{
			kernel_strsm_nt_rl_inv_4x4_vs_lib4cccc(jj, pU, A+jj, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, dA+jj, m-ii, n-jj);
//			kernel_spack_nn_4_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		}
	if(ii<m)
		{
		goto rltn_0_left_4;
		}
	goto rltn_0_return;

rltn_0_left_4:
	for(jj=0; jj<n; jj+=4)
		{
		kernel_strsm_nt_rl_inv_4x4_vs_lib4cccc(jj, pU, A+jj, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, dA+jj, m-ii, n-jj);
		kernel_spack_nn_4_vs_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4, m-ii);
		}
goto rltn_0_return;

rltn_0_return:
	return;



rltn_1:
	n1 = (n+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, n1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, n1, n1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, n, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, n, n, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;
	dB = sB.dA;

	if(pack_tran) // upper to lower
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(ii+4, A+ii*lda, lda, pB+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_tn_4_vs_lib4(n, A+ii*lda, lda, pB+ii*sdb, n-ii);
			}
		}
	else // lower to lower
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(ii+4, A+ii, lda, pB+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_nn_4_vs_lib4(n, A+ii, lda, pB+ii*sdb, n-ii);
			}
		}

	for(ii=0; ii<n; ii++)
		dB[ii] = 1.0/A[ii+ii*lda];

	ii = 0;
	for(ii=0; ii<m-3; ii+=4)
		{
		for(jj=0; jj<n-3; jj+=4)
			{
			kernel_strsm_nt_rl_inv_4x4_lib44cc4(jj, pU, pB+jj*sdb, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, pB+jj*ps_4+jj*sdb, dB+jj);
			kernel_spack_nn_4_lib4(4, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		if(jj<n)
			{
			kernel_strsm_nt_rl_inv_4x4_vs_lib44cc4(jj, pU, pB+jj*sdb, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, pB+jj*ps_4+jj*sdb, dB+jj, m-ii, n-jj);
//			kernel_spack_nn_4_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		}
	if(ii<m)
		{
		goto rltn_1_left_4;
		}
	goto rltn_1_return;

rltn_1_left_4:
	for(jj=0; jj<n; jj+=4)
		{
		kernel_strsm_nt_rl_inv_4x4_vs_lib44cc4(jj, pU, pB+jj*sdb, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, pB+jj*ps_4+jj*sdb, dB+jj, m-ii, n-jj);
		kernel_spack_nn_4_vs_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4, m-ii);
		}
goto rltn_1_return;

rltn_1_return:
	free(mem);
	return;



/************************************************
* rltu
************************************************/
rltu:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 0;
		goto rltu_1;
		}
	else
		{
		goto rltu_0;
		}

rltu_0:
	pU = pU0;
	sdu = sdu0;

	ii = 0;
	for(ii=0; ii<m-3; ii+=4)
		{
		for(jj=0; jj<n-3; jj+=4)
			{
			kernel_strsm_nt_rl_one_4x4_lib4cccc(jj, pU, A+jj, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda);
			kernel_spack_nn_4_lib4(4, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		if(jj<n)
			{
			kernel_strsm_nt_rl_one_4x4_vs_lib4cccc(jj, pU, A+jj, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, m-ii, n-jj);
//			kernel_spack_nn_4_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		}
	if(ii<m)
		{
		goto rltu_0_left_4;
		}
	goto rltu_0_return;

rltu_0_left_4:
	for(jj=0; jj<n; jj+=4)
		{
		kernel_strsm_nt_rl_one_4x4_vs_lib4cccc(jj, pU, A+jj, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, m-ii, n-jj);
		kernel_spack_nn_4_vs_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4, m-ii);
		}
goto rltu_0_return;

rltu_0_return:
	return;



rltu_1:
	n1 = (n+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, n1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, n1, n1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, n, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, n, n, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;

	if(pack_tran) // upper to lower
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(ii+4, A+ii*lda, lda, pB+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_tn_4_vs_lib4(n, A+ii*lda, lda, pB+ii*sdb, n-ii);
			}
		}
	else // lower to lower
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(ii+4, A+ii, lda, pB+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_nn_4_vs_lib4(n, A+ii, lda, pB+ii*sdb, n-ii);
			}
		}

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		for(jj=0; jj<n-3; jj+=4)
			{
			kernel_strsm_nt_rl_one_4x4_lib44cc4(jj, pU, pB+jj*sdb, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, pB+jj*ps_4+jj*sdb);
			kernel_spack_nn_4_lib4(4, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		if(jj<n)
			{
			kernel_strsm_nt_rl_one_4x4_vs_lib44cc4(jj, pU, pB+jj*sdb, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, pB+jj*ps_4+jj*sdb, m-ii, n-jj);
//			kernel_spack_nn_4_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		}
	if(ii<m)
		{
		goto rltu_1_left_4;
		}
	goto rltu_1_return;

rltu_1_left_4:
	for(jj=0; jj<n; jj+=4)
		{
		kernel_strsm_nt_rl_one_4x4_vs_lib44cc4(jj, pU, pB+jj*sdb, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, pB+jj*ps_4+jj*sdb, m-ii, n-jj);
		kernel_spack_nn_4_vs_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4, m-ii);
		}
goto rltu_1_return;

rltu_1_return:
	free(mem);
	return;



/************************************************
* runn
************************************************/
runn:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 1;
		goto rltn_1;
		}
	else
		{
		goto runn_0;
		}



runn_0:
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<n; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	ii = 0;
	for(ii=0; ii<m-3; ii+=4)
		{
		for(jj=0; jj<n-3; jj+=4)
			{
			kernel_strsm_nn_ru_inv_4x4_lib4cccc(jj, pU, A+jj*lda, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, dA+jj);
			kernel_spack_nn_4_lib4(4, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		if(jj<n)
			{
			kernel_strsm_nn_ru_inv_4x4_vs_lib4cccc(jj, pU, A+jj*lda, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, dA+jj, m-ii, n-jj);
//			kernel_spack_nn_4_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		}
	if(ii<m)
		{
		goto runn_0_left_4;
		}
	goto runn_0_return;

runn_0_left_4:
	for(jj=0; jj<n; jj+=4)
		{
		kernel_strsm_nn_ru_inv_4x4_vs_lib4cccc(jj, pU, A+jj*lda, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, dA+jj, m-ii, n-jj);
		kernel_spack_nn_4_vs_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4, m-ii);
		}
goto runn_0_return;

runn_0_return:
	return;






/************************************************
* runu
************************************************/
runu:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 1;
		goto rltu_1;
		}
	else
		{
		goto runu_0;
		}



runu_0:
	pU = pU0;
	sdu = sdu0;

	ii = 0;
	for(ii=0; ii<m-3; ii+=4)
		{
		for(jj=0; jj<n-3; jj+=4)
			{
			kernel_strsm_nn_ru_one_4x4_lib4cccc(jj, pU, A+jj*lda, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda);
			kernel_spack_nn_4_lib4(4, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		if(jj<n)
			{
			kernel_strsm_nn_ru_one_4x4_vs_lib4cccc(jj, pU, A+jj*lda, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, m-ii, n-jj);
//			kernel_spack_nn_4_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4);
			}
		}
	if(ii<m)
		{
		goto runu_0_left_4;
		}
	goto runu_0_return;

runu_0_left_4:
	for(jj=0; jj<n; jj+=4)
		{
		kernel_strsm_nn_ru_one_4x4_vs_lib4cccc(jj, pU, A+jj*lda, lda, alpha, B+ii+jj*ldb, ldb, B+ii+jj*ldb, ldb, A+jj+jj*lda, lda, m-ii, n-jj);
		kernel_spack_nn_4_vs_lib4(n-jj, B+ii+jj*ldb, ldb, pU+jj*ps_4, m-ii);
		}
goto runu_0_return;

runu_0_return:
	return;






/************************************************
* rutn
************************************************/
rutn:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 0;
		goto rutn_1;
		}
	else
		{
		goto rutn_0;
		}



rutn_0:
	pU = pU0;
	sdu = sdu0;
	dA = pd0;

	for(ii=0; ii<n; ii++)
		dA[ii] = 1.0/A[ii+ii*lda];

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nn4 = n%4;
	n4 = n - nn4;

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		if(nn4!=0)
			{
			idx = n4;
			kernel_strsm_nt_ru_inv_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx, m-ii, nn4);
			kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
			}
		for(jj=0; jj<n4-3; jj+=4)
			{
			idx = n4-jj-4;
			kernel_strsm_nt_ru_inv_4x4_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx);
			kernel_spack_nn_4_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4);
			}
		}
	if(ii<m)
		{
		goto rutn_0_left_4;
		}
	goto rutn_0_return;

rutn_0_left_4:
	if(nn4!=0)
		{
		idx = n4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx, m-ii, nn4);
		kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	for(jj=0; jj<n4-3; jj+=4)
		{
		idx = n4-jj-4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, dA+idx, m-ii, 4);
		kernel_spack_nn_4_vs_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	goto rutn_0_return;

rutn_0_return:
	return;



rutn_1:
	n1 = (n+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, n1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, n1, n1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, n, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, n, n, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;
	dB = sB.dA;

	if(pack_tran) // lower to upper
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_tn_4_vs_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, n-ii);
			}
		}
	else // upper to upper
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_nn_4_vs_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, n-ii);
			}
		}

	for(ii=0; ii<n; ii++)
		dB[ii] = 1.0/A[ii+ii*lda];

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nn4 = n%4;
	n4 = n - nn4;

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		if(nn4!=0)
			{
			idx = n4;
			kernel_strsm_nt_ru_inv_4x4_vs_lib44cc4(0, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, dB+idx, m-ii, nn4);
			kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
			}
		for(jj=0; jj<n4-3; jj+=4)
			{
			idx = n4-jj-4;
			kernel_strsm_nt_ru_inv_4x4_lib44cc4(jj+nn4, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, dB+idx);
			kernel_spack_nn_4_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4);
			}
		}
	if(ii<m)
		{
		goto rutn_1_left_4;
		}
	goto rutn_1_return;

rutn_1_left_4:
	if(nn4!=0)
		{
		idx = n4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib44cc4(0, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, dB+idx, m-ii, nn4);
		kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	for(jj=0; jj<n4-3; jj+=4)
		{
		idx = n4-jj-4;
		kernel_strsm_nt_ru_inv_4x4_vs_lib44cc4(jj+nn4, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, dB+idx, m-ii, 4);
		kernel_spack_nn_4_vs_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	goto rutn_1_return;

rutn_1_return:
	free(mem);
	return;



/************************************************
* rutu
************************************************/
rutu:
	if(m>=12 | n>=12 | n>K_MAX_STACK)
		{
		pack_tran = 0;
		goto rutu_1;
		}
	else
		{
		goto rutu_0;
		}



rutu_0:
	pU = pU0;
	sdu = sdu0;

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nn4 = n%4;
	n4 = n - nn4;

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		if(nn4!=0)
			{
			idx = n4;
			kernel_strsm_nt_ru_one_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, m-ii, nn4);
			kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
			}
		for(jj=0; jj<n4-3; jj+=4)
			{
			idx = n4-jj-4;
			kernel_strsm_nt_ru_one_4x4_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda);
			kernel_spack_nn_4_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4);
			}
		}
	if(ii<m)
		{
		goto rutu_0_left_4;
		}
	goto rutu_0_return;

rutu_0_left_4:
	if(nn4!=0)
		{
		idx = n4;
		kernel_strsm_nt_ru_one_4x4_vs_lib4cccc(0, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, m-ii, nn4);
		kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	for(jj=0; jj<n4-3; jj+=4)
		{
		idx = n4-jj-4;
		kernel_strsm_nt_ru_one_4x4_vs_lib4cccc(jj+nn4, pU+(idx+4)*ps_4, A+idx+(idx+4)*lda, lda, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, A+idx+idx*lda, lda, m-ii, 4);
		kernel_spack_nn_4_vs_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	goto rutu_0_return;

rutu_0_return:
	return;



rutu_1:
	n1 = (n+128-1)/128*128;
	sA_size = blasfeo_pm_memsize_smat(ps_4, m_kernel, n1);
	sB_size = blasfeo_pm_memsize_smat(ps_4, n1, n1);
	mem = malloc(sA_size+sB_size+64);
	blasfeo_align_64_byte(mem, (void **) &mem_align);
	blasfeo_pm_create_smat(ps_4, m_kernel, n, &sA, (void *) mem_align);
	blasfeo_pm_create_smat(ps_4, n, n, &sB, (void *) (mem_align+sA_size));

	pU = sA.pA;
	sdu = sA.cn;
	pB = sB.pA;
	sdb = sB.cn;

	if(pack_tran) // lower to upper
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_tn_4_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_tn_4_vs_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, n-ii);
			}
		}
	else // upper to upper
		{
		for(ii=0; ii<n-3; ii+=4)
			{
			kernel_spack_nn_4_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb);
			}
		if(ii<n)
			{
			kernel_spack_nn_4_vs_lib4(n-ii, A+ii+ii*lda, lda, pB+ii*ps_4+ii*sdb, n-ii);
			}
		}

	// XXX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	nn4 = n%4;
	n4 = n - nn4;

	ii = 0;
	for(; ii<m-3; ii+=4)
		{
		if(nn4!=0)
			{
			idx = n4;
			kernel_strsm_nt_ru_one_4x4_vs_lib44cc4(0, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, m-ii, nn4);
			kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
			}
		for(jj=0; jj<n4-3; jj+=4)
			{
			idx = n4-jj-4;
			kernel_strsm_nt_ru_one_4x4_lib44cc4(jj+nn4, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4);
			kernel_spack_nn_4_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4);
			}
		}
	if(ii<m)
		{
		goto rutu_1_left_4;
		}
	goto rutu_1_return;

rutu_1_left_4:
	if(nn4!=0)
		{
		idx = n4;
		kernel_strsm_nt_ru_one_4x4_vs_lib44cc4(0, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, m-ii, nn4);
		kernel_spack_nn_4_vs_lib4(nn4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	for(jj=0; jj<n4-3; jj+=4)
		{
		idx = n4-jj-4;
		kernel_strsm_nt_ru_one_4x4_vs_lib44cc4(jj+nn4, pU+(idx+4)*ps_4, pB+idx*sdb+(idx+4)*ps_4, alpha, B+ii+idx*ldb, ldb, B+ii+idx*ldb, ldb, pB+idx*sdb+idx*ps_4, m-ii, 4);
		kernel_spack_nn_4_vs_lib4(4, B+ii+idx*ldb, ldb, pU+idx*ps_4, m-ii);
		}
	goto rutu_1_return;

rutu_1_return:
	free(mem);
	return;



	}

