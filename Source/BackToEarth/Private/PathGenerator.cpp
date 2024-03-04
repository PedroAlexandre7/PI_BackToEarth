
#include "PathGenerator.h"

class PathMatrix {

private:

	vector<vector<bool>> matrix;
	int currLine;
	int currColumn;
	static const int FORWARD = 1, LEFT = 2, RIGHT = 3;

public:

	PathMatrix(int rows, int columns) {
		matrix = vector<vector<bool>>(rows, vector<bool>(columns, false)); // Initialize matrix with all elements false.
	}

	void generatePath(int leftMostStart, int rightMostStart,
		float left3Prob, float right3Prob, float left2Prob, float right2Prob) {

		if (leftMostStart < 0 || rightMostStart >= matrix.size() || leftMostStart > rightMostStart) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ERROR: Invalid start parameter(s)."));
			return;
		}

		TArray<FDiracDelta> list3 = { FDiracDelta{ FORWARD, 1 - left3Prob - right3Prob}, FDiracDelta{ LEFT, left3Prob }, FDiracDelta{ RIGHT, right3Prob } };
		TArray<FDiracDelta> list2Left = { FDiracDelta{FORWARD, 1 - left2Prob }, FDiracDelta { LEFT, left2Prob } };
		TArray<FDiracDelta> list2Right = { FDiracDelta{FORWARD, 1 - right2Prob }, FDiracDelta { RIGHT, right2Prob } };


		currLine = UProbabilityMethods::uniformProbabilityNumber(leftMostStart, rightMostStart + 1);
		currColumn = 0;
		select();

		if (matrix.size() == 1)
			for (int i = 1; i < matrix.at(0).size(); i++)
				move(FORWARD);

		while (currColumn != matrix.at(0).size() - 1) {
			if (currLine == 0)
				if (isSelected(currLine + 1, currColumn) || isSelected(currLine + 1, currColumn - 1))
					move(FORWARD);
				else
					move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list2Right));
			else if (currLine == matrix.size() - 1)
				if (isSelected(currLine - 1, currColumn) || isSelected(currLine - 1, currColumn - 1))
					move(FORWARD);
				else
					move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list2Left));
			else {
				if (isSelected(currLine + 1, currColumn))
					if (isSelected(currLine - 1, currColumn - 1))
						move(FORWARD);
					else
						move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list2Left));
				else if (isSelected(currLine - 1, currColumn))
					if (isSelected(currLine + 1, currColumn - 1))
						move(FORWARD);
					else
						move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list2Right));
				else if (isSelected(currLine - 1, currColumn - 1))
					move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list2Right));
				else if (isSelected(currLine + 1, currColumn - 1))
					move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list2Left));
				else
					move(UProbabilityMethods::empiricalDiscreteProbabilityNumber(list3));
			}

		}

	}

	TArray<bool> getPath() {
		TArray<bool> path = {};
		for (vector<bool> vec : matrix)
			for (bool b : vec)
				path.Add(b);
		return path;
	}

private:

	bool isWithinBounds(int line, int column) {
		return line >= 0 && line < matrix.size() && column >= 0 && column < matrix.at(0).size();
	}

	bool isSelected(int line, int column) {
		return !isWithinBounds(line, column) ? false : matrix.at(line).at(column);
	}

	void move(int direction) {
		switch (direction) {
		case FORWARD:
			currColumn++;
			break;
		case LEFT:
			currLine--;
			break;
		case RIGHT:
			currLine++;
			break;
		}
		select();
	}

	void select() {
		matrix.at(currLine).at(currColumn) = true;
	}
};

TArray<bool> UPathGenerator::generatePath(int rows, int columns, int leftMostStart, int rightMostStart,
	float left3Prob, float right3Prob, float left2Prob, float right2Prob) {

	PathMatrix matrix = PathMatrix(rows, columns);
	matrix.generatePath(leftMostStart, rightMostStart, left3Prob, right3Prob, left2Prob, right2Prob);
	return matrix.getPath();
}
