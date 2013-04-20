#include "carbonflowmap.h"

#include <iostream>
using std::cout;
using std::endl;
using std::swap;

CarbonFlowMap::CarbonFlowMap() {

}

CarbonFlowMap::CarbonFlowMap(HydroFile * newHydroFile, int numIterations) {
    hydroFile = newHydroFile;
    iterations = numIterations;

    Grid<CarbonSourceCollection> * source = new Grid<CarbonSourceCollection>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    Grid<CarbonSourceCollection> * dest = new Grid<CarbonSourceCollection>(hydroFile->getMapWidth(), hydroFile->getMapHeight());

    //We initialize dest because it will become the source after the swap in for loop.
    initializeCarbonCollection(*dest);

    for(int i = 0; i < iterations; i++){
        swap(source, dest);
        //We need a blank destination grid
        for(unsigned int i = 0; i < dest->getArraySize(); i++){
            (*dest)(i) = CarbonSourceCollection();
        }
        pushCarbon(*source, *dest);
    }

    /*
     * TODO: After pushing the carbon, store it all efficicently and
     * get rid of temp data.
     */

    delete source;

    int totalSources = 0;
    for(unsigned int x = 0; x < dest->getWidth(); x++) {
        for(unsigned int y = 0; y < dest->getHeight(); y++) {
            if(hydroFile->patchExists(x,y)){
                (*dest)(x,y).trim(0.0001);
                totalSources += (*dest)(x,y).getSources()->size();
            }
        }
    }

    sourceData.totalSources = totalSources;
    sourceData.sizes = new Grid<int>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    sourceData.offsets = new Grid<int>(hydroFile->getMapWidth(), hydroFile->getMapHeight());
    sourceData.x = new int[totalSources];
    sourceData.y = new int[totalSources];
    sourceData.amount = new float[totalSources];



    int currOffset = 0;
    for(unsigned int x = 0; x < dest->getWidth(); x++) {
        for(unsigned int y = 0; y < dest->getHeight(); y++) {
            if(hydroFile->patchExists(x,y)){

                const QVector<CarbonSource> * sources = (*dest)(x,y).getSources();

                (*sourceData.offsets)(x,y) = currOffset;
                (*sourceData.sizes)(x,y) = sources->size();
                for(int i = 0; i < sources->size(); i++) {
                    CarbonSource source = (*sources)[i];
                    sourceData.x[currOffset + i] = source.x;
                    sourceData.y[currOffset + i] = source.y;
                    sourceData.amount[currOffset + i] = source.amount;
                }
                currOffset += sources->size();
            }
        }
    }

    delete dest;
}




const SourceArrays CarbonFlowMap::getSourceArrays() const {
    return sourceData;
}

void CarbonFlowMap::initializeCarbonCollection(Grid<CarbonSourceCollection> & sources){
    for(int i = 0; i < hydroFile->getMapWidth(); i++){
        for( int j = 0; j < hydroFile->getMapHeight(); j++){
            sources(i,j) = CarbonSourceCollection(i,j);
        }
    }
}

void CarbonFlowMap::pushCarbon(
    Grid<CarbonSourceCollection> & source,
    Grid<CarbonSourceCollection> & dest)
{

    for( int x = 0; x < hydroFile->getMapWidth(); x++) {
        for( int y = 0; y < hydroFile->getMapHeight(); y++) {
            if(hydroFile->patchExists(x,y)) {
                QVector<CarbonSource> * targets = getFlowTargets(x,y);
                float carbonPushedToOtherWaterPatches = 0.0;

                for(int i = 0; i < targets->size(); i++){
                    CarbonSource carbonTarget = (*targets)[i];
                    carbonPushedToOtherWaterPatches += carbonTarget.amount;
                    QVector<CarbonSource> carbonPushed = source(x,y).getSourcesPercentage(carbonTarget.amount);
                    dest(carbonTarget.x, carbonTarget.y).addSources(carbonPushed);
                }
                float percentStationaryCarbon = 1.0 - carbonPushedToOtherWaterPatches;
                dest(x,y).addSources( source(x,y).getSourcesPercentage(percentStationaryCarbon) );
                //TODO: Avoid new and deleting over and over...
                delete targets;
            }
        }
    }
}

