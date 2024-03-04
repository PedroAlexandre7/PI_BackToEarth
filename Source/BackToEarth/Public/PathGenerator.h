
#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProbabilityMethods.h"
#include "PathGenerator.generated.h"
using std::vector;

UCLASS()
class BACKTOEARTH_API UPathGenerator : public UBlueprintFunctionLibrary {

	GENERATED_BODY()

public:

	/**
* Generates a random, but gentle path on a matrix using rules and Dirac Deltas.
* @param rows The number of rows of the matrix.
* @param columns The number of columns of the matrix.
* @param leftMostStart The leftmost position where the path can start. Choose 0 if you want all possible start positions.
* @param rightMostStart The rightmost position where the path can start. Choose rows - 1 if you want all possible start positions.
* @param left3Prob Probability of choosing left when there are 3 options (left, forward, right).
* @param right3Prob Probability of choosing right when there are 3 options (left, forward, right).
* @param left2Prob Probability of choosing left when there are 2 options (left, forward).
* @param right2Prob Probability of choosing right when there are 2 options (right, forward).
* @return True = Real, False = Fake.
*/

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ProbabilityMethods")
		static TArray<bool> generatePath(int rows, int columns, int leftMostStart, int rightMostStart,
			float left3Prob, float right3Prob, float left2Prob, float right2Prob);
};
