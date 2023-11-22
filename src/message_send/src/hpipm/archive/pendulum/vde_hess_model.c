/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High-Performance Interior Point Method.                                                *
* Copyright (C) 2017-2018 by Gianluca Frison.                                                     *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* This program is free software: you can redistribute it and/or modify                            *
* it under the terms of the GNU General Public License as published by                            *
* the Free Software Foundation, either version 3 of the License, or                               *
* (at your option) any later version                                                              *.
*                                                                                                 *
* This program is distributed in the hope that it will be useful,                                 *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                   *
* GNU General Public License for more details.                                                    *
*                                                                                                 *
* You should have received a copy of the GNU General Public License                               *
* along with this program.  If not, see <https://www.gnu.org/licenses/>.                          *
*                                                                                                 *
* The authors designate this particular file as subject to the "Classpath" exception              *
* as provided by the authors in the LICENSE file that accompained this code.                      *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/
#define fmin(x,y) CASADI_PREFIX(fmin)(x,y)
real_t CASADI_PREFIX(fmax)(real_t x, real_t y) { return x>y ? x : y;}
#define fmax(x,y) CASADI_PREFIX(fmax)(x,y)
#endif

#define PRINTF printf
#ifndef CASADI_SYMBOL_EXPORT
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#if defined(STATIC_LINKED)
#define CASADI_SYMBOL_EXPORT
#else /* defined(STATIC_LINKED) */
#define CASADI_SYMBOL_EXPORT __declspec(dllexport)
#endif /* defined(STATIC_LINKED) */
#elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#define CASADI_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
#else /* defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__) */
#define CASADI_SYMBOL_EXPORT
#endif /* defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__) */
#endif /* CASADI_SYMBOL_EXPORT */
real_t CASADI_PREFIX(sq)(real_t x) { return x*x;}
#define sq(x) CASADI_PREFIX(sq)(x)

real_t CASADI_PREFIX(sign)(real_t x) { return x<0 ? -1 : x>0 ? 1 : x;}
#define sign(x) CASADI_PREFIX(sign)(x)

