#include "GeneticSimulator.h"
#include <malloc.h>
#include <string.h>
#include "GFormant/GFormant.h"

_Constructor_ (GeneticSimulator)
{
    Dest -> InitialParameter = malloc(4);
    Dest -> ParameterList = malloc(4);
    Dest -> TaskList = malloc(4);
    Dest -> EvaluationList = malloc(4);
    Dest -> ResultList = malloc(4);
}

_Destructor_ (GeneticSimulator)
{
    free(Dest -> InitialParameter);
    free(Dest -> ParameterList);
    free(Dest -> TaskList);
    free(Dest -> EvaluationList);
    free(Dest -> ResultList);
}

void GeneticSimulator_SetTask(GeneticSimulator* Dest, int Size, int Num)
{
    Dest -> TaskSize = Size;
    Dest -> TaskNum = Num;
    Dest -> TaskList = realloc(Dest -> TaskList, Size * Num);
}

void GeneticSimulator_SetParameter(GeneticSimulator* Dest, int Size, int Num)
{
    Dest -> ParameterSize = Size;
    Dest -> ParameterNum = Num;
    Dest -> InitialParameter = realloc(Dest -> InitialParameter, Size);
    Dest -> ParameterList = realloc(Dest -> ParameterList, Size * Num);
    Dest -> EvaluationList = (float*)realloc(Dest -> EvaluationList, sizeof(float) * Num);
}

void GeneticSimulator_SetResult(GeneticSimulator* Dest, int Size)
{
    Dest -> ResultSize = Size;
    Dest -> ResultList = realloc(Dest -> ResultList, Size * Dest -> TaskNum);
}

void GeneticSimulator_SetSetParamFunc(GeneticSimulator* Dest, SetParamFunc FuncPtr)
{
    Dest -> HSetParam = FuncPtr;
}
void GeneticSimulator_SetRunFunc(GeneticSimulator* Dest, RunFunc FuncPtr)
{
    Dest -> HRun = FuncPtr;
}
void GeneticSimulator_SetEvaluateFunc(GeneticSimulator* Dest, EvaluateFunc FuncPtr)
{
    Dest -> HEval = FuncPtr;
}
void GeneticSimulator_SetMutateFunc(GeneticSimulator* Dest, MutateFunc FuncPtr)
{
    Dest -> HMutate = FuncPtr;
}
void GeneticSimulator_SetCrossFunc(GeneticSimulator* Dest, CrossFunc FuncPtr)
{
    Dest -> HCross = FuncPtr;
}
void GeneticSimulator_SetDisplayFunc(GeneticSimulator* Dest, DisplayFunc FuncPtr)
{
    Dest -> HDisplay = FuncPtr;
}

void GeneticSimulator_SetInitialParam(GeneticSimulator* Dest, void* ParamPtr)
{
    memcpy(Dest -> InitialParameter, ParamPtr, Dest -> ParameterSize);
}

void GeneticSimulator_SetSelectionNum(GeneticSimulator* Dest, int Num)
{
    Dest -> Simu_SelectionNum = Num;
}

void GeneticSimulator_FillCopyParam(GeneticSimulator* Dest, void* Src, int From, int To)
{
    int i;
    for(i = From; i < To; i ++)
        memcpy(Dest -> ParameterList + i * (Dest -> ParameterSize), Src, Dest -> ParameterSize);
}

void GeneticSimulator_RunSimulation(GeneticSimulator* Dest, int Round)
{
    int i, j, k;
    void* BestSelection = malloc(Dest -> ParameterSize * Dest -> Simu_SelectionNum);
    void* TempResult = malloc(Dest -> ResultSize);
    int BestNum = 1;
    ArrayType_Ctor(float, EvalSort);
    ArrayType_Ctor(int, EvalIndex);
    ArrayType_Resize(float, EvalSort, 10000);
    ArrayType_Resize(int, EvalIndex, 10000);

    memcpy(BestSelection, Dest -> InitialParameter, Dest -> ParameterSize);
    for(i = 0; i < Round; i ++)
    {
        printf("Running Round %d...\n", i + 1);
        //Fill
        for(j = 0; j < BestNum; j ++)
        {
            GeneticSimulator_FillCopyParam(Dest, BestSelection + j * Dest -> ParameterSize, j * Dest -> ParameterNum / BestNum, (j + 1) * Dest -> ParameterNum / BestNum);
        }

        //Mutate
        for(j = 0; j < Dest -> ParameterNum; j ++)
        {
            Dest -> HMutate(Dest -> ParameterList + j * Dest -> ParameterSize);
        }

        //RunTask
        for(j = 0; j < Dest -> ParameterNum; j ++)
        {
            //For each parameter
            Dest -> HSetParam(Dest -> ParameterList + j * Dest -> ParameterSize);
            Dest -> EvaluationList[j] = 0;
            for(k = 0; k < Dest -> TaskNum; k ++)
            {
                //For each task
                float Score;
                Dest -> HRun(TempResult, (Dest -> TaskList) + (k * Dest -> TaskSize));
                Score = Dest -> HEval(TempResult, Dest -> ResultList + k * Dest -> ResultSize);

                if(k < 7)
                {
                    //Emphasis "a"
                    Score *= 2;
                }
                //if(Score < Dest -> EvaluationList[j])
                    Dest -> EvaluationList[j] += Score;
            }
        }
        //Select
        EvalSort_Index = - 1;
        EvalIndex_Index = -1;
        for(j = 0; j < Dest -> ParameterNum; j ++)
        {
            int InsertPos;
            ArrayType_DecreaseSortFind(InsertPos, float, EvalSort, Dest -> EvaluationList[j]);
            ArrayType_Insert(float, EvalSort, InsertPos, Dest -> EvaluationList[j]);
            ArrayType_Insert(int, EvalIndex, InsertPos, j);
        }

        printf("\t Top 5 Score: \n");
        for(j = 0; j < Dest -> Simu_SelectionNum; j ++)
        {
            int Index = EvalIndex[j];
            printf("\t %d. %f. Index: %d\n", j, EvalSort[j], EvalIndex[j]);
            memcpy(BestSelection + j * Dest -> ParameterSize, Dest -> ParameterList + Index * Dest -> ParameterSize, Dest -> ParameterSize);
        }
        BestNum = Dest -> Simu_SelectionNum;
    }
    printf("Genetic Simulation finished after %d rounds. Best parameters:\n", Round);
    for(i = 0; i < BestNum; i ++)
    {
        printf("---\n");
        printf("* No. %d, Score: %f\n", i, EvalSort[i]);
        Dest -> HDisplay(BestSelection + i * Dest -> ParameterSize);
    }
    ArrayType_Dtor(float, EvalSort);
    ArrayType_Dtor(int, EvalIndex);
    free(BestSelection);
    free(TempResult);
}
