#ifndef GENETICSIMULATOR_H
#define GENETICSIMULATOR_H

#include "RUtil/RUtil.h"

typedef void (*SetParamFunc)(void*);
typedef void (*RunFunc)(void*, void*);
typedef float (*EvaluateFunc)(void*, void*);
typedef void (*MutateFunc)(void*);
typedef void (*CrossFunc)(void*, void*);
typedef void (*DisplayFunc)(void*);

AutoClass
{
    void* InitialParameter;
    void* ParameterList;
    void* TaskList;
    void* ResultList;
    float* EvaluationList;

    int TaskSize;
    int ParameterSize;
    int ResultSize;

    int TaskNum;
    int ParameterNum;

    int Simu_SelectionNum;

    SetParamFunc HSetParam;
    RunFunc      HRun;
    EvaluateFunc HEval;
    MutateFunc   HMutate;
    CrossFunc    HCross;
    DisplayFunc  HDisplay;
} EndClass(GeneticSimulator);

extern void GeneticSimulator_SetTask(GeneticSimulator* Dest, int Size, int Num);
extern void GeneticSimulator_SetParameter(GeneticSimulator* Dest, int Size, int Num);
extern void GeneticSimulator_SetResult(GeneticSimulator* Dest, int Size);

extern void GeneticSimulator_SetSetParamFunc(GeneticSimulator* Dest, SetParamFunc FuncPtr);
extern void GeneticSimulator_SetRunFunc(GeneticSimulator* Dest, RunFunc FuncPtr);
extern void GeneticSimulator_SetEvaluateFunc(GeneticSimulator* Dest, EvaluateFunc FuncPtr);
extern void GeneticSimulator_SetMutateFunc(GeneticSimulator* Dest, MutateFunc FuncPtr);
extern void GeneticSimulator_SetCrossFunc(GeneticSimulator* Dest, CrossFunc FuncPtr);
extern void GeneticSimulator_SetDisplayFunc(GeneticSimulator* Dest, DisplayFunc FuncPtr);

extern void GeneticSimulator_SetInitialParam(GeneticSimulator* Dest, void* ParamPtr);

extern void GeneticSimulator_SetSelectionNum(GeneticSimulator* Dest, int Num);

extern void GeneticSimulator_RunSimulation(GeneticSimulator* Dest, int Round);
#endif
