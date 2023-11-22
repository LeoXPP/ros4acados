/*
 * File: simulink_model_closedloop.c
 *
 * Code generated for Simulink model 'simulink_model_closedloop'.
 *
 * Model version                  : 20.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue Sep  5 21:03:05 2023
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

#include "simulink_model_closedloop.h"
#include <string.h>
#include "rtwtypes.h"
#include "simulink_model_closedloop_private.h"
#include "rt_nonfinite.h"

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
//  生成代码的输出 入口函数 ，每0.02s会调用一次
void simulink_model_closedloop_step(void)
{
  real_T s0;
  int32_T i;

  /* Delay: '<Root>/Delay1' */
  memcpy(&rtDW.Delay1[0], &rtDW.Delay1_DSTATE[0], sizeof(real_T) << 3U);

  /* MATLAB Function: '<S2>/reference' */
  s0 = rtDW.Delay1[5];
  memset(&rtDW.yref[0], 0, 490U * sizeof(real_T));
  for (i = 0; i < 49; i++) {
    rtDW.yref[i * 10 + 5] = ((rtDW.Delay1[5] + 3.0) - s0) * ((real_T)i + 1.0) /
      50.0 + s0;
  }

  rtDW.yref_N[0] = 0.0;
  rtDW.yref_N[1] = 0.0;
  rtDW.yref_N[2] = 0.0;
  rtDW.yref_N[3] = 0.0;
  rtDW.yref_N[4] = 0.0;
  rtDW.yref_N[5] = rtDW.Delay1[5] + 3.0;
  rtDW.yref_N[6] = 0.0;
  rtDW.yref_N[7] = 0.0;

  /* End of MATLAB Function: '<S2>/reference' */

  /* S-Function (acados_solver_sfunction_bicycle_model): '<Root>/S-Function1' incorporates:
   *  Constant: '<Root>/lbu'
   *  Constant: '<Root>/lbx'
   *  Constant: '<Root>/lh'
   *  Constant: '<Root>/ubu'
   *  Constant: '<Root>/ubx'
   *  Constant: '<Root>/uh'
   *  Constant: '<Root>/y_ref_0'
   */

  /* Level2 S-Function Block: '<Root>/S-Function1' (acados_solver_sfunction_bicycle_model) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* S-Function (acados_sim_solver_sfunction_bicycle_model): '<Root>/S-Function' */

  /* Level2 S-Function Block: '<Root>/S-Function' (acados_sim_solver_sfunction_bicycle_model) */
  {
    SimStruct *rts = rtM->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* Update for Delay: '<Root>/Delay1' */
  memcpy(&rtDW.Delay1_DSTATE[0], &rtDW.x[0], sizeof(real_T) << 3U);

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rtM->Timing.t[0] =
    ((time_T)(++rtM->Timing.clockTick0)) * rtM->Timing.stepSize0;
}

