/*
 * helicopter_day4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_day4".
 *
 * Model version              : 1.188
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Fri Feb 07 17:31:52 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_day4.h"
#include "helicopter_day4_private.h"
#include "helicopter_day4_dt.h"

/* Block signals (auto storage) */
B_helicopter_day4_T helicopter_day4_B;

/* Continuous states */
X_helicopter_day4_T helicopter_day4_X;

/* Block states (auto storage) */
DW_helicopter_day4_T helicopter_day4_DW;

/* Real-time model */
RT_MODEL_helicopter_day4_T helicopter_day4_M_;
RT_MODEL_helicopter_day4_T *const helicopter_day4_M = &helicopter_day4_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_day4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_day4_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace1[6];
  real_T rtb_Backgain;
  real_T rtb_Sum5;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_Sum3_n;
  real_T *lastU;
  real_T rtb_Gain1[6];
  real_T rtb_MatrixMultiply[2];
  real_T rtb_Derivative;
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* set solver stop time */
    if (!(helicopter_day4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_day4_M->solverInfo,
                            ((helicopter_day4_M->Timing.clockTickH0 + 1) *
        helicopter_day4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_day4_M->solverInfo,
                            ((helicopter_day4_M->Timing.clockTick0 + 1) *
        helicopter_day4_M->Timing.stepSize0 +
        helicopter_day4_M->Timing.clockTickH0 *
        helicopter_day4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_day4_M)) {
    helicopter_day4_M->Timing.t[0] = rtsiGetT(&helicopter_day4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_day4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_day4_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_day4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_day4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_day4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_Sum3_n = helicopter_day4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace3' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day4_DW.FromWorkspace3_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day4_DW.FromWorkspace3_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day4_DW.FromWorkspace3_IWORK.PrevIndex;
    real_T t = helicopter_day4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[330]) {
      currTimeIndex = 329;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_day4_DW.FromWorkspace3_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Backgain = pDataValues[currTimeIndex];
        } else {
          rtb_Backgain = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Backgain = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 331;
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_day4_B.TravelCounttorad = helicopter_day4_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_day4_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopter_day4_B.Gain = helicopter_day4_P.Gain_Gain *
      helicopter_day4_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter_day4_B.Sum3 = helicopter_day4_P.Constant_Value +
      helicopter_day4_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_day4_B.PitchCounttorad = helicopter_day4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S8>/Gain' */
    helicopter_day4_B.Gain_i = helicopter_day4_P.Gain_Gain_a *
      helicopter_day4_B.PitchCounttorad;
  }

  /* TransferFcn: '<S4>/Travel: Transfer Fcn' */
  rtb_Sum5 = 0.0;
  rtb_Sum5 += helicopter_day4_P.TravelTransferFcn_C *
    helicopter_day4_X.TravelTransferFcn_CSTATE;
  rtb_Sum5 += helicopter_day4_P.TravelTransferFcn_D *
    helicopter_day4_B.TravelCounttorad;

  /* Gain: '<S14>/Gain' */
  helicopter_day4_B.Gain_d = helicopter_day4_P.Gain_Gain_l * rtb_Sum5;

  /* TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  rtb_Sum5 = 0.0;
  rtb_Sum5 += helicopter_day4_P.PitchTransferFcn_C *
    helicopter_day4_X.PitchTransferFcn_CSTATE;
  rtb_Sum5 += helicopter_day4_P.PitchTransferFcn_D *
    helicopter_day4_B.PitchCounttorad;

  /* Gain: '<S9>/Gain' */
  helicopter_day4_B.Gain_b = helicopter_day4_P.Gain_Gain_ae * rtb_Sum5;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_day4_B.ElevationCounttorad = helicopter_day4_P.elevation_gain *
      rtb_Sum3_n * helicopter_day4_P.ElevationCounttorad_Gain;

    /* Gain: '<S6>/Gain' */
    helicopter_day4_B.Gain_e = helicopter_day4_P.Gain_Gain_lv *
      helicopter_day4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_day4_B.Sum = helicopter_day4_B.Gain_e +
      helicopter_day4_P.elavation_offsetdeg_Value;
  }

  /* TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  rtb_Sum5 = 0.0;
  rtb_Sum5 += helicopter_day4_P.ElevationTransferFcn_C *
    helicopter_day4_X.ElevationTransferFcn_CSTATE;
  rtb_Sum5 += helicopter_day4_P.ElevationTransferFcn_D *
    helicopter_day4_B.ElevationCounttorad;

  /* Gain: '<S7>/Gain' */
  helicopter_day4_B.Gain_dg = helicopter_day4_P.Gain_Gain_n * rtb_Sum5;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1[0] = helicopter_day4_P.Gain1_Gain * helicopter_day4_B.Sum3;
  rtb_Gain1[1] = helicopter_day4_P.Gain1_Gain * helicopter_day4_B.Gain_d;
  rtb_Gain1[2] = helicopter_day4_P.Gain1_Gain * helicopter_day4_B.Gain_i;
  rtb_Gain1[3] = helicopter_day4_P.Gain1_Gain * helicopter_day4_B.Gain_b;
  rtb_Gain1[4] = helicopter_day4_P.Gain1_Gain * helicopter_day4_B.Sum;
  rtb_Gain1[5] = helicopter_day4_P.Gain1_Gain * helicopter_day4_B.Gain_dg;

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_day4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[330]) {
      currTimeIndex = 329;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_day4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_FromWorkspace1[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 331;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_FromWorkspace1[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 331;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_FromWorkspace1[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 331;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum4' */
  for (i = 0; i < 6; i++) {
    helicopter_day4_B.Sum4[i] = rtb_Gain1[i] - rtb_FromWorkspace1[i];
  }

  /* End of Sum: '<Root>/Sum4' */

  /* Product: '<Root>/Matrix Multiply' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  for (i = 0; i < 2; i++) {
    rtb_MatrixMultiply[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_MatrixMultiply[i] += helicopter_day4_P.K[(i_0 << 1) + i] *
        helicopter_day4_B.Sum4[i_0];
    }
  }

  /* End of Product: '<Root>/Matrix Multiply' */

  /* Sum: '<Root>/Sum6' */
  helicopter_day4_B.Sum6 = rtb_Backgain - rtb_MatrixMultiply[1];
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day4_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day4_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day4_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_day4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[330]) {
      currTimeIndex = 329;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_day4_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Sum5 = pDataValues[currTimeIndex];
        } else {
          rtb_Sum5 = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Sum5 = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 331;
      }
    }
  }

  /* Sum: '<Root>/Sum5' */
  rtb_Sum5 -= rtb_MatrixMultiply[0];

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  helicopter_day4_B.Sum1 = ((rtb_Sum5 - rtb_Gain1[2]) * helicopter_day4_P.K_pp -
    helicopter_day4_P.K_pd * rtb_Gain1[3]) + helicopter_day4_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_day4_X.Integrator_CSTATE >=
      helicopter_day4_P.Integrator_UpperSat) {
    helicopter_day4_X.Integrator_CSTATE = helicopter_day4_P.Integrator_UpperSat;
  } else {
    if (helicopter_day4_X.Integrator_CSTATE <=
        helicopter_day4_P.Integrator_LowerSat) {
      helicopter_day4_X.Integrator_CSTATE =
        helicopter_day4_P.Integrator_LowerSat;
    }
  }

  rtb_Backgain = helicopter_day4_X.Integrator_CSTATE;

  /* End of Integrator: '<S3>/Integrator' */

  /* Sum: '<S3>/Sum' */
  rtb_Derivative = helicopter_day4_B.Sum6 - rtb_Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<S3>/Sum1'
   */
  helicopter_day4_B.Sum2 = ((helicopter_day4_P.K_ep * rtb_Derivative +
    rtb_Backgain) - helicopter_day4_P.K_ed * rtb_Gain1[5]) +
    helicopter_day4_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (helicopter_day4_B.Sum2 - helicopter_day4_B.Sum1) *
    helicopter_day4_P.Backgain_Gain;

  /* Gain: '<S3>/K_ei' */
  helicopter_day4_B.K_ei = helicopter_day4_P.K_ei * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_day4_DW.TimeStampA >= helicopter_day4_M->Timing.t[0]) &&
      (helicopter_day4_DW.TimeStampB >= helicopter_day4_M->Timing.t[0])) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = helicopter_day4_DW.TimeStampA;
    lastU = &helicopter_day4_DW.LastUAtTimeA;
    if (helicopter_day4_DW.TimeStampA < helicopter_day4_DW.TimeStampB) {
      if (helicopter_day4_DW.TimeStampB < helicopter_day4_M->Timing.t[0]) {
        rtb_Derivative = helicopter_day4_DW.TimeStampB;
        lastU = &helicopter_day4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_day4_DW.TimeStampA >= helicopter_day4_M->Timing.t[0]) {
        rtb_Derivative = helicopter_day4_DW.TimeStampB;
        lastU = &helicopter_day4_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_day4_B.PitchCounttorad - *lastU) /
      (helicopter_day4_M->Timing.t[0] - rtb_Derivative);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S10>/Gain' */
  helicopter_day4_B.Gain_l = helicopter_day4_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* Sum: '<S4>/Sum3' incorporates:
     *  Constant: '<S4>/Constant'
     */
    rtb_Sum3_n = helicopter_day4_P.Constant_Value_l + helicopter_day4_B.Gain;

    /* ToFile: '<S4>/To File' */
    {
      if (!(++helicopter_day4_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_day4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = rtb_Sum3_n;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file travel.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file travel.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<S4>/To File1' */
    {
      if (!(++helicopter_day4_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile1_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_day4_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = helicopter_day4_B.Gain_d;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file travelrate.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile1_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file travelrate.mat.\n");
          }
        }
      }
    }
  }

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn1' */
  helicopter_day4_B.VectorConcatenate[0] = helicopter_day4_B.Gain_i;

  /* Gain: '<S12>/Gain' */
  helicopter_day4_B.VectorConcatenate[1] = helicopter_day4_P.Gain_Gain_c *
    rtb_Sum5;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* ToFile: '<S4>/To File2' */
    {
      if (!(++helicopter_day4_DW.ToFile2_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile2_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          helicopter_day4_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = helicopter_day4_B.VectorConcatenate[0];
          u[2] = helicopter_day4_B.VectorConcatenate[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file pitch.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile2_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitch.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<S4>/To File3' */
    {
      if (!(++helicopter_day4_DW.ToFile3_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile3_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile3_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_day4_DW.ToFile3_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = helicopter_day4_B.Gain_b;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file pitchrate.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile3_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitchrate.mat.\n");
          }
        }
      }
    }
  }

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In1' */
  helicopter_day4_B.VectorConcatenate1[0] = helicopter_day4_B.Gain_e;

  /* Gain: '<S11>/Gain' */
  helicopter_day4_B.VectorConcatenate1[1] = helicopter_day4_P.Gain_Gain_f *
    helicopter_day4_B.Sum6;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* ToFile: '<S4>/To File4' */
    {
      if (!(++helicopter_day4_DW.ToFile4_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile4_IWORK.Count*3)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile4_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[3];
          helicopter_day4_DW.ToFile4_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = helicopter_day4_B.VectorConcatenate1[0];
          u[2] = helicopter_day4_B.VectorConcatenate1[1];
          if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file elevation.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile4_IWORK.Count)*3)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elevation.mat.\n");
          }
        }
      }
    }

    /* ToFile: '<S4>/To File5' */
    {
      if (!(++helicopter_day4_DW.ToFile5_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile5_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile5_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_day4_DW.ToFile5_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = helicopter_day4_B.Gain_dg;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file elevationrate.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile5_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elevationrate.mat.\n");
          }
        }
      }
    }
  }

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_day4_P.BackmotorSaturation_UpperSat) {
    helicopter_day4_B.BackmotorSaturation =
      helicopter_day4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_day4_P.BackmotorSaturation_LowerSat) {
    helicopter_day4_B.BackmotorSaturation =
      helicopter_day4_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter_day4_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (helicopter_day4_B.Sum1 + helicopter_day4_B.Sum2) *
    helicopter_day4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_day4_P.FrontmotorSaturation_UpperSat) {
    helicopter_day4_B.FrontmotorSaturation =
      helicopter_day4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_day4_P.FrontmotorSaturation_LowerSat) {
    helicopter_day4_B.FrontmotorSaturation =
      helicopter_day4_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter_day4_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_day4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_day4_DW.HILWriteAnalog_Buffer[0] =
        helicopter_day4_B.FrontmotorSaturation;
      helicopter_day4_DW.HILWriteAnalog_Buffer[1] =
        helicopter_day4_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILWriteAnalog_channels, 2,
        &helicopter_day4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_day4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_day4_DW.TimeStampA == (rtInf)) {
    helicopter_day4_DW.TimeStampA = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeA;
  } else if (helicopter_day4_DW.TimeStampB == (rtInf)) {
    helicopter_day4_DW.TimeStampB = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeB;
  } else if (helicopter_day4_DW.TimeStampA < helicopter_day4_DW.TimeStampB) {
    helicopter_day4_DW.TimeStampA = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeA;
  } else {
    helicopter_day4_DW.TimeStampB = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeB;
  }

  *lastU = helicopter_day4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_day4_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter_day4_M->Timing.clockTick0)) {
    ++helicopter_day4_M->Timing.clockTickH0;
  }

  helicopter_day4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_day4_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter_day4_M->Timing.clockTick1)) {
      ++helicopter_day4_M->Timing.clockTickH1;
    }

    helicopter_day4_M->Timing.t[1] = helicopter_day4_M->Timing.clockTick1 *
      helicopter_day4_M->Timing.stepSize1 +
      helicopter_day4_M->Timing.clockTickH1 *
      helicopter_day4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_day4_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter_day4_T *_rtXdot;
  _rtXdot = ((XDot_helicopter_day4_T *) helicopter_day4_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_day4_P.TravelTransferFcn_A *
    helicopter_day4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_day4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_day4_P.PitchTransferFcn_A *
    helicopter_day4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_day4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_day4_P.ElevationTransferFcn_A *
    helicopter_day4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_day4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_day4_X.Integrator_CSTATE <=
          helicopter_day4_P.Integrator_LowerSat);
  usat = (helicopter_day4_X.Integrator_CSTATE >=
          helicopter_day4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_day4_B.K_ei > 0.0)) || (usat &&
       (helicopter_day4_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_day4_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_day4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_day4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_day4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_day4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_day4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      return;
    }

    if ((helicopter_day4_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_day4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter_day4_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_day4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_day4_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_analog_input_chan, 8U,
        &helicopter_day4_DW.HILInitialize_AIMinimums[0],
        &helicopter_day4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_day4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter_day4_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_day4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_day4_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_day4_DW.HILInitialize_AOMinimums[0],
         &helicopter_day4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day4_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_analog_output_cha, 8U,
        &helicopter_day4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_day4_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day4_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_day4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_day4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_day4_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_day4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_day4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_day4_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_encoder_channels, 8U,
        &helicopter_day4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_day4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_day4_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter_day4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter_day4_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &helicopter_day4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter_day4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter_day4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_day4_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_day4_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            helicopter_day4_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_day4_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_day4_DW.HILInitialize_Card,
          &helicopter_day4_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_day4_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_day4_DW.HILInitialize_Card,
          &helicopter_day4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_day4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_day4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_day4_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_day4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_day4_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_day4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_day4_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter_day4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_day4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_day4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_day4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            helicopter_day4_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_pwm_channels, 8U,
        &helicopter_day4_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_day4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_pwm_channels, 8U,
        &helicopter_day4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_day4_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_pwm_channels, 8U,
         &helicopter_day4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_day4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_day4_DW.HILInitialize_Card,
       helicopter_day4_P.HILReadEncoderTimebase_samples_,
       helicopter_day4_P.HILReadEncoderTimebase_channels, 3,
       &helicopter_day4_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/From Workspace3' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
      21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0,
      45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0,
      69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0,
      81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0,
      93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0,
      104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0,
      114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 121.0, 122.0, 123.0,
      124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0,
      134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
      144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0, 152.0, 153.0,
      154.0, 155.0, 156.0, 157.0, 158.0, 159.0, 160.0, 161.0, 162.0, 163.0,
      164.0, 165.0, 166.0, 167.0, 168.0, 169.0, 170.0, 171.0, 172.0, 173.0,
      174.0, 175.0, 176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
      184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0,
      194.0, 195.0, 196.0, 197.0, 198.0, 199.0, 200.0, 201.0, 202.0, 203.0,
      204.0, 205.0, 206.0, 207.0, 208.0, 209.0, 210.0, 211.0, 212.0, 213.0,
      214.0, 215.0, 216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
      224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0, 232.0, 233.0,
      234.0, 235.0, 236.0, 237.0, 238.0, 239.0, 240.0, 241.0, 242.0, 243.0,
      244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0, 253.0,
      254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
      264.0, 265.0, 266.0, 267.0, 268.0, 269.0, 270.0, 271.0, 272.0, 273.0,
      274.0, 275.0, 276.0, 277.0, 278.0, 279.0, 280.0, 281.0, 282.0, 283.0,
      284.0, 285.0, 286.0, 287.0, 288.0, 289.0, 290.0, 291.0, 292.0, 293.0,
      294.0, 295.0, 296.0, 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0,
      304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0, 313.0,
      314.0, 315.0, 316.0, 317.0, 318.0, 319.0, 320.0, 321.0, 322.0, 323.0,
      324.0, 325.0, 326.0, 327.0, 328.0, 329.0, 330.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0,
      0.030276326785146489, 0.026932439502780046, 0.028215911682544545,
      0.029202787911474702, 0.029473759284497483, 0.028837704743114864,
      0.027241925127196004, 0.024715803317617212, 0.02133546508541035,
      0.017193136035738153, 0.012355018537236296, 0.0067906711320689676,
      0.00026060365242739519, -0.0078213011881444, -0.018429630880583997,
      -0.019781553866394012, -0.023189297857591943, -0.026053548031819355,
      -0.028130591828808321, -0.029274870138849031, -0.029415571874832243,
      -0.028537765983943812, -0.02667145653228983, -0.023882705998332449,
      -0.020261140709447911, -0.015897487833188728, -0.010843040632249404,
      -0.0050437067811601516, 0.0017432981757041336, 0.0099800445077042645,
      0.020093431992002437, 0.020674124286280241, 0.023984678528729854,
      0.026659042472054521, 0.028485155486510167, 0.029345705750177913,
      0.029190592290310118, 0.028020937428785111, 0.025880166747354764,
      0.022845760173652856, 0.019015882904557042, 0.014483492124606879,
      0.0092866520328125091, 0.003320449744933058, -0.003796259950453339,
      -0.012858660502248001, -0.02080007634928226, -0.021795910510930768,
      -0.0249239846608047, -0.02736011059853382, -0.028911398279585446,
      -0.029478224962775818, -0.029025215274589667, -0.027566047225805045,
      -0.025154205858704582, -0.021872602513067402, -0.017815132072549179,
      -0.013050726372470751, -0.0075564879205772791, -0.001107312940889963,
      0.0068645056679439475, 0.0173251574617711, 0.019636966375636136,
      0.022681748852083395, 0.025649172037445656, 0.027842893418328712,
      0.029111580599587149, 0.029379135137563076, 0.028625280133317485,
      0.026874530653933793, 0.024187962965431284, 0.020653115567801021,
      0.01636868398370973, 0.011423092784506457, 0.005874767904365117,
      -0.00022980614892233487, -0.0066883364262043258, -0.012556194019801296,
      -0.0047405972972888854, 0.0013567147610118525, 0.00063974728872490583,
      0.00029092138018542023, 0.00012767864702154593, 5.3978979988238613E-5,
      2.18717789928899E-5, 8.4075364962203054E-6, 3.0045535858540592E-6,
      9.5393758418447811E-7, 2.3497765654865656E-7, 1.4564268733669016E-8,
      -3.471776697170222E-8, -3.3651582508488213E-8, -2.2726151121136792E-8,
      -1.3280596144680136E-8, -7.1408108672003334E-9, -3.6246026281605054E-9,
      -1.7588446314735917E-9, -8.211715699134148E-10, -3.6990198942542257E-10,
      -1.6077300233858521E-10, -6.7246468020605512E-11, -2.690081063096628E-11,
      -1.0167316479273221E-11, -3.5420706070816443E-12, -1.0728101656868717E-12,
      -2.312187913394758E-13, 1.2838628744149731E-14, 5.8189160187660406E-14,
      4.8856943442484029E-14, 3.1418103630363648E-14, 1.7887015318118849E-14,
      9.4536906322322743E-15, 4.736838573074935E-15, 2.2739136083132316E-15,
      1.0513597870706309E-15, 4.69128283712866E-16, 2.0189327642639878E-16,
      8.3510421630379014E-17, 3.2953928143817272E-17, 1.2225745607357191E-17,
      4.1362482773605261E-18, 1.1812941145897653E-18, 2.0679590015950937E-19,
      -5.6410706684890455E-20, -9.1773487295526457E-20, -6.9730086889831757E-20,
      -4.3073680767066E-20, -2.3966143635233335E-20, -1.2468596057471393E-20,
      -6.1715737218895242E-21, -2.9319708405864861E-21, -1.3426690825648184E-21,
      -5.9344110063552794E-22, -2.5281722644268342E-22, -1.0336237598314758E-22,
      -4.0194131699077054E-23, -1.4607145760385132E-23, -4.77557741917037E-24,
      -1.2642850441851539E-24, -1.5068325238362653E-25, 1.2284263239301592E-25,
      1.3915402871431002E-25, 9.8172928384081924E-26, 5.8628688034605707E-26,
      3.1960275082053395E-26, 1.6387097171449154E-26, 8.0174682092255871E-27,
      3.7705897015665525E-27, 1.710367118248786E-27, 7.4873098369231751E-28,
      3.1566132414441516E-28, 1.2748076776689399E-28, 4.8792659612336326E-29,
      1.7325521128582229E-29, 5.437756045808555E-30, 1.2992242811262308E-30,
      4.7449376356126741E-32, -2.2121119235370308E-31, -2.052317169579454E-31,
      -1.36680838102446E-31, -7.9297083629397084E-32, -4.2437467807833062E-32,
      -2.1465636406445488E-32, -1.0386231815229872E-32, -4.8366117336739973E-33,
      -2.1732485907253703E-33, -9.421301217535536E-34, -3.9292560923644258E-34,
      -1.566317203435365E-34, -5.8920597156370213E-35, -2.0376978716884584E-35,
      -6.0846864234368743E-36, -1.2532099984888608E-36, 1.2428421159126563E-37,
      3.63757091094929E-37, 2.9650075529733854E-37, 1.8851725479968654E-37,
      1.0664930667941454E-37, 5.6125441085845456E-38, 2.8029637986973488E-38,
      1.3418234926241576E-38, 6.1882505012809478E-39, 2.7543591413161764E-39,
      1.182226356176149E-39, 4.8753630356259764E-40, 1.9166337874727955E-40,
      7.0735234968437794E-41, 2.372881238627599E-41, 6.6555851726270862E-42,
      1.079115516827019E-42, -3.938800307904383E-43, -5.669000430769258E-43,
      -4.2153365832511452E-43, -2.5793699699133946E-43, -1.4271150464192315E-43,
      -7.3954089577967128E-44, -3.6491004386436549E-44, -1.7289369205844756E-44,
      -7.89761449516036E-45, -3.4818366978138257E-45, -1.4792961513277725E-45,
      -6.0288140789348143E-46, -2.33490197853063E-46, -8.4358964344230025E-47,
      -2.7304022242642941E-47, -7.0575685109049566E-48, -7.1039945260928813E-49,
      8.0136704230031863E-49, 8.5255960595229619E-49, 5.91605935252858E-49,
      3.5047113119280049E-49, 1.9009091043571467E-49, 9.7108653177505862E-50,
      4.7369738769819543E-50, 2.2219398538701142E-50, 1.0053712145996137E-50,
      4.3898772822162532E-51, 1.8455499760315087E-51, 7.4283206199770336E-52,
      2.8306212684356482E-52, 9.984769989855288E-53, 3.0959632331754044E-53,
      7.1528745857427332E-54, 5.4198213201512454E-56, -1.4009608092209364E-54,
      -1.2498689238282694E-54, -8.2149853354472729E-55, -4.7328944826684311E-55,
      -2.5213384237585408E-55, -1.2709601535319464E-55, -6.1320569077784877E-56,
      -2.8482073686009039E-56, -1.2766003379901573E-56, -5.5198268755778215E-57,
      -2.2953784514319913E-57, -9.1173904829177627E-58, -3.4131165752588971E-58,
      -1.1714476182506569E-58, -3.4456633948423622E-59, -6.7416255227779942E-60,
      1.0178294855235162E-60, 2.2656680998421016E-60, 1.797392108298489E-60,
      1.1305259917646952E-60, 6.3566052072574049E-61, 3.3312427665284766E-61,
      1.6582711436194747E-61, 7.91656025700363E-62, 3.6417315936873275E-62,
      1.6168559285634503E-62, 6.9213919484647994E-63, 2.845580257278038E-63,
      1.1143891272343723E-63, 4.0906904628380886E-64, 1.3601475012553954E-64,
      3.7418682307215567E-65, 5.5386967386549782E-66, -2.6815910117281844E-66,
      -3.4932914721263362E-66, -2.5459855523861545E-66, -1.5438504511182755E-66,
      -8.49534113830658E-67, -4.385327154474547E-67, -2.1571904760800144E-67,
      -1.0193420740759556E-67, -4.644580268634278E-68, -2.042488192949226E-68,
      -8.6539472346247816E-69, -3.5155423120535905E-69, -1.3558994701499604E-69,
      -4.8693246209280021E-70, -1.5595009829414331E-70, -3.92757634427486E-71,
      -3.142829264381253E-72, 5.1764633952843447E-72, 5.214236424387026E-72,
      3.562480475219851E-72, 2.0941567650450202E-72, 1.1302765722552591E-72,
      5.753271894521173E-73, 2.7982113559278484E-73, 1.3091149608815629E-73,
      5.9086306496113538E-74, 2.5733416721192578E-74, 1.0787898191274816E-74,
      4.3273280298994248E-75, 1.6415197256461397E-75, 5.7507507354760429E-76,
      1.7604057100682629E-76, 3.9187865600211868E-77, -1.004434181540047E-78,
      -8.8261456167586688E-78, -7.60163345983712E-78, -4.9344101666139289E-78,
      -2.8237825426321163E-78, -1.497596896679426E-78, -7.5236073876394134E-79,
      -3.6196999060053706E-79, -1.6769696671222056E-79, -7.4976141665589218E-80,
      -3.2333755223236837E-80, -1.3406024570311147E-80, -5.30560901712493E-81,
      -1.9762994635096654E-81, -6.7296480019807374E-82, -1.9479279904763237E-82,
      -3.5942159518222861E-83, 7.6731164278016E-84, 1.4065902107968231E-83,
      1.0884399793579652E-83, 6.7760007087612753E-84, 3.787275217811079E-84,
      1.9763853229816932E-84, 9.8014991277122109E-85, 4.6551331996056566E-85,
      2.1134344269478746E-85, 8.9334913569761612E-86, 3.0712329009909046E-86,
      1.2652593612371711E-87, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_day4_DW.FromWorkspace3_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day4_DW.FromWorkspace3_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day4_DW.FromWorkspace3_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
      21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0,
      45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0,
      69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0,
      81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0,
      93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0,
      104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0,
      114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 121.0, 122.0, 123.0,
      124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0,
      134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
      144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0, 152.0, 153.0,
      154.0, 155.0, 156.0, 157.0, 158.0, 159.0, 160.0, 161.0, 162.0, 163.0,
      164.0, 165.0, 166.0, 167.0, 168.0, 169.0, 170.0, 171.0, 172.0, 173.0,
      174.0, 175.0, 176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
      184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0,
      194.0, 195.0, 196.0, 197.0, 198.0, 199.0, 200.0, 201.0, 202.0, 203.0,
      204.0, 205.0, 206.0, 207.0, 208.0, 209.0, 210.0, 211.0, 212.0, 213.0,
      214.0, 215.0, 216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
      224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0, 232.0, 233.0,
      234.0, 235.0, 236.0, 237.0, 238.0, 239.0, 240.0, 241.0, 242.0, 243.0,
      244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0, 253.0,
      254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
      264.0, 265.0, 266.0, 267.0, 268.0, 269.0, 270.0, 271.0, 272.0, 273.0,
      274.0, 275.0, 276.0, 277.0, 278.0, 279.0, 280.0, 281.0, 282.0, 283.0,
      284.0, 285.0, 286.0, 287.0, 288.0, 289.0, 290.0, 291.0, 292.0, 293.0,
      294.0, 295.0, 296.0, 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0,
      304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0, 313.0,
      314.0, 315.0, 316.0, 317.0, 318.0, 319.0, 320.0, 321.0, 322.0, 323.0,
      324.0, 325.0, 326.0, 327.0, 328.0, 329.0, 330.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 0.034126705674757146,
      0.034126705674757167, 0.027997278980208082, 0.019676866165801232,
      0.01213151758694926, 0.0064560214255492175, 0.0027230174455281342,
      0.00057244016584080519, -0.0004670983909429, -0.00082067633093507947,
      -0.00080844176492946864, -0.000641325356079076, -0.00044105402286672069,
      -0.00026661864020831349, -0.00013821786571607849, -5.5322482490286809E-5,
      -8.59445289614425E-6, 1.3223287169540975E-5, 1.9959422817045024E-5,
      1.8860556343939483E-5, 1.4611962203748262E-5, 9.8593053079124371E-6,
      5.8413659100689611E-6, 2.9438319057710085E-6, 1.1082710579708094E-6,
      9.6939616992107843E-8, -3.5742798273933258E-7, -4.81286202877501E-7,
      -4.3819978544119416E-7, -3.3193891017208714E-7, -2.1978157833244276E-7,
      -1.2754277419030633E-7, -6.2337369346904421E-8, -2.1813137589718515E-8,
      -1.7112596992357591E-11, 9.3604843094659634E-9, 1.1519639619792348E-8,
      1.0141967652366724E-8, 7.5189723488907323E-9, 4.8855186277300747E-9,
      2.7747987556986222E-9, 1.3114772185483997E-9, 4.195578032065683E-10,
      -4.8042254408214484E-11, -2.3953229163471384E-10, -2.7393384772957879E-10,
      -2.3388642639335142E-10, -1.6983723605829283E-10, -1.0828821365902271E-10,
      -6.0136930835895229E-11, -2.7387982501581754E-11, -7.8198855597057063E-12,
      2.1616680382504411E-12, 6.0218192973609714E-12, 6.4764160674057313E-12,
      5.375317898638746E-12, 3.8255826104977579E-12, 2.3931601417740309E-12,
      1.2979711260359074E-12, 5.6708444906556166E-13, 1.3920673087632409E-13,
      -7.2687552569887E-14, -1.49267940421224E-13, -1.5231984779577734E-13,
      -1.2313714825963248E-13, -8.5933343376550779E-14, -5.2728186130204147E-14,
      -2.7890627032213185E-14, -1.1624463253759432E-14, -2.3013337470721183E-15,
      2.1691413257960389E-15, 3.6575625479759988E-15, 3.5654624518363985E-15,
      2.8120210361724178E-15, 1.924979750352112E-15, 1.1580892850770636E-15,
      5.964188689538416E-16, 2.3544051138600829E-16, 3.3037739576911892E-17,
      -6.0621946116204809E-17, -8.875238503639177E-17, -8.308748830449097E-17,
      -6.4030982515238781E-17, -4.3010385508897695E-17, -2.5344341529219536E-17,
      -1.2677644644520179E-17, -4.7061974833899953E-18, -3.3027904967634145E-19,
      1.6323261006686673E-18, 2.1443129726312945E-18, 1.9207491987308077E-18,
      1.4453549762974504E-18, 9.659855449979103E-19, 5.6111773421344676E-19,
      2.6019172428484486E-19, 8.39777762144559E-20, 5.8368483273509366E-21,
      -3.42410636898233E-20, -5.9081855454575967E-20, -5.2635023783119174E-20,
      -2.4865428638474475E-20, -1.3245915766135856E-20, -2.0055699115623676E-20,
      -1.3667228901884649E-20, 6.27569963541386E-21, 8.294446150999096E-21,
      -6.9569934277693056E-21, -6.8215962517170644E-21, 9.0614383071617065E-21,
      8.7763600530456325E-21, -7.5624047093998186E-21, -7.7734444976515711E-21,
      8.1511575195572367E-21, 8.0662000617239735E-21, -8.0443175727418752E-21,
      -8.06070981041989E-21, 8.0051195341499429E-21, 8.01013961456257E-21,
      -8.050456308170209E-21, -8.044148895075441E-21, 8.0281276713628719E-21,
      8.0313142581215136E-21, -8.0343095047537657E-21, -8.0333971751777475E-21,
      8.0344064867063523E-21, 8.0344122854236487E-21, -8.0331997327324377E-21,
      -8.03336470687617E-21, 8.0339691211483355E-21, 8.0338604137604019E-21,
      -8.0336903641660458E-21, -8.0337307726259446E-21, 8.033729917757349E-21,
      8.0337236619569352E-21, -8.03375567448868E-21, -8.0337522814646379E-21,
      8.03373155352252E-21, 8.0337349244090574E-21, -8.0337425265354165E-21,
      -8.0337409548755864E-21, 8.0337398291225548E-21, 8.0337402310002354E-21,
      -8.0337395592828379E-21, -8.0337395878005852E-21, 8.03374023428728E-21,
      8.0337401413442709E-21, -8.0337398438047538E-21, -8.0337398991689383E-21,
      8.0337399737104153E-21, 8.0337399547810983E-21, -8.0337399611846875E-21,
      -8.0337399632938968E-21, 8.0337399453278728E-21, 8.0337399474531681E-21,
      -8.0337399579901926E-21, -8.0337399562134515E-21, 8.0337399526619946E-21,
      8.033739953428104E-21, -8.0337399537961055E-21, -8.0337399536249656E-21,
      8.0337399540416766E-21, 8.0337399540116487E-21, -8.0337399536717747E-21,
      -8.0337399537229774E-21, 8.0337399538676764E-21, 8.0337399538398061E-21,
      -8.0337399538082223E-21, -8.0337399538169627E-21, 8.0337399538107471E-21,
      8.033739953810228E-21, -8.03373995382013E-21, -8.0337399538187954E-21,
      8.0337399538135427E-21, 8.0337399538143627E-21, -8.0337399538162074E-21,
      -8.0337399538158418E-21, 8.0337399538155815E-21, 8.0337399538157124E-21,
      -8.0337399538154912E-21, -8.033739953815428E-21, 8.03373995381585E-21,
      8.0337399538158147E-21, -8.0337399538154611E-21, -8.0337399538155333E-21,
      8.0337399538156627E-21, 8.03373995381567E-21, -8.0337399538156327E-21,
      -8.0337399538156673E-21, 8.0337399538155409E-21, 8.0337399538155439E-21,
      -8.0337399538157124E-21, -8.0337399538156778E-21, 8.033739953815568E-21,
      8.0337399538155168E-21, -8.0337399538157621E-21, -8.0337399538158042E-21,
      8.0337399538153663E-21, 8.0337399538153408E-21, -8.0337399538158674E-21,
      -8.0337399538157515E-21, 8.0337399538155815E-21, 8.033739953815759E-21,
      -8.0337399538150458E-21, -8.033739953814453E-21, 8.0337399538175721E-21,
      8.0337399538186464E-21, -8.0337399538113971E-21, -8.0337399538101287E-21,
      8.0337399538224547E-21, 8.033739953823377E-21, -8.0337399538077875E-21,
      -8.0337399538089747E-21, 8.0337399538189564E-21, 8.0337399538127739E-21,
      -8.0337399538287892E-21, -8.033739953844162E-21, 8.0337399537656292E-21,
      8.0337399537376566E-21, -8.0337399539279685E-21, -8.0337399539669852E-21,
      8.0337399536241275E-21, 8.03373995358952E-21, -8.0337399540603913E-21,
      -8.0337399540481736E-21, 8.0337399536467467E-21, 8.0337399537881445E-21,
      -8.033739953592962E-21, -8.0337399531998512E-21, 8.03373995500061E-21,
      8.0337399557713017E-21, -8.0337399508806674E-21, -8.033739949718477E-21,
      8.0337399591798531E-21, 8.033739960397423E-21, -8.0337399463246228E-21,
      -8.0337399461161559E-21, 8.0337399604703631E-21, 8.03373995744307E-21,
      -8.0337399561004235E-21, -8.0337399659356317E-21, 8.0337399268538713E-21,
      8.0337399060410822E-21, -8.0337400289561641E-21, -8.0337400626877392E-21,
      8.033739806334082E-21, 8.0337397663176453E-21, -8.03374017646179E-21,
      -8.0337401967496824E-21, 8.03373972006598E-21, 8.0337397786771066E-21,
      -8.0337399953427538E-21, -8.0337397560834567E-21, 8.03374053030515E-21,
      8.0337410817862929E-21, -8.0337380755592839E-21, -8.0337371175289234E-21,
      8.0337439334782043E-21, 8.03374518956884E-21, -8.0337334957066015E-21,
      -8.0337325547832972E-21, 8.0337476342920508E-21, 8.033746721143968E-21,
      -8.0337360041545221E-21, -8.0337416100902153E-21, 8.0337288790149463E-21,
      8.0337145660915274E-21, -8.03378553377174E-21, -8.0338122433142549E-21,
      8.0336345170231633E-21, 8.0335962421161546E-21, -8.0339238597301463E-21,
      -8.0339600511087033E-21, 8.0334972298602442E-21, 8.0335023197526475E-21,
      -8.0339252198033014E-21, -8.0338001607018717E-21, 8.0339084561502647E-21,
      8.0342757558293432E-21, -8.0326628432999287E-21, -8.0319179157724587E-21,
      8.0365242905696208E-21, 8.0376870116063E-21, -8.0284979382763651E-21,
      -8.02721684910901E-21, 8.04127392429419E-21, 8.0416122043278519E-21,
      -8.0267845615047849E-21, -8.02974274743516E-21, 8.0317500073280385E-21,
      8.0215947651436689E-21, -8.061371087086564E-21, -8.0831302920357848E-21,
      7.955994467516551E-21, 7.92193100147853E-21, -8.18243153265119E-21,
      -8.2162932747579733E-21, 7.8301075750910018E-21, 7.836204726661047E-21,
      -8.179009962597832E-21, -8.058482950010484E-21, 8.2190810532562947E-21,
      8.531880888213113E-21, -7.1266431356349854E-21, -6.6635962723618189E-21,
      9.8253451612374434E-21, 1.0040676437268353E-20, -6.2532236041160294E-21,
      -7.2002857190561469E-21, 6.9596821150786258E-21, 4.056623883444154E-21,
      -1.5464497525568774E-20, -1.8092620451648823E-20, -7.7526120741398529E-22,
      8.9333778751335537E-21, 1.000925135467681E-20, 6.9967172698768171E-21,
      2.8741071592696922E-21, -1.0943526084200877E-21, -4.6063565896110724E-21,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      2.894449426580702E-17, 1.9296329510538012E-17, -0.00612942669454908,
      -0.0083204128144068485, -0.007545348578851965, -0.0056754961614000421,
      -0.0037330039800210863, -0.0021505772796873296, -0.0010395385567837034,
      -0.00035357793999217876, 1.2234566005610206E-5, 0.00016711640885039254,
      0.00020027133321235549, 0.00017443538265840726, 0.000128400774492235,
      8.2895383225791688E-5, 4.6728029594142557E-5, 2.1817740065685239E-5,
      6.7361356475040295E-6, -1.0988664731055426E-6, -4.2485941401912454E-6,
      -4.7526568958358261E-6, -4.0179393978434786E-6, -2.8975340042979518E-6,
      -1.8355608478001958E-6, -1.0113314409787018E-6, -4.5436759973143866E-7,
      -1.2385822013816823E-7, 4.3086417436306092E-8, 1.0626087526910696E-7,
      1.1215733183964452E-7, 9.223880414213643E-8, 6.5205404843401813E-8,
      4.0524231757185916E-8, 2.1796024992726174E-8, 9.3775969064583138E-9,
      2.1591553103263809E-9, -1.377671967425622E-9, -2.6229953034759919E-9,
      -2.6334537211606588E-9, -2.1107198720314563E-9, -1.4633215371502229E-9,
      -8.9191941534182922E-10, -4.676000576147826E-10, -1.9149003722649918E-10,
      -3.4401556094864942E-11, 4.0047421336227649E-11, 6.4049190335058566E-11,
      6.1549022399270221E-11, 4.8151282823127479E-11, 3.2748948334313468E-11,
      1.9568096941876054E-11, 9.9815535979561458E-12, 3.8601512591105327E-12,
      4.54596770044758E-13, -1.1010981687669877E-12, -1.5497352881409825E-12,
      -1.4324224687237276E-12, -1.0951890157381241E-12, -7.3088667697034606E-13,
      -4.2787771818923716E-13, -2.1189428344621092E-13, -7.6580387851337073E-14,
      -3.0519073745533722E-15, 2.9182699536144974E-14, 3.72038048830817E-14,
      3.3205157246346612E-14, 2.483755909799096E-14, 1.6266163778453753E-14,
      9.3231295066873109E-15, 4.4704750728681737E-15, 1.4884212221799629E-15,
      -9.2100096139607683E-17, -7.5344141566398029E-16, -8.8704128582030508E-16,
      -7.6689046527504852E-16, -5.616704161232222E-16, -3.6097835756783336E-16,
      -2.0240277180909648E-16, -9.3659685693116657E-17, -2.8130438920186924E-17,
      5.6648967319008117E-18, 1.905650578925225E-17, 2.1020597006341062E-17,
      1.7666043979678162E-17, 1.2666696884699357E-17, 7.9714471611301916E-18,
      4.3759184337136523E-18, 1.9626051503450084E-18, 5.1198687196262533E-19,
      -2.2356377390048563E-19, -4.7539422243335736E-19, -4.7936943129954088E-19,
      -4.0486781078446353E-19, -3.0092600992860156E-19, -1.7621394807038897E-19,
      -7.8140927887105123E-20, -4.0077912017174193E-20, -2.484079176475268E-20,
      6.4468316714567816E-21, 2.7769595144644684E-20, 1.1619512872338618E-20,
      -6.80978334948782E-21, 6.388470213739027E-21, 1.9942928537298496E-20,
      2.0187465155852359E-21, -1.5251439578768338E-20, 1.3539717605224249E-22,
      1.5883034558878756E-20, -2.8507825411607194E-22, -1.6338764762445486E-20,
      -2.1103978825175461E-22, 1.5924602017208859E-20, -8.4957457833261267E-23,
      -1.611051763446578E-20, -1.6392237678015134E-23, 1.6065829344569821E-20,
      5.0200804126273189E-24, -1.6060595922732804E-20, 6.3074130947694779E-24,
      1.6072276566438304E-20, 3.1865867586428838E-24, -1.6065623762875278E-20,
      9.1232957601733075E-25, 1.6067803661884128E-20, 5.7987172979132463E-27,
      -1.6067612018156067E-20, -1.6497414373240768E-25, 1.606733382802448E-20,
      -1.0870738793329992E-25, -1.6067550777926449E-20, -4.0408459900274541E-26,
      1.6067460690383331E-20, -6.2558004143917429E-27, -1.6067479336445622E-20,
      3.3930240438665075E-27, 1.6067483834987157E-20, 3.3708865376011431E-27,
      -1.6067477450944507E-20, 1.5716598299026646E-27, 1.6067480783998176E-20,
      4.0187768188271107E-28, -1.6067479790283027E-20, -2.8517746197744092E-29,
      1.6067479822087876E-20, -9.2943008781114131E-29, -1.606747998514901E-20,
      -5.5364184669950787E-29, 1.6067479872879367E-20, -1.8929319336576917E-29,
      -1.6067479915965751E-20, -2.1092099662993464E-30, 1.6067479908621789E-20,
      2.1252973219454674E-30, -1.6067479905443364E-20, 1.7767410892656217E-30,
      1.6067479908875434E-20, 7.6611015620014108E-31, -1.6067479907224187E-20,
      1.7113846113320023E-31, 1.606747990766666E-20, -3.0028122803357921E-32,
      -1.6067479907683413E-20, -5.1201701118734886E-32, 1.6067479907590607E-20,
      -2.7871141017250743E-32, -1.606747990764806E-20, -8.741890984945923E-33,
      1.6067479907627705E-20, -5.1959160161145717E-34, -1.606747990763032E-20,
      1.3355534745070436E-33, 1.6067479907632385E-20, 8.1705793654950138E-34,
      -1.6067479907630621E-20, 3.6615218419260107E-34, 1.6067479907631461E-20,
      1.2879565962922901E-34, -1.6067479907631211E-20, 6.3297983273428885E-35,
      1.6067479907631335E-20, -3.2427739683298266E-35, -1.6067479907631277E-20,
      -7.2770364921857216E-35, 1.6067479907631217E-20, 8.776362313755874E-36,
      -1.6067479907631283E-20, -3.5171338532038767E-35, 1.6067479907631247E-20,
      2.0596604119704041E-36, -1.6067479907631193E-20, 3.4781365950634432E-35,
      1.60674799076312E-20, -4.9700945653084382E-35, -1.6067479907631329E-20,
      -4.1842244752642925E-35, 1.6067479907631151E-20, -2.7740917932196564E-35,
      -1.6067479907631166E-20, 1.14862663311545E-34, 1.6067479907631332E-20,
      1.7844118678187806E-34, -1.6067479907630826E-20, 5.9210031483524454E-34,
      1.6067479907632063E-20, 1.0739073629795511E-33, -1.6067479907629989E-20,
      1.269399890190878E-33, 1.6067479907632553E-20, 9.1948332843932835E-34,
      -1.6067479907631127E-20, -1.1854962166855984E-33, 1.6067479907627937E-20,
      -6.1820020070698775E-33, -1.6067479907641524E-20, -1.5373984079846583E-32,
      1.6067479907609815E-20, -2.797366542162593E-32, -1.6067479907665571E-20,
      -3.9017108689750415E-32, 1.60674799075911E-20, -3.4608213112564313E-32,
      -1.6067479907649953E-20, 1.2216889411652919E-32, 1.60674799076949E-20,
      1.4139733016018097E-31, -1.606747990738106E-20, 3.9311136391332663E-31,
      1.6067479908200426E-20, 7.7069282912698943E-31, -1.6067479906651942E-20,
      1.1621893244776974E-30, 1.6067479908898344E-20, 1.2175707489825278E-30,
      -1.6067479906721986E-20, 2.0846589468450981E-31, 1.6067479906586536E-20,
      -3.02729163813431E-30, -1.6067479913543482E-20, -9.835208961180069E-30,
      1.606747989278945E-20, -2.0812789458828752E-29, -1.6067479934997219E-20,
      -3.3731574645830569E-29, 1.6067479869021871E-20, -4.0016436897391633E-29,
      -1.6067479942779415E-20, -2.0287892435553168E-29, 1.6067479916815631E-20,
      5.8611126419479665E-29, -1.6067479774019884E-20, 2.3925929979632327E-28,
      1.6067480286388617E-20, 5.5148114451041168E-28, -1.6067479157345569E-20,
      9.58030361133639E-28, 1.6067481051007129E-20, 1.2560906373358395E-27,
      -1.6067478685275431E-20, 9.409233025598875E-28, 1.6067480189075422E-20,
      -9.1314808098398858E-28, -1.6067482725298492E-20, -5.6059356929505929E-27,
      1.6067470489105207E-20, -1.4312923419326174E-26, -1.6067500099863244E-20,
      -2.6709542517248131E-26, 1.6067446760337402E-20, -3.8274907010066321E-26,
      -1.6067520101846296E-20, -3.6191378556728976E-26, 1.6067457280968941E-20,
      5.0898924014225344E-27, -1.6067427539555904E-20, 1.2505910142878393E-25,
      1.6067708616852142E-20, 3.6729967907979207E-25, -1.6066938599129267E-20,
      7.44927527472194E-25, 1.6068442206342036E-20, 1.1627210366777575E-24,
      -1.6066184949882634E-20, 1.281089167355564E-24, 1.6068490773403173E-20,
      3.3828003366337821E-25, -1.6068396765832607E-20, -2.9581859303747415E-24,
      1.6061492754763254E-20, -1.0155242184366673E-23, -1.6082965852230192E-20,
      -2.1759204949220672E-23, 1.6039124759552336E-20, -3.4063466038020712E-23,
      -1.61043625341297E-20, -3.386174210678452E-23, 1.6046400849849002E-20,
      6.0971515700451617E-24, -1.6015214689258873E-20, 1.2052701258734851E-22,
      1.6277564003266779E-20, 3.1279983495681812E-22, -1.5658524023848092E-20,
      4.6304686327316663E-22, 1.6488941433599219E-20, 2.1533127603091066E-22,
      -1.6293900041384412E-20, -9.470621149401173E-22, 1.415996783413477E-20,
      -2.9030582316344722E-21, -1.9521121409012923E-20, -2.6281229260800504E-21,
      1.7317359244234827E-20, 9.7086390825475453E-21, 1.0758734795432311E-21,
      -3.0125340847999881E-21, -4.1226101106071347E-21, -3.9684597676897807E-21,
      -3.512003981190984E-21, -3.2288545788812816E-21, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -5.3600915307050033E-18,
      0.010830111726692335, 0.0038712632766769984, -0.0013694645004707433,
      -0.0033038506866292943, -0.0034321982137854377, -0.0027959968881194428,
      -0.0019630993405024984, -0.0012120269138008628, -0.00064635577002667473,
      -0.00027366142806417533, -5.8581585688823944E-5, 4.5649657791549552E-5,
      8.1338757208323481E-5, 8.0403681476556523E-5, 6.3904260579196015E-5,
      4.4014103142364166E-5, 2.6647755003242265E-5, 1.3843700654831698E-5,
      5.5652680492170254E-6, 8.906307609078608E-7, -1.2981756675365988E-6,
      -1.9796493531895222E-6, -1.8764051694829584E-6, -1.4563346637688552E-6,
      -9.8410192812972059E-7, -5.8397851644071477E-7, -2.9497523458622487E-7,
      -1.1162323504266527E-7, -1.0418475761738439E-8, 3.5194136604499755E-8,
      4.7765435390220913E-8, 4.3609276265145439E-8, 3.3090953168600283E-8,
      2.1942176706963227E-8, 1.2754297077773038E-8, 6.2492361006831174E-9,
      2.2003674303302525E-9, 1.8479025470688128E-11, -9.2362080036421094E-10,
      -1.1438910436229658E-9, -1.0096129913026338E-9, -7.4973179075115079E-10,
      -4.8786004281993634E-10, -2.7756034722545004E-10, -1.315442346726741E-10,
      -4.2408834112783205E-11, 4.4175580244985525E-12, 2.3672526604125911E-11,
      2.7214454414486167E-11, 2.3289305892176291E-11, 1.6938506757860495E-11,
      1.0815933456336163E-11, 6.0172896171056781E-12, 2.7487644178801021E-12,
      7.926989537019246E-13, -2.0728055078821989E-13, -5.9585931210504433E-13,
      -6.436874487232232E-13, -5.3538789862784964E-13, -3.8162210691938127E-13,
      -2.390867336368829E-13, -1.2991780444419812E-13, -5.6955472625087271E-14,
      -1.4172527286466517E-14, 7.0652285800280149E-15, 1.478474698316329E-14,
      1.5144837125923748E-14, 1.2267678631731372E-14, 8.5741770492217072E-15,
      5.2690044252730739E-15, 2.7926302600277874E-15, 1.1685269662000559E-15,
      2.360582143434862E-16, -2.1229502780677304E-16, -3.6260423227641748E-16,
      -3.5460370522868585E-16, -2.8018791911159728E-16, -1.921386502898735E-16,
      -1.1578392226273688E-16, -5.9713131291490513E-17, -2.3661694562768456E-17,
      -3.4703616475915404E-18, 5.9271749027003231E-18, 8.8333689751579589E-18,
      8.29605795533802E-18, 6.3529559573788706E-18, 4.2640941466248417E-18,
      2.5631039917052029E-18, 1.2996477602746128E-18, 4.4496035758441547E-19,
      7.0238145104145963E-21, -1.3163724997567158E-19, -1.8365523766581096E-19,
      -2.2035430569578889E-19, -1.7328566257325082E-19, -6.7253714754889691E-20,
      -2.6922536633568352E-20, -5.5282243244406824E-20, -3.7675287142567753E-20,
      2.8535653352358755E-20, 3.2562806779985395E-20, -2.3320053866387937E-20,
      -2.3949433667179498E-20, 3.16703182170945E-20, 3.0514769857505519E-20,
      -2.718707139825574E-20, -2.7824571658408982E-20, 2.8567511596185233E-20,
      2.8365331241356873E-20, -2.8496150141286676E-20, -2.8510138426230185E-20,
      2.8287362986823E-20, 2.8315634698773151E-20, -2.8436782896125252E-20,
      -2.8415749992419011E-20, 2.8377916470818148E-20, 2.8386409519659008E-20,
      -2.83886841135927E-20, -2.8387033502339781E-20, 2.8392547704496981E-20,
      2.8392053624905288E-20, -2.8388035229611393E-20, -2.8388662904519979E-20,
      2.8390264657990974E-20, 2.8389946533381395E-20, -2.8389644794041508E-20,
      -2.8389736245761009E-20, 2.8389636827776005E-20, 2.8389636006388021E-20,
      -2.8389756684072738E-20, -2.8389740303766475E-20, 2.838967995927812E-20,
      2.8389690798285861E-20, -2.8389707846837153E-20, -2.8389703805031647E-20,
      2.83897038441466E-20, 2.8389704476222108E-20, -2.8389701297160056E-20,
      -2.838970163240209E-20, 2.8389703699295794E-20, 2.8389703363654756E-20,
      -2.8389702603186945E-20, -2.8389702760159564E-20, 2.8389702873992767E-20,
      2.8389702833663409E-20, -2.8389702900061577E-20, -2.8389702897337945E-20,
      2.8389702832961359E-20, 2.8389702842198234E-20, -2.8389702871917752E-20,
      -2.8389702866395112E-20, 2.8389702858913133E-20, 2.8389702860807718E-20,
      -2.8389702860191824E-20, -2.83897028599773E-20, 2.838970286176307E-20,
      2.8389702861552578E-20, -2.8389702860501465E-20, -2.8389702860678446E-20,
      2.8389702861033907E-20, 2.8389702860957393E-20, -2.8389702860919808E-20,
      -2.8389702860936996E-20, 2.8389702860895896E-20, 2.8389702860898839E-20,
      -2.8389702860932495E-20, -2.8389702860927397E-20, 2.8389702860913163E-20,
      2.8389702860915932E-20, -2.8389702860918917E-20, -2.83897028609181E-20,
      2.8389702860918766E-20, 2.8389702860918814E-20, -2.8389702860917731E-20,
      -2.8389702860917864E-20, 2.8389702860918489E-20, 2.8389702860918405E-20,
      -2.8389702860918116E-20, -2.8389702860918189E-20, 2.8389702860918297E-20,
      2.8389702860918291E-20, -2.8389702860918225E-20, -2.8389702860918225E-20,
      2.8389702860918243E-20, 2.8389702860918225E-20, -2.8389702860918267E-20,
      -2.8389702860918267E-20, 2.8389702860918219E-20, 2.8389702860918267E-20,
      -2.8389702860918164E-20, -2.8389702860918158E-20, 2.8389702860918339E-20,
      2.8389702860918363E-20, -2.8389702860918128E-20, -2.838970286091817E-20,
      2.8389702860918339E-20, 2.8389702860918309E-20, -2.8389702860918279E-20,
      -2.8389702860918357E-20, 2.838970286091811E-20, 2.838970286091805E-20,
      -2.8389702860918514E-20, -2.8389702860918556E-20, 2.8389702860917924E-20,
      2.8389702860917978E-20, -2.8389702860918351E-20, -2.838970286091808E-20,
      2.8389702860918893E-20, 2.8389702860919615E-20, -2.83897028609159E-20,
      -2.8389702860914608E-20, 2.83897028609235E-20, 2.8389702860925351E-20,
      -2.8389702860909257E-20, -2.8389702860907536E-20, 2.83897028609299E-20,
      2.8389702860929449E-20, -2.8389702860909829E-20, -2.8389702860916329E-20,
      2.83897028609086E-20, 2.8389702860890287E-20, -2.8389702860972891E-20,
      -2.8389702861009086E-20, 2.8389702860781207E-20, 2.8389702860726119E-20,
      -2.838970286117078E-20, -2.8389702861229407E-20, 2.8389702860562343E-20,
      2.8389702860549722E-20, -2.8389702861241335E-20, -2.8389702861103469E-20,
      2.8389702861005873E-20, 2.8389702861463094E-20, -2.8389702859680032E-20,
      -2.8389702858703808E-20, 2.8389702864421142E-20, 2.83897028660157E-20,
      -2.8389702853986712E-20, -2.838970285207217E-20, 2.83897028714686E-20,
      2.8389702872497012E-20, -2.8389702849670854E-20, -2.8389702852299664E-20,
      2.8389702863404341E-20, 2.8389702852316624E-20, -2.8389702887174861E-20,
      -2.8389702912992975E-20, 2.8389702773586125E-20, 2.8389702728399944E-20,
      -2.8389703047587847E-20, -2.8389703107398089E-20, 2.8389702555732158E-20,
      2.8389702509649686E-20, -2.8389703227983163E-20, -2.8389703188406265E-20,
      2.8389702661762082E-20, 2.8389702920524625E-20, -2.8389702363653934E-20,
      -2.8389701695681341E-20, 2.8389704971648725E-20, 2.8389706226021787E-20,
      -2.8389697934313918E-20, -2.8389696124435072E-20, 2.8389711508851E-20,
      2.8389713249095166E-20, -2.8389691345452868E-20, -2.8389691486026363E-20,
      2.8389711920921172E-20, 2.8389706252152263E-20, -2.8389709933548189E-20,
      -2.8389726828476721E-20, 2.8389653888412573E-20, 2.83896193248832E-20,
      -2.838983129902064E-20, -2.8389886000782793E-20, 2.8389457984811522E-20,
      2.8389395403942789E-20, -2.8390062636294624E-20, -2.8390086935044339E-20,
      2.8389348733805178E-20, 2.8389469211274587E-20, -2.8389678356459427E-20,
      -2.8389225401979758E-20, 2.8390891255698793E-20, 2.8391920570338095E-20,
      -2.8386096029728587E-20, -2.8384350965547523E-20, 2.8397067476767817E-20,
      2.839912170310511E-20, -2.8378618608855192E-20, -2.8378048459193894E-20,
      2.8399788913717114E-20, 2.8394684048276153E-20, -2.8395040475201946E-20,
      -2.841228864361877E-20, 2.8341685093799104E-20, 2.8308128295042474E-20,
      -2.85103149336052E-20, -2.8547941675682426E-20, 2.8208213956918827E-20,
      2.8219804303698779E-20, -2.8485276457026831E-20, -2.8316225540501326E-20,
      2.8753915331075472E-20, 2.9170235423228066E-20, -2.7116397287635096E-20,
      -2.6692679488681431E-20, 3.0148737866802778E-20, 2.9362530928429664E-20,
      -2.9848315362300662E-20, -3.524176258431447E-20, 1.344388203899904E-20,
      1.5253272557126295E-20, 7.2238258017616959E-21, 1.9613983466521128E-21,
      -2.7236893753660653E-22, -8.0651379197885E-22, -5.0029795854925348E-22,
      -5.2860030590571592E-23, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.01083011172669234, -0.0069588484500153367, -0.0052407277771477408,
      -0.0019343861861585508, -0.00012834752715614234, 0.0006362013256659961,
      0.00083289754761694309, 0.00075107242670163527, 0.0005656711437741881,
      0.00037269434196249957, 0.00021507984237535146, 0.00010423124348037349,
      3.568909941677397E-5, -9.35075731766972E-7, -1.6499420897360489E-5,
      -1.9890157436831883E-5, -1.736634813912189E-5, -1.2804054348410564E-5,
      -8.2784326056146789E-6, -4.6746372883091652E-6, -2.1888064284444604E-6,
      -6.8147368565292222E-7, 1.032441837065639E-7, 4.2007050571410336E-7,
      4.7223273563913454E-7, 4.0012341168900545E-7, 2.8900328185448985E-7,
      1.8335199954355966E-7, 1.0120475928092683E-7, 4.5612612366238195E-8,
      1.2571298785721178E-8, -4.1561591250754926E-9, -1.051832309654515E-8,
      -1.114877646163705E-8, -9.1878796291901953E-9, -6.5050609770899175E-9,
      -4.0488686703528657E-9, -2.1818884048595646E-9, -9.42099825834899E-10,
      -2.2027024325875419E-10, 1.3427805232033163E-10, 2.5988120055148292E-10,
      2.6187174793121445E-10, 2.1029969559448628E-10, 1.4601611255277589E-10,
      8.9135400559890907E-11, 4.682639213728175E-11, 1.9254968579627375E-11,
      3.5419278103602514E-12, -3.92514852230988E-12, -6.3507991343158E-12,
      -6.1225733015243336E-12, -4.7986438392304853E-12, -3.2685251992255773E-12,
      -1.9560654641781762E-12, -9.9997950449014443E-13, -3.885787613168246E-13,
      -4.7828136618179209E-14, 1.0829955009537372E-13, 1.5376579170846847E-13,
      1.4253537328249837E-13, 1.0916892919268478E-13, 7.2962331819110921E-14,
      4.2782945338620741E-14, 2.1237755866494531E-14, 7.7195184031352685E-15,
      3.6009014276045512E-16, -2.8771584941923747E-15, -3.6935015825096658E-15,
      -3.3051726239486337E-15, -2.4763741652452849E-15, -1.6241032938277319E-15,
      -9.3246875185656932E-16, -4.4835324215025939E-16, -1.5030920446964454E-16,
      8.00052704773154E-18, 7.4415786117088589E-17, 8.8049268821723891E-17,
      7.6354728027136576E-17, 5.6070790971246382E-17, 3.605143672872206E-17,
      2.0191332915176917E-17, 9.3975365502918635E-18, 2.9061940724576367E-18,
      -5.373110198199349E-19, -1.9431019979591451E-18, -2.0888618107540297E-18,
      -1.7009901549196391E-18, -1.2634562314305895E-18, -8.5468740269019766E-19,
      -4.3793654307400088E-19, -1.3866106448608624E-19, -5.2017987690139439E-20,
      -3.6699068029977878E-20, 4.7068643122538113E-20, 1.0603194781836114E-19,
      4.0331178121321324E-20, -2.8359706610838488E-20, 1.7606956101839092E-20,
      6.621094049492652E-20, 4.0271534276266468E-21, -5.5882860646373347E-20,
      -6.2937980079157305E-22, 5.5619751884274034E-20, -1.1555483595889985E-21,
      -5.77018412557613E-20, -6.3750026015325134E-22, 5.6392083254594191E-20,
      -2.0218035482836164E-22, -5.6861481382643549E-20, -1.3988284943509478E-23,
      5.67975014130532E-20, 2.8271711950164873E-23, -5.67524175948984E-20,
      2.1032903706241722E-23, 5.6793666463237153E-20, 8.4930488408716414E-24,
      -5.6775093633251713E-20, 1.6506112529102332E-24, 5.6779581206836768E-20,
      -4.9407959169865254E-25, -5.6780088854516627E-20, -6.2767490856674785E-25,
      5.6778927562510946E-20, -3.1812460958023938E-25, -5.6779591327422873E-20,
      -9.145171949784843E-26, 5.677937307353702E-20, -8.2138798280046823E-28,
      -5.6779392690460758E-20, 1.6380306233876603E-26, 5.6779420263044619E-20,
      1.0839007737064251E-26, -5.6779398645123038E-20, 4.0418055187637712E-27,
      5.6779407649178209E-20, 6.32075508005289E-28, -5.6779405773382231E-20,
      -3.3524202199843487E-28, 5.67794053316979E-20, -3.3564103291330297E-28,
      -5.6779405966841725E-20, -1.5697260212972342E-28, 5.6779405634152314E-20,
      -4.0329350524897141E-29, -5.6779405733725046E-20, 2.7236081447228376E-30,
      5.6779405730299286E-20, 9.2368700955840258E-30, -5.6779405714115962E-20,
      5.52267741921794E-30, 5.6779405725308227E-20, 1.8945854607161072E-30,
      -5.6779405720999536E-20, 2.1455042495066674E-31, 5.6779405721740381E-20,
      -2.1050205701383365E-31, -5.6779405722054043E-20, -1.7700188098397293E-31,
      5.6779405721712359E-20, -7.651272875468286E-32, -5.67794057218772E-20,
      -1.7206816138573364E-32, 5.6779405721832886E-20, 2.94360191834843E-33,
      -5.6779405721831334E-20, 5.1096743890873321E-33, 5.6779405721840566E-20,
      2.7762329393378582E-33, -5.6779405721834848E-20, 8.3065653840171311E-34,
      5.6779405721836883E-20, 6.2763367128964393E-35, -5.6779405721836594E-20,
      -1.3555660495149091E-34, 5.6779405721836365E-20, -8.5776601742918E-35,
      -5.6779405721836546E-20, -2.2863132200908164E-35, 5.6779405721836461E-20,
      -4.1842244752642926E-36, -5.67794057218365E-20, -1.3549695664039448E-35,
      5.67794057218365E-20, -1.673689790105717E-35, -5.67794057218365E-20,
      2.3765087449352663E-35, 5.67794057218365E-20, 4.6026469227907219E-35,
      -5.6779405721836449E-20, -1.7672627788591863E-36, 5.6779405721836509E-20,
      1.4644785663425023E-35, -5.6779405721836509E-20, -2.6949426334000092E-35,
      5.6779405721836509E-20, -2.5105346851585757E-35, -5.677940572183657E-20,
      -7.5681049272486237E-35, 5.6779405721836461E-20, -5.0210693703171514E-35,
      -5.6779405721836582E-20, -3.9320339857580809E-35, 5.6779405721836485E-20,
      5.6487030416067953E-35, -5.6779405721836377E-20, 3.1493452719853252E-34,
      5.6779405721836943E-20, 7.2177872198309044E-34, -5.6779405721835462E-20,
      1.3344243704453229E-33, 5.6779405721838134E-20, 1.8431508813539208E-33,
      -5.6779405721834608E-20, 1.6842157298013037E-33, 5.6779405721837448E-20,
      -4.43527794378015E-34, -5.6779405721839326E-20, -6.5138404857482573E-33,
      5.6779405721824918E-20, -1.8322718977182337E-32, -5.6779405721863172E-20,
      -3.619541201958443E-32, 5.6779405721790323E-20, -5.5087407329092041E-32,
      -5.6779405721896936E-20, -5.862539175462273E-32, 5.6779405721791756E-20,
      -1.2615436792921843E-32, -5.6779405721791058E-20, 1.3785317800431169E-31,
      5.6779405722109329E-20, 4.57222761085555E-31, -5.6779405721143139E-20,
      9.762319982151883E-31, 5.6779405723124945E-20, 1.5945451841560929E-30,
      -5.6779405720002386E-20, 1.9145561757299767E-30, 5.6779405723540753E-20,
      1.0284258889895471E-30, -5.677940572216789E-20, -2.6288205208942984E-30,
      5.6779405715704036E-20, -1.1087724134196908E-29, -5.6779405739491485E-20,
      -2.5818120339999066E-29, 5.6779405686579088E-20, -4.5186174439774507E-29,
      -5.6779405775987809E-20, -5.9810247607032232E-29, 5.6779405663130265E-20,
      -4.6082475072508632E-29, -5.6779405737632818E-20, 3.9576887875747768E-29,
      5.6779405850168348E-20, 2.5876255063667611E-28, -5.6779405284178547E-20,
      6.6797257161920246E-28, 5.6779406667330047E-20, 1.2543730629269751E-27,
      -5.6779404160335736E-20, 1.8098788715600952E-27, 5.6779407633286037E-20,
      1.7402441733991072E-27, -5.6779404594547993E-20, -1.4057349025975753E-28,
      5.6779403406947559E-20, -5.668768912684597E-27, -5.6779416185700464E-20,
      -1.6894928558039683E-26, 5.67793807168893E-20, -3.456352937072213E-26,
      -5.6779450623903849E-20, -5.4701762176438623E-26, 5.6779343985594309E-20,
      -6.25808687369511E-26, -5.6779458040237431E-20, -2.4298749700793E-26,
      5.6779435668849529E-20, 1.2047746942194536E-25, -5.677914756773402E-20,
      4.5295447967947518E-25, 5.6780116657678563E-20, 1.0293146393105581E-24,
      -5.6778016600066665E-20, 1.7450641810489888E-24, 5.6781418442315335E-20,
      2.0542263372929787E-24, -5.6777740311960332E-20, 5.7014966132255118E-25,
      5.6777837372910978E-20, -5.1048654409549416E-24, -5.6789724523478057E-20,
      -1.7248168416832638E-23, 5.67539737374179E-20, -3.3556798756641028E-23,
      -5.6818443228647683E-20, -3.7626742077217554E-23, 5.6756155632601241E-20,
      1.159034677995596E-23, -5.6705080760725665E-20, 1.6905091652549971E-22,
      5.70701408715768E-20, 4.1632009215258252E-22, -5.6286632710863145E-20,
      4.2371779895365255E-22, 5.68414173554842E-20, -7.862069383731068E-22,
      -5.92108462907303E-20, -5.3934472220138154E-21, 4.8685644623313508E-20,
      1.8093905181272538E-21, -8.0294467553645978E-21, -5.2624274551095835E-21,
      -2.2337672841887197E-21, -5.3414485444224316E-22, 3.0621583342959654E-22,
      4.4743792795868185E-22, 5.1167053757077856E-23, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.5765263800816643E-18,
      0.0075690816962866222, 0.014302191571981636, 0.019463899068546123,
      0.023189048153419378, 0.025691513207407216, 0.027103677354831095,
      0.027491280334778292, 0.026894311825474804, 0.025355358013132812,
      0.022930064065698648, 0.019679979196724515, 0.015645130963317093,
      0.010790287077242814, 0.00492367903937744, -0.0023813004500792614,
      -0.0085576086765221174, -0.01375960802840029, -0.018133592867224595,
      -0.021726338817326614, -0.024511658135232709, -0.02643396639960912,
      -0.0274404933617869, -0.027499865894957065, -0.026610419054093441,
      -0.024800737757716157, -0.022122504952489984, -0.0186330806711233,
      -0.014363381128290843, -0.0092692864165839876, -0.0031834300075852121,
      0.0041572495945613871, 0.010121638168027748, 0.015078495401569863,
      0.01921284647757656, 0.022564511498811637, 0.025097726316961957,
      0.026754246514836572, 0.02748504929279235, 0.0272665293509219,
      0.026106707071137023, 0.0240440454595458, 0.021138241722913273,
      0.017448893366229949, 0.012994445371734893, 0.0076831570425640715,
      0.0012198805740683491, -0.0059009277738932267, -0.011654875545143,
      -0.016410639766870863, -0.020336948530218554, -0.023462138158397195,
      -0.025747457266536503, -0.027138226545584621, -0.027592874035401751,
      -0.02709686886368174, -0.025666800983098145, -0.023346366785315008,
      -0.020192348132658165, -0.016244878416473728, -0.011473619618531675,
      -0.0056962735974272561, 0.0015034206726484416, 0.0078367306659142891,
      0.01313131271077303, 0.017584423053655866, 0.02126231823054478,
      0.024144107617027594, 0.026173311843782143, 0.027293604972854605,
      0.027468909675392512, 0.02669249917353668, 0.024988550646638807,
      0.022407596849182063, 0.019016232383648978, 0.01488302514744474,
      0.010071515514301911, 0.0046786751208896466, -0.00097825226263615348,
      -0.0033330703671807858, -0.0027493286112687844, -0.0017561241972923619,
      -0.00099606169942881078, -0.00052511098835033383, -0.00026260081849607142,
      -0.00012585512666026544, -5.81030379121925E-5, -2.5888117850662623E-5,
      -1.1123873976568376E-5, -4.5931000997655566E-6, -1.8084905384400454E-6,
      -6.6889495524158172E-7, -2.2518521625869242E-7, -6.3643015228581209E-8,
      -1.0666860200078139E-8, 3.4586908902670832E-9, 5.2192552832464904E-9,
      3.9148714028113216E-9, 2.4047646895213452E-9, 1.3335713414621596E-9,
      6.92186918497177E-10, 3.4198246612648564E-10, 1.6221053384444981E-10,
      7.4173088193010085E-11, 3.2734937080127234E-11, 1.3923462490452991E-11,
      5.6819235225863141E-12, 2.2042675571591033E-12, 7.9833396655944011E-13,
      2.5948131313028519E-13, 6.7752347398016E-14, 7.3537729449744076E-15,
      -7.2208912464715232E-15, -7.8751248394463908E-15, -5.5014236257502023E-15,
      -3.2698024691209466E-15, -1.7771644917551795E-15, -9.0924055536834327E-16,
      -4.4407182702195345E-16, -2.0852320614391334E-16, -9.4448812986585643E-17,
      -4.1283949381267167E-17, -1.7376422605973311E-17, -7.0037362856166434E-18,
      -2.6737333107945377E-18, -9.4574261121425864E-19, -2.9474180523808211E-19,
      -6.9074572626283959E-20, -1.3806572255717594E-21, 1.2770836916631385E-20,
      1.1573107792551944E-20, 7.6474058532474768E-21, 4.418461634468285E-21,
      2.3582498959975337E-21, 1.1904301807697911E-21, 5.7502711277462071E-22,
      2.6737103465740365E-22, 1.1996247002365219E-22, 5.1925817004508691E-23,
      2.1619128237549348E-23, 8.6000031733262716E-24, 3.2259317720371869E-24,
      1.1107194858841966E-24, 3.2877977497092039E-25, 6.5757075508522582E-26,
      -8.4477994636941683E-27, -2.0790294047962529E-26, -1.6673977129732585E-26,
      -1.0533756192350318E-26, -5.9376701303549732E-27, -3.1170483363443133E-27,
      -1.5537154727194663E-27, -7.4258319669166457E-28, -3.4195616360871373E-28,
      -1.5197898415365204E-28, -6.513050424002145E-29, -2.6810952131326872E-29,
      -1.0516463727232479E-29, -3.869028492489186E-30, -1.2912204899205529E-30,
      -3.5813357632386782E-31, -5.5152724751078848E-32, 2.3771302377929838E-32,
      3.2193074464088178E-32, 2.3653690915798251E-32, 1.4396269366357706E-32,
      7.9395344897268E-33, 4.104934617698986E-33, 2.021819592958175E-33,
      9.5642800844754472E-34, 4.3624296091890825E-34, 1.9204171412780091E-34,
      8.1459802292214635E-35, 3.3136071260642181E-35, 1.2802191740486333E-35,
      4.6091131980995187E-36, 1.4826904518022692E-36, 3.7754146597731126E-37,
      3.3531179696597458E-38, -4.6822826526268982E-38, -4.8198211953674969E-38,
      -3.3137946590547325E-38, -1.9541330976808342E-38, -1.0568254543842464E-38,
      -5.3873652105963385E-39, -2.623417498745073E-39, -1.2286603514091687E-39,
      -5.5512216798079068E-40, -2.4202487703192955E-40, -1.0158043874357505E-40,
      -4.0804440606385906E-41, -1.550780092818975E-41, -5.4484157873625036E-42,
      -1.6768489698963445E-42, -3.7922927230355353E-43, 4.3050940100518066E-45,
      8.06238896914484E-44, 7.0424865092326323E-44, 4.5946550368003023E-44,
      2.6365930471131349E-44, 1.400883370467714E-44, 7.0475270490623589E-45,
      3.3945982709197033E-45, 1.5743439591908478E-45, 7.0460465037486442E-46,
      3.0419265501649172E-46, 1.2627710029504941E-46, 5.0051336677774147E-47,
      1.8682403364586873E-47, 6.3827090966314117E-48, 1.860009739297908E-48,
      3.5195024793825477E-49, -6.5529459277293683E-50, -1.2923985796748087E-49,
      -1.0101505845570258E-49, -6.3150244329157062E-50, -3.5383051678732376E-50,
      -1.8498021275889045E-50, -9.1908708621980729E-51, -4.3806575277263861E-51,
      -2.0121742804659755E-51, -8.920479735597408E-52, -3.8126449536030829E-52,
      -1.5646428332393736E-52, -6.11346099305599E-53, -2.2368779301880791E-53,
      -7.39759405019788E-54, -2.0107738581138651E-54, -2.7969770763110549E-55,
      1.599622963033973E-55, 1.98112719372875E-55, 1.4279200302757945E-55,
      8.6143304762858453E-56, 4.7253803160988188E-56, 2.4338020251379119E-56,
      1.1950724848274071E-56, 5.6382850233563471E-57, 2.5652758969063575E-57,
      1.1264184506110042E-57, 4.7648531789730878E-58, 1.9319529886386317E-58,
      7.4328426760916805E-59, 2.6596019069911532E-59, 8.4632604067569515E-60,
      2.0968871372202392E-60, 1.3998716571243639E-61, -3.0095354942941161E-61,
      -2.9449356226703384E-61, -1.9946377426717188E-61, -1.1673605471619507E-61,
      -6.2827971327993486E-62, -3.1913609661828509E-62, -1.5495221765510625E-62,
      -7.2382220682449034E-63, -3.2621493652962952E-63, -1.4185901607036844E-63,
      -5.9369814880280671E-64, -2.3766593444222183E-64, -8.9911794994452233E-65,
      -3.1368634251928343E-65, -9.5271818914118211E-66, -2.0709859412093039E-66,
      9.8426003185986989E-68, 5.0653930962644931E-67, 4.2800304692795218E-67,
      2.7588466766944095E-67, 1.5727245526586716E-67, 8.3195067866133831E-68,
      4.1713467241010848E-68, 2.0035814696463989E-68, 9.26847301867379E-69,
      4.1377862290345911E-69, 1.781680449792608E-69, 7.3741495167327285E-70,
      2.9120913190902561E-70, 1.0814950983952843E-70, 3.6650785968368768E-71,
      1.0504028627291626E-71, 1.8648713264606885E-72, -4.785666872984034E-73,
      -8.0095272155054623E-73, -6.113557658277492E-73, -3.783897114180736E-73,
      -2.1077919333710791E-73, -1.0974841130229137E-73, -5.4356638420195692E-74,
      -2.5837703587147992E-74, -1.1838164050687534E-74, -5.2349693855136359E-75,
      -2.2314182300900466E-75, -9.1287891731158444E-76, -3.552754683344576E-76,
      -1.2926227541075108E-76, -4.2343816692095945E-77, -1.1261850381061657E-77,
      -1.3818418436956983E-78, 1.0592215273998596E-78, 1.2165918036327987E-78,
      8.6129392413269947E-79, 5.1522173154644462E-79, 2.811542150968724E-79,
      1.4426534340445206E-79, 7.0625283487656173E-80, 3.3232545382261913E-80,
      1.5082149644470457E-80, 6.6057720988554586E-81, 2.7865364879759373E-81,
      1.1261079233825173E-81, 4.3139208049548323E-82, 1.5338157517684605E-82,
      4.8254655001370137E-83, 1.160326138434895E-83, 4.8641643845918462E-85,
      -1.9203025768826296E-84, -1.7968692083046203E-84, -1.2004152340938208E-84,
      -6.9836207134396926E-85, -3.7592453442807369E-85, -1.9365593433960413E-85,
      -9.9358485892276413E-86, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0075690816962866213, 0.0067331098756950114, 0.00516170749656449,
      0.0037251490848732595, 0.002502465053987833, 0.0014121641474238709,
      0.00038760297994719362, -0.0005969685093034845, -0.0015389538123419893,
      -0.0024252939474341622, -0.0032500848689741312, -0.0040348482334074225,
      -0.0048548438860742792, -0.0058666080378653729, -0.0073049794894567005,
      -0.0061763082264428577, -0.0052019993518781782, -0.0043739848388243087,
      -0.0035927459501020136, -0.0027853193179060991, -0.0019223082643764098,
      -0.0010065269621777769, -5.9372533170170482E-5, 0.00088944684086362136,
      0.0018096812963772841, 0.0026782328052261757, 0.0034894242813666874,
      0.0042696995428324544, 0.0050940947117068579, 0.0060858564089987756,
      0.0073406796021466018, 0.00596438857346636, 0.0049568572335421182,
      0.0041343510760066988, 0.0033516650212350734, 0.002533214818150332,
      0.0016565201978746074, 0.00073080277795579333, -0.00021851994187044912,
      -0.0011598222797848732, -0.002062661611591209, -0.0029058037366325338,
      -0.0036893483566833264, -0.0044544479944950569, -0.0053112883291708225,
      -0.0064632764684957244, -0.007120808347961579, -0.0057539477712497756,
      -0.0047557642217278626, -0.0039263087633476983, -0.0031251896281786398,
      -0.002285319108139304, -0.0013907692790481191, -0.00045464748981713366,
      0.00049600517172001743, 0.0014300678805835914, 0.0023204341977831433,
      0.0031540186526568459, 0.003947469716184435, 0.0047712587979420514,
      0.0057773460211044186, 0.0071996942700756975, 0.0063333099932658459,
      0.00529458204485874, 0.0044531103428828408, 0.0036778951768889128,
      0.0028817893864828111, 0.0020292042267545658, 0.0011202931290724752,
      0.00017530470253790972, -0.00077641050185583234, -0.0017039485268978698,
      -0.0025809537974567365, -0.0033913644655330856, -0.0041332072362042348,
      -0.0048115096331428292, -0.0053928403934122675, -0.0056569273835258014,
      -0.0023548181045446336, 0.00058374175591200165, 0.000993204413976423,
      0.0007600624978635511, 0.000470950711078477, 0.00026251016985426242,
      0.00013674569183580595, 6.7752088748072935E-5, 3.2214920061529873E-5,
      1.4764243874094243E-5, 6.5307738768028194E-6, 2.7846095613255112E-6,
      1.1395955831984637E-6, 4.437097389828893E-7, 1.6154220103011122E-7,
      5.2976155028503073E-8, 1.4125551090345222E-8, 1.7605643929794081E-9,
      -1.3043838804351687E-9, -1.5101067132899764E-9, -1.0711933480591859E-9,
      -6.4138442296498254E-10, -3.5020445237069132E-10, -1.7977193228203578E-10,
      -8.8037445651439712E-11, -4.1438151112882857E-11, -1.8811474589674239E-11,
      -8.2415389678666766E-12, -3.47765596542721E-12, -1.4059335905996632E-12,
      -5.3885265342915486E-13, -1.9172896573226914E-13, -6.0398574453041585E-14,
      -1.4574664191445931E-14, -6.5423359297486846E-16, 2.3737012136961885E-15,
      2.2316211566292561E-15, 1.4926379773657671E-15, 8.679239363868361E-16,
      4.6516872834638963E-16, 2.3554862087804011E-16, 1.1407439315732769E-16,
      5.3164863605318463E-17, 2.3907526775293853E-17, 1.0372686320356667E-17,
      4.3300029748221054E-18, 1.7279906995802792E-18, 6.5100080597617648E-19,
      2.256672326117981E-19, 6.76939154007122E-20, 1.4151494142203142E-20,
      -1.1977291240794411E-21, -3.9257019393044669E-21, -3.2289442187791906E-21,
      -2.0602117384707509E-21, -1.1678197152277424E-21, -6.1540306799517028E-22,
      -3.0765607811721705E-22, -1.4740856463375146E-22, -6.8036653019143511E-23,
      -3.0306688766959333E-23, -1.301912506422308E-23, -5.374071401289084E-24,
      -2.1152122861529909E-24, -7.8193971091327629E-25, -2.6302269946239772E-25,
      -7.4204874972216759E-26, -1.2342494584268358E-26, 4.11631691822994E-27,
      6.1402209373822709E-27, 4.5960860619953435E-27, 2.8206217940106588E-27,
      1.5633328636248472E-27, 8.11132276027802E-28, 4.0062703308295066E-28,
      1.8997717945506171E-28, 8.6848479913630583E-29, 3.8319552108694572E-29,
      1.6294488404094395E-29, 6.6474352347432918E-30, 2.5778080025686333E-30,
      9.3308691359668517E-31, 3.0298085157278892E-31, 7.8924027129008689E-32,
      8.4217720861583442E-33, -8.5393835482899285E-33, -9.2574215494405445E-33,
      -6.4567348766309056E-33, -3.8345998720278147E-33, -2.0831150247408113E-33,
      -1.0653915845106307E-33, -5.2018504752863638E-34, -2.4420124679110732E-34,
      -1.1058191183558626E-34, -4.8323731031572449E-35, -2.0333879520155845E-35,
      -8.193078542386815E-36, -3.1264227462972492E-36, -1.105148985824958E-36,
      -3.4401028628071375E-37, -8.035400622286644E-38, -1.3753854274059953E-39,
      1.506026536312764E-38, 1.3596615613738983E-38, 8.9730764329658781E-39,
      5.1808893332461239E-39, 2.7639477118512651E-39, 1.3947571473359044E-39,
      6.7353818342837774E-40, 3.1309729094886113E-40, 1.4044443828835446E-40,
      6.0775998137189148E-41, 2.5296639678196153E-41, 1.0059385140827246E-41,
      3.7715668174661591E-42, 1.2976196975927908E-42, 3.8353436631360534E-43,
      7.6318795681396592E-44, -1.0199024599122078E-44, -2.447831472432329E-44,
      -1.9580619896871672E-44, -1.2357096766454212E-44, -6.9613066556147819E-45,
      -3.652928778142655E-45, -1.8202543117288555E-45, -8.6973930881598334E-46,
      -4.0041199535837266E-46, -1.7791555472144231E-46, -7.6225763617275253E-47,
      -3.1368933313187272E-47, -1.2299694267955462E-47, -4.5226993573335031E-48,
      -1.508059491359653E-48, -4.1747970721554837E-49, -6.37103986901872E-50,
      2.8224799511778288E-50, 3.7864814126545508E-50, 2.7767192650424686E-50,
      1.6885030402843333E-50, 9.3071504136909737E-51, 4.8102133344716869E-51,
      2.36848324726041E-51, 1.120126306906235E-51, 5.1078347819943244E-52,
      2.2480021203637091E-52, 9.5329673393377454E-53, 3.8765830628679103E-53,
      1.4971185251682908E-53, 5.3868201920840153E-54, 1.7310761504827596E-54,
      4.3966000393450279E-55, 3.815042306947769E-56, -5.5320716345295546E-56,
      -5.6648698264721E-56, -3.8889501601870255E-56, -2.2915782909609074E-56,
      -1.2387295403105046E-56, -6.3124398249177235E-57, -3.0730091264499896E-57,
      -1.4388574462953532E-57, -6.4993313271369535E-58, -2.8329001903344554E-58,
      -1.1886687210294633E-58, -4.7732407691005273E-59, -1.8132758663154581E-59,
      -6.3663732695367111E-60, -1.9568999715078028E-60, -4.4094071514184789E-61,
      6.4599871623777871E-63, 9.5029787999861962E-62, 8.2727719550976771E-62,
      5.39080833882016E-62, 3.0914361666164968E-62, 1.6418387896317881E-62,
      8.2569996972657227E-63, 3.9760727029486087E-63, 1.843559204592611E-63,
      8.2489201190087766E-64, 3.5603221436058488E-64, 1.4775413944776961E-64,
      5.8543160742523878E-65, 2.1841452360516522E-65, 7.4561959502025173E-66,
      2.1694119443952906E-66, 4.0811330644046226E-67, -7.85362626984971E-68,
      -1.5211837925851124E-67, -1.1861221240357372E-67, -7.4077387399733305E-68,
      -4.1481600625122983E-68, -2.1677652544546855E-68, -1.07673416777902E-68,
      -5.1306867896391975E-69, -2.3561057792419834E-69, -1.0442654981193352E-69,
      -4.462058197642473E-70, -1.8305962206949717E-70, -7.1498723871159646E-71,
      -2.6146757341077146E-71, -8.6391573008309373E-72, -2.3434380137590915E-72,
      -3.2238603425214289E-73, 1.8959695572279703E-73, 2.3296605440967562E-73,
      1.6761051808096567E-73, 1.0103078203481653E-73, 5.539177288209569E-74,
      2.8518934833047703E-74, 1.3999539536460458E-74, 6.6031946651738984E-75,
      3.00355115542359E-75, 1.3185393127784624E-75, 5.5760344897712678E-76,
      2.2601319292370648E-76, 8.6918458718655114E-77, 3.1081966311034288E-77,
      9.880008537365959E-78, 2.4410633710955577E-78, 1.5737027623293931E-79,
      -3.5529787950009924E-79, -3.460721925862548E-79, -2.3406751644957219E-79,
      -1.3688887169242034E-79, -7.3640059916795874E-80, -3.7392738105394252E-80,
      -1.8150395737791458E-80, -8.4763775456149988E-81, -3.8192356108795222E-81,
      -1.6604285645934197E-81, -6.94715842887034E-82, -2.780105053186373E-82,
      -1.0512692017547591E-82, -3.6651393617021183E-83, -1.1116844945889763E-83,
      -2.4067190153418142E-84, 1.2343336857800923E-85, 5.96453974210799E-85,
      5.0205316274985184E-85, 3.2243753691589557E-85, 1.8226860008846959E-85,
      9.4297448447327716E-86, 4.8413983584901032E-86, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_day4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0,
      21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
      33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0,
      45.0, 46.0, 47.0, 48.0, 49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
      57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0,
      69.0, 70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0, 80.0,
      81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0, 90.0, 91.0, 92.0,
      93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0,
      104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0, 112.0, 113.0,
      114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 121.0, 122.0, 123.0,
      124.0, 125.0, 126.0, 127.0, 128.0, 129.0, 130.0, 131.0, 132.0, 133.0,
      134.0, 135.0, 136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
      144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0, 152.0, 153.0,
      154.0, 155.0, 156.0, 157.0, 158.0, 159.0, 160.0, 161.0, 162.0, 163.0,
      164.0, 165.0, 166.0, 167.0, 168.0, 169.0, 170.0, 171.0, 172.0, 173.0,
      174.0, 175.0, 176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
      184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0, 192.0, 193.0,
      194.0, 195.0, 196.0, 197.0, 198.0, 199.0, 200.0, 201.0, 202.0, 203.0,
      204.0, 205.0, 206.0, 207.0, 208.0, 209.0, 210.0, 211.0, 212.0, 213.0,
      214.0, 215.0, 216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
      224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0, 232.0, 233.0,
      234.0, 235.0, 236.0, 237.0, 238.0, 239.0, 240.0, 241.0, 242.0, 243.0,
      244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0, 253.0,
      254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
      264.0, 265.0, 266.0, 267.0, 268.0, 269.0, 270.0, 271.0, 272.0, 273.0,
      274.0, 275.0, 276.0, 277.0, 278.0, 279.0, 280.0, 281.0, 282.0, 283.0,
      284.0, 285.0, 286.0, 287.0, 288.0, 289.0, 290.0, 291.0, 292.0, 293.0,
      294.0, 295.0, 296.0, 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0,
      304.0, 305.0, 306.0, 307.0, 308.0, 309.0, 310.0, 311.0, 312.0, 313.0,
      314.0, 315.0, 316.0, 317.0, 318.0, 319.0, 320.0, 321.0, 322.0, 323.0,
      324.0, 325.0, 326.0, 327.0, 328.0, 329.0, 330.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0,
      0.00334262707613961, 0.0065430376664767677, 0.0036283420516344308,
      -0.00093129178713247042, -0.0029613631458930813, -0.0032104871819811378,
      -0.0026645991414556438, -0.0018958098354942311, -0.0011857970401326096,
      -0.00064306416201833554, -0.000280897396113758, -6.889635594803732E-5,
      3.6075924331467733E-5, 7.4000454937180832E-5, 7.5495973936732554E-5,
      6.1024467967306775E-5, 4.2583039136330348E-5, 2.6126276133065561E-5,
      1.3817824783649008E-5, 5.7577247094899286E-6, 1.1384583646342214E-6,
      -1.0761502266256328E-6, -1.8131717783363004E-6, -1.7671476916613833E-6,
      -1.3935607094533896E-6, -9.5388758835195549E-7, -5.7381669595505878E-7,
      -2.9547217929095148E-7, -1.16604877149749E-7, -1.633157254369987E-8,
      3.0064268354909859E-8, 4.3999450714931721E-8, 4.1183849951411833E-8,
      3.1727666230375549E-8, 2.1308638838524193E-8, 1.2561452011597665E-8,
      6.2845355929623438E-9, 2.3267216106284827E-9, 1.5869777648155923E-10,
      -8.0551165058779708E-10, -1.0589370288063187E-9, -9.5592680393643946E-10,
      -7.2024173532576044E-10, -4.7468048204261874E-10, -2.7403432643152892E-10,
      -1.3287599747325613E-10, -4.5563236650143827E-11, 1.1107918552908459E-12,
      2.0962263616286026E-11, 2.5303348759874916E-11, 2.2104520682288175E-11,
      1.6303302481452395E-11, 1.054426773835625E-11, 5.95636580780998E-12,
      2.7906751164375679E-12, 8.7044660573399E-13, -1.2968545154227298E-13,
      -5.3386478413449243E-13, -6.0081412849760367E-13, -5.0932182466259355E-13,
      -3.6800319747830752E-13, -2.3354775515173297E-13, -1.2896279915537323E-13,
      -5.8163172324349626E-14, -1.6068616530362443E-14, 5.25268371847825E-15,
      1.3371042774753987E-14, 1.4185696327911687E-14, 1.1696036611291082E-14,
      8.2836426013382372E-15, 5.1575650160390734E-15, 2.7805241402528659E-15,
      1.2015384958893082E-15, 2.8186894244161771E-16, -1.7012315419364925E-16,
      -3.304442267491633E-16, -3.3321622102913641E-16, -2.6771163339962587E-16,
      -1.8596482436973969E-16, -1.135605379930212E-16, -5.96618564436126E-17,
      -2.4551073140300925E-17, -4.5582988437092461E-18, 4.9678448657468789E-18,
      8.0934692139873357E-18, 7.8024706265496331E-18, 6.0920681388417838E-18,
      4.1517118638973538E-18, 2.5091464200132209E-18, 1.2854269533071382E-18,
      4.786218991423551E-19, 5.0733173486116436E-20, -1.2030234454945071E-19,
      -1.8470695245231987E-19, -1.9857774808414563E-19, -1.4985726250536908E-19,
      -7.575040255810876E-20, -4.3642184969520258E-20, -4.4246080178735313E-20,
      -2.0717728935854925E-20, 1.6699897645838292E-20, 1.4519523187376026E-20,
      -1.2475717134015306E-20, -6.6585216434817856E-21, 2.0327049832673426E-20,
      1.2933816059473302E-20, -1.5985936168769979E-20, -1.0293681713627429E-20,
      1.7365933312923289E-20, 1.085542816865521E-20, -1.7268569956117424E-20,
      -1.0977282279496528E-20, 1.7076829285463797E-20, 1.0793871893048934E-20,
      -1.7219937166359433E-20, -1.0890995237831002E-20, 1.7162035764759217E-20,
      1.0861554833081903E-20, -1.7173341355403198E-20, -1.0862797448131491E-20,
      1.7176675466235493E-20, 1.08674324386158E-20, -1.7172408935789704E-20,
      -1.0864178560553164E-20, 1.717457584175128E-20, 1.0865444148297217E-20,
      -1.717395127619235E-20, -1.0865220319021047E-20, 1.7173957942451421E-20,
      1.0865132251828623E-20, -1.7174069121664995E-20, -1.0865231112516931E-20,
      1.7173995351456905E-20, 1.0865182902579693E-20, -1.7174022916379068E-20,
      -1.0865196069715994E-20, 1.7174018577665527E-20, 1.0865196396620082E-20,
      -1.7174016309591405E-20, -1.0865193747756157E-20, 1.7174018591910704E-20,
      1.0865195415496903E-20, -1.7174017522382617E-20, -1.0865194817377212E-20,
      1.7174017798009159E-20, 1.0865194899121983E-20, -1.7174017816016077E-20,
      -1.0865194956425571E-20, 1.7174017753283962E-20, 1.0865194903918117E-20,
      -1.7174017790881659E-20, -1.0865194927576033E-20, 1.7174017777955494E-20,
      1.0865194921853376E-20, -1.7174017779434332E-20, -1.0865194921210899E-20,
      1.71740177808605E-20, 1.0865194922688587E-20, -1.717401777965653E-20,
      -1.0865194921843397E-20, 1.7174017780178225E-20, 1.0865194922121519E-20,
      -1.7174017780060494E-20, -1.0865194922096311E-20, 1.7174017780040921E-20,
      1.086519492206143E-20, -1.7174017780075335E-20, -1.0865194922088715E-20,
      1.7174017780056636E-20, 1.0865194922077477E-20, -1.7174017780062395E-20,
      -1.0865194922079711E-20, 1.7174017780062134E-20, 1.0865194922080367E-20,
      -1.7174017780061213E-20, -1.086519492207946E-20, 1.7174017780061908E-20,
      1.0865194922079981E-20, -1.7174017780061547E-20, -1.0865194922079723E-20,
      1.7174017780061691E-20, 1.0865194922079874E-20, -1.7174017780061613E-20,
      -1.0865194922079815E-20, 1.7174017780061667E-20, 1.0865194922079808E-20,
      -1.7174017780061667E-20, -1.0865194922079826E-20, 1.7174017780061643E-20,
      1.0865194922079845E-20, -1.7174017780061607E-20, -1.0865194922079743E-20,
      1.7174017780061751E-20, 1.0865194922079921E-20, -1.7174017780061562E-20,
      -1.0865194922079725E-20, 1.7174017780061739E-20, 1.0865194922079872E-20,
      -1.7174017780061688E-20, -1.0865194922079925E-20, 1.7174017780061502E-20,
      1.0865194922079623E-20, -1.7174017780061935E-20, -1.0865194922080127E-20,
      1.7174017780061351E-20, 1.0865194922079588E-20, -1.7174017780061739E-20,
      -1.086519492207954E-20, 1.7174017780062407E-20, 1.0865194922081367E-20,
      -1.7174017780059055E-20, -1.0865194922075899E-20, 1.717401778006718E-20,
      1.086519492208714E-20, -1.7174017780052525E-20, -1.0865194922069188E-20,
      1.7174017780072991E-20, 1.0865194922090253E-20, -1.7174017780054734E-20,
      -1.0865194922080206E-20, 1.7174017780048628E-20, 1.0865194922047237E-20,
      -1.7174017780122205E-20, -1.0865194922177767E-20, 1.7174017779916756E-20,
      1.0865194921879925E-20, -1.717401778032038E-20, -1.0865194922393214E-20,
      1.7174017779710709E-20, 1.0865194921727821E-20, -1.7174017780351168E-20,
      -1.0865194922208085E-20, 1.7174017780236484E-20, 1.0865194922748361E-20,
      -1.7174017778659109E-20, -1.0865194919660543E-20, 1.7174017783802184E-20,
      1.086519492742838E-20, -1.7174017772901472E-20, -1.086519491308591E-20,
      1.7174017790592757E-20, 1.0865194933353175E-20, -1.7174017769560191E-20,
      -1.086519491483472E-20, 1.7174017780336976E-20, 1.0865194910219293E-20,
      -1.7174017810799419E-20, -1.0865194979936601E-20, 1.7174017685747593E-20,
      1.0865194781773821E-20, -1.7174017974494671E-20, -1.0865195174864509E-20,
      1.7174017472248891E-20, 1.0865194575038565E-20, -1.7174018131791189E-20,
      -1.0865195217776916E-20, 1.7174017635420982E-20, 1.0865195065652235E-20,
      -1.7174017163083916E-20, -1.0865193596969142E-20, 1.7174020091180134E-20,
      1.0865198521350649E-20, -1.7174012603297367E-20, -1.0865187953150004E-20,
      1.7174026587536491E-20, 1.0865205314433366E-20, -1.7174006530657382E-20,
      -1.0865184233892227E-20, 1.7174025547706586E-20, 1.086519620348302E-20,
      -1.717402800023964E-20, -1.0865223269944779E-20, 1.7173963079048846E-20,
      1.0865104354745843E-20, -1.7174154231879826E-20, -1.0865386311053775E-20,
      1.7173765783685252E-20, 1.0864883679102842E-20, -1.7174374720553198E-20,
      -1.086556495354762E-20, 1.7173694921893379E-20, 1.0865017151609647E-20,
      -1.7173904468240467E-20, -1.0864587510988521E-20, 1.717538343277443E-20,
      1.0867638051376431E-20, -1.717014674323977E-20, -1.0859566520720542E-20,
      1.7181618841970116E-20, 1.0874722006556902E-20, -1.7163086525733019E-20,
      -1.0854137200821115E-20, 1.7182838054425733E-20, 1.0867999662598429E-20,
      -1.7182640621310192E-20, -1.0892223037074135E-20, 1.7120666578149724E-20,
      1.0778200246448817E-20, -1.7298531932291218E-20, -1.1023177247432216E-20,
      1.7000698753806209E-20, 1.0715946716456553E-20, -1.7232096641165796E-20,
      -1.0735377304390078E-20, 1.7609294940440719E-20, 1.1715581852289542E-20,
      -1.5867272987046787E-20, -9.2327294997450712E-21, 1.8678147111900614E-20,
      1.1242878505537231E-20, -1.9816989928950771E-20, -1.9149956767832278E-20,
      4.385418446161574E-21, 1.2417637777198502E-20, 7.1856833537134757E-21,
      2.3114558426648945E-21, 4.0095215493617347E-24, -6.0649263757371637E-22,
      -4.2268691084439536E-22, -1.254505306326946E-22, -1.254505306326946E-22,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_day4_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day4_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day4_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<S4>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M, "Error creating .mat file travel.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"tra")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file travel.mat");
      return;
    }

    helicopter_day4_DW.ToFile_IWORK.Count = 0;
    helicopter_day4_DW.ToFile_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travelrate.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error creating .mat file travelrate.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"tr")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file travelrate.mat");
      return;
    }

    helicopter_day4_DW.ToFile1_IWORK.Count = 0;
    helicopter_day4_DW.ToFile1_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"p")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    helicopter_day4_DW.ToFile2_IWORK.Count = 0;
    helicopter_day4_DW.ToFile2_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File3' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitchrate.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error creating .mat file pitchrate.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"pr")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file pitchrate.mat");
      return;
    }

    helicopter_day4_DW.ToFile3_IWORK.Count = 0;
    helicopter_day4_DW.ToFile3_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile3_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File4' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevation.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error creating .mat file elevation.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"e")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file elevation.mat");
      return;
    }

    helicopter_day4_DW.ToFile4_IWORK.Count = 0;
    helicopter_day4_DW.ToFile4_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile4_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File5' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevationrate.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error creating .mat file elevationrate.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"er")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file elevationrate.mat");
      return;
    }

    helicopter_day4_DW.ToFile5_IWORK.Count = 0;
    helicopter_day4_DW.ToFile5_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile5_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_day4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_day4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_day4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_day4_X.Integrator_CSTATE = helicopter_day4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_day4_DW.TimeStampA = (rtInf);
  helicopter_day4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_day4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_day4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_day4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_day4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_day4_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day4_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter_day4_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter_day4_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_day4_DW.HILInitialize_Card
                         , helicopter_day4_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter_day4_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_day4_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_day4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_day4_DW.HILInitialize_Card,
            helicopter_day4_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs,
            &helicopter_day4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_day4_DW.HILInitialize_Card,
            helicopter_day4_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter_day4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_day4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_day4_DW.HILInitialize_Card);
    hil_close(helicopter_day4_DW.HILInitialize_Card);
    helicopter_day4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<S4>/To File' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M, "Error closing MAT-file travel.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file travel.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_day4_DW.ToFile_IWORK.Count,
           "tra")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for tra to MAT-file travel.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M, "Error closing MAT-file travel.mat");
        return;
      }

      helicopter_day4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File1' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travelrate.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file travelrate.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file travelrate.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_day4_DW.ToFile1_IWORK.Count,
           "tr")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for tr to MAT-file travelrate.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file travelrate.mat");
        return;
      }

      helicopter_day4_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File2' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, helicopter_day4_DW.ToFile2_IWORK.Count,
           "p")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for p to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M, "Error closing MAT-file pitch.mat");
        return;
      }

      helicopter_day4_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File3' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile3_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitchrate.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file pitchrate.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file pitchrate.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_day4_DW.ToFile3_IWORK.Count,
           "pr")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for pr to MAT-file pitchrate.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file pitchrate.mat");
        return;
      }

      helicopter_day4_DW.ToFile3_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File4' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile4_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevation.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file elevation.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file elevation.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, helicopter_day4_DW.ToFile4_IWORK.Count,
           "e")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for e to MAT-file elevation.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file elevation.mat");
        return;
      }

      helicopter_day4_DW.ToFile4_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File5' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile5_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevationrate.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file elevationrate.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file elevationrate.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_day4_DW.ToFile5_IWORK.Count,
           "er")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for er to MAT-file elevationrate.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file elevationrate.mat");
        return;
      }

      helicopter_day4_DW.ToFile5_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter_day4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_day4_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_day4_initialize();
}

