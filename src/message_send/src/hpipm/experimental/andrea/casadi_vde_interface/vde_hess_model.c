/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef CODEGEN_PREFIX
  #define NAMESPACE_CONCAT(NS, ID) _NAMESPACE_CONCAT(NS, ID)
  #define _NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else /* CODEGEN_PREFIX */
  #define CASADI_PREFIX(ID) vde_hess_model_ ## ID
#endif /* CODEGEN_PREFIX */

#include <math.h>

#ifndef real_t
#define real_t double
#endif /* real_t */

#define to_double(x) (double) x
#define to_int(x) (int) x
#define CASADI_CAST(x,y) (x) y
/* Pre-c99 compatibility */
#if __STDC_VERSION__ < 199901L
real_t CASADI_PREFIX(fmin)(real_t x, real_t y) { return x<y ? x : y;}
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
/* hessFun */
CASADI_SYMBOL_EXPORT int hessFun(const real_t** arg, real_t** res, int* iw, real_t* w, int mem) {
  real_t a0=arg[0] ? arg[0][1] : 0;
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
  real_t a8=cos(a0);
  real_t a9=(a8*a7);
  real_t a10=cos(a0);
  real_t a11=sq(a10);
  a11=(a3*a11);
  a4=(a4-a11);
  a11=arg[3] ? arg[3][2] : 0;
  real_t a12=(a11/a4);
  a9=(a9+a12);
  if (res[0]!=0) res[0][0]=a9;
  a9=0.;
  if (res[0]!=0) res[0][1]=a9;
  a9=9.8100000000000005e+00;
  real_t a13=(a9*a7);
  real_t a14=cos(a0);
  real_t a15=(a14*a13);
  real_t a16=(a1+a1);
  real_t a17=cos(a0);
  real_t a18=-8.0000000000000016e-02;
  a17=(a18*a17);
  real_t a19=sin(a0);
  real_t a20=(a17*a19);
  real_t a21=arg[0] ? arg[0][3] : 0;
  real_t a22=sq(a21);
  real_t a23=(a20*a22);
  real_t a24=arg[4] ? arg[4][0] : 0;
  real_t a25=(a24*a8);
  a23=(a23+a25);
  a25=sin(a0);
  real_t a26=9.8100000000000009e-01;
  a25=(a26*a25);
  a23=(a23+a25);
  a25=sin(a0);
  a25=(a9*a25);
  a23=(a23+a25);
  a23=(a23/a2);
  a25=(a23/a2);
  real_t a27=(a25*a6);
  a27=(a5*a27);
  a27=(a3*a27);
  real_t a28=(a16*a27);
  real_t a29=sin(a0);
  real_t a30=(a29*a28);
  a15=(a15-a30);
  a30=(a26*a7);
  real_t a31=cos(a0);
  real_t a32=(a31*a30);
  a15=(a15+a32);
  a32=(a24*a7);
  real_t a33=sin(a0);
  real_t a34=(a33*a32);
  a15=(a15-a34);
  a34=(a22*a7);
  real_t a35=(a17*a34);
  real_t a36=cos(a0);
  real_t a37=(a36*a35);
  a15=(a15+a37);
  a37=(a19*a34);
  a37=(a18*a37);
  real_t a38=sin(a0);
  real_t a39=(a38*a37);
  a15=(a15-a39);
  a39=(a10+a10);
  real_t a40=sin(a0);
  a40=(a18*a40);
  real_t a41=sq(a21);
  real_t a42=(a40*a41);
  a42=(a42+a24);
  real_t a43=cos(a0);
  a43=(a26*a43);
  real_t a44=sin(a0);
  real_t a45=(a43*a44);
  a42=(a42+a45);
  a42=(a42/a4);
  a45=(a42/a4);
  real_t a46=(a45*a11);
  a46=(a3*a46);
  real_t a47=(a39*a46);
  real_t a48=sin(a0);
  real_t a49=(a48*a47);
  a15=(a15-a49);
  a49=(a43*a12);
  real_t a50=cos(a0);
  real_t a51=(a50*a49);
  a15=(a15+a51);
  a51=(a44*a12);
  a51=(a26*a51);
  real_t a52=sin(a0);
  real_t a53=(a52*a51);
  a15=(a15-a53);
  a53=(a41*a12);
  a53=(a18*a53);
  real_t a54=cos(a0);
  real_t a55=(a54*a53);
  a15=(a15+a55);
  if (res[0]!=0) res[0][2]=a15;
  a15=arg[3] ? arg[3][0] : 0;
  if (res[0]!=0) res[0][3]=a15;
  a15=(a21+a21);
  a55=(a20*a7);
  real_t a56=(a15*a55);
  real_t a57=(a21+a21);
  real_t a58=(a40*a12);
  real_t a59=(a57*a58);
  a56=(a56+a59);
  a59=arg[3] ? arg[3][1] : 0;
  a56=(a56+a59);
  if (res[0]!=0) res[0][4]=a56;
  a56=(a21+a21);
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
  real_t a68=(a22*a67);
  a61=(a61-a68);
  a68=(a17*a61);
  real_t a69=sin(a0);
  real_t a70=(a69*a64);
  a70=(a18*a70);
  real_t a71=(a34*a70);
  a68=(a68-a71);
  a68=(a36*a68);
  a71=sin(a0);
  real_t a72=(a71*a64);
  a72=(a35*a72);
  a68=(a68-a72);
  a72=sin(a0);
  real_t a73=(a72*a64);
  a73=(a13*a73);
  real_t a74=(a9*a67);
  a74=(a14*a74);
  a73=(a73+a74);
  a74=cos(a0);
  real_t a75=(a74*a64);
  a75=(a28*a75);
  real_t a76=cos(a0);
  real_t a77=(a76*a64);
  real_t a78=(a17*a77);
  a70=(a19*a70);
  a78=(a78-a70);
  a70=(a22*a78);
  a60=(a20*a60);
  a70=(a70+a60);
  a60=sin(a0);
  real_t a79=(a60*a64);
  real_t a80=(a24*a79);
  a70=(a70-a80);
  a80=cos(a0);
  real_t a81=(a80*a64);
  a81=(a26*a81);
  a70=(a70+a81);
  a81=cos(a0);
  real_t a82=(a81*a64);
  a82=(a9*a82);
  a70=(a70+a82);
  a70=(a70/a2);
  a23=(a23/a2);
  a82=(a23*a66);
  a70=(a70-a82);
  a70=(a70/a2);
  a25=(a25/a2);
  a66=(a25*a66);
  a70=(a70-a66);
  a70=(a6*a70);
  a70=(a5*a70);
  a70=(a3*a70);
  a70=(a16*a70);
  a65=(a65+a65);
  a65=(a27*a65);
  a70=(a70-a65);
  a70=(a29*a70);
  a75=(a75+a70);
  a73=(a73+a75);
  a75=sin(a0);
  a70=(a75*a64);
  a70=(a30*a70);
  a65=(a26*a67);
  a65=(a31*a65);
  a70=(a70+a65);
  a73=(a73+a70);
  a70=cos(a0);
  a65=(a70*a64);
  a65=(a32*a65);
  a66=(a24*a67);
  a66=(a33*a66);
  a65=(a65-a66);
  a73=(a73+a65);
  a68=(a68-a73);
  a73=cos(a0);
  a65=(a73*a64);
  a65=(a37*a65);
  a77=(a34*a77);
  a61=(a19*a61);
  a77=(a77+a61);
  a77=(a18*a77);
  a77=(a38*a77);
  a65=(a65+a77);
  a68=(a68-a65);
  a65=cos(a0);
  a77=(a65*a64);
  a77=(a47*a77);
  a61=cos(a0);
  a66=(a61*a64);
  a66=(a18*a66);
  a82=(a41*a66);
  a21=(a21+a21);
  real_t a83=(a21*a59);
  real_t a84=(a40*a83);
  a82=(a82+a84);
  a84=cos(a0);
  real_t a85=(a84*a64);
  real_t a86=(a43*a85);
  real_t a87=sin(a0);
  real_t a88=(a87*a64);
  a88=(a26*a88);
  real_t a89=(a44*a88);
  a86=(a86-a89);
  a82=(a82+a86);
  a82=(a82/a4);
  a42=(a42/a4);
  a10=(a10+a10);
  a86=sin(a0);
  a89=(a86*a64);
  real_t a90=(a10*a89);
  a90=(a3*a90);
  real_t a91=(a42*a90);
  a82=(a82-a91);
  a82=(a82/a4);
  a45=(a45/a4);
  a91=(a45*a90);
  a82=(a82-a91);
  a82=(a11*a82);
  a82=(a3*a82);
  a82=(a39*a82);
  a89=(a89+a89);
  a89=(a46*a89);
  a82=(a82-a89);
  a82=(a48*a82);
  a77=(a77+a82);
  a68=(a68-a77);
  a77=sin(a0);
  a82=(a77*a64);
  a82=(a49*a82);
  a88=(a12*a88);
  a89=(a12/a4);
  a90=(a89*a90);
  a91=(a43*a90);
  a88=(a88+a91);
  a88=(a50*a88);
  a82=(a82+a88);
  a68=(a68-a82);
  a82=cos(a0);
  a88=(a82*a64);
  a88=(a51*a88);
  a85=(a12*a85);
  a91=(a44*a90);
  a85=(a85-a91);
  a85=(a26*a85);
  a85=(a52*a85);
  a88=(a88+a85);
  a68=(a68-a88);
  a83=(a12*a83);
  a88=(a41*a90);
  a83=(a83-a88);
  a83=(a18*a83);
  a83=(a54*a83);
  a0=sin(a0);
  a64=(a0*a64);
  a64=(a53*a64);
  a83=(a83-a64);
  a68=(a68+a83);
  a83=arg[1] ? arg[1][2] : 0;
  a83=(a83*a68);
  a79=(a7*a79);
  a64=(a8*a67);
  a79=(a79+a64);
  a79=(a79+a90);
  a64=arg[1] ? arg[1][0] : 0;
  a64=(a64*a79);
  a83=(a83-a64);
  if (res[1]!=0) res[1][0]=a83;
  a83=arg[1] ? arg[1][6] : 0;
  a64=(a83*a68);
  a88=arg[1] ? arg[1][4] : 0;
  a85=(a88*a79);
  a64=(a64-a85);
  if (res[1]!=0) res[1][1]=a64;
  a64=arg[1] ? arg[1][10] : 0;
  a85=(a64*a68);
  a91=arg[1] ? arg[1][8] : 0;
  real_t a92=(a91*a79);
  a85=(a85-a92);
  if (res[1]!=0) res[1][2]=a85;
  a85=arg[1] ? arg[1][14] : 0;
  a92=(a85*a68);
  real_t a93=arg[1] ? arg[1][12] : 0;
  real_t a94=(a93*a79);
  a92=(a92-a94);
  if (res[1]!=0) res[1][3]=a92;
  a92=arg[2] ? arg[2][2] : 0;
  a68=(a92*a68);
  a94=arg[2] ? arg[2][0] : 0;
  a79=(a94*a79);
  a68=(a68-a79);
  a79=(a59+a59);
  a79=(a55*a79);
  a78=(a7*a78);
  a67=(a20*a67);
  a78=(a78-a67);
  a78=(a15*a78);
  a79=(a79+a78);
  a59=(a59+a59);
  a59=(a58*a59);
  a66=(a12*a66);
  a90=(a40*a90);
  a66=(a66-a90);
  a66=(a57*a66);
  a59=(a59+a66);
  a79=(a79+a59);
  a68=(a68+a79);
  if (res[1]!=0) res[1][4]=a68;
  a68=arg[1] ? arg[1][7] : 0;
  a79=(a56*a68);
  a59=(a7*a79);
  a66=arg[1] ? arg[1][5] : 0;
  a90=(a63*a66);
  a78=(a1*a90);
  a78=(a3*a78);
  a78=(a5*a78);
  a67=(a62*a78);
  real_t a95=(a22*a67);
  a59=(a59-a95);
  a95=(a17*a59);
  real_t a96=(a69*a66);
  a96=(a18*a96);
  real_t a97=(a34*a96);
  a95=(a95-a97);
  a95=(a36*a95);
  a97=(a71*a66);
  a97=(a35*a97);
  a95=(a95-a97);
  a97=(a72*a66);
  a97=(a13*a97);
  real_t a98=(a9*a67);
  a98=(a14*a98);
  a97=(a97+a98);
  a98=(a74*a66);
  a98=(a28*a98);
  real_t a99=(a76*a66);
  real_t a100=(a17*a99);
  a96=(a19*a96);
  a100=(a100-a96);
  a96=(a22*a100);
  a79=(a20*a79);
  a96=(a96+a79);
  a79=(a60*a66);
  real_t a101=(a24*a79);
  a96=(a96-a101);
  a101=(a80*a66);
  a101=(a26*a101);
  a96=(a96+a101);
  a101=(a81*a66);
  a101=(a9*a101);
  a96=(a96+a101);
  a96=(a96/a2);
  a101=(a23*a78);
  a96=(a96-a101);
  a96=(a96/a2);
  a78=(a25*a78);
  a96=(a96-a78);
  a96=(a6*a96);
  a96=(a5*a96);
  a96=(a3*a96);
  a96=(a16*a96);
  a90=(a90+a90);
  a90=(a27*a90);
  a96=(a96-a90);
  a96=(a29*a96);
  a98=(a98+a96);
  a97=(a97+a98);
  a98=(a75*a66);
  a98=(a30*a98);
  a96=(a26*a67);
  a96=(a31*a96);
  a98=(a98+a96);
  a97=(a97+a98);
  a98=(a70*a66);
  a98=(a32*a98);
  a96=(a24*a67);
  a96=(a33*a96);
  a98=(a98-a96);
  a97=(a97+a98);
  a95=(a95-a97);
  a97=(a73*a66);
  a97=(a37*a97);
  a99=(a34*a99);
  a59=(a19*a59);
  a99=(a99+a59);
  a99=(a18*a99);
  a99=(a38*a99);
  a97=(a97+a99);
  a95=(a95-a97);
  a97=(a65*a66);
  a97=(a47*a97);
  a99=(a61*a66);
  a99=(a18*a99);
  a59=(a41*a99);
  a98=(a21*a68);
  a96=(a40*a98);
  a59=(a59+a96);
  a96=(a84*a66);
  a90=(a43*a96);
  a78=(a87*a66);
  a78=(a26*a78);
  a101=(a44*a78);
  a90=(a90-a101);
  a59=(a59+a90);
  a59=(a59/a4);
  a90=(a86*a66);
  a101=(a10*a90);
  a101=(a3*a101);
  real_t a102=(a42*a101);
  a59=(a59-a102);
  a59=(a59/a4);
  a102=(a45*a101);
  a59=(a59-a102);
  a59=(a11*a59);
  a59=(a3*a59);
  a59=(a39*a59);
  a90=(a90+a90);
  a90=(a46*a90);
  a59=(a59-a90);
  a59=(a48*a59);
  a97=(a97+a59);
  a95=(a95-a97);
  a97=(a77*a66);
  a97=(a49*a97);
  a78=(a12*a78);
  a101=(a89*a101);
  a59=(a43*a101);
  a78=(a78+a59);
  a78=(a50*a78);
  a97=(a97+a78);
  a95=(a95-a97);
  a97=(a82*a66);
  a97=(a51*a97);
  a96=(a12*a96);
  a78=(a44*a101);
  a96=(a96-a78);
  a96=(a26*a96);
  a96=(a52*a96);
  a97=(a97+a96);
  a95=(a95-a97);
  a98=(a12*a98);
  a97=(a41*a101);
  a98=(a98-a97);
  a98=(a18*a98);
  a98=(a54*a98);
  a66=(a0*a66);
  a66=(a53*a66);
  a98=(a98-a66);
  a95=(a95+a98);
  a83=(a83*a95);
  a79=(a7*a79);
  a98=(a8*a67);
  a79=(a79+a98);
  a79=(a79+a101);
  a88=(a88*a79);
  a83=(a83-a88);
  if (res[1]!=0) res[1][5]=a83;
  a83=(a64*a95);
  a88=(a91*a79);
  a83=(a83-a88);
  if (res[1]!=0) res[1][6]=a83;
  a83=(a85*a95);
  a88=(a93*a79);
  a83=(a83-a88);
  if (res[1]!=0) res[1][7]=a83;
  a95=(a92*a95);
  a79=(a94*a79);
  a95=(a95-a79);
  a79=(a68+a68);
  a79=(a55*a79);
  a100=(a7*a100);
  a67=(a20*a67);
  a100=(a100-a67);
  a100=(a15*a100);
  a79=(a79+a100);
  a68=(a68+a68);
  a68=(a58*a68);
  a99=(a12*a99);
  a101=(a40*a101);
  a99=(a99-a101);
  a99=(a57*a99);
  a68=(a68+a99);
  a79=(a79+a68);
  a95=(a95+a79);
  if (res[1]!=0) res[1][8]=a95;
  a95=arg[1] ? arg[1][11] : 0;
  a79=(a56*a95);
  a68=(a7*a79);
  a99=arg[1] ? arg[1][9] : 0;
  a101=(a63*a99);
  a100=(a1*a101);
  a100=(a3*a100);
  a100=(a5*a100);
  a67=(a62*a100);
  a83=(a22*a67);
  a68=(a68-a83);
  a83=(a17*a68);
  a88=(a69*a99);
  a88=(a18*a88);
  a98=(a34*a88);
  a83=(a83-a98);
  a83=(a36*a83);
  a98=(a71*a99);
  a98=(a35*a98);
  a83=(a83-a98);
  a98=(a72*a99);
  a98=(a13*a98);
  a66=(a9*a67);
  a66=(a14*a66);
  a98=(a98+a66);
  a66=(a74*a99);
  a66=(a28*a66);
  a97=(a76*a99);
  a96=(a17*a97);
  a88=(a19*a88);
  a96=(a96-a88);
  a88=(a22*a96);
  a79=(a20*a79);
  a88=(a88+a79);
  a79=(a60*a99);
  a78=(a24*a79);
  a88=(a88-a78);
  a78=(a80*a99);
  a78=(a26*a78);
  a88=(a88+a78);
  a78=(a81*a99);
  a78=(a9*a78);
  a88=(a88+a78);
  a88=(a88/a2);
  a78=(a23*a100);
  a88=(a88-a78);
  a88=(a88/a2);
  a100=(a25*a100);
  a88=(a88-a100);
  a88=(a6*a88);
  a88=(a5*a88);
  a88=(a3*a88);
  a88=(a16*a88);
  a101=(a101+a101);
  a101=(a27*a101);
  a88=(a88-a101);
  a88=(a29*a88);
  a66=(a66+a88);
  a98=(a98+a66);
  a66=(a75*a99);
  a66=(a30*a66);
  a88=(a26*a67);
  a88=(a31*a88);
  a66=(a66+a88);
  a98=(a98+a66);
  a66=(a70*a99);
  a66=(a32*a66);
  a88=(a24*a67);
  a88=(a33*a88);
  a66=(a66-a88);
  a98=(a98+a66);
  a83=(a83-a98);
  a98=(a73*a99);
  a98=(a37*a98);
  a97=(a34*a97);
  a68=(a19*a68);
  a97=(a97+a68);
  a97=(a18*a97);
  a97=(a38*a97);
  a98=(a98+a97);
  a83=(a83-a98);
  a98=(a65*a99);
  a98=(a47*a98);
  a97=(a61*a99);
  a97=(a18*a97);
  a68=(a41*a97);
  a66=(a21*a95);
  a88=(a40*a66);
  a68=(a68+a88);
  a88=(a84*a99);
  a101=(a43*a88);
  a100=(a87*a99);
  a100=(a26*a100);
  a78=(a44*a100);
  a101=(a101-a78);
  a68=(a68+a101);
  a68=(a68/a4);
  a101=(a86*a99);
  a78=(a10*a101);
  a78=(a3*a78);
  a59=(a42*a78);
  a68=(a68-a59);
  a68=(a68/a4);
  a59=(a45*a78);
  a68=(a68-a59);
  a68=(a11*a68);
  a68=(a3*a68);
  a68=(a39*a68);
  a101=(a101+a101);
  a101=(a46*a101);
  a68=(a68-a101);
  a68=(a48*a68);
  a98=(a98+a68);
  a83=(a83-a98);
  a98=(a77*a99);
  a98=(a49*a98);
  a100=(a12*a100);
  a78=(a89*a78);
  a68=(a43*a78);
  a100=(a100+a68);
  a100=(a50*a100);
  a98=(a98+a100);
  a83=(a83-a98);
  a98=(a82*a99);
  a98=(a51*a98);
  a88=(a12*a88);
  a100=(a44*a78);
  a88=(a88-a100);
  a88=(a26*a88);
  a88=(a52*a88);
  a98=(a98+a88);
  a83=(a83-a98);
  a66=(a12*a66);
  a98=(a41*a78);
  a66=(a66-a98);
  a66=(a18*a66);
  a66=(a54*a66);
  a99=(a0*a99);
  a99=(a53*a99);
  a66=(a66-a99);
  a83=(a83+a66);
  a64=(a64*a83);
  a79=(a7*a79);
  a66=(a8*a67);
  a79=(a79+a66);
  a79=(a79+a78);
  a91=(a91*a79);
  a64=(a64-a91);
  if (res[1]!=0) res[1][9]=a64;
  a64=(a85*a83);
  a91=(a93*a79);
  a64=(a64-a91);
  if (res[1]!=0) res[1][10]=a64;
  a83=(a92*a83);
  a79=(a94*a79);
  a83=(a83-a79);
  a79=(a95+a95);
  a79=(a55*a79);
  a96=(a7*a96);
  a67=(a20*a67);
  a96=(a96-a67);
  a96=(a15*a96);
  a79=(a79+a96);
  a95=(a95+a95);
  a95=(a58*a95);
  a97=(a12*a97);
  a78=(a40*a78);
  a97=(a97-a78);
  a97=(a57*a97);
  a95=(a95+a97);
  a79=(a79+a95);
  a83=(a83+a79);
  if (res[1]!=0) res[1][11]=a83;
  a83=arg[1] ? arg[1][15] : 0;
  a79=(a56*a83);
  a95=(a7*a79);
  a97=arg[1] ? arg[1][13] : 0;
  a78=(a63*a97);
  a96=(a1*a78);
  a96=(a3*a96);
  a96=(a5*a96);
  a67=(a62*a96);
  a64=(a22*a67);
  a95=(a95-a64);
  a64=(a17*a95);
  a91=(a69*a97);
  a91=(a18*a91);
  a66=(a34*a91);
  a64=(a64-a66);
  a64=(a36*a64);
  a66=(a71*a97);
  a66=(a35*a66);
  a64=(a64-a66);
  a66=(a72*a97);
  a66=(a13*a66);
  a99=(a9*a67);
  a99=(a14*a99);
  a66=(a66+a99);
  a99=(a74*a97);
  a99=(a28*a99);
  a98=(a76*a97);
  a88=(a17*a98);
  a91=(a19*a91);
  a88=(a88-a91);
  a91=(a22*a88);
  a79=(a20*a79);
  a91=(a91+a79);
  a79=(a60*a97);
  a100=(a24*a79);
  a91=(a91-a100);
  a100=(a80*a97);
  a100=(a26*a100);
  a91=(a91+a100);
  a100=(a81*a97);
  a100=(a9*a100);
  a91=(a91+a100);
  a91=(a91/a2);
  a100=(a23*a96);
  a91=(a91-a100);
  a91=(a91/a2);
  a96=(a25*a96);
  a91=(a91-a96);
  a91=(a6*a91);
  a91=(a5*a91);
  a91=(a3*a91);
  a91=(a16*a91);
  a78=(a78+a78);
  a78=(a27*a78);
  a91=(a91-a78);
  a91=(a29*a91);
  a99=(a99+a91);
  a66=(a66+a99);
  a99=(a75*a97);
  a99=(a30*a99);
  a91=(a26*a67);
  a91=(a31*a91);
  a99=(a99+a91);
  a66=(a66+a99);
  a99=(a70*a97);
  a99=(a32*a99);
  a91=(a24*a67);
  a91=(a33*a91);
  a99=(a99-a91);
  a66=(a66+a99);
  a64=(a64-a66);
  a66=(a73*a97);
  a66=(a37*a66);
  a98=(a34*a98);
  a95=(a19*a95);
  a98=(a98+a95);
  a98=(a18*a98);
  a98=(a38*a98);
  a66=(a66+a98);
  a64=(a64-a66);
  a66=(a65*a97);
  a66=(a47*a66);
  a98=(a61*a97);
  a98=(a18*a98);
  a95=(a41*a98);
  a99=(a21*a83);
  a91=(a40*a99);
  a95=(a95+a91);
  a91=(a84*a97);
  a78=(a43*a91);
  a96=(a87*a97);
  a96=(a26*a96);
  a100=(a44*a96);
  a78=(a78-a100);
  a95=(a95+a78);
  a95=(a95/a4);
  a78=(a86*a97);
  a100=(a10*a78);
  a100=(a3*a100);
  a68=(a42*a100);
  a95=(a95-a68);
  a95=(a95/a4);
  a68=(a45*a100);
  a95=(a95-a68);
  a95=(a11*a95);
  a95=(a3*a95);
  a95=(a39*a95);
  a78=(a78+a78);
  a78=(a46*a78);
  a95=(a95-a78);
  a95=(a48*a95);
  a66=(a66+a95);
  a64=(a64-a66);
  a66=(a77*a97);
  a66=(a49*a66);
  a96=(a12*a96);
  a100=(a89*a100);
  a95=(a43*a100);
  a96=(a96+a95);
  a96=(a50*a96);
  a66=(a66+a96);
  a64=(a64-a66);
  a66=(a82*a97);
  a66=(a51*a66);
  a91=(a12*a91);
  a96=(a44*a100);
  a91=(a91-a96);
  a91=(a26*a91);
  a91=(a52*a91);
  a66=(a66+a91);
  a64=(a64-a66);
  a99=(a12*a99);
  a66=(a41*a100);
  a99=(a99-a66);
  a99=(a18*a99);
  a99=(a54*a99);
  a97=(a0*a97);
  a97=(a53*a97);
  a99=(a99-a97);
  a64=(a64+a99);
  a85=(a85*a64);
  a79=(a7*a79);
  a99=(a8*a67);
  a79=(a79+a99);
  a79=(a79+a100);
  a93=(a93*a79);
  a85=(a85-a93);
  if (res[1]!=0) res[1][12]=a85;
  a64=(a92*a64);
  a79=(a94*a79);
  a64=(a64-a79);
  a79=(a83+a83);
  a79=(a55*a79);
  a88=(a7*a88);
  a67=(a20*a67);
  a88=(a88-a67);
  a88=(a15*a88);
  a79=(a79+a88);
  a83=(a83+a83);
  a83=(a58*a83);
  a98=(a12*a98);
  a100=(a40*a100);
  a98=(a98-a100);
  a98=(a57*a98);
  a83=(a83+a98);
  a79=(a79+a83);
  a64=(a64+a79);
  if (res[1]!=0) res[1][13]=a64;
  a64=arg[2] ? arg[2][3] : 0;
  a56=(a56*a64);
  a79=(a7*a56);
  a83=arg[2] ? arg[2][1] : 0;
  a63=(a63*a83);
  a1=(a1*a63);
  a1=(a3*a1);
  a1=(a5*a1);
  a62=(a62*a1);
  a98=(a22*a62);
  a79=(a79-a98);
  a98=(a17*a79);
  a69=(a69*a83);
  a69=(a18*a69);
  a100=(a34*a69);
  a98=(a98-a100);
  a36=(a36*a98);
  a71=(a71*a83);
  a35=(a35*a71);
  a36=(a36-a35);
  a72=(a72*a83);
  a13=(a13*a72);
  a72=(a9*a62);
  a14=(a14*a72);
  a13=(a13+a14);
  a74=(a74*a83);
  a28=(a28*a74);
  a76=(a76*a83);
  a17=(a17*a76);
  a69=(a19*a69);
  a17=(a17-a69);
  a22=(a22*a17);
  a56=(a20*a56);
  a22=(a22+a56);
  a60=(a60*a83);
  a56=(a24*a60);
  a56=(a8-a56);
  a22=(a22+a56);
  a80=(a80*a83);
  a80=(a26*a80);
  a22=(a22+a80);
  a81=(a81*a83);
  a9=(a9*a81);
  a22=(a22+a9);
  a22=(a22/a2);
  a23=(a23*a1);
  a22=(a22-a23);
  a22=(a22/a2);
  a25=(a25*a1);
  a22=(a22-a25);
  a6=(a6*a22);
  a5=(a5*a6);
  a5=(a3*a5);
  a16=(a16*a5);
  a63=(a63+a63);
  a27=(a27*a63);
  a16=(a16-a27);
  a29=(a29*a16);
  a28=(a28+a29);
  a13=(a13+a28);
  a75=(a75*a83);
  a30=(a30*a75);
  a75=(a26*a62);
  a31=(a31*a75);
  a30=(a30+a31);
  a13=(a13+a30);
  a70=(a70*a83);
  a32=(a32*a70);
  a24=(a24*a62);
  a24=(a7-a24);
  a33=(a33*a24);
  a32=(a32+a33);
  a13=(a13+a32);
  a36=(a36-a13);
  a73=(a73*a83);
  a37=(a37*a73);
  a34=(a34*a76);
  a19=(a19*a79);
  a34=(a34+a19);
  a34=(a18*a34);
  a38=(a38*a34);
  a37=(a37+a38);
  a36=(a36-a37);
  a65=(a65*a83);
  a47=(a47*a65);
  a61=(a61*a83);
  a61=(a18*a61);
  a65=(a41*a61);
  a21=(a21*a64);
  a37=(a40*a21);
  a65=(a65+a37);
  a37=1.;
  a65=(a65+a37);
  a84=(a84*a83);
  a37=(a43*a84);
  a87=(a87*a83);
  a87=(a26*a87);
  a38=(a44*a87);
  a37=(a37-a38);
  a65=(a65+a37);
  a65=(a65/a4);
  a86=(a86*a83);
  a10=(a10*a86);
  a10=(a3*a10);
  a42=(a42*a10);
  a65=(a65-a42);
  a65=(a65/a4);
  a45=(a45*a10);
  a65=(a65-a45);
  a11=(a11*a65);
  a3=(a3*a11);
  a39=(a39*a3);
  a86=(a86+a86);
  a46=(a46*a86);
  a39=(a39-a46);
  a48=(a48*a39);
  a47=(a47+a48);
  a36=(a36-a47);
  a77=(a77*a83);
  a49=(a49*a77);
  a87=(a12*a87);
  a89=(a89*a10);
  a43=(a43*a89);
  a87=(a87+a43);
  a50=(a50*a87);
  a49=(a49+a50);
  a36=(a36-a49);
  a82=(a82*a83);
  a51=(a51*a82);
  a84=(a12*a84);
  a44=(a44*a89);
  a84=(a84-a44);
  a26=(a26*a84);
  a52=(a52*a26);
  a51=(a51+a52);
  a36=(a36-a51);
  a21=(a12*a21);
  a41=(a41*a89);
  a21=(a21-a41);
  a18=(a18*a21);
  a54=(a54*a18);
  a0=(a0*a83);
  a53=(a53*a0);
  a54=(a54-a53);
  a36=(a36+a54);
  a92=(a92*a36);
  a60=(a7*a60);
  a8=(a8*a62);
  a60=(a60+a8);
  a60=(a60+a89);
  a94=(a94*a60);
  a92=(a92-a94);
  a94=(a64+a64);
  a55=(a55*a94);
  a7=(a7*a17);
  a20=(a20*a62);
  a7=(a7-a20);
  a15=(a15*a7);
  a55=(a55+a15);
  a64=(a64+a64);
  a58=(a58*a64);
  a12=(a12*a61);
  a40=(a40*a89);
  a12=(a12-a40);
  a57=(a57*a12);
  a58=(a58+a57);
  a55=(a55+a58);
  a92=(a92+a55);
  if (res[1]!=0) res[1][14]=a92;
  return 0;
}

CASADI_SYMBOL_EXPORT void hessFun_incref(void) {
}

CASADI_SYMBOL_EXPORT void hessFun_decref(void) {
}

CASADI_SYMBOL_EXPORT int hessFun_n_in(void) { return 5;}

CASADI_SYMBOL_EXPORT int hessFun_n_out(void) { return 2;}

CASADI_SYMBOL_EXPORT const char* hessFun_name_in(int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    case 3: return "i3";
    case 4: return "i4";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* hessFun_name_out(int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const int* hessFun_sparsity_in(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s1;
    case 2: return s0;
    case 3: return s0;
    case 4: return s2;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const int* hessFun_sparsity_out(int i) {
  switch (i) {
    case 0: return s3;
    case 1: return s4;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int hessFun_work(int *sz_arg, int* sz_res, int *sz_iw, int *sz_w) {
  if (sz_arg) *sz_arg = 5;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 103;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
