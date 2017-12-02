#ifndef _ML_BUILDER_H_
#define _ML_BUILDER_H_

#include <lcthw/bstrlib.h>

// Measurelook Builder
typedef struct MLBuilder MLBuilder;

struct MLBuilder {
	bstring meta;
	bstring constantParams;
	bstring changedParams;
	bstring measuredParams;
	bstring measures;
	bstring version;
};

typedef struct MLMeasure MLMeasure;

struct MLMeasure {
	bstring measureKey;
	int passId;
	bstring raw;
	bstring dataString;
};

MLBuilder *mlb_create(const char *version);
void mlb_destroy(MLBuilder *mlBuilder);

void mlb_addMetaString(MLBuilder *mlBuilder, const char *key, const char *value);
void mlb_addMetaValue(MLBuilder *mlBuilder, const char *key, bstring value);
void mlb_addConstantParam(MLBuilder *mlBuilder, const char *name, const char *units, bstring value);
void mlb_addChangedParam(MLBuilder *mlBuilder, const char *name, const char *units);
void mlb_addDirectMeasuredParam(MLBuilder *mlBuilder, const char *name, const char *units);
void mlb_addIndirectMeasuredParam(MLBuilder *mlBuilder, const char *name, const char *units, const char *arr);
void mlb_addMeasure(MLBuilder *mlBuilder, MLMeasure *mlMeasure);

bstring mlb_build(MLBuilder *mlBuilder);

#define i_bformat(num) bformat("%d",(num))
#define d_bformat(num) bformat("%f",(num))

MLMeasure *mlm_create(const char *measureKey, int passId);
void mlm_destroy(MLMeasure *mlMeasure);

void mlm_addEntry(MLMeasure *mlMeasure, const char *name, bstring value);

bstring mlm_build(MLMeasure *mlMeasure);

#endif