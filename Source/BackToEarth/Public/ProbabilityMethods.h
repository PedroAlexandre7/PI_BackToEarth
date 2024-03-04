
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProbabilityMethods.generated.h"

USTRUCT(BlueprintType)
struct FDiracDelta {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float prob;
};

USTRUCT(BlueprintType)
struct FMiuSigma {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float miu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float sigma;
};

UCLASS()
class BACKTOEARTH_API UProbabilityMethods : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static float uniformProbabilityNumber(float min, float max);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static int binomialProbabilityNumberMinMax(int min, int max, float prob);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static int binomialProbabilityNumber(int n, float prob);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static float empiricalDiscreteProbabilityNumber(TArray<FDiracDelta> arr);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static float exponentialProbabilityNumber(float a, float b);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static float normalProbabilityNumber(float miu, float sigma);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static float normalMultipleProbabilityNumber(TArray<FMiuSigma> arr);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static float rayleighProbabilityNumber(float a, float b);
};



