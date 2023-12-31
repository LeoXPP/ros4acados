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

#include <hpipm_s_ocp_qp_dim.h>
#include <hpipm_s_ocp_qcqp_dim.h>
#include <hpipm_aux_string.h>
#include <hpipm_aux_mem.h>



#define OCP_QCQP_DIM s_ocp_qcqp_dim
#define OCP_QP_DIM s_ocp_qp_dim
#define OCP_QP_DIM_CREATE s_ocp_qp_dim_create
#define OCP_QP_DIM_MEMSIZE s_ocp_qp_dim_memsize
#define OCP_QP_DIM_SET_NX s_ocp_qp_dim_set_nx
#define OCP_QP_DIM_SET_NU s_ocp_qp_dim_set_nu
#define OCP_QP_DIM_SET_NBX s_ocp_qp_dim_set_nbx
#define OCP_QP_DIM_SET_NBU s_ocp_qp_dim_set_nbu
#define OCP_QP_DIM_SET_NG s_ocp_qp_dim_set_ng
#define OCP_QP_DIM_SET_NS s_ocp_qp_dim_set_ns
#define OCP_QP_DIM_SET_NSBX s_ocp_qp_dim_set_nsbx
#define OCP_QP_DIM_SET_NSBU s_ocp_qp_dim_set_nsbu
#define OCP_QP_DIM_SET_NSG s_ocp_qp_dim_set_nsg



#define OCP_QCQP_DIM_STRSIZE s_ocp_qcqp_dim_strsize
#define OCP_QCQP_DIM_MEMSIZE s_ocp_qcqp_dim_memsize
#define OCP_QCQP_DIM_CREATE s_ocp_qcqp_dim_create
#define OCP_QCQP_DIM_COPY_ALL s_ocp_qcqp_dim_copy_all
#define OCP_QCQP_DIM_SET s_ocp_qcqp_dim_set
#define OCP_QCQP_DIM_SET_NX s_ocp_qcqp_dim_set_nx
#define OCP_QCQP_DIM_SET_NU s_ocp_qcqp_dim_set_nu
#define OCP_QCQP_DIM_SET_NBX s_ocp_qcqp_dim_set_nbx
#define OCP_QCQP_DIM_SET_NBU s_ocp_qcqp_dim_set_nbu
#define OCP_QCQP_DIM_SET_NG s_ocp_qcqp_dim_set_ng
#define OCP_QCQP_DIM_SET_NQ s_ocp_qcqp_dim_set_nq
#define OCP_QCQP_DIM_SET_NS s_ocp_qcqp_dim_set_ns
#define OCP_QCQP_DIM_SET_NSBX s_ocp_qcqp_dim_set_nsbx
#define OCP_QCQP_DIM_SET_NSBU s_ocp_qcqp_dim_set_nsbu
#define OCP_QCQP_DIM_SET_NSG s_ocp_qcqp_dim_set_nsg
#define OCP_QCQP_DIM_SET_NSQ s_ocp_qcqp_dim_set_nsq
#define OCP_QCQP_DIM_GET s_ocp_qcqp_dim_get
#define OCP_QCQP_DIM_GET_N s_ocp_qcqp_dim_get_N
#define OCP_QCQP_DIM_GET_NX s_ocp_qcqp_dim_get_nx
#define OCP_QCQP_DIM_GET_NU s_ocp_qcqp_dim_get_nu



#include "x_ocp_qcqp_dim.c"