void MdlTerminate(void)
{
  helicopter_day4_terminate();
}

/* Registration function */
RT_MODEL_helicopter_day4_T *helicopter_day4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_day4_P.Integrator_UpperSat = rtInf;
  helicopter_day4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_day4_M, 0,
                sizeof(RT_MODEL_helicopter_day4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_day4_M->solverInfo,
                          &helicopter_day4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_day4_M->solverInfo, &rtmGetTPtr(helicopter_day4_M));
    rtsiSetStepSizePtr(&helicopter_day4_M->solverInfo,
                       &helicopter_day4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_day4_M->solverInfo,
                 &helicopter_day4_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter_day4_M->solverInfo, (real_T **)
                         &helicopter_day4_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_day4_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_day4_M)));
    rtsiSetRTModelPtr(&helicopter_day4_M->solverInfo, helicopter_day4_M);
  }

  rtsiSetSimTimeStep(&helicopter_day4_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_day4_M->ModelData.intgData.f[0] = helicopter_day4_M->
    ModelData.odeF[0];
  helicopter_day4_M->ModelData.contStates = ((real_T *) &helicopter_day4_X);
  rtsiSetSolverData(&helicopter_day4_M->solverInfo, (void *)
                    &helicopter_day4_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter_day4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_day4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_day4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_day4_M->Timing.sampleTimes =
      (&helicopter_day4_M->Timing.sampleTimesArray[0]);
    helicopter_day4_M->Timing.offsetTimes =
      (&helicopter_day4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_day4_M->Timing.sampleTimes[0] = (0.0);
    helicopter_day4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_day4_M->Timing.offsetTimes[0] = (0.0);
    helicopter_day4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_day4_M, &helicopter_day4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_day4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_day4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_day4_M, -1);
  helicopter_day4_M->Timing.stepSize0 = 0.002;
  helicopter_day4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_day4_M->Sizes.checksums[0] = (3034317653U);
  helicopter_day4_M->Sizes.checksums[1] = (4267382141U);
  helicopter_day4_M->Sizes.checksums[2] = (3990989151U);
  helicopter_day4_M->Sizes.checksums[3] = (1088589491U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter_day4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter_day4_M->extModeInfo,
      &helicopter_day4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_day4_M->extModeInfo,
                        helicopter_day4_M->Sizes.checksums);
    rteiSetTPtr(helicopter_day4_M->extModeInfo, rtmGetTPtr(helicopter_day4_M));
  }

  helicopter_day4_M->solverInfoPtr = (&helicopter_day4_M->solverInfo);
  helicopter_day4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_day4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_day4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_day4_M->ModelData.blockIO = ((void *) &helicopter_day4_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_day4_B.Sum4[i] = 0.0;
    }

    helicopter_day4_B.TravelCounttorad = 0.0;
    helicopter_day4_B.Gain = 0.0;
    helicopter_day4_B.Sum3 = 0.0;
    helicopter_day4_B.Gain_d = 0.0;
    helicopter_day4_B.PitchCounttorad = 0.0;
    helicopter_day4_B.Gain_i = 0.0;
    helicopter_day4_B.Gain_b = 0.0;
    helicopter_day4_B.ElevationCounttorad = 0.0;
    helicopter_day4_B.Gain_e = 0.0;
    helicopter_day4_B.Sum = 0.0;
    helicopter_day4_B.Gain_dg = 0.0;
    helicopter_day4_B.Sum6 = 0.0;
    helicopter_day4_B.Sum1 = 0.0;
    helicopter_day4_B.Sum2 = 0.0;
    helicopter_day4_B.K_ei = 0.0;
    helicopter_day4_B.Gain_l = 0.0;
    helicopter_day4_B.VectorConcatenate[0] = 0.0;
    helicopter_day4_B.VectorConcatenate[1] = 0.0;
    helicopter_day4_B.VectorConcatenate1[0] = 0.0;
    helicopter_day4_B.VectorConcatenate1[1] = 0.0;
    helicopter_day4_B.BackmotorSaturation = 0.0;
    helicopter_day4_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter_day4_M->ModelData.defaultParam = ((real_T *)&helicopter_day4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_day4_X;
    helicopter_day4_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter_day4_X, 0,
                  sizeof(X_helicopter_day4_T));
  }

  /* states (dwork) */
  helicopter_day4_M->ModelData.dwork = ((void *) &helicopter_day4_DW);
  (void) memset((void *)&helicopter_day4_DW, 0,
                sizeof(DW_helicopter_day4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_day4_DW.TimeStampA = 0.0;
  helicopter_day4_DW.LastUAtTimeA = 0.0;
  helicopter_day4_DW.TimeStampB = 0.0;
  helicopter_day4_DW.LastUAtTimeB = 0.0;
  helicopter_day4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_day4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_day4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_day4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_day4_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter_day4_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_day4_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_day4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_day4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_day4_M->Sizes.numBlocks = (79);/* Number of blocks */
  helicopter_day4_M->Sizes.numBlockIO = (21);/* Number of block outputs */
  helicopter_day4_M->Sizes.numBlockPrms = (158);/* Sum of parameter "widths" */
  return helicopter_day4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
