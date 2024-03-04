
#include "ProbabilityMethods.h"
#include <random>

using namespace::std;

random_device rd; // Gera números aleatórios...
uniform_real_distribution<double> dist(0, 1); // De 0 a 1 uniformemente

float UProbabilityMethods::uniformProbabilityNumber(float min, float max) {
	return dist(rd) * (max - min) + min;
}

int UProbabilityMethods::binomialProbabilityNumberMinMax(int min, int max, float prob) {

	if (min < 0 || max < 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Illegal Argument(s)."));
		return 0;
	}

	return binomialProbabilityNumber(max - min, prob) + min;
}

int UProbabilityMethods::binomialProbabilityNumber(int n, float prob) {

	if (n <= 0 || prob < 0 || prob > 1) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Illegal Argument(s)."));
		return 0;
	}

	int result = 0;

	for (int i = 0; i < n; i++)
		if (prob > dist(rd))
			result++;

	return result;
}

float UProbabilityMethods::empiricalDiscreteProbabilityNumber(TArray<FDiracDelta> arr) {

	float sum = 0;
	double random = dist(rd);
	// -------------------------- Verificar se a soma das probabilidades dos Delta de Dirac é 1 -----------------------------
	for (FDiracDelta dd : arr) {
		if (dd.prob < 0)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Probabilities can't be negative."));
		sum += dd.prob;
	}

	if (sum != 1) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ERROR: Sum of Dirac Delta's probabilities must be 1. Current sum is: %f"), sum));
		return 0;
	}
	// ----------------------------------------------------------------------------------------------------------------------
	sum = 0;
	for (FDiracDelta dd : arr) {
		if (dd.prob + sum > random)
			return dd.x;
		sum += dd.prob;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Unexpected error."));
	return 0;
}

float UProbabilityMethods::exponentialProbabilityNumber(float a, float b) {

	if (b <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Invalid argument."));
		return 0;
	}

	return a - b * log(dist(rd));
}

float UProbabilityMethods::normalProbabilityNumber(float miu, float sigma) {

	if (sigma <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Sigma must be > 0"));
		return 0;
	}

	float p1, p2, p;
	do {
		p1 = uniformProbabilityNumber(-1.0f, 1.0f);
		p2 = uniformProbabilityNumber(-1.0f, 1.0f);
		p = p1 * p1 + p2 * p2;
	} while (p >= 1);

	return  miu + sigma * p1 * sqrt(-2. * log(p) / p);
}

float UProbabilityMethods::normalMultipleProbabilityNumber(TArray<FMiuSigma> arr) {

	int chosenDistribution = uniformProbabilityNumber(0, arr.Num());

	return normalProbabilityNumber(arr[chosenDistribution].miu, arr[chosenDistribution].sigma);
}

float UProbabilityMethods::rayleighProbabilityNumber(float a, float b) {

	if (b <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Invalid argument."));
		return 0;
	}

	return  a + b * sqrt(-log(dist(rd)));
}


