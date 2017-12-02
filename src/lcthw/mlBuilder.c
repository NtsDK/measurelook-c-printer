#include <dbg.h>
#include <lcthw/mlBuilder.h>
#include <stdlib.h>
//#include <macro.h>


//static struct tagbstring quotes = bsStatic ("\"");
//static struct tagbstring quotes = bsStatic ("\"");

MLBuilder *mlb_create(const char *version){
	check_mem(version)
	
	MLBuilder *mlBuilder = calloc(1, sizeof(MLBuilder));
	check_mem(mlBuilder);
	
	mlBuilder->meta = bfromcstr ("");
	check_mem(mlBuilder->meta);
	mlBuilder->constantParams = bfromcstr ("");
	check_mem(mlBuilder->constantParams);
	mlBuilder->changedParams = bfromcstr ("");
	check_mem(mlBuilder->changedParams);
	mlBuilder->measuredParams = bfromcstr ("");
	check_mem(mlBuilder->measuredParams);
	mlBuilder->measures = bfromcstr ("");
	check_mem(mlBuilder->measures);
	mlBuilder->version = bfromcstr (version);
	check_mem(mlBuilder->version);
	
	return mlBuilder;
error:
	if(mlBuilder) {
		mlb_destroy(mlBuilder);
	}

	return NULL;
}

void mlb_addMetaString(MLBuilder *mlBuilder, const char *key, const char *value){
	if(blength(mlBuilder->meta) != 0){
		bconchar (mlBuilder->meta, ',');
	}
	bstring item = bformat ("\"%s\":\"%s\"", key, value);
	//debug("%s", bdata(item));
	int ret = bconcat (mlBuilder->meta, item);
	bdestroy(item);
	//debug("%s", bdata(mlBuilder->meta));
}

void mlb_addMetaValue(MLBuilder *mlBuilder, const char *key, bstring value){
	if(blength(mlBuilder->meta) != 0){
		bconchar (mlBuilder->meta, ',');
	}
	bstring item = bformat ("\"%s\":%s", key, bdata(value));
	bdestroy(value);
	int ret = bconcat (mlBuilder->meta, item);
	bdestroy(item);
}

void mlb_addConstantParam(MLBuilder *mlBuilder, const char *name, const char *units, bstring value){
	if(blength(mlBuilder->constantParams) != 0){
		bconchar(mlBuilder->constantParams, ',');
	}
	bstring item = bformat ("{\"name\":\"%s\",\"units\":\"%s\",\"value\":%s}", name, units, bdata(value));
	bdestroy(value);
	int ret = bconcat (mlBuilder->constantParams, item);
	bdestroy(item);
}

void mlb_addChangedParam(MLBuilder *mlBuilder, const char *name, const char *units){
	if(blength(mlBuilder->changedParams) != 0){
		bconchar(mlBuilder->changedParams, ',');
	}
	bstring item = bformat ("{\"name\":\"%s\",\"units\":\"%s\"}", name, units);
	int ret = bconcat (mlBuilder->changedParams, item);
	bdestroy(item);
}

void mlb_addDirectMeasuredParam(MLBuilder *mlBuilder, const char *name, const char *units){
	if(blength(mlBuilder->measuredParams) != 0){
		bconchar(mlBuilder->measuredParams, ',');
	}
	bstring item = bformat ("{\"name\":\"%s\",\"units\":\"%s\", \"type\":\"direct\"}", name, units);
	int ret = bconcat (mlBuilder->measuredParams, item);
	bdestroy(item);
}

void mlb_addIndirectMeasuredParam(MLBuilder *mlBuilder, const char *name, const char *units, const char *arr){
	if(blength(mlBuilder->measuredParams) != 0){
		bconchar(mlBuilder->measuredParams, ',');
	}
	bstring item = bformat ("{\"name\":\"%s\",\"units\":\"%s\", \"type\":\"indirect\", \"sumOf\":%s}", name, units, arr);
	int ret = bconcat (mlBuilder->measuredParams, item);
	bdestroy(item);
}

void mlb_addMeasure(MLBuilder *mlBuilder, MLMeasure *mlMeasure){
	if(blength(mlBuilder->measures) != 0){
		bconchar(mlBuilder->measures, ',');
	}
	bstring item = mlm_build(mlMeasure);
	int ret = bconcat (mlBuilder->measures, item);
	bdestroy(item);
}

bstring mlb_build(MLBuilder *mlBuilder){
	return bformat ("{ \
		\"meta\": {%s}, \
		\"constantParams\": [%s], \
		\"changedParams\": [%s], \
		\"measuredParams\": [%s], \
		\"measures\": {%s}, \
		\"version\": \"%s\" \
		}", mlBuilder->meta->data, 
				mlBuilder->constantParams->data,
				mlBuilder->changedParams->data,
				mlBuilder->measuredParams->data,
				mlBuilder->measures->data,
				mlBuilder->version->data);
}
		
void mlb_destroy(MLBuilder *mlBuilder){
	if(mlBuilder){
		if(mlBuilder->meta){
			bdestroy(mlBuilder->meta);
		}
		if(mlBuilder->constantParams){
			bdestroy(mlBuilder->constantParams);
		}
		if(mlBuilder->changedParams){
			bdestroy(mlBuilder->changedParams);
		}
		if(mlBuilder->measuredParams){
			bdestroy(mlBuilder->measuredParams);
		}
		if(mlBuilder->measures){
			bdestroy(mlBuilder->measures);
		}
		if(mlBuilder->version){
			bdestroy(mlBuilder->version);
		}
		free(mlBuilder);
	}
}


MLMeasure *mlm_create(const char *measureKey, int passId){
	check_mem(measureKey)
	
	MLMeasure *mlMeasure = calloc(1, sizeof(MLMeasure));
	check_mem(mlMeasure);
	
	mlMeasure->measureKey = bfromcstr (measureKey);
	check_mem(mlMeasure->measureKey);
	mlMeasure->passId = passId;
	mlMeasure->raw = bfromcstr ("");
	check_mem(mlMeasure->raw);
	mlMeasure->dataString = bfromcstr ("");
	check_mem(mlMeasure->dataString);
	
	return mlMeasure;
error:
	if(mlMeasure) {
		mlm_destroy(mlMeasure);
	}

	return NULL;
}

void mlm_addEntry(MLMeasure *mlMeasure, const char *name, bstring value){
	bconchar(mlMeasure->dataString, ',');
	bstring item = bformat ("\"%s\":%s", name, bdata(value));
	bdestroy(value);
	int ret = bconcat (mlMeasure->dataString, item);
	bdestroy(item);
}

bstring mlm_build(MLMeasure *mlMeasure){
	return bformat ("\"%s\" : {\
	\"measureKey\":\"%s\",\
	\"raw\": {%s}, \
	\"passId\": %d \
	%s}", mlMeasure->measureKey->data, 
				mlMeasure->measureKey->data, 
				mlMeasure->raw->data, 
				mlMeasure->passId, 
				mlMeasure->dataString->data);
}
		
void mlm_destroy(MLMeasure *mlMeasure){
	if(mlMeasure){
		if(mlMeasure->measureKey){
			bdestroy(mlMeasure->measureKey);
		}
		if(mlMeasure->raw){
			bdestroy(mlMeasure->raw);
		}
		if(mlMeasure->dataString){
			bdestroy(mlMeasure->dataString);
		}
		free(mlMeasure);
	}
}