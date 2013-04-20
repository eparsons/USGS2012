#ifndef PATCHCOLLECTION_H
#define PATCHCOLLECTION_H

#include <QVector>
#include <QHash>
#include "configuration.h"
#include "hydrofiledict.h"
#include "grid.h"
#include "utility.h"

/**
 * @brief The PatchCollection class provides all patch related data in public QVectors.
 *  Each vector holds the data for one type of value for all patches.  This is done for
 *  data locality and to pave way for future SIMD parallel operations.
 */
class PatchCollection {
    public:
        /**
         * @brief PatchCollection Default constructor
         */
        PatchCollection() {}

        /**
         * @brief PatchCollection Copy Constructor
         * @param other PatchCollection to copy
         */
        PatchCollection(const PatchCollection & other);

        /**
         * @brief operator= Assignment operator
         * @param rhs PatchCollection to copy
         * @return Reference to this object
         */
        PatchCollection & operator=(const PatchCollection & rhs);

        /**
         * @brief Destructor
         */
        ~PatchCollection();



        /**
         * @brief Constructor that initializes all patches for the river
         * @param newConfig The config being used by the river.
         * @param hydroDict The collection of hydrofiles used in this simulation.
         */
        PatchCollection(const Configuration & newConfig, HydroFileDict & hydroDict);

        /**
         * @brief Provides an index to a patch given an x and y coordinate
         * @param x The x coordinate
         * @param y The y coordinate
         * @return A positive integer if the index exists, -1 otherwise.
         */
        int getIndex(int x, int y) const;

        /**
         * @brief Indicates whether or not a patch exists at the given coordinates
         * @param x The x coordinate
         * @param y The y coordinate
         * @return True if the patch exists, false otherwise
         */
        bool patchExists(int x, int y) const;

        /**
         * @brief Provides the number of patches
         * @return An int representing the size of the collection
         */
        int getSize() const;


        int * pxcor;             ///< the x_coordinate for the patch
        int * pycor;             ///< the y_coordinate for the patch
        float * flowX;          ///< flow vector in the x_direction for hydraulics
        float * flowY;          ///< flow vector in the y_direction for hydraulics
        float * flowMagnitude;  ///< the rate of flow for hydraulics
        float * depth;          ///< depth of the water
        bool * hasWater;         ///< indicates whether or not the patch has water

        int * pcolor;

        int * aqa_point;        ///< biomass estimates of macro from USGS

        float * waterdecomp_doc_prey_limitation;       ///< NOT AVAILABLE
        float * waterdecomp_poc_prey_limitation;       ///< NOT AVAILABLE
        float * peri_doc_prey_limitation;              ///< NOT AVAILABLE
        float * peri_poc_prey_limitation;              ///< NOT AVAILABLE
        float * seddecomp_detritus_prey_limitation;    ///< NOT AVAILABLE
        float * herbivore_phyto_prey_limitation;       ///< NOT AVAILABLE
        float * herbivore_waterdecomp_prey_limitation; ///< NOT AVAILABLE
        float * herbivore_peri_prey_limitation;        ///< NOT AVAILABLE
        float * sedconsumer_seddecomp_prey_limitation; ///< NOT AVAILABLE
        float * sedconsumer_peri_prey_limitation;      ///< NOT AVAILABLE
        float * sedconsumer_detritus_prey_limitation;  ///< NOT AVAILABLE
        float * consumer_herbivore_prey_limitation;      ///< NOT AVAILABLE
        float * consumer_sedconsumer_prey_limitation;    ///< NOT AVAILABLE

        float * peri_space_limitation;           ///< NOT AVAILABLE
        float * waterdecomp_space_limitation;    ///< NOT AVAILABLE
        float * seddecomp_space_limitation;      ///< NOT AVAILABLE
        float * herbivore_space_limitation;      ///< NOT AVAILABLE
        float * sedconsumer_space_limitation;    ///< NOT AVAILABLE
        float * consumer_space_limitation;         ///< NOT AVAILABLE

