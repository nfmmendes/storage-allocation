#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "TSP.h"
#include "DistanceMatrix.h"
using std::set;

TSP::TSP() {}

TSP::TSP(const DistanceMatrix<Vertex>* distanceMatrix)
{
    this->distanceMatrix = distanceMatrix;
    this->distanceMatrixSet = true;
}

pair<double, vector<Vertex> > TSP::bruteForceTSP(const vector<Vertex>& points,
    VertexVertexMap& bestStart,
    VertexVertexMap& bestEnd)
{

    vector<Vertex> currentOrder = points;
    vector<Vertex> solution = points;
    double bestCost = std::numeric_limits<double>::max();
    auto orderSize {currentOrder.size()};

    do {
        double sum = 0.0;
        for (int i = 1; sum <= bestCost && i < orderSize; i++) {
            sum += distanceMatrix->getDistance(currentOrder[i - 1], currentOrder[i]);
        }

        sum += distanceMatrix->getDistance(bestStart[currentOrder[0]], currentOrder[0]);
        sum += distanceMatrix->getDistance(currentOrder[orderSize - 1],
            bestEnd[currentOrder[orderSize - 1]]);

        if (sum < bestCost) {
            bestCost = sum;
            solution = currentOrder;
        }
    } while (std::next_permutation(currentOrder.begin(), currentOrder.end()));

    return make_pair(bestCost, solution);
}

pair<double, vector<Vertex> >
TSP::closestNeighborTSP(const vector<Vertex>& points,
    VertexVertexMap& bestStart,
    VertexVertexMap& bestEnd)
{

    vector<Vertex> solution;
    set<Vertex> remainingPoints;
    Vertex previousPoint;
    double sumCost = 0;

    double lowerDistance = 1e100;
    int bestVertexToInit = 0;
    double distance;

    for (auto i = 0; i < points.size(); i++) {
        distance = distanceMatrix->getDistance(bestStart[points[i]], points[i]);
        // find the closest point to a delivery point
        if (distance < lowerDistance) {
            lowerDistance = distance;
            bestVertexToInit = i;
        }

        remainingPoints.insert(points[i]);
    }

    sumCost = lowerDistance;
    solution.push_back(points[bestVertexToInit]);
    remainingPoints.erase(points[bestVertexToInit]);

    solution.push_back(points[0]);
    previousPoint = solution[0];

    while (!remainingPoints.empty()) {
        lowerDistance = 1e100;
        distance = 0;
        Vertex bestPoint;

        for (auto value : remainingPoints) {
            distance = distanceMatrix->getDistance(previousPoint, value);

            if (distance < lowerDistance) {
                lowerDistance = distance;
                bestPoint = value;
            }
        }

        sumCost += lowerDistance;
        solution.push_back(bestPoint);
        previousPoint = bestPoint;
        remainingPoints.erase(bestPoint);
    }

    sumCost += distanceMatrix->getDistance(previousPoint, bestEnd[previousPoint]);

    return make_pair(sumCost, solution);
}

pair<double, vector<Vertex> >
TSP::quickLocalSearchTSP(const vector<Vertex>& points, VertexVertexMap& bestStart,
    VertexVertexMap& bestEnd)
{
    pair<double, vector<Vertex> > currentOrder = closestNeighborTSP(points, bestStart, bestEnd);
    const auto& order { currentOrder.second };
    auto orderSize = order.size();

    for (int i = 1; i + 1 < orderSize; i++) {
        double costReduction = 0;
        int changingPoint = 0;

        for (int j = 1; j + 2 < orderSize; j++) {
            auto oldCost = distanceMatrix->getDistance(order[j - 1], order[j])
                + distanceMatrix->getDistance(order[j], order[j + 1])
                + distanceMatrix->getDistance(order[j + 1], order[j + 2]);

            auto newCost = distanceMatrix->getDistance(order[j - 1], order[j + 1])
                + distanceMatrix->getDistance(order[j + 1], order[j])
                + distanceMatrix->getDistance(order[j], order[j + 2]);

            if (newCost - oldCost < costReduction) {
                costReduction = newCost - oldCost;
                changingPoint = j;
                break;
            }
        }

        if (costReduction < 0) {
            currentOrder.first -= costReduction;
            auto elem = currentOrder.second[changingPoint + 1];
            currentOrder.second[changingPoint + 1] = currentOrder.second[changingPoint];
            currentOrder.second[changingPoint] = elem;
            i--;
        }
    }

    return currentOrder;
}