/* Model initialize function */
void simulink_model_closedloop_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtsiSetSolverName(&rtM->solverInfo,"FixedStepDiscrete");
  rtM->solverInfoPtr = (&rtM->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "rtM points to
       static memory which is guaranteed to be non-NULL" */
    rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    rtM->Timing.sampleTimes = (&rtM->Timing.sampleTimesArray[0]);
    rtM->Timing.offsetTimes = (&rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    rtM->Timing.sampleTimes[0] = (0.02);

    /* task offsets */
    rtM->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(rtM, -1);
  rtM->Timing.stepSize0 = 0.02;
  rtM->solverInfoPtr = (&rtM->solverInfo);
  rtM->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&rtM->solverInfo, 0.02);
  rtsiSetSolverMode(&rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &rtM->NonInlinedSFcns.sfcnInfo;
    rtM->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(rtM)));
    rtM->Sizes.numSampTimes = (1);
    rtssSetNumRootSampTimesPtr(sfcnInfo, &rtM->Sizes.numSampTimes);
    rtM->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr(rtM)[0]);
    rtssSetTPtrPtr(sfcnInfo,rtM->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(rtM));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(rtM));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(rtM));
    rtssSetStepSizePtr(sfcnInfo, &rtM->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(rtM));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo, &rtM->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &rtM->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &rtM->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &rtM->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &rtM->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &rtM->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &rtM->solverInfoPtr);
  }

  rtM->Sizes.numSFcns = (2);

  /* register each child */
  {
    (void) memset((void *)&rtM->NonInlinedSFcns.childSFunctions[0], 0,
                  2*sizeof(SimStruct));
    rtM->childSfunctions = (&rtM->NonInlinedSFcns.childSFunctionPtrs[0]);
    rtM->childSfunctions[0] = (&rtM->NonInlinedSFcns.childSFunctions[0]);
    rtM->childSfunctions[1] = (&rtM->NonInlinedSFcns.childSFunctions[1]);

    /* Level2 S-Function Block: simulink_model_closedloop/<Root>/S-Function1 (acados_solver_sfunction_bicycle_model) */
    {
      SimStruct *rts = rtM->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = rtM->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = rtM->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = rtM->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &rtM->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts, &rtM->
        NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &rtM->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &rtM->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &rtM->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &rtM->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts, &rtM->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 11);
        ssSetPortInfoForInputs(rts, &rtM->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts, &rtM->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &rtM->NonInlinedSFcns.Sfcn0.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        ssSetInputPortUnit(rts, 2, 0);
        ssSetInputPortUnit(rts, 3, 0);
        ssSetInputPortUnit(rts, 4, 0);
        ssSetInputPortUnit(rts, 5, 0);
        ssSetInputPortUnit(rts, 6, 0);
        ssSetInputPortUnit(rts, 7, 0);
        ssSetInputPortUnit(rts, 8, 0);
        ssSetInputPortUnit(rts, 9, 0);
        ssSetInputPortUnit(rts, 10, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &rtM->NonInlinedSFcns.Sfcn0.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);
        ssSetInputPortIsContinuousQuantity(rts, 2, 0);
        ssSetInputPortIsContinuousQuantity(rts, 3, 0);
        ssSetInputPortIsContinuousQuantity(rts, 4, 0);
        ssSetInputPortIsContinuousQuantity(rts, 5, 0);
        ssSetInputPortIsContinuousQuantity(rts, 6, 0);
        ssSetInputPortIsContinuousQuantity(rts, 7, 0);
        ssSetInputPortIsContinuousQuantity(rts, 8, 0);
        ssSetInputPortIsContinuousQuantity(rts, 9, 0);
        ssSetInputPortIsContinuousQuantity(rts, 10, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs0;

          {
            int_T i1;
            const real_T *u0 = rtDW.Delay1;
            for (i1=0; i1 < 8; i1++) {
              sfcnUPtrs[i1] = &u0[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 8);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs1;

          {
            int_T i1;
            const real_T *u1 = rtDW.Delay1;
            for (i1=0; i1 < 8; i1++) {
              sfcnUPtrs[i1] = &u1[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 8);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs2;

          {
            int_T i1;
            const real_T *u2 = rtConstP.y_ref_0_Value;
            for (i1=0; i1 < 10; i1++) {
              sfcnUPtrs[i1] = &u2[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 2, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidthAsInt(rts, 2, 10);
        }

        /* port 3 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs3;

          {
            int_T i1;
            const real_T *u3 = rtDW.yref;
            for (i1=0; i1 < 490; i1++) {
              sfcnUPtrs[i1] = &u3[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 3, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidthAsInt(rts, 3, 490);
        }

        /* port 4 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs4;

          {
            int_T i1;
            const real_T *u4 = rtDW.yref_N;
            for (i1=0; i1 < 8; i1++) {
              sfcnUPtrs[i1] = &u4[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 4, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidthAsInt(rts, 4, 8);
        }

        /* port 5 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs5;

          {
            int_T i1;
            const real_T *u5 = rtConstP.lbx_Value;
            for (i1=0; i1 < 196; i1++) {
              sfcnUPtrs[i1] = &u5[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 5, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 5, 1);
          ssSetInputPortWidthAsInt(rts, 5, 196);
        }

        /* port 6 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs6;

          {
            int_T i1;
            const real_T *u6 = rtConstP.ubx_Value;
            for (i1=0; i1 < 196; i1++) {
              sfcnUPtrs[i1] = &u6[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 6, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 6, 1);
          ssSetInputPortWidthAsInt(rts, 6, 196);
        }

        /* port 7 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs7;

          {
            int_T i1;
            const real_T *u7 = rtConstP.lbu_Value;
            for (i1=0; i1 < 100; i1++) {
              sfcnUPtrs[i1] = &u7[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 7, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 7, 1);
          ssSetInputPortWidthAsInt(rts, 7, 100);
        }

        /* port 8 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs8;

          {
            int_T i1;
            const real_T *u8 = rtConstP.ubu_Value;
            for (i1=0; i1 < 100; i1++) {
              sfcnUPtrs[i1] = &u8[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 8, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 8, 1);
          ssSetInputPortWidthAsInt(rts, 8, 100);
        }

        /* port 9 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs9;

          {
            int_T i1;
            const real_T *u9 = rtConstP.lh_Value;
            for (i1=0; i1 < 100; i1++) {
              sfcnUPtrs[i1] = &u9[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 9, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 9, 1);
          ssSetInputPortWidthAsInt(rts, 9, 100);
        }

        /* port 10 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs10;

          {
            int_T i1;
            const real_T *u10 = rtConstP.uh_Value;
            for (i1=0; i1 < 100; i1++) {
              sfcnUPtrs[i1] = &u10[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 10, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 10, 1);
          ssSetInputPortWidthAsInt(rts, 10, 100);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts, &rtM->NonInlinedSFcns.Sfcn0.outputPortInfo
          [0]);
        ssSetPortInfoForOutputs(rts, &rtM->NonInlinedSFcns.Sfcn0.outputPortInfo
          [0]);
        _ssSetNumOutputPorts(rts, 8);
        _ssSetPortInfo2ForOutputUnits(rts,
          &rtM->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);
        ssSetOutputPortUnit(rts, 2, 0);
        ssSetOutputPortUnit(rts, 3, 0);
        ssSetOutputPortUnit(rts, 4, 0);
        ssSetOutputPortUnit(rts, 5, 0);
        ssSetOutputPortUnit(rts, 6, 0);
        ssSetOutputPortUnit(rts, 7, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &rtM->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 1, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 2, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 3, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 4, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 5, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 6, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 7, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 2);
          ssSetOutputPortSignal(rts, 0, ((real_T *) rtDW.u0));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidthAsInt(rts, 1, 408);
          ssSetOutputPortSignal(rts, 1, ((real_T *) rtDW.SFunction1_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidthAsInt(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *) &rtDW.SFunction1_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidthAsInt(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *) &rtDW.SFunction1_o4));
        }

        /* port 4 */
        {
          _ssSetOutputPortNumDimensions(rts, 4, 1);
          ssSetOutputPortWidthAsInt(rts, 4, 1);
          ssSetOutputPortSignal(rts, 4, ((real_T *) &rtDW.SFunction1_o5));
        }

        /* port 5 */
        {
          _ssSetOutputPortNumDimensions(rts, 5, 1);
          ssSetOutputPortWidthAsInt(rts, 5, 8);
          ssSetOutputPortSignal(rts, 5, ((real_T *) rtDW.SFunction1_o6));
        }

        /* port 6 */
        {
          _ssSetOutputPortNumDimensions(rts, 6, 1);
          ssSetOutputPortWidthAsInt(rts, 6, 1);
          ssSetOutputPortSignal(rts, 6, ((real_T *) &rtDW.SFunction1_o7));
        }

        /* port 7 */
        {
          _ssSetOutputPortNumDimensions(rts, 7, 1);
          ssSetOutputPortWidthAsInt(rts, 7, 1);
          ssSetOutputPortSignal(rts, 7, ((real_T *) &rtDW.SFunction1_o8));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function1");
      ssSetPath(rts, "simulink_model_closedloop/S-Function1");
      ssSetRTModel(rts,rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* registration */
      acados_solver_sfunction_bicycle_model(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.02);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);
      _ssSetInputPortConnected(rts, 5, 1);
      _ssSetInputPortConnected(rts, 6, 1);
      _ssSetInputPortConnected(rts, 7, 1);
      _ssSetInputPortConnected(rts, 8, 1);
      _ssSetInputPortConnected(rts, 9, 1);
      _ssSetInputPortConnected(rts, 10, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 4, 1);
      _ssSetOutputPortConnected(rts, 5, 1);
      _ssSetOutputPortConnected(rts, 6, 1);
      _ssSetOutputPortConnected(rts, 7, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 4, 0);
      _ssSetOutputPortBeingMerged(rts, 5, 0);
      _ssSetOutputPortBeingMerged(rts, 6, 0);
      _ssSetOutputPortBeingMerged(rts, 7, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
      ssSetInputPortBufferDstPort(rts, 5, -1);
      ssSetInputPortBufferDstPort(rts, 6, -1);
      ssSetInputPortBufferDstPort(rts, 7, -1);
      ssSetInputPortBufferDstPort(rts, 8, -1);
      ssSetInputPortBufferDstPort(rts, 9, -1);
      ssSetInputPortBufferDstPort(rts, 10, -1);
    }

    /* Level2 S-Function Block: simulink_model_closedloop/<Root>/S-Function (acados_sim_solver_sfunction_bicycle_model) */
    {
      SimStruct *rts = rtM->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod = rtM->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset = rtM->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap = rtM->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &rtM->NonInlinedSFcns.blkInfo2[1]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts, &rtM->
        NonInlinedSFcns.inputOutputPortInfo2[1]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &rtM->NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &rtM->NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &rtM->NonInlinedSFcns.methods4[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &rtM->NonInlinedSFcns.statesInfo2[1]);
        ssSetPeriodicStatesInfo(rts, &rtM->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts, &rtM->NonInlinedSFcns.Sfcn1.inputPortInfo[0]);
        ssSetPortInfoForInputs(rts, &rtM->NonInlinedSFcns.Sfcn1.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &rtM->NonInlinedSFcns.Sfcn1.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &rtM->NonInlinedSFcns.Sfcn1.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn1.UPtrs0;

          {
            int_T i1;
            const real_T *u0 = rtDW.Delay1;
            for (i1=0; i1 < 8; i1++) {
              sfcnUPtrs[i1] = &u0[i1];
            }
          }

          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidthAsInt(rts, 0, 8);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn1.UPtrs1;
          sfcnUPtrs[0] = rtDW.u0;
          sfcnUPtrs[1] = &rtDW.u0[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidthAsInt(rts, 1, 2);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts, &rtM->NonInlinedSFcns.Sfcn1.outputPortInfo
          [0]);
        ssSetPortInfoForOutputs(rts, &rtM->NonInlinedSFcns.Sfcn1.outputPortInfo
          [0]);
        _ssSetNumOutputPorts(rts, 1);
        _ssSetPortInfo2ForOutputUnits(rts,
          &rtM->NonInlinedSFcns.Sfcn1.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &rtM->NonInlinedSFcns.Sfcn1.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidthAsInt(rts, 0, 8);
          ssSetOutputPortSignal(rts, 0, ((real_T *) rtDW.x));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function");
      ssSetPath(rts, "simulink_model_closedloop/S-Function");
      ssSetRTModel(rts,rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* registration */
      acados_sim_solver_sfunction_bicycle_model(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.02);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCsAsInt(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
    }
  }

  /* Start for S-Function (acados_solver_sfunction_bicycle_model): '<Root>/S-Function1' incorporates:
   *  Constant: '<Root>/lbu'
   *  Constant: '<Root>/lbx'
   *  Constant: '<Root>/lh'
   *  Constant: '<Root>/ubu'
   *  Constant: '<Root>/ubx'
   *  Constant: '<Root>/uh'
   *  Constant: '<Root>/y_ref_0'
   */
  /* Level2 S-Function Block: '<Root>/S-Function1' (acados_solver_sfunction_bicycle_model) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (acados_sim_solver_sfunction_bicycle_model): '<Root>/S-Function' */
  /* Level2 S-Function Block: '<Root>/S-Function' (acados_sim_solver_sfunction_bicycle_model) */
  {
    SimStruct *rts = rtM->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  memcpy(&rtDW.Delay1_DSTATE[0], &rtConstP.Delay1_InitialCondition[0], sizeof
         (real_T) << 3U);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