        float * assimilation;                       ///< NOT AVAILABLE
        float * detritus;                           ///< NOT AVAILABLE
        float * DOC;                                ///< NOT AVAILABLE
        float * POC;                                ///< NOT AVAILABLE
        float * waterdecomp;                        ///< NOT AVAILABLE
        float * seddecomp;                          ///< NOT AVAILABLE
        float * macro;                              ///< NOT AVAILABLE
        float * phyto;                              ///< NOT AVAILABLE
        float * herbivore;                          ///< NOT AVAILABLE
        float * sedconsumer;                        ///< NOT AVAILABLE
        float * peri;                               ///< NOT AVAILABLE
        float * consumer;                           ///< consumers in the water column, such as fish
        float * bottom_light;                    ///< par that reaches the bottom of the river

        float * consumer_consumption;              ///< NOT AVAILABLE
        float * consumer_ingest_herbivore;         ///< NOT AVAILABLE
        float * consumer_pred_herbivore;           ///< NOT AVAILABLE
        float * consumer_ingest_sedconsumer;       ///< NOT AVAILABLE
        float * consumer_pred_sedconsumer;         ///< NOT AVAILABLE
        float * consumer_excretion;                ///< NOT AVAILABLE
        float * consumer_sda;                      ///< NOT AVAILABLE
        float * consumer_senescence;               ///< NOT AVAILABLE
        float * consumer_respiration;              ///< NOT AVAILABLE
        float * consumer_growth;                   ///< NOT AVAILABLE
        float * detritus_growth;                 ///< NOT AVAILABLE
        float * detritus_POC_transfer;           ///< the amount of carbon that transfers from detritus to POC
        float * seddecomp_pred_detritus;         ///< NOT AVAILABLE
        float * sedconsumer_pred_detritus;       ///< NOT AVAILABLE
        float * direction;                       ///< the direction carbon flows
        float * DOC_growth;                      ///< NOT AVAILABLE
        float * DOC_pred;                        ///< NOT AVAILABLE
        float * egestion;                        ///< NOT AVAILABLE
        float * excretion;                       ///< NOT AVAILABLE
        float * excretion_phyto;                 ///< NOT AVAILABLE
        float * flocculation;                    ///< the act of DOC sticking together to create POC
        float * gross_photo;                     ///< NOT AVAILABLE
        float * gross_photo_macro;               ///< photosynthesis of macrophytes
        float * gross_photo_phyto;               ///< photosythesis of phytoplankton
        float * growth_herbivore;                ///< NOT AVAILABLE
        float * growth_detritus;                 ///< NOT AVAILABLE
        float * growth_macro;                    ///< amount of biomass macro gains
        float * growth_sedconsumer;              ///< NOT AVAILABLE
        float * growth_phyto;                    ///< NOT AVAILABLE
        float * growth_waterdecomp;              ///< NOT AVAILABLE
        float * herbivore_consumption;           ///< NOT AVAILABLE
        float * herbivore_ingest_peri;           ///< NOT AVAILABLE
        float * herbivore_pred_peri;             ///< NOT AVAILABLE
        float * herbivore_ingest_phyto;          ///< NOT AVAILABLE
        float * herbivore_pred_phyto;            ///< amount of biomass herbivore "consume" from phyto
        float * herbivore_ingest_waterdecomp;    ///< NOT AVAILABLE
        float * herbivore_pred_waterdecomp;      ///< NOT AVAILABLE
        float * herbivore_excretion;             ///< NOT AVAILABLE
        float * herbivore_sda;                   ///< NOT AVAILABLE
        float * herbivore_senescence;            ///< NOT AVAILABLE
        float * herbivore_respiration;           ///< NOT AVAILABLE
        float * herbivore_growth;                ///< NOT AVAILABLE
        float * K;                               ///< carrying capacity
        float * large_death;                     ///< death of large_sized trophic groups
        float * light;                           ///< NOT AVAILABLE
        float * light_k;                         ///< attenuation coefficient of phytoplankon
        float * macro_death;                     ///< NOT AVAILABLE
        float * macro_exudation;                 ///< amount of photosynthetic material released
        float * micro_death;                     ///< amount of dead plant material that becomes DOC
        float * phyto_maximum_growth_rate;       ///< NOT AVAILABLE
        float * phyto_pred;                      ///< NOT AVAILABLE
        float * POC_detritus_transfer;           ///< the amount of carbon that transfers from detritus to POC
        float * POC_growth;                      ///< NOT AVAILABLE
        float * POC_pred;                        ///< NOT AVAILABLE
        float * phyto_density;                   ///< NOT AVAILABLE
        float * peri_ingest_doc;                 ///< NOT AVAILABLE
        float * peri_pred_doc;                   ///< NOT AVAILABLE
        float * peri_ingest_poc;                 ///< NOT AVAILABLE
        float * peri_pred_poc;                   ///< NOT AVAILABLE
        float * peri_respiration;                ///< NOT AVAILABLE
        float * peri_excretion;                  ///< NOT AVAILABLE
        float * peri_senescence;                 ///< NOT AVAILABLE
        float * senescence;                      ///< death
        float * scouring;                        ///< NOT AVAILABLE
        float * small_death;                     ///< amount of dead plant material that becomes POC
        float * respiration;                     ///< NOT AVAILABLE
        float * respiration_macro;               ///< hourly macrophyte respiration
        float * respiration_phyto;               ///< NOT AVAILABLE
        float * scouring_macro;                  ///< NOT AVAILABLE
        float * sedconsumer_ingest_peri;         ///< NOT AVAILABLE
        float * sedconsumer_pred_peri;           ///< NOT AVAILABLE
        float * senescence_macro;                ///< hourly macrophyte death
        float * senescence_phyto;                ///< NOT AVAILABLE
        float * sedconsumer_consumption;         ///< NOT AVAILABLE
        float * sedconsumer_ingest_detritus;     ///< NOT AVAILABLE
        float * sedconsumer_ingest_seddecomp;    ///< NOT AVAILABLE
        float * sedconsumer_pred_seddecomp;      ///< NOT AVAILABLE
        float * sedconsumer_excretion;           ///< NOT AVAILABLE
        float * sedconsumer_egestion;            ///< NOT AVAILABLE
        float * sedconsumer_senescence;          ///< NOT AVAILABLE
        float * sedconsumer_respiration;         ///< NOT AVAILABLE
        float * sedconsumer_growth;              ///< NOT AVAILABLE
        float * seddecomp_consumption;           ///< NOT AVAILABLE
        float * seddecomp_ingest_detritus;       ///< NOT AVAILABLE
        float * seddecomp_excretion;             ///< NOT AVAILABLE
        float * seddecomp_growth;                ///< NOT AVAILABLE
        float * seddcomp_ingest_peri;            ///< NOT AVAILABLE
        float * seddecomp_pred_peri;             ///< NOT AVAILABLE
        float * seddecomp_respiration;           ///< NOT AVAILABLE
        float * seddecomp_senescence;            ///< NOT AVAILABLE
        float * velpoc;                          ///< velocity used for poc_to_detritus transfer equation
        float * waterdecomp_consumption;         ///< NOT AVAILABLE
        float * waterdecomp_ingest_doc;          ///< NOT AVAILABLE
        float * waterdecomp_sda;                 ///< NOT AVAILABLE
        float * waterdecomp_excretion;           ///< NOT AVAILABLE
        float * waterdecomp_ingest_poc;          ///< NOT AVAILABLE
        float * waterdecomp_pred_doc;            ///< NOT AVAILABLE
        float * waterdecomp_pred_poc;            ///< NOT AVAILABLE
        float * waterdecomp_respiration;         ///< NOT AVAILABLE
        float * waterdecomp_senescence;          ///< NOT AVAILABLE
        float * turbidity;                       ///< metric of suspended solids in water column


    private:
        /**
         * @brief Creates a new patch by adding default values to the appropriate QVectors
         * @return The index of the new patch in the QVectors
         */
        void initializePatches(Configuration & config, int newSize);

        /**
         * @brief Provides a key to use with the index map given an x and y coordinate
         * @param x The x coordinate
         * @param y The y coordinate
         * @return The key for the indexMap
         */
        int getIndexMapKey(int x, int y) const;

        int size;
        int width;
        int height;
        QHash<int,int> indexMap;
        Configuration config;

        /**
         * @brief copy Copy helper
         * @param other Other PatchCollection to copy
         */
        void copy(const PatchCollection & other);

        /**
         * @brief Clears the object's memory
         */
        void clear();
};

#endif // PATCHCOLLECTION_H