QVector<CarbonSource> * CarbonFlowMap::getFlowTargets(int i, int j){
    QVector<CarbonSource> * targets = new QVector<CarbonSource>();
    QVector2D flowVector = hydroFile->getVector(i,j);

    int x = i * PATCH_LENGTH;
    int y = j * PATCH_LENGTH;

    //One cell can flow into at most four others
    //Percents are calculated by target's area over area of a cell
    float newX = x + flowVector.x() * 60;
    float newY = y + flowVector.y() * 60;

    /**
     * Note: HydroFiles have 0,0 in the bottom left
     *  _______
     * |   |   |
     * | C | D |
     * |___|___|
     * |   |   |
     * | A | B |
     * |___|___|
     *
     * i,j = Patch coordinates
     * x,y = meters from origin
     *
     */
    //Target Coordinates (unused commented out)
    int iA = floor(newX/((float)PATCH_LENGTH));
    int jA = floor(newY/((float)PATCH_LENGTH));
    //float xA = iA * PATCH_LENGTH;
    //float yA = jA * PATCH_LENGTH;

    int iB = iA + 1;
    int jB = jA;
    float xB = iB * PATCH_LENGTH;
    //float yB = jB * PATCH_LENGTH;

    int iC = iA;
    int jC = jA + 1;
    //float xC = iC * PATCH_LENGTH;
    float yC = jC * PATCH_LENGTH;

    int iD = iA + 1;
    int jD = jA + 1;
    float xD = iD * PATCH_LENGTH;
    float yD = jD * PATCH_LENGTH;

    //We need to find what percentage of water flowed to A,B,C and D

    //Target A
    if(hydroFile->patchExists(iA, jA)) {
        float targetWidthA = xB - newX;
        float targetHeightA = yC - newY;
        float targetAreaA = targetWidthA*targetHeightA;
        float percentA = targetAreaA/PATCH_AREA;
        CarbonSource targetA(iA, jA, percentA);
        targets->append(targetA);
    }

    //Target B
    if(hydroFile->patchExists(iB, jB)) {
        float targetWidthB = (newX+PATCH_LENGTH) - xB;
        float targetHeightB = yD - newY;
        float targetAreaB = targetWidthB*targetHeightB;
        float percentB = targetAreaB/PATCH_AREA;
        CarbonSource targetB(iB, jB, percentB);
        targets->append(targetB);
    }

    //Target C
    if(hydroFile->patchExists(iC, jC)) {
        float targetWidthC = xD-newX;
        float targetHeightC = (newY+PATCH_LENGTH) - yC;
        float targetAreaC = targetWidthC*targetHeightC;
        float percentC = targetAreaC/PATCH_AREA;
        CarbonSource targetC(iC, jC, percentC);
        targets->append(targetC);
    }

    //Target D
    if(hydroFile->patchExists(iD, jD)) {
        float targetWidthD = (newX+PATCH_LENGTH) - xD;
        float targetHeightD = (newY+PATCH_LENGTH) - yD;
        float targetAreaD = targetWidthD*targetHeightD;
        float percentD = targetAreaD/PATCH_AREA;
        CarbonSource targetD(iD, jD, percentD);
        targets->append(targetD);
    }

    return targets;
}

void CarbonFlowMap::printDebug(){
    //Debugging info
    for(unsigned int x = 0; x < sourceData.offsets->getWidth(); x++){
        for(unsigned int y = 0; y < sourceData.offsets->getHeight(); y++) {
            int currOffset = (*sourceData.offsets)(x,y);
            int numSources = (*sourceData.sizes)(x,y);
            for(int i = 0; i < numSources; i++) {

                cout << "(" << x << "," << y << ") receives ";
                cout << sourceData.amount[currOffset] * 100.0 << "% from (";
                cout << sourceData.x[currOffset] << "," << sourceData.y[currOffset] << ")" << endl;

            }
        }
    }
}
