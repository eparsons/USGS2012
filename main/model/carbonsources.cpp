#include "carbonsources.h"

CarbonSourceCollection::CarbonSourceCollection() {

}

CarbonSourceCollection::CarbonSourceCollection(int newX, int newY) {
    initializeCollection(newX,newY);
}


void CarbonSourceCollection::initializeCollection(int newX, int newY) {
    sources.clear();
    addSource( newX, newY, 1.0);
}

void CarbonSourceCollection::addSource(int x, int y, float amount) {
    for( int i = 0; i < sources.size(); i++ ) {
        if( sources[i].x == x && sources[i].y == y ) {
            sources[i].amount += amount;
            return;
        }
    }

    //Source not already in the collection
    CarbonSource newSource( x, y, amount );
    sources.append( newSource );
}

void CarbonSourceCollection::addSource( const CarbonSource & newSource ) {
    addSource( newSource.x, newSource.y, newSource.amount );
}

void CarbonSourceCollection::addSources( const QVector<CarbonSource> & newSources ) {
    for( int i = 0; i < newSources.size(); i++ ) {
        addSource( newSources[i] );
    }
}

void CarbonSourceCollection::addSources( const CarbonSourceCollection & newCollection ) {
    addSources(newCollection.sources);
}

void CarbonSourceCollection::removeSourcesPercent( float percent ) {
    for( int i = 0; i < sources.size(); i++) {
        sources[i].amount *= (1.0 - percent);
    }
}

const QVector<CarbonSource> * CarbonSourceCollection::getSources() const {
    return &sources;
}

const QVector<CarbonSource> CarbonSourceCollection::getSourcesPercentage(float percent) const {
    QVector<CarbonSource> pctSources;
    pctSources.resize(sources.size());
    for( int i = 0; i < sources.size(); i++ ) {
        pctSources[i].x = sources[i].x;
        pctSources[i].y = sources[i].y;
        pctSources[i].amount = sources[i].amount * percent;
    }
    return pctSources;
}

void CarbonSourceCollection::trim(float percent) {
    QVector<CarbonSource> newSources;
    for( int i = 0; i < sources.size(); i++) {
        if(sources[i].amount > percent) {
            newSources.push_back(sources[i]);
        }
    }
    sources = newSources;
}