static const int CASADI_PREFIX(s0)[8] = {4, 1, 0, 4, 0, 1, 2, 3};
#define s0 CASADI_PREFIX(s0)
static const int CASADI_PREFIX(s1)[23] = {4, 4, 0, 4, 8, 12, 16, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
#define s1 CASADI_PREFIX(s1)
static const int CASADI_PREFIX(s2)[5] = {1, 1, 0, 1, 0};
#define s2 CASADI_PREFIX(s2)
static const int CASADI_PREFIX(s3)[9] = {5, 1, 0, 5, 0, 1, 2, 3, 4};
#define s3 CASADI_PREFIX(s3)
static const int CASADI_PREFIX(s4)[19] = {15, 1, 0, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
#define s4 CASADI_PREFIX(s4)
/* adjFun */
CASADI_SYMBOL_EXPORT int adjFun(const real_t** arg, real_t** res, int* iw, real_t* w, int mem) {
  real_t a0=0.;
  if (res[0]!=0) res[0][0]=a0;
  a0=arg[0] ? arg[0][1] : 0;
  real_t a1=cos(a0);
  real_t a2=sq(a1);
  real_t a3=1.0000000000000001e-01;
  a2=(a3*a2);
  real_t a4=1.1000000000000001e+00;
  a2=(a4-a2);
  real_t a5=8.0000000000000004e-01;
  a2=(a5*a2);
  real_t a6=arg[3] ? arg[3][3] : 0;
  real_t a7=(a6/a2);
  real_t a8=9.8100000000000005e+00;
  real_t a9=(a8*a7);
  real_t a10=cos(a0);
  real_t a11=(a10*a9);
  real_t a12=(a1+a1);
  real_t a13=cos(a0);
  real_t a14=-8.0000000000000016e-02;
  a13=(a14*a13);
  real_t a15=sin(a0);
  real_t a16=(a13*a15);
  real_t a17=arg[0] ? arg[0][3] : 0;
  real_t a18=sq(a17);
  real_t a19=(a16*a18);
  real_t a20=cos(a0);
  real_t a21=arg[4] ? arg[4][0] : 0;
  real_t a22=(a21*a20);
  a19=(a19+a22);
  a22=sin(a0);
  real_t a23=9.8100000000000009e-01;
  a22=(a23*a22);
  a19=(a19+a22);
  a22=sin(a0);
  a22=(a8*a22);
  a19=(a19+a22);
  a19=(a19/a2);
  a22=(a19/a2);
  real_t a24=(a22*a6);
  a24=(a5*a24);
  a24=(a3*a24);
  real_t a25=(a12*a24);
  real_t a26=sin(a0);
  real_t a27=(a26*a25);
  a11=(a11-a27);
  a27=(a23*a7);
  real_t a28=cos(a0);
  real_t a29=(a28*a27);
  a11=(a11+a29);
  a29=(a21*a7);
  real_t a30=sin(a0);
  real_t a31=(a30*a29);
  a11=(a11-a31);
  a31=(a18*a7);
  real_t a32=(a13*a31);
  real_t a33=cos(a0);
  real_t a34=(a33*a32);
  a11=(a11+a34);
  a34=(a15*a31);
  a34=(a14*a34);
  real_t a35=sin(a0);
  real_t a36=(a35*a34);
  a11=(a11-a36);
  a36=cos(a0);
  real_t a37=(a36+a36);
  real_t a38=sin(a0);
  a38=(a14*a38);
  real_t a39=sq(a17);
  real_t a40=(a38*a39);
  a40=(a40+a21);
  real_t a41=cos(a0);
  a41=(a23*a41);
  real_t a42=sin(a0);
  real_t a43=(a41*a42);
  a40=(a40+a43);
  a43=sq(a36);
  a43=(a3*a43);
  a4=(a4-a43);
  a40=(a40/a4);
  a43=(a40/a4);
  real_t a44=arg[3] ? arg[3][2] : 0;
  real_t a45=(a43*a44);
  a45=(a3*a45);
  real_t a46=(a37*a45);
  real_t a47=sin(a0);
  real_t a48=(a47*a46);
  a11=(a11-a48);
  a48=(a44/a4);
  real_t a49=(a41*a48);
  real_t a50=cos(a0);
  real_t a51=(a50*a49);
  a11=(a11+a51);
  a51=(a42*a48);
  a51=(a23*a51);
  real_t a52=sin(a0);
  real_t a53=(a52*a51);
  a11=(a11-a53);
  a53=(a39*a48);
  a53=(a14*a53);
  real_t a54=cos(a0);
  real_t a55=(a54*a53);
  a11=(a11+a55);
  if (res[0]!=0) res[0][1]=a11;
  a11=arg[3] ? arg[3][0] : 0;
  if (res[0]!=0) res[0][2]=a11;
  a11=(a17+a17);
  a55=(a16*a7);
  real_t a56=(a11*a55);
  real_t a57=(a17+a17);
  real_t a58=(a38*a48);
  real_t a59=(a57*a58);
  a56=(a56+a59);
  a59=arg[3] ? arg[3][1] : 0;
  a56=(a56+a59);
  if (res[0]!=0) res[0][3]=a56;
  a56=(a20*a7);
  a56=(a56+a48);
  if (res[0]!=0) res[0][4]=a56;
  a56=(a17+a17);
  a59=arg[1] ? arg[1][3] : 0;
  real_t a60=(a56*a59);
  real_t a61=(a7*a60);
  real_t a62=(a7/a2);
  a1=(a1+a1);
  real_t a63=sin(a0);
  real_t a64=arg[1] ? arg[1][1] : 0;
  real_t a65=(a63*a64);
  real_t a66=(a1*a65);
  a66=(a3*a66);
  a66=(a5*a66);
  real_t a67=(a62*a66);
  real_t a68=(a18*a67);
  a61=(a61-a68);
  a68=(a13*a61);
  real_t a69=sin(a0);
  real_t a70=(a69*a64);
  a70=(a14*a70);
  real_t a71=(a31*a70);
  a68=(a68-a71);
  a68=(a33*a68);
  a71=sin(a0);
  real_t a72=(a71*a64);
  a72=(a32*a72);
  a68=(a68-a72);
  a72=sin(a0);
  real_t a73=(a72*a64);
  a73=(a9*a73);
  real_t a74=(a8*a67);
  a74=(a10*a74);
  a73=(a73+a74);
  a74=cos(a0);
  real_t a75=(a74*a64);
  a75=(a25*a75);
  real_t a76=cos(a0);
  real_t a77=(a76*a64);
  real_t a78=(a13*a77);
  a70=(a15*a70);
  a78=(a78-a70);
  a70=(a18*a78);
  a60=(a16*a60);
  a70=(a70+a60);
  a60=sin(a0);
  real_t a79=(a60*a64);
  real_t a80=(a21*a79);
  a70=(a70-a80);
  a80=cos(a0);
  real_t a81=(a80*a64);
  a81=(a23*a81);
  a70=(a70+a81);
  a81=cos(a0);
  real_t a82=(a81*a64);
  a82=(a8*a82);
  a70=(a70+a82);
  a70=(a70/a2);
  a19=(a19/a2);
  a82=(a19*a66);
  a70=(a70-a82);
  a70=(a70/a2);
  a22=(a22/a2);
  a66=(a22*a66);
  a70=(a70-a66);
  a70=(a6*a70);
  a70=(a5*a70);
  a70=(a3*a70);
  a70=(a12*a70);
  a65=(a65+a65);
  a65=(a24*a65);
  a70=(a70-a65);
  a70=(a26*a70);
  a75=(a75+a70);
  a73=(a73+a75);
  a75=sin(a0);
  a70=(a75*a64);
  a70=(a27*a70);
  a65=(a23*a67);
  a65=(a28*a65);
  a70=(a70+a65);
  a73=(a73+a70);
  a70=cos(a0);
  a65=(a70*a64);
  a65=(a29*a65);
  a66=(a21*a67);
  a66=(a30*a66);
  a65=(a65-a66);
  a73=(a73+a65);
  a68=(a68-a73);
  a73=cos(a0);
  a65=(a73*a64);
  a65=(a34*a65);
  a77=(a31*a77);
  a61=(a15*a61);
  a77=(a77+a61);
  a77=(a14*a77);
  a77=(a35*a77);
  a65=(a65+a77);
  a68=(a68-a65);
  a65=cos(a0);
  a77=(a65*a64);
  a77=(a46*a77);
  a61=cos(a0);
  a66=(a61*a64);
  a66=(a14*a66);
  a82=(a39*a66);
  a17=(a17+a17);
  real_t a83=(a17*a59);
  real_t a84=(a38*a83);
  a82=(a82+a84);
  a84=cos(a0);
  real_t a85=(a84*a64);
  real_t a86=(a41*a85);
  real_t a87=sin(a0);
  real_t a88=(a87*a64);
  a88=(a23*a88);
  real_t a89=(a42*a88);
  a86=(a86-a89);
  a82=(a82+a86);
  a82=(a82/a4);
  a40=(a40/a4);
  a36=(a36+a36);
  a86=sin(a0);
  a89=(a86*a64);
  real_t a90=(a36*a89);
  a90=(a3*a90);
  real_t a91=(a40*a90);
  a82=(a82-a91);
  a82=(a82/a4);
  a43=(a43/a4);
  a91=(a43*a90);
  a82=(a82-a91);
  a82=(a44*a82);
  a82=(a3*a82);
  a82=(a37*a82);
  a89=(a89+a89);
  a89=(a45*a89);
  a82=(a82-a89);
  a82=(a47*a82);
  a77=(a77+a82);
  a68=(a68-a77);
  a77=sin(a0);
  a82=(a77*a64);
  a82=(a49*a82);
  a88=(a48*a88);
  a89=(a48/a4);
  a90=(a89*a90);
  a91=(a41*a90);
  a88=(a88+a91);
  a88=(a50*a88);
  a82=(a82+a88);
  a68=(a68-a82);
  a82=cos(a0);
  a88=(a82*a64);
  a88=(a51*a88);
  a85=(a48*a85);
  a91=(a42*a90);
  a85=(a85-a91);
  a85=(a23*a85);
  a85=(a52*a85);
  a88=(a88+a85);
  a68=(a68-a88);
  a83=(a48*a83);
  a88=(a39*a90);
  a83=(a83-a88);
  a83=(a14*a83);
  a83=(a54*a83);
  a0=sin(a0);
  a88=(a0*a64);
  a88=(a53*a88);
  a83=(a83-a88);
  a68=(a68+a83);
  a64=(a64*a68);
  a83=(a59+a59);
  a83=(a55*a83);
  a78=(a7*a78);
  a88=(a16*a67);
  a78=(a78-a88);
  a78=(a11*a78);
  a83=(a83+a78);
  a78=(a59+a59);
  a78=(a58*a78);
  a66=(a48*a66);
  a88=(a38*a90);
  a66=(a66-a88);
  a66=(a57*a66);
  a78=(a78+a66);
  a83=(a83+a78);
  a59=(a59*a83);
  a64=(a64+a59);
  if (res[1]!=0) res[1][0]=a64;
  a64=arg[1] ? arg[1][5] : 0;
  a59=(a64*a68);
  a78=arg[1] ? arg[1][7] : 0;
  a66=(a78*a83);
  a59=(a59+a66);
  if (res[1]!=0) res[1][1]=a59;
  a59=arg[1] ? arg[1][9] : 0;
  a66=(a59*a68);
  a88=arg[1] ? arg[1][11] : 0;
  a85=(a88*a83);
  a66=(a66+a85);
  if (res[1]!=0) res[1][2]=a66;
  a66=arg[1] ? arg[1][13] : 0;
  a85=(a66*a68);
  a91=arg[1] ? arg[1][15] : 0;
  real_t a92=(a91*a83);
  a85=(a85+a92);
  if (res[1]!=0) res[1][3]=a85;
  a85=arg[2] ? arg[2][1] : 0;
  a68=(a85*a68);
  a92=arg[2] ? arg[2][3] : 0;
  a83=(a92*a83);
  a68=(a68+a83);
  a79=(a7*a79);
  a67=(a20*a67);
  a79=(a79+a67);
  a79=(a79+a90);
  a68=(a68-a79);
  if (res[1]!=0) res[1][4]=a68;
  a68=(a56*a78);
  a79=(a7*a68);
  a90=(a63*a64);
  a67=(a1*a90);
  a67=(a3*a67);
  a67=(a5*a67);
  a83=(a62*a67);
  real_t a93=(a18*a83);
  a79=(a79-a93);
  a93=(a13*a79);
  real_t a94=(a69*a64);
  a94=(a14*a94);
  real_t a95=(a31*a94);
  a93=(a93-a95);
  a93=(a33*a93);
  a95=(a71*a64);
  a95=(a32*a95);
  a93=(a93-a95);
  a95=(a72*a64);
  a95=(a9*a95);
  real_t a96=(a8*a83);
  a96=(a10*a96);
  a95=(a95+a96);
  a96=(a74*a64);
  a96=(a25*a96);
  real_t a97=(a76*a64);
  real_t a98=(a13*a97);
  a94=(a15*a94);
  a98=(a98-a94);
  a94=(a18*a98);
  a68=(a16*a68);
  a94=(a94+a68);
  a68=(a60*a64);
  real_t a99=(a21*a68);
  a94=(a94-a99);
  a99=(a80*a64);
  a99=(a23*a99);
  a94=(a94+a99);
  a99=(a81*a64);
  a99=(a8*a99);
  a94=(a94+a99);
  a94=(a94/a2);
  a99=(a19*a67);
  a94=(a94-a99);
  a94=(a94/a2);
  a67=(a22*a67);
  a94=(a94-a67);
  a94=(a6*a94);
  a94=(a5*a94);
  a94=(a3*a94);
  a94=(a12*a94);
  a90=(a90+a90);
  a90=(a24*a90);
  a94=(a94-a90);
  a94=(a26*a94);
  a96=(a96+a94);
  a95=(a95+a96);
  a96=(a75*a64);
  a96=(a27*a96);
  a94=(a23*a83);
  a94=(a28*a94);
  a96=(a96+a94);
  a95=(a95+a96);
  a96=(a70*a64);
  a96=(a29*a96);
  a94=(a21*a83);
  a94=(a30*a94);
  a96=(a96-a94);
  a95=(a95+a96);
  a93=(a93-a95);
  a95=(a73*a64);
  a95=(a34*a95);
  a97=(a31*a97);
  a79=(a15*a79);
  a97=(a97+a79);
  a97=(a14*a97);
  a97=(a35*a97);
  a95=(a95+a97);
  a93=(a93-a95);
  a95=(a65*a64);
  a95=(a46*a95);
  a97=(a61*a64);
  a97=(a14*a97);
  a79=(a39*a97);
  a96=(a17*a78);
  a94=(a38*a96);
  a79=(a79+a94);
  a94=(a84*a64);
  a90=(a41*a94);
  a67=(a87*a64);
  a67=(a23*a67);
  a99=(a42*a67);
  a90=(a90-a99);
  a79=(a79+a90);
  a79=(a79/a4);
  a90=(a86*a64);
  a99=(a36*a90);
  a99=(a3*a99);
  real_t a100=(a40*a99);
  a79=(a79-a100);
  a79=(a79/a4);
  a100=(a43*a99);
  a79=(a79-a100);
  a79=(a44*a79);
  a79=(a3*a79);
  a79=(a37*a79);
  a90=(a90+a90);
  a90=(a45*a90);
  a79=(a79-a90);
  a79=(a47*a79);
  a95=(a95+a79);
  a93=(a93-a95);
  a95=(a77*a64);
  a95=(a49*a95);
  a67=(a48*a67);
  a99=(a89*a99);
  a79=(a41*a99);
  a67=(a67+a79);
  a67=(a50*a67);
  a95=(a95+a67);
  a93=(a93-a95);
  a95=(a82*a64);
  a95=(a51*a95);
  a94=(a48*a94);
  a67=(a42*a99);
  a94=(a94-a67);
  a94=(a23*a94);
  a94=(a52*a94);
  a95=(a95+a94);
  a93=(a93-a95);
  a96=(a48*a96);
  a95=(a39*a99);
  a96=(a96-a95);
  a96=(a14*a96);
  a96=(a54*a96);
  a95=(a0*a64);
  a95=(a53*a95);
  a96=(a96-a95);
  a93=(a93+a96);
  a64=(a64*a93);
  a96=(a78+a78);
  a96=(a55*a96);
  a98=(a7*a98);
  a95=(a16*a83);
  a98=(a98-a95);
  a98=(a11*a98);
  a96=(a96+a98);
  a98=(a78+a78);
  a98=(a58*a98);
  a97=(a48*a97);
  a95=(a38*a99);
  a97=(a97-a95);
  a97=(a57*a97);
  a98=(a98+a97);
  a96=(a96+a98);
  a78=(a78*a96);
  a64=(a64+a78);
  if (res[1]!=0) res[1][5]=a64;
  a64=(a59*a93);
  a78=(a88*a96);
  a64=(a64+a78);
  if (res[1]!=0) res[1][6]=a64;
  a64=(a66*a93);
  a78=(a91*a96);
  a64=(a64+a78);
  if (res[1]!=0) res[1][7]=a64;
  a93=(a85*a93);
  a96=(a92*a96);
  a93=(a93+a96);
  a68=(a7*a68);
  a83=(a20*a83);
  a68=(a68+a83);
  a68=(a68+a99);
  a93=(a93-a68);
  if (res[1]!=0) res[1][8]=a93;
  a93=(a56*a88);
  a68=(a7*a93);
  a99=(a63*a59);
  a83=(a1*a99);
  a83=(a3*a83);
  a83=(a5*a83);
  a96=(a62*a83);
  a64=(a18*a96);
  a68=(a68-a64);
  a64=(a13*a68);
  a78=(a69*a59);
  a78=(a14*a78);
  a98=(a31*a78);
  a64=(a64-a98);
  a64=(a33*a64);
  a98=(a71*a59);
  a98=(a32*a98);
  a64=(a64-a98);
  a98=(a72*a59);
  a98=(a9*a98);
  a97=(a8*a96);
  a97=(a10*a97);
  a98=(a98+a97);
  a97=(a74*a59);
  a97=(a25*a97);
  a95=(a76*a59);
  a94=(a13*a95);
  a78=(a15*a78);
  a94=(a94-a78);
  a78=(a18*a94);
  a93=(a16*a93);
  a78=(a78+a93);
  a93=(a60*a59);
  a67=(a21*a93);
  a78=(a78-a67);
  a67=(a80*a59);
  a67=(a23*a67);
  a78=(a78+a67);
  a67=(a81*a59);
  a67=(a8*a67);
  a78=(a78+a67);
  a78=(a78/a2);
  a67=(a19*a83);
  a78=(a78-a67);
  a78=(a78/a2);
  a83=(a22*a83);
  a78=(a78-a83);
  a78=(a6*a78);
  a78=(a5*a78);
  a78=(a3*a78);
  a78=(a12*a78);
  a99=(a99+a99);
  a99=(a24*a99);
  a78=(a78-a99);
  a78=(a26*a78);
  a97=(a97+a78);
  a98=(a98+a97);
  a97=(a75*a59);
  a97=(a27*a97);
  a78=(a23*a96);
  a78=(a28*a78);
  a97=(a97+a78);
  a98=(a98+a97);
  a97=(a70*a59);
  a97=(a29*a97);
  a78=(a21*a96);
  a78=(a30*a78);
  a97=(a97-a78);
  a98=(a98+a97);
  a64=(a64-a98);
  a98=(a73*a59);
  a98=(a34*a98);
  a95=(a31*a95);
  a68=(a15*a68);
  a95=(a95+a68);
  a95=(a14*a95);
  a95=(a35*a95);
  a98=(a98+a95);
  a64=(a64-a98);
  a98=(a65*a59);
  a98=(a46*a98);
  a95=(a61*a59);
  a95=(a14*a95);
  a68=(a39*a95);
  a97=(a17*a88);
  a78=(a38*a97);
  a68=(a68+a78);
  a78=(a84*a59);
  a99=(a41*a78);
  a83=(a87*a59);
  a83=(a23*a83);
  a67=(a42*a83);
  a99=(a99-a67);
  a68=(a68+a99);
  a68=(a68/a4);
  a99=(a86*a59);
  a67=(a36*a99);
  a67=(a3*a67);
  a79=(a40*a67);
  a68=(a68-a79);
  a68=(a68/a4);
  a79=(a43*a67);
  a68=(a68-a79);
  a68=(a44*a68);
  a68=(a3*a68);
  a68=(a37*a68);
  a99=(a99+a99);
  a99=(a45*a99);
  a68=(a68-a99);
  a68=(a47*a68);
  a98=(a98+a68);
  a64=(a64-a98);
  a98=(a77*a59);
  a98=(a49*a98);
  a83=(a48*a83);
  a67=(a89*a67);
  a68=(a41*a67);
  a83=(a83+a68);
  a83=(a50*a83);
  a98=(a98+a83);
  a64=(a64-a98);
  a98=(a82*a59);
  a98=(a51*a98);
  a78=(a48*a78);
  a83=(a42*a67);
  a78=(a78-a83);
  a78=(a23*a78);
  a78=(a52*a78);
  a98=(a98+a78);
  a64=(a64-a98);
  a97=(a48*a97);
  a98=(a39*a67);
  a97=(a97-a98);
  a97=(a14*a97);
  a97=(a54*a97);
  a98=(a0*a59);
  a98=(a53*a98);
  a97=(a97-a98);
  a64=(a64+a97);
  a59=(a59*a64);
  a97=(a88+a88);
  a97=(a55*a97);
  a94=(a7*a94);
  a98=(a16*a96);
  a94=(a94-a98);
  a94=(a11*a94);
  a97=(a97+a94);
  a94=(a88+a88);
  a94=(a58*a94);
  a95=(a48*a95);
  a98=(a38*a67);
  a95=(a95-a98);
  a95=(a57*a95);
  a94=(a94+a95);
  a97=(a97+a94);
  a88=(a88*a97);
  a59=(a59+a88);
  if (res[1]!=0) res[1][9]=a59;
  a59=(a66*a64);
  a88=(a91*a97);
  a59=(a59+a88);
  if (res[1]!=0) res[1][10]=a59;
  a64=(a85*a64);
  a97=(a92*a97);
  a64=(a64+a97);
  a93=(a7*a93);
  a96=(a20*a96);
  a93=(a93+a96);
  a93=(a93+a67);
  a64=(a64-a93);
  if (res[1]!=0) res[1][11]=a64;
  a64=(a56*a91);
  a93=(a7*a64);
  a67=(a63*a66);
  a96=(a1*a67);
  a96=(a3*a96);
  a96=(a5*a96);
  a97=(a62*a96);
  a59=(a18*a97);
  a93=(a93-a59);
  a59=(a13*a93);
  a88=(a69*a66);
  a88=(a14*a88);
  a94=(a31*a88);
  a59=(a59-a94);
  a59=(a33*a59);
  a94=(a71*a66);
  a94=(a32*a94);
  a59=(a59-a94);
  a94=(a72*a66);
  a94=(a9*a94);
  a95=(a8*a97);
  a95=(a10*a95);
  a94=(a94+a95);
  a95=(a74*a66);
  a95=(a25*a95);
  a98=(a76*a66);
  a78=(a13*a98);
  a88=(a15*a88);
  a78=(a78-a88);
  a88=(a18*a78);
  a64=(a16*a64);
  a88=(a88+a64);
  a64=(a60*a66);
  a83=(a21*a64);
  a88=(a88-a83);
  a83=(a80*a66);
  a83=(a23*a83);
  a88=(a88+a83);
  a83=(a81*a66);
  a83=(a8*a83);
  a88=(a88+a83);
  a88=(a88/a2);
  a83=(a19*a96);
  a88=(a88-a83);
  a88=(a88/a2);
  a96=(a22*a96);
  a88=(a88-a96);
  a88=(a6*a88);
  a88=(a5*a88);
  a88=(a3*a88);
  a88=(a12*a88);
  a67=(a67+a67);
  a67=(a24*a67);
  a88=(a88-a67);
  a88=(a26*a88);
  a95=(a95+a88);
  a94=(a94+a95);
  a95=(a75*a66);
  a95=(a27*a95);
  a88=(a23*a97);
  a88=(a28*a88);
  a95=(a95+a88);
  a94=(a94+a95);
  a95=(a70*a66);
  a95=(a29*a95);
  a88=(a21*a97);
  a88=(a30*a88);
  a95=(a95-a88);
  a94=(a94+a95);
  a59=(a59-a94);
  a94=(a73*a66);
  a94=(a34*a94);
  a98=(a31*a98);
  a93=(a15*a93);
  a98=(a98+a93);
  a98=(a14*a98);
  a98=(a35*a98);
  a94=(a94+a98);
  a59=(a59-a94);
  a94=(a65*a66);
  a94=(a46*a94);
  a98=(a61*a66);
  a98=(a14*a98);
  a93=(a39*a98);
  a95=(a17*a91);
  a88=(a38*a95);
  a93=(a93+a88);
  a88=(a84*a66);
  a67=(a41*a88);
  a96=(a87*a66);
  a96=(a23*a96);
  a83=(a42*a96);
  a67=(a67-a83);
  a93=(a93+a67);
  a93=(a93/a4);
  a67=(a86*a66);
  a83=(a36*a67);
  a83=(a3*a83);
  a68=(a40*a83);
  a93=(a93-a68);
  a93=(a93/a4);
  a68=(a43*a83);
  a93=(a93-a68);
  a93=(a44*a93);
  a93=(a3*a93);
  a93=(a37*a93);
  a67=(a67+a67);
  a67=(a45*a67);
  a93=(a93-a67);
  a93=(a47*a93);
  a94=(a94+a93);
  a59=(a59-a94);
  a94=(a77*a66);
  a94=(a49*a94);
  a96=(a48*a96);
  a83=(a89*a83);
  a93=(a41*a83);
  a96=(a96+a93);
  a96=(a50*a96);
  a94=(a94+a96);
  a59=(a59-a94);
  a94=(a82*a66);
  a94=(a51*a94);
  a88=(a48*a88);
  a96=(a42*a83);
  a88=(a88-a96);
  a88=(a23*a88);
  a88=(a52*a88);
  a94=(a94+a88);
  a59=(a59-a94);
  a95=(a48*a95);
  a94=(a39*a83);
  a95=(a95-a94);
  a95=(a14*a95);
  a95=(a54*a95);
  a94=(a0*a66);
  a94=(a53*a94);
  a95=(a95-a94);
  a59=(a59+a95);
  a66=(a66*a59);
  a95=(a91+a91);
  a95=(a55*a95);
  a78=(a7*a78);
  a94=(a16*a97);
  a78=(a78-a94);
  a78=(a11*a78);
  a95=(a95+a78);
  a78=(a91+a91);
  a78=(a58*a78);
  a98=(a48*a98);
  a94=(a38*a83);
  a98=(a98-a94);
  a98=(a57*a98);
  a78=(a78+a98);
  a95=(a95+a78);
  a91=(a91*a95);
  a66=(a66+a91);
  if (res[1]!=0) res[1][12]=a66;
  a59=(a85*a59);
  a95=(a92*a95);
  a59=(a59+a95);
  a64=(a7*a64);
  a97=(a20*a97);
  a64=(a64+a97);
  a64=(a64+a83);
  a59=(a59-a64);
  if (res[1]!=0) res[1][13]=a59;
  a56=(a56*a92);
  a59=(a7*a56);
  a63=(a63*a85);
  a1=(a1*a63);
  a1=(a3*a1);
  a1=(a5*a1);
  a62=(a62*a1);
  a64=(a18*a62);
  a59=(a59-a64);
  a64=(a13*a59);
  a69=(a69*a85);
  a69=(a14*a69);
  a83=(a31*a69);
  a64=(a64-a83);
  a33=(a33*a64);
  a71=(a71*a85);
  a32=(a32*a71);
  a33=(a33-a32);
  a72=(a72*a85);
  a9=(a9*a72);
  a72=(a8*a62);
  a10=(a10*a72);
  a9=(a9+a10);
  a74=(a74*a85);
  a25=(a25*a74);
  a76=(a76*a85);
  a13=(a13*a76);
  a69=(a15*a69);
  a13=(a13-a69);
  a18=(a18*a13);
  a56=(a16*a56);
  a18=(a18+a56);
  a60=(a60*a85);
  a56=(a21*a60);
  a56=(a20-a56);
  a18=(a18+a56);
  a80=(a80*a85);
  a80=(a23*a80);
  a18=(a18+a80);
  a81=(a81*a85);
  a8=(a8*a81);
  a18=(a18+a8);
  a18=(a18/a2);
  a19=(a19*a1);
  a18=(a18-a19);
  a18=(a18/a2);
  a22=(a22*a1);
  a18=(a18-a22);
  a6=(a6*a18);
  a5=(a5*a6);
  a5=(a3*a5);
  a12=(a12*a5);
  a63=(a63+a63);
  a24=(a24*a63);
  a12=(a12-a24);
  a26=(a26*a12);
  a25=(a25+a26);
  a9=(a9+a25);
  a75=(a75*a85);
  a27=(a27*a75);
  a75=(a23*a62);
  a28=(a28*a75);
  a27=(a27+a28);
  a9=(a9+a27);
  a70=(a70*a85);
  a29=(a29*a70);
  a21=(a21*a62);
  a21=(a7-a21);
  a30=(a30*a21);
  a29=(a29+a30);
  a9=(a9+a29);
  a33=(a33-a9);
  a73=(a73*a85);
  a34=(a34*a73);
  a31=(a31*a76);
  a15=(a15*a59);
  a31=(a31+a15);
  a31=(a14*a31);
  a35=(a35*a31);
  a34=(a34+a35);
  a33=(a33-a34);
  a65=(a65*a85);
  a46=(a46*a65);
  a61=(a61*a85);
  a61=(a14*a61);
  a65=(a39*a61);
  a17=(a17*a92);
  a34=(a38*a17);
  a65=(a65+a34);
  a34=1.;
  a65=(a65+a34);
  a84=(a84*a85);
  a34=(a41*a84);
  a87=(a87*a85);
  a87=(a23*a87);
  a35=(a42*a87);
  a34=(a34-a35);
  a65=(a65+a34);
  a65=(a65/a4);
  a86=(a86*a85);
  a36=(a36*a86);
  a36=(a3*a36);
  a40=(a40*a36);
  a65=(a65-a40);
  a65=(a65/a4);
  a43=(a43*a36);
  a65=(a65-a43);
  a44=(a44*a65);
  a3=(a3*a44);
  a37=(a37*a3);
  a86=(a86+a86);
  a45=(a45*a86);
  a37=(a37-a45);
  a47=(a47*a37);
  a46=(a46+a47);
  a33=(a33-a46);
  a77=(a77*a85);
  a49=(a49*a77);
  a87=(a48*a87);
  a89=(a89*a36);
  a41=(a41*a89);
  a87=(a87+a41);
  a50=(a50*a87);
  a49=(a49+a50);
  a33=(a33-a49);
  a82=(a82*a85);
  a51=(a51*a82);
  a84=(a48*a84);
  a42=(a42*a89);
  a84=(a84-a42);
  a23=(a23*a84);
  a52=(a52*a23);
  a51=(a51+a52);
  a33=(a33-a51);
  a17=(a48*a17);
  a39=(a39*a89);
  a17=(a17-a39);
  a14=(a14*a17);
  a54=(a54*a14);
  a0=(a0*a85);
  a53=(a53*a0);
  a54=(a54-a53);
  a33=(a33+a54);
  a85=(a85*a33);
  a33=(a92+a92);
  a55=(a55*a33);
  a13=(a7*a13);
  a16=(a16*a62);
  a13=(a13-a16);
  a11=(a11*a13);
  a55=(a55+a11);
  a11=(a92+a92);
  a58=(a58*a11);
  a48=(a48*a61);
  a38=(a38*a89);
  a48=(a48-a38);
  a57=(a57*a48);
  a58=(a58+a57);
  a55=(a55+a58);
  a92=(a92*a55);
  a85=(a85+a92);
  a7=(a7*a60);
  a20=(a20*a62);
  a7=(a7+a20);
  a7=(a7+a89);
  a85=(a85-a7);
  if (res[1]!=0) res[1][14]=a85;
  return 0;
}

CASADI_SYMBOL_EXPORT void adjFun_incref(void) {
}

CASADI_SYMBOL_EXPORT void adjFun_decref(void) {
}

CASADI_SYMBOL_EXPORT int adjFun_n_in(void) { return 5;}

CASADI_SYMBOL_EXPORT int adjFun_n_out(void) { return 2;}

CASADI_SYMBOL_EXPORT const char* adjFun_name_in(int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    case 3: return "i3";
    case 4: return "i4";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* adjFun_name_out(int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const int* adjFun_sparsity_in(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s1;
    case 2: return s0;
    case 3: return s0;
    case 4: return s2;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const int* adjFun_sparsity_out(int i) {
  switch (i) {
    case 0: return s3;
    case 1: return s4;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int adjFun_work(int *sz_arg, int* sz_res, int *sz_iw, int *sz_w) {
  if (sz_arg) *sz_arg = 5;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 101;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
