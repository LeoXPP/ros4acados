/*
 * File: simulink_model_closedloop.h
 *
 * Code generated for Simulink model 'simulink_model_closedloop'.
 *
 * Model version                  : 20.7
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Sep  7 08:27:22 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */
#include"sfcn_bridge.h"
#ifndef RTW_HEADER_simulink_model_closedloop_h_
#define RTW_HEADER_simulink_model_closedloop_h_
#ifndef simulink_model_closedloop_COMMON_INCLUDES_
#define simulink_model_closedloop_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                          /* simulink_model_closedloop_COMMON_INCLUDES_ */

#include "simulink_model_closedloop_types.h"
#include <stddef.h>
#include <string.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay1[8];                    /* '<Root>/Delay1' */
  real_T u0[2];                        /* '<Root>/S-Function1' */
  real_T SFunction1_o2[408];           /* '<Root>/S-Function1' */
  real_T SFunction1_o6[8];             /* '<Root>/S-Function1' */
  real_T x[8];                         /* '<Root>/S-Function' */
  real_T yref_N[8];                    /* '<S2>/reference' */
  real_T yref[490];                    /* '<S2>/reference' */
  real_T Delay1_DSTATE[8];             /* '<Root>/Delay1' */
  real_T SFunction1_o3;                /* '<Root>/S-Function1' */
  real_T SFunction1_o4;                /* '<Root>/S-Function1' */
  real_T SFunction1_o5;                /* '<Root>/S-Function1' */
  real_T SFunction1_o7;                /* '<Root>/S-Function1' */
  real_T SFunction1_o8;                /* '<Root>/S-Function1' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [model.x0 0 0]
   * Referenced by: '<Root>/y_ref_0'
   */
  real_T y_ref_0_Value[10];

  /* Expression: repmat([ model.ddelta_min, model.dTc_min]',N,1)
   * Referenced by: '<Root>/lbu'
   */
  real_T lbu_Value[100];

  /* Expression: repmat([model.ey_min, model.Track_vel_min , model.delta_min, model.Tc_min]',N-1,1)
   * Referenced by: '<Root>/lbx'
   */
  real_T lbx_Value[196];

  /* Expression: repmat([constraint.alon_min, constraint.alat_min]',N,1)
   * Referenced by: '<Root>/lh'
   */
  real_T lh_Value[100];

  /* Expression: repmat([model.ddelta_max, model.dTc_max]',N,1)
   * Referenced by: '<Root>/ubu'
   */
  real_T ubu_Value[100];

  /* Expression: repmat([model.ey_max, model.Track_vel_max , model.delta_max, model.Tc_max]',N-1,1)
   * Referenced by: '<Root>/ubx'
   */
  real_T ubx_Value[196];

  /* Expression: repmat([constraint.alon_max, constraint.alat_max]',N,1)
   * Referenced by: '<Root>/uh'
   */
  real_T uh_Value[100];

  /* Expression: model.x0
   * Referenced by: '<Root>/Delay1'
   */
  real_T Delay1_InitialCondition[8];
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[1];
    SimStruct childSFunctions[2];
    SimStruct *childSFunctionPtrs[2];
    struct _ssBlkInfo2 blkInfo2[2];
    struct _ssSFcnModelMethods2 methods2[2];
    struct _ssSFcnModelMethods3 methods3[2];
    struct _ssSFcnModelMethods4 methods4[2];
    struct _ssStatesInfo2 statesInfo2[2];
    ssPeriodicStatesInfo periodicStatesInfo[2];
    struct _ssPortInfo2 inputOutputPortInfo2[2];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[11];
      struct _ssInPortUnit inputPortUnits[11];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[11];
      real_T const *UPtrs0[8];
      real_T const *UPtrs1[8];
      real_T const *UPtrs2[10];
      real_T const *UPtrs3[490];
      real_T const *UPtrs4[8];
      real_T const *UPtrs5[196];
      real_T const *UPtrs6[196];
      real_T const *UPtrs7[100];
      real_T const *UPtrs8[100];
      real_T const *UPtrs9[100];
      real_T const *UPtrs10[100];
      struct _ssPortOutputs outputPortInfo[8];
      struct _ssOutPortUnit outputPortUnits[8];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[8];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[2];
      struct _ssInPortUnit inputPortUnits[2];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[2];
      real_T const *UPtrs0[8];
      real_T const *UPtrs1[2];
      struct _ssPortOutputs outputPortInfo[1];
      struct _ssOutPortUnit outputPortUnits[1];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[1];
    } Sfcn1;
  } NonInlinedSFcns;

  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void simulink_model_closedloop_initialize(void);
extern void simulink_model_closedloop_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/CPU' : Unused code path elimination
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Display2' : Unused code path elimination
 * Block '<Root>/KKT residual' : Unused code path elimination
 * Block '<Root>/OCP status' : Unused code path elimination
 * Block '<S2>/Display' : Unused code path elimination
 * Block '<Root>/SQP iter' : Unused code path elimination
 * Block '<Root>/Scope state' : Unused code path elimination
 * Block '<Root>/Scope state1' : Unused code path elimination
 * Block '<Root>/Scope state2' : Unused code path elimination
 * Block '<Root>/To Workspace2' : Unused code path elimination
 * Block '<Root>/cost_W' : Unused code path elimination
 * Block '<Root>/cost_W0' : Unused code path elimination
 * Block '<Root>/cost_W_e' : Unused code path elimination
 * Block '<Root>/cost_value' : Unused code path elimination
 * Block '<Root>/u' : Unused code path elimination
 * Block '<Root>/x1 ocp' : Unused code path elimination
 * Block '<Root>/x_init' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'simulink_model_closedloop'
 * '<S1>'   : 'simulink_model_closedloop/MATLAB Function'
 * '<S2>'   : 'simulink_model_closedloop/Reference generator'
 * '<S3>'   : 'simulink_model_closedloop/Reference generator/MATLAB Function'
 * '<S4>'   : 'simulink_model_closedloop/Reference generator/reference'
 */
#endif                             /* RTW_HEADER_simulink_model_closedloop_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
